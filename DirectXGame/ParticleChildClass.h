#pragma once
#include "TextureManager.h"
#include "WorldTransform.h"
#include <Model.h>
#include <stdlib.h>
#include <Easing.h>
#include <ObjectColor.h>
class ParticleChildClass {

public:
	ParticleChildClass();
	~ParticleChildClass();
	void Init(Model* model, const Vector3& position, const Vector3& rotate, const Vector3& move);
	void Update();
	void Draw(ViewProjection& viewProjection);
	bool GetIsDead() { return isDead; }
	private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	Vector3 rotateSpeed;
	Vector3 moveSpeed;
	ObjectColor* objColor=nullptr;
	float currentEaseT;
	float initColor;
	float currentColor;

	float totalTime = 1.5f;
	bool isDead;

};
