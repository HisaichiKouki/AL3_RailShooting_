#pragma once
#include <ImGuiManager.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <stdlib.h>

#include "Collider.h"
#include "Easing.h"
#include "RailCamera.h"
#include "Vector3AndMatrix4x4.h"
#include <ObjectColor.h>
#include <TextureManager.h>
#include <Audio.h>
class PlayerBoomerang : public Collider {
public:
	~PlayerBoomerang();
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& pos);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Attack();
	void Move();

	Vector3 GetWorldPosition() override;

	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }
	void OnCollision([[maybe_unused]] Collider* other) override;
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetCamera(RailCamera* setCamera) { camera = setCamera; }
	int GetHitPoint() { return hitPoint; }
	void SetHitPoint(int value) {
		hitPoint = value;
		barriar = 90;
	}

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;

	// 移動処理用
	Vector3 moveDirection;
	const float kCharacterSpeed = 0.2f;
	const float kMoveLimitX = 20;
	const float kMoveLimitY = 12;

	float moveEaseT;
	float fastEaseT = 15; // 100-fastEaseTしてfastEaseTのフレーム分スキップする
	RailCamera* camera = nullptr;
	ObjectColor* objectColor = nullptr;
	Model* barriarModel = nullptr;
	uint32_t barriarTex = 0u;
	WorldTransform barriarTransform;
	int initHitpoint = 3;
	int hitPoint;
	int barriar;

	Audio* audio_ = nullptr;
	uint32_t soundHandle1 = 0;
	uint32_t soundHandle2 = 0;
};
