#pragma once
#include "ParticleChildClass.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <Model.h>
#include <stdlib.h>
#include <iostream>
#include <random>

const int kParticleNum = 30;
class ParticleClass {
public:
	ParticleClass();
	~ParticleClass();
	void Init(Model* model, const Vector3& pos);
	void Update();
	void Draw(ViewProjection& viewProjection);

	Vector3 RandomValue(const Vector3& min,const Vector3& max);
	bool GetIsDead() { return isDead; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	ParticleChildClass* child[kParticleNum] = {nullptr};
	Vector3 rotateMin = {1, 1, 1};
	Vector3 rotateMax = {10, 10, 10};
	Vector3 moveMin = {-19, -19, -5};
	Vector3 moveMax = {19, 19, 0};
	
	float currentTime;
	bool isDead;

};
