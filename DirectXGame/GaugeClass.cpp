#include "GaugeClass.h"

GaugeClass::GaugeClass() { Init(); }

GaugeClass::~GaugeClass() {
	delete backSprite;
	delete frontSprite;
}

void GaugeClass::Init() {

	backTexHandle = TextureManager::Load(backTexName);
	backSprite = Sprite::Create(backTexHandle, pos);
	frontTexHandle = TextureManager::Load(frontTexName);
	frontSprite = Sprite::Create(frontTexHandle, pos);
	initSize = frontSprite->GetSize();

	currentSize = initSize;
	currentPos = pos;
	raito = 0;
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
#ifdef _DEBUG

	ImGui::Begin("Gauge");
	ImGui::DragFloat2("Pos", &pos.x, 1);
	ImGui::DragFloat2("Scale", &scale.x, 1);
	ImGui::DragFloat("Raito", &raito, 0.01f);
	ImGui::End();
	#endif
}

void GaugeClass::Draw() {
	backSprite->SetPosition(currentPos);
	backSprite->SetSize(initSize * scale);
	backSprite->Draw();

	frontSprite->SetTextureRect({0, 0}, currentSize);
	frontSprite->SetPosition(currentPos);
	frontSprite->SetSize(currentSize * scale);
	frontSprite->Draw();
}
