#include "ShakeClass.h"

ShakeClass::ShakeClass() { Init(); }

ShakeClass::~ShakeClass() {}

void ShakeClass::Init() {
	currentShakeTime = 0;
	currentShakeNum = initShakeNum;
	currentShakeSize = initShakeSize;
	initPos = {0, 0, 0};
	newPos = initPos;
	isShake = false;
}

void ShakeClass::Update() {
	if (!isShake) {
		return;
	}
	if (currentShakeTime > 0) {
		currentShakeTime--;
		return;
	}
	currentShakeTime = initShakeTime;
	currentShakeNum--;
	if (currentShakeNum <= 0) {
		isShake = false;
		if (worldTransform != nullptr) {
			worldTransform->translation_ = initPos;
		} 
		vector3pos = initPos;
		currentShakeTime = 0;
		return;
	}

	currentShakeSize = initShakeSize * (currentShakeNum / initShakeNum);
	newPos = initPos;
	if (currentShakeSize != 0) {
		newPos.x += RandomValue(-currentShakeSize, currentShakeSize);
		newPos.y += RandomValue(-currentShakeSize, currentShakeSize);
	}

	if (worldTransform != nullptr) {
		worldTransform->translation_ = newPos;
		worldTransform->UpdateMatrix();
	}
	vector3pos = newPos;
}

void ShakeClass::Start() {
	isShake = true;
	// initPos = worldTransform->translation_;
	currentShakeTime = 0;
	newPos = initPos;
	currentShakeNum = initShakeNum;
	currentShakeSize = initShakeSize;
}


float ShakeClass::RandomValue(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> ranX((int)min, (int)max);

	return (float)ranX(gen) / 100;
}
