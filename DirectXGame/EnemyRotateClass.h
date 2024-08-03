#pragma once 

#include "WorldTransform.h"
#include <imgui.h>
#include "Enemy.h"
class EnemyRotateClass {
public:
	void Init(Enemy* setEnemy, float rotateZ,float setRotateSpeed);
	void Update();
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	Enemy* enemy = nullptr;
	float rotateSpeed;
};
