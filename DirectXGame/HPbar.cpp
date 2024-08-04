#include "HPbar.h"
#include "Enemy.h"

HPbar::HPbar() { Init(); }

HPbar::~HPbar() {
	delete objColor;
	delete model_;
}

void HPbar::Init() {
	model_ = Model::Create();
	textureHandle_ = TextureManager::Load("white1x1.png");
	objColor = new ObjectColor;
	objColor->Initialize();
	//objColor->SetColor({0.2f, 0.8f, 0.2f, 0.8f});
	//objColor->TransferMatrix();
	worldTransform_.Initialize();
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.scale_ = {1.2f, 0.3f, 0.15f};
	worldTransform_.UpdateMatrix();

	raito = 1;
}

void HPbar::Update() {
#ifdef _DEBUG

	ImGui::Begin("HPbar");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	if (enemy->GetHitPoint() > 0) {
		raito = (float)enemy->GetHitPoint() / initHp;
	} else {
		raito = 0;
	}

	worldTransform_.scale_ = {1.2f * raito, 0.3f, 0.15f};

	worldTransform_.UpdateMatrix();
	isDead = enemy->IsDead();
}

void HPbar::Draw(const ViewProjection& viewprojection) { model_->Draw(worldTransform_, viewprojection, textureHandle_, objColor); }

void HPbar::SetEnemy(Enemy* set) {
	enemy = set;

	worldTransform_.parent_ = &enemy->GetWorldTransform();
	initHp = (float)enemy->GetHitPoint();
	if (initHp >= 2000) {
		objColor->SetColor({1.0f, 0.1f, 0.2f, 0.8f});

	} else if (initHp >= 400) {
		objColor->SetColor({1.0f, 0.6f, 1.0f, 0.9f});
	} else if (initHp >= 100) {
		objColor->SetColor({0.2f, 0.6f, 1.0f, 0.8f});
	} else {

		objColor->SetColor({0.2f, 0.8f, 0.2f, 0.8f});
	}
	objColor->TransferMatrix();
}
