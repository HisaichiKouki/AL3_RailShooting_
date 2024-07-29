#include "PlayerBoomerang.h"

PlayerBoomerang::~PlayerBoomerang()
{
}

void PlayerBoomerang::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos)
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	input_ = Input::GetInstance();
	moveDirection = { 0,0,0 };
}

void PlayerBoomerang::Update()
{
	Move();
	worldTransform_.UpdateMatrix();
}

void PlayerBoomerang::Draw(ViewProjection& viewProjection)
{
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBoomerang::Attack()
{
}

void PlayerBoomerang::Move()
{
	moveDirection = { 0,0,0 };

	if (input_->PushKey(DIK_LEFTARROW)) {
		moveDirection.x--;
	}
	if (input_->PushKey(DIK_RIGHTARROW)) {
		moveDirection.x++;
	}
	if (input_->PushKey(DIK_DOWNARROW)) {
		moveDirection.y--;
	}
	if (input_->PushKey(DIK_UPARROW)) {
		moveDirection.y++;
	}
	moveDirection *= kCharacterSpeed;

	worldTransform_.translation_ += moveDirection;

	//画面外に出ないように
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

Vector3 PlayerBoomerang::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void PlayerBoomerang::OnCollision()
{
}
