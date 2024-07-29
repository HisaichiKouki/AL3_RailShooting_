#include "SkyDome.h"



SkyDome::~SkyDome()
{
	
}

void SkyDome::Init( Model* model)
{
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_.z = -10;
	
	worldTransform2_.Initialize();
	worldTransform2_.translation_.z = 990;
}

void SkyDome::Update() {
	worldTransform_.translation_.z -= moveSpeed;
	worldTransform2_.translation_.z -= moveSpeed;

	if (worldTransform_.translation_.z <= -1010) {
		worldTransform_.translation_.z = 990;
	}
	if (worldTransform2_.translation_.z <= -1010) {
		worldTransform2_.translation_.z = 990;
	}

	ImGui::DragFloat("z1", &worldTransform_.translation_.z, 1);
	ImGui::DragFloat("z2", &worldTransform2_.translation_.z, 1);
	worldTransform_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
}

void SkyDome::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
	model_->Draw(worldTransform2_, viewProjection);
}
