#include "HeartClass.h"

HeartClass::HeartClass() { Init(); }

HeartClass::~HeartClass() {
	delete sprite;
	delete frontSprite;
}

void HeartClass::Init() {
	texHandle = TextureManager::Load("heart.png");
	sprite = Sprite::Create(texHandle, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	frontSprite = Sprite::Create(texHandle, {0, 0}, {1, 0.2f, 0.6f, 1}, {0.5f, 0.5f});
	initSize = sprite->GetSize();
}

void HeartClass::Updaet() {
	currentT++;

	scale = InOutQuad(currentT, 30, 0, 2);
	color = InOutQuad(currentT, 30, 1, 0);
	if (currentT>=45) {
		currentT = 0;
	}
}

void HeartClass::Draw(Vector2 pos) {
	sprite->SetSize({initSize.x * scale, initSize.x * scale});
	sprite->SetColor({1, 1, 1, color});
	sprite->SetPosition(pos);
	sprite->Draw();
	frontSprite->SetPosition(pos);
	frontSprite->Draw();
}
