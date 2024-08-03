#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Boomerang.h"
#include "CatmullRomSpline.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "EnemyRotateClass.h"
#include "NumberDrawClass.h"
#include "ParticleClass.h"
#include "Player.h"
#include "PlayerBoomerang.h"
#include "Prediction.h"
#include "RailCamera.h"
#include "SkyDome.h"
#include <ObjectColor.h>
#include <sstream>
#include "GaugeClass.h"
#include "HPbar.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();
	const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void LoadEnemyPopDate();
	void UpdateEnemyPopCommands();
	void AddKillCount() {

		killCount--;
		killVoiceHandle = audio_->PlayWave(killSoundHandle);
		audio_->SetVolume(killVoiceHandle, 1.0f);
	}
	void AddEffect(const Vector3& pos);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	uint32_t texHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;

	PlayerBoomerang* playerBoom_ = nullptr;
	Model* playerModel_ = nullptr;
	uint32_t playerTex_ = 0;

	Boomerang* boomerang = nullptr;
	Model* boomerangModel = nullptr;
	uint32_t boomerangTex;

	Prediction* prediction = nullptr;
	Model* predictionModel = nullptr;
	uint32_t predictionTex;
	ObjectColor* predictionColor;
	bool isDebugCameraActive = false;
	DebugCamera* debugCamera_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	std::list<Enemy*> enemys_;
	std::list<EnemyRotateClass*> enemyRotates;
	// Enemy* enemy_ = nullptr;

	Model* modelSkydome_ = nullptr;
	SkyDome* skydome_ = nullptr;

	// CatmullRomSpline* catmullromSpline = nullptr;

	std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;
	std::stringstream copyEnemyPopCommands;

	bool isEnemySpown_ = false;
	int32_t isEnemySpownWaitTime_;

	int32_t killCount;

	NumberDrawClass* killNumTex = nullptr;
	uint32_t killSoundHandle = 0;
	uint32_t killVoiceHandle = 0;

	uint32_t bgmSH = 0;
	uint32_t bgmVH = 0;

	std::list<ParticleClass*> particles_;
	GaugeClass* gauge = nullptr;
	std::list<HPbar*> hpbars_;

 private:
	/// <summary>
	/// コライダー２つの衝突判定と応答
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
