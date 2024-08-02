#include "NumberDrawClass.h"

NumberDrawClass::NumberDrawClass() { Init(); }

NumberDrawClass::~NumberDrawClass() { delete sprite; }

void NumberDrawClass::Init() {
	texHandle = TextureManager::Load(texName);
	sprite = Sprite::Create(texHandle, {0, 0});
	initSize = sprite->GetSize();
	scale = {0.3f, 0.3f};
	width = initSize.x / 10;
	drawNum = 3;
}

void NumberDrawClass::Draw(const Vector2& pos) {
	sprite->SetPosition(pos);
	sprite->SetTextureRect({drawNum * width, 0}, {width, initSize.y});
	sprite->SetSize({width*scale.x,initSize.y*scale.y});

	sprite->Draw();
}
