#include "ParticleChildClass.h"

ParticleChildClass::ParticleChildClass() {}

ParticleChildClass::~ParticleChildClass() {
	//delete model_;
	delete objColor;
}

void ParticleChildClass::Init(Model* model, const Vector3& position, const Vector3& rotate, const Vector3& move) {

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.7f, 0.7f, 0.7f};
	textureHandle_ = TextureManager::Load("white1x1.png");
	rotateSpeed = rotate;
	moveSpeed = move;
	initColor = 1;
	currentColor = 0;
	objColor = new ObjectColor;
	objColor->Initialize();
	objColor->SetColor({1.0f, 1.0f, 0.6f, initColor});
	objColor->TransferMatrix();
	currentEaseT = 0;
}

void ParticleChildClass::Update() {
	currentEaseT += 0.01f;
	currentColor = (0.7f - currentEaseT) * initColor + currentEaseT * 0.1f;
	objColor->SetColor({1.0f, 1.0f, 0.6f, currentColor});
	objColor->TransferMatrix();

	worldTransform_.rotation_ += rotateSpeed;
	worldTransform_.translation_ += moveSpeed;

	worldTransform_.UpdateMatrix();

	if (currentEaseT >= 0.7f) {
		objColor->SetColor({1.0f, 1.0f, 0.6f, 0.0f});

		isDead = true;
	}
}

void ParticleChildClass::Draw(ViewProjection& viewProjection) { 
	
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_, objColor);

}
