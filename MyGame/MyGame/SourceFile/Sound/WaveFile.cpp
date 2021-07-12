#include "stdafx.h"
#include "WaveFile.h"

WaveFile::WaveFile()
{

}

WaveFile::~WaveFile()
{
	Release();
}


bool WaveFile::Open(const wchar_t* fileName)
{
	//ファイルパスを代入
	m_filePath = fileName;
	m_filePathHash = Util::MakeHash(fileName);
	m_hmmio = mmioOpenW(const_cast<wchar_t*>(fileName), NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (m_hmmio == NULL)
	{
		//ファイルパスが間違っている可能性があります
		std::abort();
	}
	MMCKINFO ckIn;
	PCMWAVEFORMAT pcmWaveFormat;
	memset(&ckIn, 0, sizeof(ckIn));

	m_pwfx = NULL;

	if ((0 != mmioDescend(m_hmmio, &m_ckRiff, NULL, 0)))
	{
		//Failed mmioDescend
		std::abort();
	}
	if ((m_ckRiff.ckid != FOURCC_RIFF) ||
		(m_ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
	{
		//Failed mmioDescend
		std::abort();
	}
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK))
	{
		//Failed mmioDescend
		std::abort();
	}
	if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
	{
		//Failed mmioDescend
		std::abort();
	}
	if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat,
		sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
	{
		//Failed mmioRead
		std::abort();
	}
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
		m_pwfx->cbSize = 0;
	}
	else
	{
		// Read in length of extra bytes.
		WORD cbExtraBytes = 0L;
		if (mmioRead(m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD)) {
			//Failed mmioRead
			std::abort();
		}
		m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
		m_pwfx->cbSize = cbExtraBytes;

		// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
		if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(m_pwfx->cbSize)) + sizeof(WORD)),
			cbExtraBytes) != cbExtraBytes)
		{
			//Failed mmioRead
			std::abort();
		}
	}
	if (0 != mmioAscend(m_hmmio, &ckIn, 0))
	{
		//Failed mmioAscend
		std::abort();
	}
	ResetFile();
	m_dwSize = m_ck.cksize;
	return true;
}

void WaveFile::ResetFile()
{
	while (!m_isReadEnd) {}		//読み込み中にリセットはさせない
	if (m_hmmio == NULL)
	{
		return;
	}

	if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
		SEEK_SET)) {
		//Failed mmioSeek
		std::abort();
		return;
	}

	// Search the input file for the 'data' chunk.
	m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (0 != mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK)) {
		//Faild mmioDescend
		std::abort();
		return;
	}
}

void WaveFile::Read(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize)
{
	MMIOINFO mmioinfoIn;

	if (m_hmmio == NULL) {
		return;
	}
	if (pBuffer == NULL) {
		return;
	}

	if (0 != mmioGetInfo(m_hmmio, &mmioinfoIn, 0)) {
		//mmioGetInfo
		std::abort();
		return;
	}

	UINT cbDataIn = sizeToRead;
	if (cbDataIn > m_ck.cksize) {
		cbDataIn = m_ck.cksize;
	}
	*currentReadSize = cbDataIn;
	m_ck.cksize -= cbDataIn;

	for (DWORD cT = 0; cT < cbDataIn; cT++)
	{
		// Copy the bytes from the io to the buffer.
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (0 != mmioAdvance(m_hmmio, &mmioinfoIn, MMIO_READ)) {
				//mmioAdvance
				std::abort();
				return;
			}

			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) {
				//mmioinfoIn.pchNext
				std::abort();
				return;
			}
		}

		// Actual copy.
		*((BYTE*)pBuffer + cT) = *((BYTE*)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}
	m_isReadEnd = true;
	return;
}

void WaveFile::ReadAsync(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize)
{
	if (m_isInvokeReadAsyncThread) {
		m_readAsyncThread.join();
		m_isInvokeReadAsyncThread = false;
	}
	m_isReadEnd = false;

	//読み込みスレッドを立てる。
	m_readAsyncThread = std::thread([this, pBuffer, sizeToRead, currentReadSize] {
		this->Read(pBuffer, sizeToRead, currentReadSize);
	});
	m_isInvokeReadAsyncThread = true;
}

void WaveFile::Release()
{
	if (m_isInvokeReadAsyncThread) {
		m_readAsyncThread.join();
		m_isInvokeReadAsyncThread = false;
	}

	if (m_hmmio != NULL)
	{
		mmioClose(m_hmmio, 0);
		m_hmmio = NULL;
	}
	delete[] m_pwfx;
	m_pwfx = NULL;
}