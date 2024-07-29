#pragma once 

#include "WorldTransform.h"
#include <imgui.h>
class EnemyRotateClass {
public:
	void Init(float rotateZ);
	void Update();
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
};
