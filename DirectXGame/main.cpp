#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	bool gameIsTitle = true;
	bool gameIsStart = false;
	bool gameIsClear = false;
	bool gameIsOver = false;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();
	uint32_t bgmSH = 0;
	uint32_t bgmVH = 0;
	bgmSH = audio->LoadWave("./Resources/Sounds/BGM.mp3");
	bgmVH = audio->PlayWave(bgmSH, true, 0.1f);
	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	uint32_t fadeTexHandle = TextureManager::Load("./Resources/addTexture/black.png");
	Sprite* fadeTex = Sprite::Create(fadeTexHandle, {0, 0});

	uint32_t titleTH = TextureManager::Load("./Resources/addTexture/title.png");
	Sprite* title = Sprite::Create(titleTH, {0, 0});
	uint32_t clearTH = TextureManager::Load("./Resources/addTexture/clear.png");
	Sprite* clear = Sprite::Create(clearTH, {0, 0});
	uint32_t overTH = TextureManager::Load("./Resources/addTexture/over.png");
	Sprite* over = Sprite::Create(overTH, {0, 0});
	float easeT = 30;
	float maxEase = 30;
	bool change = false;
	bool restart = false;
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理

		if (gameIsTitle) {

			if (!change) {
				if (easeT > 0) {
					easeT--;
				}

			} else {
				if (easeT < maxEase) {
					easeT++;
				} else {
					easeT = maxEase;
					gameIsStart = true;
					gameIsTitle = false;
					delete gameScene;
					gameScene = nullptr;
					gameScene = new GameScene();
					gameScene->Initialize();
					change = false;
				}
			}

			// タイトル
#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("Title");

			ImGui::End();
#endif // _DEBUG

			if (input->TriggerKey(DIK_SPACE)) {
				change = true;
			}
		}

		// ゲーム
		else if (gameIsStart) {
			if (!change) {
				if (easeT > 0) {
					easeT--;
					restart = false;
				}
			}

			gameScene->Update();

			if (gameScene->GetClear()) {
				change = true;
				if (easeT < maxEase) {
					easeT++;
				} else {
					easeT = maxEase;
					change = false;
					gameIsClear = true;
					gameIsStart = false;
				}

			} else if (gameScene->GetOver()) {
				change = true;
				if (easeT < maxEase) {
					easeT++;
				} else {
					easeT = maxEase;
					change = false;
					gameIsOver = true;
					gameIsStart = false;
				}
			}

			// クリア画面
		} else if (gameIsClear) {
			if (!change) {
				if (easeT > 0) {
					easeT--;
				}
			} else {
				if (easeT < maxEase) {
					easeT++;
				} else {
					easeT = maxEase;
					change = false;
					gameIsClear = false;
					gameIsTitle = true;
				}
			}
#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("GameClear");

			ImGui::End();
#endif // _DEBUG

			if (input->TriggerKey(DIK_SPACE)) {
				change = true;
			}

			// ゲームオーバー画面
		} else if (gameIsOver) {
			if (!change) {
				if (easeT > 0) {
					easeT--;
				}
			} else {
				if (easeT < maxEase) {
					easeT++;
				} else {
					easeT = maxEase;
					change = false;
					if (restart) {
						gameIsOver = false;
						gameIsStart = true;
						gameScene->SetHitPoint(3);
					} else {
						gameIsOver = false;
						gameIsTitle = true;
					}
				}
			}
#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("GameOver");

			ImGui::End();
#endif // _DEBUG
			if (input->TriggerKey(DIK_SPACE)) {
				restart = false;
				change = true;

			} else if (input->TriggerKey(DIK_R)) {
				restart = true;
				change = true;
			}
		}

		fadeTex->SetColor({1, 1, 1, easeT / maxEase});

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		if (gameIsStart) {
			gameScene->Draw();
		}
		

		Sprite::PreDraw(dxCommon->GetCommandList());
		if (gameIsTitle) {
			// タイトル
			title->Draw();
		} else if (gameIsClear) {
			// クリア画面
			clear->Draw();
		} else if (gameIsOver) {
			// ゲームオーバー
			over->Draw();
		}
		fadeTex->Draw();
		Sprite::PostDraw();

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete gameScene;
	delete fadeTex;
	delete title;
	delete clear;
	delete over;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	return 0;
}