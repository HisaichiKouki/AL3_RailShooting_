#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

#include <fstream>

GameScene::GameScene() {  }

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete modelSkydome_;
	delete skydome_;
	//delete enemy_;
	delete railCamera_;
	//delete catmullromSpline;

	delete playerBoom_;
	delete playerModel_;
	
	for (EnemyBullet* bullet : enemyBullets_)
	{
		delete bullet;
	}
	for (Enemy* enemy : enemys_)
	{
		delete enemy;
	}
	for (EnemyRotateClass* pos : enemyRotates) {
		delete pos;
	}
	/*for (auto itr = enemys_.begin(); itr != enemys_.end(); ++itr) {
		delete* itr;
	}*/

	delete boomerang;
	delete boomerangModel;
	delete prediction;
	delete predictionModel;
	delete predictionColor;
	delete killNumTex;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	texHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();
	Vector3 playerPosition(0, 0, 20.0f);
	player_->Initialize(model_, texHandle_, playerPosition);


	
	//player_->Initialize(model_, texHandle_);

	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	/*Enemy *enemy = new Enemy();
	enemy->SetGameScene(this);
	enemy->SetPlayer(player_);
	enemy->Initialize(model_, { 10,1,50.0f });
	enemys_.push_back(enemy);
	Enemy* enemy2 = new Enemy();
	enemy2->SetGameScene(this);
	enemy2->SetPlayer(player_);
	enemy2->Initialize(model_, { -10,1,50.0f });
	enemys_.push_back(enemy2);*/

	skydome_ = new SkyDome();
	modelSkydome_ = Model::CreateFromOBJ("skyholl", true);
	skydome_->Init(modelSkydome_);
	railCamera_ = new RailCamera();
	railCamera_->Init({ 0.0f,0.0f,-9.0f }, player_->GetWorldTransform().rotation_);//player_->GetWorldTransform().rotation_
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

	player_->SetParent(&railCamera_->GetWorldTransform());
	player_->SetViewProjection(&railCamera_->GetViewProjection());
	//player_->SetGameScene(this);
	//catmullromSpline = new CatmullRomSpline(debugCamera_->GetViewProjection());
	LoadEnemyPopDate();
	isEnemySpownWaitTime_ = 0;
	TextureManager::Load("./Resources/addTexture/reticle.png");
	playerBoom_ = new PlayerBoomerang;
	playerModel_ = Model::CreateFromOBJ("player", true);
	playerTex_ = TextureManager::Load("./Resources/addTexture/player.png");
	playerPosition = {0, -10, 8.5f};
	playerBoom_->SetParent(&railCamera_->GetWorldTransform());
	playerBoom_->Initialize(playerModel_, playerTex_, playerPosition);


	boomerang = new Boomerang;
	boomerangModel = Model::CreateFromOBJ("boomerang", true);
	boomerangTex= TextureManager::Load("./Resources/addTexture/boomerang.png");
	boomerang->Init(boomerangModel, boomerangTex);
	//boomerang->SetPlayer(playerBoom_);
	boomerang->SetParent(&playerBoom_->GetWorldTransform());

	prediction = new Prediction;
	predictionModel = Model::CreateFromOBJ("prediction", true);
	predictionTex = TextureManager::Load("./Resources/addTexture/prediction.png");
	prediction->Initialize(predictionModel, predictionTex);
	predictionColor = new ObjectColor;
	predictionColor->Initialize();
	predictionColor->SetColor(Vector4{ 1.0f,1.0f,1.0f,0.4f });
	predictionColor->TransferMatrix();
	//predictionColor.Initialize();
	//predictionColor.SetColor(Vector4{ 1,0,0,0.4f });
	killCount = 0;
	killNumTex = new NumberDrawClass;
}

void GameScene::Update() {
	
	UpdateEnemyPopCommands();
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			
			delete enemy;
			return true;
		}
		return false;
		});
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead())
		{
			delete bullet;
			return true;
		}
		return false;
		});


	railCamera_->Update();

	skydome_->Update();
	//player_->Update();
	playerBoom_->Update();
	boomerang->Update();
	prediction->SetWorldPos(playerBoom_->GetWorldPosition());
	/*if (enemy_)
	{
		enemy_->Update();
	}*/
	for (auto* enemy : enemys_)
	{

		enemy->Update();

	}
	for (auto* enemy : enemyRotates) {

		enemy->Update();
	}
	for (EnemyBullet* bullet : enemyBullets_)
	{
		bullet->Update();
	}
	CheckAllCollisions();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_T)) {
		isDebugCameraActive = !isDebugCameraActive;
	}
#endif // _DEBUG
	if (isDebugCameraActive) {

		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();


	} else {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		//viewProjection_.UpdateMatrix();
	}
	

