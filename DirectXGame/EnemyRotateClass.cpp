#include "EnemyRotateClass.h"

void EnemyRotateClass::Init(float rotateZ) {
	worldTransform_.Initialize();
	worldTransform_.rotation_.z = rotateZ;
	worldTransform_.UpdateMatrix();
}

void EnemyRotateClass::Update() {

	//子オブジェクトのパラメーターによる、プレイヤーのホーミング処理
	//worldTransform_.rotation_.z += 1;
	worldTransform_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Window");

	ImGui::DragFloat("rotate.z", &worldTransform_.rotation_.z);

	ImGui::End();
#endif // _DEBUG
}
