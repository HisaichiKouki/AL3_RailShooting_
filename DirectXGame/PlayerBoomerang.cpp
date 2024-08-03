#include "PlayerBoomerang.h"

PlayerBoomerang::~PlayerBoomerang() {
	delete objectColor;
	delete barriarModel;
}

void PlayerBoomerang::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	input_ = Input::GetInstance();
	moveDirection = {0, 0, 0};
	moveEaseT = 50;
	SetName("player");
	SetRadius(-10);
	hitPoint = initHitpoint;
	objectColor = new ObjectColor;
	objectColor->Initialize();
	objectColor->SetColor({0.1f, 0.4f, 1.0f, 0.4f});
	objectColor->TransferMatrix();
	barriarModel = Model::CreateSphere();
	barriarTransform.Initialize();
	barriarTransform.scale_ = {2, 2, 2};
	barriarTex = TextureManager::Load("white1x1.png");
}

void PlayerBoomerang::Update() {
	barriar--;
	if (barriar > 0) {
		barriarTransform.scale_ = {3, 3, 3};

	} else {
		barriarTransform.scale_ = {0, 0, 0};

	}
	Move();
	worldTransform_.UpdateMatrix();

	barriarTransform.translation_ = GetWorldPosition();
	barriarTransform.UpdateMatrix();
}

void PlayerBoomerang::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	barriarModel->Draw(barriarTransform, viewProjection, barriarTex, objectColor);
}

void PlayerBoomerang::Attack() {}

void PlayerBoomerang::Move() {
	moveDirection = {0, 0, 0};

	/*if (input_->PushKey(DIK_LEFTARROW)) {
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

	worldTransform_.translation_ += moveDirection;*/

	// 移動方向と反対側にいる時は素早く戻る
	if (input_->TriggerKey(DIK_D)) {

		if (moveEaseT < fastEaseT) {
			moveEaseT = fastEaseT;
		}

	} else if (input_->TriggerKey(DIK_A)) {

		if (moveEaseT > 100 - fastEaseT) {
			moveEaseT = 100 - fastEaseT;
		}
	}

	// 移動
	if (input_->PushKey(DIK_D) && input_->PushKey(DIK_A)) {
		if (moveEaseT > 100 - fastEaseT) {
			moveEaseT = 100 - fastEaseT;
		} else if (moveEaseT < fastEaseT) {
			moveEaseT = fastEaseT;
		} else if (moveEaseT > 50) {
			moveEaseT -= 3;
			if (moveEaseT < 50) {
				moveEaseT = 50;
			}
		} else if (moveEaseT < 50) {
			moveEaseT += 3;
			if (moveEaseT > 50) {
				moveEaseT = 50;
			}
		}
	} else if (input_->PushKey(DIK_D)) {

		moveEaseT += 3;
	} else if (input_->PushKey(DIK_A)) {
		moveEaseT -= 3;
	} else {

		if (moveEaseT > 100 - fastEaseT) {
			moveEaseT = 100 - fastEaseT;
		} else if (moveEaseT < fastEaseT) {
			moveEaseT = fastEaseT;
		} else if (moveEaseT > 50) {
			moveEaseT -= 3;
			if (moveEaseT < 50) {
				moveEaseT = 50;
			}
		} else if (moveEaseT < 50) {
			moveEaseT += 3;
			if (moveEaseT > 50) {
				moveEaseT = 50;
			}
		}
	}
	moveEaseT = std::clamp(moveEaseT, 0.0f, 100.0f);
	worldTransform_.translation_.x = InOutQuad(moveEaseT, 100, -2, 2);
	// 画面外に出ないように
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
#ifdef _DEBUG

	ImGui::Begin("PlayerMove");
	ImGui::Text("HitPoint=%d", hitPoint);
	ImGui::Text("moveEaseT=%f,fastEaseT=%d", moveEaseT, fastEaseT);
	ImGui::End();
#endif
}

Vector3 PlayerBoomerang::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void PlayerBoomerang::OnCollision([[maybe_unused]] Collider* other) {
	camera->ShakeStart();

	if (barriar <= 0) {
		hitPoint--;
		barriar = 90;
	}
}
