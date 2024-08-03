#include "EnemyRotateClass.h"



void EnemyRotateClass::Init(Enemy* setEnemy, float rotateZ, float setRotateSpeed) {
	worldTransform_.Initialize();
	worldTransform_.rotation_.z = rotateZ;
	worldTransform_.UpdateMatrix();
	enemy = setEnemy;
	rotateSpeed = setRotateSpeed;
}

void EnemyRotateClass::Update() {

	if (!enemy->GetIsStop()) {
		worldTransform_.rotation_.z += rotateSpeed;
	}
	//子オブジェクトのパラメーターによる、プレイヤーのホーミング処理
	//worldTransform_.rotation_.z += 1;
	worldTransform_.UpdateMatrix();
	isDead = enemy->IsDead();

#ifdef _DEBUG
	ImGui::Begin("Window");

	ImGui::DragFloat("rotate.z", &worldTransform_.rotation_.z);

	ImGui::End();
#endif // _DEBUG
}
