#include "Enemy.h"
#include "PlayerBoomerang.h"
#include "GameScene.h"
Enemy::~Enemy()
{

	//for (int i = 0; i < timedCalls_.size(); i++)
	//{
	//	delete timedCalls_.front();
	//	//delete timedCalls_;
	//}
	
	for (TimedCall* timedCall : timedCalls_)
	{
		
		delete timedCall;
	}

	
}

void Enemy::Initialize(Model* model, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	textureHandle_ = TextureManager::Load("sample.png");
	//pFunc = &Enemy::ApproachMove;
	//Fire();	
	isDead_ = false;
	SetRadius(5);


	//ApproachInitialize();
}

void Enemy::Update() {




	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	//worldTransform_.translation_ = Add(worldTransform_.translation_,velocity_);
	worldTransform_.UpdateMatrix();
	//worldTransform_.translation_ += velocity_;
	//SwitchPhase();
	//(this->*pFunc)();



#ifdef _DEBUG
	ImGui::SliderFloat("homingPower", &homingPower, 0.0f, 0.5f);


#endif // _DEBUG

}

void Enemy::Draw(const ViewProjection& viewprojection) {

	model_->Draw(worldTransform_, viewprojection, textureHandle_);

}

void Enemy::SwitchPhase()
{
	//pFunc = &Enemy::ApproachMove;
	/*switch (phase_)
	{
	case Phase::Approach:
		ApproachMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	default:
		break;
	}*/
}

void Enemy::ApproachInitialize()
{
	FireReset();
}

void Enemy::ApproachMove()
{

	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
		});
	for (auto& timedCall : timedCalls_)
	{
		timedCall->Update();
	}
	/*if (--isFireCoolTime <= 0)
	{
		Fire();
		isFireCoolTime = kFireCoolTime;
	}*/
	worldTransform_.translation_ += approachVelocity_;
	if (worldTransform_.translation_.z < 0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveMove()
{
	worldTransform_.translation_ += leaveVelocity_;
}

void Enemy::Fire()
{
	EnemyBullet* newBullet = new EnemyBullet();
	Vector3 pWorldPos = player_->GetWorldPosition();
	Vector3 eWorldPos = this->GetWorldPosition();
	Vector3 subVector = Subtract(pWorldPos, eWorldPos);
	Vector3 normalVec = Normalize(subVector);
	normalVec.x *= kBulletSpeed;
	normalVec.y *= kBulletSpeed;
	normalVec.z *= kBulletSpeed;
	newBullet->SetPlayer(player_);
	newBullet->Initialize(model_, worldTransform_.translation_, normalVec);
	//bullets_.push_back(newBullet);
	newBullet->SetHomingPower(homingPower);
	gameScene_->AddEnemyBullet(newBullet);

}

void Enemy::FireReset()
{
	Fire();
	timedCalls_.push_back(new TimedCall(std::bind(&Enemy::FireReset, this), kFireCoolTime));
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollision()
{
	//isDead_ = true;
}



void(Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::ApproachMove,
	&Enemy::LeaveMove
};
