#include "NumberDrawClass.h"

NumberDrawClass::NumberDrawClass() { Init(); }

NumberDrawClass::~NumberDrawClass() {
	for (int i = 0; i < 5; i++) {
		delete sprite[i];
	}
}

void NumberDrawClass::Init() {
	texHandle = TextureManager::Load(texName);

	for (int i = 0; i < 5; i++) {
		sprite[i] = Sprite::Create(texHandle, {0, 0});
	}
	initSize = sprite[0]->GetSize();
	scale = {0.3f, 0.3f};
	width = initSize.x / 10;

	for (int i = 0; i < numDigits; i++) {
		drawNum[i] = (float)i;

	}
}

void NumberDrawClass::Draw(const Vector2& pos, int32_t num) {
	currentNum = num;
	

	for (int i = 0; i < numDigits; i++) {
		sprite[i]->SetSize({0, 0});

	}
	for (int i = 0; i < numDigits; i++) {
		if (currentNum < 0) {
			break;
		}
		drawNum[i] = (float)(currentNum % 10);
		

		sprite[i]->Draw();
		if (currentNum != 0) {
			currentNum /= 10;
		} else {
			break;
		}
		sprite[i]->SetPosition({pos.x - (float)i * width * scale.x, pos.y});     // スクリーンに描画する場所をずらす
		sprite[i]->SetTextureRect({drawNum[i] * width, 0}, {width, initSize.y}); // テクスチャの描画範囲を指定する
		sprite[i]->SetSize({width * scale.x, initSize.y * scale.y});             // 描画するサイズを決める
		sprite[i]->Draw();
	}
	
	
	
	
}
