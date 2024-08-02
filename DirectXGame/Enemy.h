#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include <stdlib.h>

#include "EnemyBullet.h"
#include "TimedCall.h"

#include "Collider.h"
#include "Easing.h"
class PlayerBoomerang;
class GameScene;
class Boomerang;
enum class Phase
{
	Approach,
	Leave,
	Stoppage,
};
class Enemy: public Collider
{

public:
	~Enemy();
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewprojection);
	void SwitchPhase();
	void ApproachInitialize();
	void ApproachMove();
	void LeaveMove();
	void Stoping();

	void Fire();
	void FireReset();

	void SetPlayer(PlayerBoomerang* player) { player_ = player; }
	void SetBoomerang(Boomerang* boomerang) { boomerang_ = boomerang; }
	Vector3 GetWorldPosition() override;

	void OnCollision([[maybe_unused]] Collider* other) override;
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	bool IsDead() { return isDead_; }
	void SetHitPoint(int value) { currentHitPoint = value; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	const float kMoveSpeed = 0.2f;
	const float kBulletSpeed = 0.4f;
	float homingPower = 1.0f;
	Vector3 velocity_{ 0,0,-kMoveSpeed };

	Phase phase_ = Phase::Approach;

	Vector3 approachVelocity_{ 0,0,-kMoveSpeed };
	Vector3 leaveVelocity_{ -kMoveSpeed * 0.7f,kMoveSpeed * 0.7f,0 };

	//void (Enemy::* pFunc)();
	static void(Enemy::* spFuncTable[])();

	std::list<TimedCall*>timedCalls_;
	//std::list<EnemyBullet*>bullets_;

	PlayerBoomerang* player_ = nullptr;
	Boomerang* boomerang_ = nullptr;

	GameScene* gameScene_ = nullptr;

	bool isDead_;
	const int stopTime=60;
	int currentStopTime;

	int currentHitPoint;
	int setHitPoint = 1000;
	Vector3 initScale;



public:
	static const int32_t kFireCoolTime = 30 * 1;


};