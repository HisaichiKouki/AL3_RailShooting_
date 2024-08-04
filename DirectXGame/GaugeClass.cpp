#include "GaugeClass.h"

GaugeClass::GaugeClass() { Init(); }

GaugeClass::~GaugeClass() {
	delete backSprite;
	delete frontSprite;
	delete textSprite;
	delete uiSprite;
	delete ui2Sprite;
	delete ui3Sprite;
	for (int i = 0; i < 3; i++) {
		delete heart[i];
	}
}

void GaugeClass::Init() {

	backTexHandle = TextureManager::Load(backTexName);
	backSprite = Sprite::Create(backTexHandle, pos);
	frontTexHandle = TextureManager::Load(frontTexName);
	frontSprite = Sprite::Create(frontTexHandle, pos);
	textTexHandle = TextureManager::Load(textTex);
	textSprite = Sprite::Create(textTexHandle, pos);
	uiTexHandle = TextureManager::Load(uiTex);
	uiSprite = Sprite::Create(uiTexHandle, pos);
	ui2TexHandle = TextureManager::Load(ui2Tex);
	ui2Sprite = Sprite::Create(ui2TexHandle, pos);
	ui3TexHandle = TextureManager::Load(ui3Tex);
	ui3Sprite = Sprite::Create(ui3TexHandle, pos);


	initSize = backSprite->GetSize();
	initSize2 = textSprite->GetSize();
	initSize3 = uiSprite->GetSize();
	currentSize = initSize;
	currentPos2 = initSize;
	currentPos = pos;
	raito = 0;
	
	for (int i = 0; i < 3; i++) {
		heart[i] = new HeartClass;
	}
}

void GaugeClass::Update() {
	if (boomerang->GetPower() > 0) {
		raito = (float)boomerang->GetPower() / (float)boomerang->GetMaxPower();
	} else {
		raito = 0;
	}
	currentSize = initSize;
	currentSize.x *= raito;
	currentPos = pos;
	currentPos.x -= cameraPos->translation_.x * 20;
	currentPos.y -= cameraPos->translation_.y * 20;

	for (int i = 0; i < 3; i++) {
		heart[i]->Updaet();
	}
#ifdef _DEBUG

	ImGui::Begin("Gauge");
	ImGui::DragFloat2("currentPos2", &currentPos2.x, 1);
	ImGui::DragFloat2("Scale", &scale.x, 1);
	ImGui::DragFloat("Raito", &raito, 0.01f);
	ImGui::End();
	#endif
}

void GaugeClass::Draw() {
	textSprite->SetPosition(currentPos);
	textSprite->SetSize({initSize2.x / 2, initSize2.y/2});
	if (boomerang->GetPower() >= boomerang->GetMaxPower()) {
		textSprite->Draw();
	}
	
	uiSprite->SetPosition({31 - cameraPos->translation_.x * 20, 516 - cameraPos->translation_.y * 20});
	uiSprite->SetSize({initSize3.x / 2, initSize3.y / 2});
	uiSprite->Draw();

	ui2Sprite->SetPosition({-cameraPos->translation_.x * 20, -cameraPos->translation_.y * 20});
	ui2Sprite->Draw();
	ui3Sprite->SetPosition({-cameraPos->translation_.x * 20,270 -cameraPos->translation_.y * 20});
	if (!boomerang->GetIsHold()) {
		ui3Sprite->Draw();
	}
		

	backSprite->SetPosition(currentPos);
	//backSprite->SetSize(initSize * scale);
	backSprite->Draw();

	frontSprite->SetTextureRect({0, 0}, currentSize);
	frontSprite->SetPosition(currentPos);
	frontSprite->SetSize(currentSize * scale);
	frontSprite->Draw();

	if (player->GetHitPoint() > 0) {
		heart[0]->Draw({540, 660});
	}
	if (player->GetHitPoint() > 1) {
		heart[1]->Draw({640, 660});
	}
	if (player->GetHitPoint() > 2) {
		heart[2]->Draw({740, 660});
	}
	
}
