#include "Boomerang.h"
#include "PlayerBoomerang.h"
#include <cassert>
void Boomerang::Init(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input = Input::GetInstance();
	SetRadius(1);
	SetName("boomerang");
	reverceCoolTime = 0;
}

void Boomerang::Update() {
	
	// worldTransform_.rotation_.z = player->GetWorldTransform().rotation_.z;
	if (boundCoolTime > 0) {
		boundCoolTime--;
	}
	if (reverceCoolTime > 0) {
		reverceCoolTime--;
	}
	(this->*spFuncTable[static_cast<size_t>(phase)])();
#ifdef _DEBUG
	ImGui::Begin("Boomerang");
	ImGui::Text("attackPower=%f", attackPower);
	ImGui::End();
#endif // _DEBUG
}

void Boomerang::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void Boomerang::Move() {
	isHold = false;
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

	if (attackPower < maxAttackPower) {
		attackPower++;
	}
	if (worldTransform_.translation_.z < 0) { // player->GetWorldPosition().z
		attackPower = 0;
		rotate.y = 0;
		// worldTransform_.translation_.z = player->GetWorldPosition().z;
		worldTransform_.translation_.z = 0;
		phase = PhaseBoomerang::kHold;
	}
	worldTransform_.rotation_ = rotate;
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Boomerang::Hold() {
	isHold = true;
	PlayerPosXY();
	if (input->TriggerKey(DIK_SPACE)) {
		phase = PhaseBoomerang::kMove;
		velocity.z = throwPower;
	}
}

void Boomerang::PlayerPosXY() {
	// worldTransform_.translation_.x = player->GetWorldPosition().x;
	// worldTransform_.translation_.y = player->GetWorldPosition().y;

	worldTransform_.UpdateMatrix();
}

void Boomerang::OnCollision([[maybe_unused]] Collider* other) {
	// バウンドする
	if (reverceCoolTime <= 0) {
		preHit = true;
		// 進行方向の力を代入
		velocity.z += boundPower * moveDire;
		// 跳ね返るので力の向きを反転
		velocity.z *= -1;
		boundCoolTime = 4.0f;   // すぐに戻せないようにするためのクールタイム
		reverceCoolTime = 5.0f; // 重なってる敵にぶつかった時に連続して判定が起きないように
	}
	
	
}

void Boomerang::ExitCollision([[maybe_unused]] Collider* other) { preHit = false; }

Vector3 Boomerang::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

//バウンドする。敵がヒットした時に呼び出す
void Boomerang::ReverceMove() {
	
}

void (Boomerang::*Boomerang::spFuncTable[])() = {&Boomerang::Hold, &Boomerang::Move};
