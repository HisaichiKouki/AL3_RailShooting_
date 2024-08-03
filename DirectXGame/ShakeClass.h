#pragma once
#include "Easing.h"
#include <WorldTransform.h>
#include <iostream>
#include <random>
#include <stdlib.h>
class ShakeClass {
public:
	ShakeClass();
	~ShakeClass();
	void Init();
	void Update();
	void Start();
	Vector3 Value() { return vector3pos; };
	void SetWorldTransfrom(WorldTransform* worldTransform_) {
		worldTransform = worldTransform_;
		initPos = worldTransform->translation_;
	}
	void SetVector3(Vector3& set) {
		vector3pos = set;
		initPos = vector3pos;
	}
	float RandomValue(float min, float max);

	void SetParamater(float time, float num, float size) {
		initShakeTime = time;
		initShakeNum = num;
		initShakeSize = size;
	}

private:
	WorldTransform* worldTransform = nullptr;
	Vector3 vector3pos;
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
