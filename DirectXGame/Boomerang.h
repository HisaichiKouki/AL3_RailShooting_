#pragma once
#include <Model.h>
#include <Sprite.h>
#include <WorldTransform.h>
#include <ViewProjection.h>	
#include <Input.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "Collider.h"
#include "Vector3AndMatrix4x4.h"




class PlayerBoomerang;
enum class PhaseBoomerang 
{
	kHold,
	kMove,
};
class Boomerang :public Collider
{
public:
	void Init(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Move();
	void Hold();
	void SetPlayer(PlayerBoomerang* player_) { player = player_; }
	void  PlayerPosXY();
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	void OnCollision([[maybe_unused]] Collider* other) override;
	Vector3 GetWorldPosition() override;
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input = nullptr;
	Vector3 rotate;
	float kRotateSpeed = 0.1f;
	PhaseBoomerang phase = PhaseBoomerang::kHold;
	static void (Boomerang::* spFuncTable[])();
	PlayerBoomerang *player;
	Vector3 velocity;
	float throwPower = 1.0f;//投げだす力
	float returnPower = 0.01f;//戻ってくる力
	float maxSpeed = 1.2f;//最大速度
	float boundPower = 0.3f;//加算してバウンドする
	float moveDire;
	float boundCoolTime;

	float attackPower;
	float maxAttackPower;

};

