#include "Boomerang.h"
#include "PlayerBoomerang.h"
#include <cassert>
void Boomerang::Init(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input = Input::GetInstance();
	SetRadius(10);
	SetName("boomerang");
}

void Boomerang::Update() {

	//worldTransform_.rotation_.z = player->GetWorldTransform().rotation_.z;
	if (boundCoolTime > 0) {
		boundCoolTime--;
	}
	(this->*spFuncTable[static_cast<size_t>(phase)])();
#ifdef _DEBUG
	ImGui::Begin("Boomerang");
	ImGui::Text("attackPower=%f", attackPower);
	ImGui::End();
#endif // _DEBUG
}

void Boomerang::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

void Boomerang::Move() {
	PlayerPosXY();

	// スペースを押してる間は早く戻る
	// ずっと押してると連続攻撃できるからちょっとcoolTimeを付けた。
	if (input->PushKey(DIK_SPACE) && boundCoolTime <= 0) {

		velocity.z -= returnPower * 5;
		rotate.y += kRotateSpeed * 3;
	} else {
		velocity.z -= returnPower;
		rotate.y += kRotateSpeed;
	}
	velocity.z = std::clamp(velocity.z, -maxSpeed, maxSpeed);
	worldTransform_.translation_.z += velocity.z;
	if (velocity.z > 0) {
		moveDire = 1;
	} else if (velocity.z < 0) {
		moveDire = -1;
	}
	attackPower++;
	if (worldTransform_.translation_.z < 0) {//player->GetWorldPosition().z
		attackPower = 0;
		rotate.y = 0;
		//worldTransform_.translation_.z = player->GetWorldPosition().z;
		worldTransform_.translation_.z = 0;
		phase = PhaseBoomerang::kHold;
	}
	worldTransform_.rotation_ = rotate;
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Boomerang::Hold() {
	PlayerPosXY();
	if (input->TriggerKey(DIK_SPACE)) {
		phase = PhaseBoomerang::kMove;
		velocity.z = throwPower;
	}
}

void Boomerang::PlayerPosXY() {
	//worldTransform_.translation_.x = player->GetWorldPosition().x;
	//worldTransform_.translation_.y = player->GetWorldPosition().y;

	worldTransform_.UpdateMatrix();
}

void Boomerang::OnCollision([[maybe_unused]] Collider* other) {
	// バウンドする

	if (boundCoolTime <= 0) {
		// 進行方向の力を代入
		velocity.z += boundPower * moveDire;
		// 跳ね返るので力の向きを反転
		velocity.z *= -1;
		boundCoolTime = 10.0f; // 一度ぶつかったら10Fのクールタイム
	}
}

Vector3 Boomerang::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void (Boomerang::*Boomerang::spFuncTable[])() = {&Boomerang::Hold, &Boomerang::Move};
