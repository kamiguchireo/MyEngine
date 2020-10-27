/*!
*@brief	�p�b�h�B
*/
#include "stdafx.h"
#include "GamePad.h"
#include <limits.h>

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
std::array<GamePad*, GamePad::CONNECT_PAD_MAX> g_pad;

namespace {
	/*!
	*@brief	���z�{�^����XBox�R���g���[���̃{�^���Ƃ̊֘A�t����\���\���́B
	*/
	struct VirtualPadToXPad {
		EnButton vButton;		//!<���z�{�^���B
		DWORD	 xButton;		//!<XBox�R���g���[���̃{�^���B
	};
		
	const VirtualPadToXPad vPadToXPadTable[static_cast<int>(EnButton::enButtonNum)] = {
		{ EnButton::enButtonUp		, XINPUT_GAMEPAD_DPAD_UP },
		{ EnButton::enButtonDown		, XINPUT_GAMEPAD_DPAD_DOWN },
		{ EnButton::enButtonLeft		, XINPUT_GAMEPAD_DPAD_LEFT },
		{ EnButton::enButtonRight		, XINPUT_GAMEPAD_DPAD_RIGHT },
		{ EnButton::enButtonA			, XINPUT_GAMEPAD_A },
		{ EnButton::enButtonB			, XINPUT_GAMEPAD_B },
		{ EnButton::enButtonY			, XINPUT_GAMEPAD_Y },
		{ EnButton::enButtonX			, XINPUT_GAMEPAD_X },
		{ EnButton::enButtonSelect	, XINPUT_GAMEPAD_BACK },
		{ EnButton::enButtonStart		, XINPUT_GAMEPAD_START },
		{ EnButton::enButtonRB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
		{ EnButton::enButtonRB2		, 0 },
		{ EnButton::enButtonRB3		, XINPUT_GAMEPAD_RIGHT_THUMB },
		{ EnButton::enButtonLB1		, XINPUT_GAMEPAD_LEFT_SHOULDER },
		{ EnButton::enButtonLB2		, 0 },
		{ EnButton::enButtonLB3		, XINPUT_GAMEPAD_LEFT_THUMB },
	};
	/*!
	*@brief	���z�{�^���ƃL�[�{�[�h�Ƃ̊֘A�t����\���\���́B
	*/
	struct VirtualPadToKeyboard {
		EnButton vButton;		//!<���z�{�^��
		DWORD keyCoord1;		//!<�L�[�{�[�h�̃L�[�R�[�h�B
		DWORD keyCoord2;		//!<�L�[�{�[�h�̃L�[�R�[�h�B
	};
	const VirtualPadToKeyboard vPadToKeyboardTable[static_cast<int>(EnButton::enButtonNum)] = {
		{ EnButton::enButtonUp		, VK_NUMPAD8,	'8' 		},
		{ EnButton::enButtonDown		, VK_NUMPAD2,	'2' 		},
		{ EnButton::enButtonLeft		, VK_NUMPAD4,	'4' 		},
		{ EnButton::enButtonRight		, VK_NUMPAD6,	'6' 		},
		{ EnButton::enButtonA			, 'J',			0xFFFFFFFF	},
		{ EnButton::enButtonB			, 'K',			0xFFFFFFFF	},
		{ EnButton::enButtonY			, 'I',			0xFFFFFFFF	},
		{ EnButton::enButtonX			, 'L',			0xFFFFFFFF	},
		{ EnButton::enButtonSelect	, VK_SPACE,		0xFFFFFFFF	},
		{ EnButton::enButtonStart		, VK_RETURN,	0xFFFFFFFF	},
		{ EnButton::enButtonRB1		, '7',			0xFFFFFFFF	},
		{ EnButton::enButtonRB2		, '8',			0xFFFFFFFF	},
		{ EnButton::enButtonRB3		, '9',			0xFFFFFFFF	},
		{ EnButton::enButtonLB1		, 'B',			0xFFFFFFFF	},
		{ EnButton::enButtonLB2		, 'N',			0xFFFFFFFF	},
		{ EnButton::enButtonLB3		, 'M',			0xFFFFFFFF	},
	};
}
GamePad::EnXInputPadState GamePad::m_padStates[4] = { GamePad::EnXInputPadState::Undef };
GamePad::GamePad()
{
	memset(&m_state, 0, sizeof(m_state));
	memset(m_trigger, 0, sizeof(m_trigger));
	memset(m_press, 0, sizeof(m_press));
}
GamePad::~GamePad()
{
}
void GamePad::BeginFrame()
{
	//�S�Ė���`�ɂ���B
	for (auto& padState : m_padStates) {
		padState = EnXInputPadState::Undef;
	}
}
void GamePad::Update()
{
	//�A�N�e�B�u�p�b�h��T���B
	DWORD result = ERROR_DEVICE_NOT_CONNECTED;
	for (int i = m_padNo; i < MAX_PAD; i++) {
		if (m_padStates[i] == EnXInputPadState::Undef) {
			//���̃p�b�h�͖������B
			result = XInputGetState(i, &m_state.state);
			if (result == ERROR_SUCCESS) {
				//�ڑ��ł����B
				m_padStates[i] = EnXInputPadState::Connect;
				break;
			}
			else {
				//�q�����Ă��Ȃ��B
				//���̃p�b�h�𒲂ׂ�B
				m_padStates[i] = EnXInputPadState::Disconnect;
			}
		}
	}
		
	if (result == ERROR_SUCCESS) {
		//�ڑ�����Ă���B
		m_state.bConnected = true;
		for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable) {
			if (m_state.state.Gamepad.wButtons & vPadToXPad.xButton) {
				m_trigger[static_cast<int>(vPadToXPad.vButton)] = 1 ^ m_press[static_cast<int>(vPadToXPad.vButton)];
				m_press[static_cast<int>(vPadToXPad.vButton)] = 1;
			}
			else {
				m_trigger[static_cast<int>(vPadToXPad.vButton)] = 0;
				m_press[static_cast<int>(vPadToXPad.vButton)] = 0;
			}
		}
		//���g���K�[�B
		if (m_state.state.Gamepad.bLeftTrigger != 0) {
			m_trigger[static_cast<int>(EnButton::enButtonLB2)] = 1 ^ m_press[static_cast<int>(EnButton::enButtonLB2)];
			m_press[static_cast<int>(EnButton::enButtonLB2)] = 1;
		}
		else {
			m_trigger[static_cast<int>(EnButton::enButtonLB2)] = 0;
			m_press[static_cast<int>(EnButton::enButtonLB2)] = 0;
		}
		//�E�g���K�[
		if (m_state.state.Gamepad.bRightTrigger != 0) {
			m_trigger[static_cast<int>(EnButton::enButtonRB2)] = 1 ^ m_press[static_cast<int>(EnButton::enButtonRB2)];
			m_press[static_cast<int>(EnButton::enButtonRB2)] = 1;
		}
		else {
			m_trigger[static_cast<int>(EnButton::enButtonRB2)] = 0;
			m_press[static_cast<int>(EnButton::enButtonRB2)] = 0;
		}
		if ((m_state.state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbLY < INPUT_DEADZONE &&
				m_state.state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbLX = 0;
			m_state.state.Gamepad.sThumbLY = 0;
			m_lStickX = 0.0f;
			m_lStickY = 0.0f;
		}
		else {
			//���X�e�B�b�N�̓��͗ʁB
			if (m_state.state.Gamepad.sThumbLX > 0) {
				m_lStickX = static_cast<float>(m_state.state.Gamepad.sThumbLX) / SHRT_MAX;
			}
			else {
				m_lStickX = static_cast<float>(m_state.state.Gamepad.sThumbLX) / -SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbLY > 0) {
				m_lStickY = static_cast<float>(m_state.state.Gamepad.sThumbLY) / SHRT_MAX;
			}
			else {
				m_lStickY = static_cast<float>(m_state.state.Gamepad.sThumbLY) / -SHRT_MIN;
			}
		}

		if ((m_state.state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbRY < INPUT_DEADZONE &&
				m_state.state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbRX = 0;
			m_state.state.Gamepad.sThumbRY = 0;
			m_rStickX = 0.0f;
			m_rStickY = 0.0f;
		}
		else {
			//�E�X�e�B�b�N�̓��͗ʁB
			if (m_state.state.Gamepad.sThumbRX > 0) {
				m_rStickX = static_cast<float>(m_state.state.Gamepad.sThumbRX) / SHRT_MAX;
			}
			else {
				m_rStickX = static_cast<float>(m_state.state.Gamepad.sThumbRX) / -SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbRY > 0) {
				m_rStickY = static_cast<float>(m_state.state.Gamepad.sThumbRY) / SHRT_MAX;
			}
			else {
				m_rStickY = static_cast<float>(m_state.state.Gamepad.sThumbRY) / -SHRT_MIN;
			}
		}			
	}
	else {
		//�ڑ�����Ă��Ȃ��ꍇ�̓L�[�{�[�h�̓��͂ŃG�~�����[�g����B
		if (m_state.bConnected) {
			//���ڑ��ɂȂ����B
			memset(&m_state, 0, sizeof(m_state));
			memset(m_trigger, 0, sizeof(m_trigger));
			memset(m_press, 0, sizeof(m_press));
		}
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)) {
			m_rStickX = -1.0f;
		}else if (GetAsyncKeyState(VK_RIGHT)) {
			m_rStickX = 1.0f;
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_rStickY = 1.0f;
		}else if (GetAsyncKeyState(VK_DOWN)) {
			m_rStickY = -1.0f;
		}
		//�X�e�B�b�N�̓��͗ʂ𐳋K���B
		float t = fabsf(m_rStickX) + fabsf(m_rStickY);
		if (t > 0.0f) {
			m_rStickX /= t;
			m_rStickY /= t;
		}

		if (GetAsyncKeyState('A')) {
			m_lStickX = -1.0f;
		}
		else if (GetAsyncKeyState('D')) {
			m_lStickX = 1.0f;
		}
		if (GetAsyncKeyState('W')) {
			m_lStickY = 1.0f;
		}
		else if (GetAsyncKeyState('S')) {
			m_lStickY = -1.0f;
		}
		//�X�e�B�b�N�̓��͗ʂ𐳋K���B
		t = fabsf(m_lStickX) + fabsf(m_lStickY);
		if (t > 0.0f) {
			m_lStickX /= t;
			m_lStickY /= t;
		}

		for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable) {
			if (GetAsyncKeyState(vPadToKeyboard.keyCoord1)) {
				//�D�揇�ʂP�Ԗڂ̃L�[�B
				m_trigger[static_cast<int>(vPadToKeyboard.vButton)] = 1 ^ m_press[static_cast<int>(vPadToKeyboard.vButton)];
				m_press[static_cast<int>(vPadToKeyboard.vButton)] = 1;
			}
			else if (vPadToKeyboard.keyCoord2 != 0xFFFFFFFF
				&& GetAsyncKeyState(vPadToKeyboard.keyCoord2)) {
				//�D�揇�ʂQ�Ԗڂ̃L�[�B
				m_trigger[static_cast<int>(vPadToKeyboard.vButton)] = 1 ^ m_press[static_cast<int>(vPadToKeyboard.vButton)];
				m_press[static_cast<int>(vPadToKeyboard.vButton)] = 1;
			}
			else {
				m_trigger[static_cast<int>(vPadToKeyboard.vButton)] = 0;
				m_press[static_cast<int>(vPadToKeyboard.vButton)] = 0;
			}
		}
	}
}

