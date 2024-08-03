#pragma once
#include "Boomerang.h"
#include "ShakeClass.h"
#include <Audio.h>
#include <Sprite.h>
#include <TextureManager.h>
#include <WorldTransform.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

class GaugeClass {
public:
	GaugeClass();
	~GaugeClass();
	void Init();
	void Update();
	void Draw();
	void SetCamera(const WorldTransform* set) { cameraPos = set; }
	void SetPlayer(Boomerang* set) { boomerang = set; }

private:
	const WorldTransform* cameraPos;
	Boomerang* boomerang = nullptr;
	uint32_t backTexHandle;
	std::string backTexName = "./Resources/addTexture/gaugeBack.png";
	Sprite* backSprite = nullptr;
	uint32_t frontTexHandle;
	std::string frontTexName = "./Resources/addTexture/gauge.png";
	Sprite* frontSprite = nullptr;
	uint32_t textTexHandle;
	std::string textTex = "./Resources/addTexture/gaugeText.png";
	Sprite* textSprite = nullptr;
	uint32_t uiTexHandle;
	std::string uiTex = "./Resources/addTexture/ui.png";
	Sprite* uiSprite = nullptr;
	Vector2 pos = {835, 565};
	Vector2 currentPos;
	Vector2 currentPos2;
	Vector2 initSize;
	Vector2 initSize2;
	Vector2 initSize3;
	Vector2 scale = {1, 1};
	float raito;
	Vector2 currentSize;

	
};
