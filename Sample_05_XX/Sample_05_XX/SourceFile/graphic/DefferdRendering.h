#pragma once

class DefferdRendering
{
public:
	DefferdRendering();
	~DefferdRendering();

	void CreateRT();
	void DrawRT();
private:
	static const int TexNum = 1;
	RenderTarget albedRT;
	SpriteInitData initData;
	Sprite defferdLightingSprite;
	std::vector<Model*> m_Casters;		//キャスターの配列

};

