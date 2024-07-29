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


#include "Collider.h"
#include "Vector3AndMatrix4x4.h"


class PlayerBoomerang :public Collider
{
public:
	~PlayerBoomerang();
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& pos);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Attack();
	void Move();

	Vector3 GetWorldPosition() override;

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	void OnCollision() override;
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;

	//移動処理用
	Vector3 moveDirection;
	const float kCharacterSpeed = 0.2f;
	const float kMoveLimitX = 20;
	const float kMoveLimitY = 12;
};

