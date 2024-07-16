#include "Prediction.h"

void Prediction::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
}

void Prediction::Update()
{
}

void Prediction::Draw(ViewProjection& viewProjection, ObjectColor* objectColor)
{
	model_->Draw(worldTransform_, viewProjection, objectColor);

}



void Prediction::SetWorldPos(const Vector3& pos)
{
	worldTransform_.translation_ = pos;
	worldTransform_.UpdateMatrix();
}
