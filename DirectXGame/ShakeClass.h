#pragma once
#include <WorldTransform.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include "Easing.h"
class ShakeClass {
public:
	ShakeClass();
	~ShakeClass();
	void Init();
	void Update();
	void Start();
	void SetWorldTransfrom(WorldTransform* worldTransform_) { worldTransform = worldTransform_; 
	initPos = worldTransform->translation_;
	}
	float RandomValue(float min, float max);

private:
	WorldTransform* worldTransform = nullptr;
	float initShakeTime = 2;
	float currentShakeTime;
	float initShakeNum = 25;
	float currentShakeNum;
	float initShakeSize = 60.0f;
	float currentShakeSize;

	Vector3 initPos;
	Vector3 newPos;
	bool isShake;
};
