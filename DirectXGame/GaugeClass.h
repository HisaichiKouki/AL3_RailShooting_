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
#include "HeartClass.h"
#include "PlayerBoomerang.h"
class GaugeClass {
public:
	GaugeClass();
	~GaugeClass();
	void Init();
	void Update();
	void Draw();
	void SetCamera(const WorldTransform* set) { cameraPos = set; }
	void SetPlayer(Boomerang* set) { boomerang = set; }
	void SetPlayer(PlayerBoomerang* set) { player = set; }

private:
	const WorldTransform* cameraPos;
	Boomerang* boomerang = nullptr;
	PlayerBoomerang* player = nullptr;
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
	uint32_t ui2TexHandle;
	std::string ui2Tex = "./Resources/addTexture/ui2.png";
	Sprite* ui2Sprite = nullptr;
	uint32_t ui3TexHandle;
	std::string ui3Tex = "./Resources/addTexture/ui3.png";
	Sprite* ui3Sprite = nullptr;
	Vector2 pos = {835, 565};
	Vector2 currentPos;
	Vector2 currentPos2;
	Vector2 initSize;
	Vector2 initSize2;
	Vector2 initSize3;
	Vector2 scale = {1, 1};
	float raito;
	Vector2 currentSize;
	HeartClass* heart[3] = {nullptr};
};
