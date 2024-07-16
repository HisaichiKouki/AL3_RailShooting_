#pragma once
#include <cassert>
#include <Input.h>
#include <Model.h>
#include <WorldTransform.h>
#include <ImGuiManager.h>
#include <ViewProjection.h>	
#include <stdlib.h>
#include <list>
#include <Sprite.h>
#include<ObjectColor.h>
class Prediction
{public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection, ObjectColor* objectColor);
	void SetWorldPos(const Vector3& pos);
	//void SetWorldTransform(WorldTransform  worldTransform) { worldTransform_ = worldTransform; }
private :
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//ObjectColor* objectColor = nullptr;


};

