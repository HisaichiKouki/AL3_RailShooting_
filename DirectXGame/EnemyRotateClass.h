#pragma once 

#include "WorldTransform.h"
#ifdef _DEBUG
#include <imgui.h>
#endif

#include "Enemy.h"

class EnemyRotateClass {
public:
	void Init(Enemy* setEnemy, float rotateZ,float setRotateSpeed);
	void Update();
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	bool GetIsDead() { return isDead; }

	private:
	WorldTransform worldTransform_;
	Enemy* enemy = nullptr;
	float rotateSpeed;
	bool isDead;
};
