#include "RailCamera.h"
#include <GameScene.h>
void RailCamera::Init(const Vector3& worldPos, const Vector3& rotate) {
	worldTransfome_.Initialize();
	worldTransfome_.translation_ = worldPos;
	worldTransfome_.rotation_ = rotate;
	viewprojection_.farZ = 1000;
	viewprojection_.Initialize();
	input_ = Input::GetInstance();
	shake = new ShakeClass;
	shake->SetWorldTransfrom(&this->worldTransfome_);
}

void RailCamera::Update() {
	worldTransfome_.translation_ += velocity_;
	worldTransfome_.rotation_ += rotate_;

	if (!gameScene->GetIsChange()) {
		if (input_->PushKey(DIK_A)) {
			worldTransfome_.rotation_.z -= rotateSpeed;
		}
		if (input_->PushKey(DIK_D)) {
			worldTransfome_.rotation_.z += rotateSpeed;
		}
	}
	

	
	shake->Update();
	// worldTransfome_.UpdateMatrix();

#ifdef _DEBUG
	if (input_->PushKey(DIK_G)) {
		shake->Start();
	}
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translate", &worldTransfome_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransfome_.rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	worldTransfome_.matWorld_ = MakeAffineMatrix(worldTransfome_.scale_, worldTransfome_.rotation_, worldTransfome_.translation_);

	viewprojection_.matView = Inverse(worldTransfome_.matWorld_);
}

void RailCamera::ShakeStart() { shake->Start(); }
