#include "NumberDrawClass.h"

NumberDrawClass::NumberDrawClass() { Init(); }

NumberDrawClass::~NumberDrawClass() { delete sprite; }

void NumberDrawClass::Init() {
	texHandle = TextureManager::Load(texName);
	sprite = Sprite::Create(texHandle, {0, 0});
	initSize = sprite->GetSize();
	scale = {0.3f, 0.3f};
	width = initSize.x / 10;

	for (int i = 0; i < numDigits; i++) {
		drawNum[i] = (float)i;
	}

}

void NumberDrawClass::Draw(const Vector2& pos, int32_t num) {
	currentNum = num;
	for (int i = 0; i < numDigits; i++) {
		if (currentNum < 0) {
			break;
		}
		drawNum[i] = (float)(currentNum % 10);
		

		
		if (currentNum != 0) {
			currentNum /= 10;
		} else {
			break;
		}
	}
	for (int i = 0; i < 3; i++) {
		sprite->SetPosition({pos.x - (float)i * width, pos.y});
		sprite->SetTextureRect({2 * width, 0}, {width, initSize.y});
		sprite->SetSize({width * scale.x, initSize.y * scale.y});

		sprite->Draw();
	}
	
	
}