ImGui::Text("KillCount=%d", killCount);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	skydome_->Draw(viewProjection_);
	//player_->Draw(viewProjection_);
	playerBoom_->Draw(viewProjection_);
	boomerang->Draw(viewProjection_);
	prediction->Draw(viewProjection_, predictionColor);
	//if (enemy_)
	//{
	//	enemy_->Draw(viewProjection_);
	//}
	for (auto* enemy : enemys_)
	{
		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* bullet : enemyBullets_)
	{
		bullet->Draw(viewProjection_);
	}
	//catmullromSpline->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	killCount = 12;
	//player_->DrawUI();
	killNumTex->Draw({100, 100},killCount);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions()
{
	//Vector3 posA, posB;

	//const std::list<PlayerBullet*>& playerBullets_ = player_->GetBullets();
	//const std::list<EnemyBullet*>& enemyBullets_ = enemy_->GetBullets();

	//posA = player_->GetWorldPosition();

	for (auto* enemy : enemys_) {

		CheckCollisionPair(boomerang, enemy);
	}
	for (auto* enemy : enemys_) {

		CheckCollisionPair(playerBoom_, enemy);
	}
//#pragma region playerToEnemyBullet
//	/*for (auto* bullet : enemyBullets_)
//	{
//		
//		CheckCollisionPair(player_, bullet);
//		
//	}*/
//	/*for (auto* enemy : enemys_)
//	{
//
//		CheckCollisionPair(player_, enemy);
//
//	}*/
//	for (auto* enemy : enemys_)
//	{
//
//		CheckCollisionPair(boomerang, enemy);
//
//	}
//	/*for (auto* bullet : enemyBullets_)
//	{
//		posB = bullet->GetWorldPosition();
//
//		if (Length(posA, posB) <= 16.0f)
//		{
//			player_->OnCollision();
//			bullet->OnCollision();
//		}
//	}*/
//#pragma endregion
//
//#pragma region PlayerBulletToEnemy
//	/*for (auto* bullet : playerBullets_)
//	{
//		for (auto* enemy:enemys_)
//		{
//			CheckCollisionPair(enemy, bullet);
//
//		}
//
//	}*/
//	/*posA = enemy_->GetWorldPosition();
//	for (auto* bullet : playerBullets_)
//	{
//		posB = bullet->GetWorldPosition();
//
//		if (Length(posA, posB) <= 10.0f)
//		{
//			enemy_->OnCollision();
//			bullet->OnCollision();
//		}
//	}*/
//#pragma endregion
//
//
//#pragma region playerBulletToEnemyBullet
//	for (auto* playerBullet : playerBullets_)
//	{
//
//		for (auto* enemyBullet : enemyBullets_)
//		{
//			CheckCollisionPair(playerBullet, enemyBullet);
//
//		}
//
//
//	}
//	/*for (auto* playerBullet : playerBullets_)
//	{
//		posA = playerBullet->GetWorldPosition();
//
//		for (auto* enemyBullet : enemyBullets_)
//		{
//			posB = enemyBullet->GetWorldPosition();
//
//
//			if (Length(posA, posB) <= 10.0f)
//			{
//				playerBullet->OnCollision();
//				enemyBullet->OnCollision();
//			}
//		}
//
//		
//	}*/
//#pragma endregion

}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet)
{
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::LoadEnemyPopDate()
{
	std::ifstream file;
	file.open("./Resources/Scripts/enemyPop.csv");
	assert(file.is_open() && "スクリプトファイルが開けませんでした");//
	enemyPopCommands << file.rdbuf();
	copyEnemyPopCommands << enemyPopCommands.rdbuf();
	file.close();

}

//エネミーの生成
void GameScene::UpdateEnemyPopCommands()
{

	if (isEnemySpown_) {
		isEnemySpownWaitTime_--;
		if (isEnemySpownWaitTime_ <= 0) {
			isEnemySpown_ = false;
		}
		return;
	}
	std::string line;

	while (getline(copyEnemyPopCommands, line))
	{
		std::istringstream line_stream(line);
		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//")==0)
		{
			continue;
		}

		if (word.find("POP") == 0)
		{
			getline(line_stream, word, ',');
			float posZ = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			float rotateZ = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			int hitPoint = (int)std::atof(word.c_str());
			/*getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());*/
			/*getline(line_stream, word, ',');
			float rotateZ = (float)std::atof(word.c_str());*/
			EnemyRotateClass* enemyRotate;
			enemyRotate = new EnemyRotateClass;
			enemyRotate->Init(rotateZ);
			Enemy* spownEnemy = new Enemy;
			spownEnemy->SetGameScene(this);
			spownEnemy->SetPlayer(playerBoom_);
			
			spownEnemy->SetParent(&enemyRotate->GetWorldTransform());
			
			spownEnemy->Initialize(model_, Vector3(0, -10, posZ));
			spownEnemy->SetBoomerang(boomerang);
			spownEnemy->SetHitPoint(hitPoint);
			enemys_.push_back(spownEnemy);
			enemyRotates.push_back(enemyRotate);

		}
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');
			int32_t waitTime = atoi(word.c_str());
			isEnemySpown_ = true;
			isEnemySpownWaitTime_ = waitTime;

			break;

		} else if (word.find("RETRY") == 0) {
			
			copyEnemyPopCommands.seekg(0, std::ios_base::beg);
			break;
		}
	}
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB)
{
	colliderA->GetWorldPosition();
	colliderB->GetWorldPosition();

	float distance = Length(colliderA->GetWorldPosition(), colliderB->GetWorldPosition());

	if (distance<=colliderA->GetRadius()+ colliderB->GetRadius())
	{
		colliderA->OnCollision(colliderB);
		colliderB->OnCollision(colliderA);
	}
}



