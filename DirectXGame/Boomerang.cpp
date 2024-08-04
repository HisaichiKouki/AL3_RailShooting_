#include "Boomerang.h"
#include "PlayerBoomerang.h"
#include <cassert>
#include "Enemy.h"

void Boomerang::Init(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input = Input::GetInstance();
	SetRadius(1);
	SetName("boomerang");
	reverceCoolTime = 0;
	audio_ = Audio::GetInstance();
	soundHandle1 = audio_->LoadWave("./Resources/Sounds/slow.mp3");
	soundHandle2 = audio_->LoadWave("./Resources/Sounds/speedSlow.mp3");
	soundHandle3 = audio_->LoadWave("./Resources/Sounds/powerUP.mp3");
	soundHandle4 = audio_->LoadWave("./Resources/Sounds/back.mp3");
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

	if (player->GetHitPoint()<=0) {
		StopSE();
	}
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
		if (input->TriggerKey(DIK_SPACE)) {
			vh2 = audio_->PlayWave(soundHandle4, true, 0.6f);
		}
	} else {
		if (vh2 != 0) {
			audio_->StopWave(vh2);
		}
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
		if (attackPower >= maxAttackPower) {
			audio_->PlayWave(soundHandle3, false, 0.2f);
		}
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
	StopSE();
	if (input->TriggerKey(DIK_SPACE)) {
		phase = PhaseBoomerang::kMove;
		velocity.z = throwPower;
		audio_->PlayWave(soundHandle1, false, 0.3f);
		vh=audio_->PlayWave(soundHandle2, true, 0.2f);
	}
}

void Boomerang::PlayerPosXY() {
	// worldTransform_.translation_.x = player->GetWorldPosition().x;
	// worldTransform_.translation_.y = player->GetWorldPosition().y;

	worldTransform_.UpdateMatrix();
}

void Boomerang::OnCollision([[maybe_unused]] Collider* other) {
	// バウンドする
	//if (reverceCoolTime <= 0) {
	//	preHit = true;
	//	// 進行方向の力を代入
	//	velocity.z += boundPower * moveDire;
	//	// 跳ね返るので力の向きを反転
	//	velocity.z *= -1;
	//	boundCoolTime = 4.0f;   // すぐに戻せないようにするためのクールタイム
	//	reverceCoolTime = 5.0f; // 重なってる敵にぶつかった時に連続して判定が起きないように
	//}

	if (!targetEenemy->GetPreHit()) {
		velocity.z += boundPower * moveDire;
		// 跳ね返るので力の向きを反転
		velocity.z *= -1;
		boundCoolTime = 2.0f; // すぐに戻せないようにするためのクールタイム

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

void Boomerang::StopSE() {
	if (vh != 0) {
		audio_->StopWave(vh);
	}
	if (vh2 != 0) {
		audio_->StopWave(vh2);
	}
}

void (Boomerang::*Boomerang::spFuncTable[])() = {&Boomerang::Hold, &Boomerang::Move};
