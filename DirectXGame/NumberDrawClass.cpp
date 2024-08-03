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
	shake = new ShakeClass;
	preNum = 0;
	currentNum = 0;
	num = 1023030;//一回目を特例で設定する時に使う
}

void NumberDrawClass::Draw(const Vector2& pos, int32_t num_) {
	if (num == 1023030) {
		initPos = {pos.x, pos.y, 0};
		shake->SetVector3(initPos);
		
		
		shake->SetParamater(1, 20, 1500);
		preNum = num_;
		num = num_;
	}
	
	preNum = num;
	currentNum = num_;
	num = num_;
	if (preNum != num) {
		shake->Start();
	}

	shake->Update();
	initPos = shake->Value();
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
		sprite[i]->SetPosition({initPos.x - (float)i * width * scale.x - camera->translation_.x * 20, initPos.y - camera->translation_.y * 20}); // スクリーンに描画する場所をずらす
		sprite[i]->SetTextureRect({drawNum[i] * width, 0}, {width, initSize.y}); // テクスチャの描画範囲を指定する
		sprite[i]->SetSize({width * scale.x, initSize.y * scale.y});             // 描画するサイズを決める
		sprite[i]->Draw();
	}
	
	
	
	
}
