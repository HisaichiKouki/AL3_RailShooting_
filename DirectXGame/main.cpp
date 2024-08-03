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
			// タイトル
#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("Title");

			ImGui::End();
#endif // _DEBUG		

			if (input->TriggerKey(DIK_SPACE)) {
				gameIsStart = true;
				gameIsTitle = false;
				delete gameScene;
				gameScene = nullptr;
				gameScene = new GameScene();
				gameScene->Initialize();
			}
		} else if (gameIsStart) {
			gameScene->Update();

			if (gameScene->GetClear()) {
				gameIsClear = true;
				gameIsStart = false;
			} else if (gameScene->GetOver()) {
				gameIsOver = true;
				gameIsStart = false;
			}

		} else if (gameIsClear) {

#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("GameClear");

			ImGui::End();
#endif // _DEBUG

			if (input->TriggerKey(DIK_SPACE)) {
				gameIsClear = false;
				gameIsTitle = true;
			}
		} else if (gameIsOver) {
#ifdef _DEBUG
			ImGui::Begin("GameState");
			ImGui::Text("GameOver");

			ImGui::End();
#endif // _DEBUG		
			if (input->TriggerKey(DIK_SPACE)) {
				gameIsOver = false;
				gameIsTitle = true;
			}
		}

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		if (gameIsTitle) {
			// タイトル

		} else if (gameIsStart) {
			gameScene->Draw();
		} else if (gameIsClear) {

		} else if (gameIsOver) {
		}

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
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	return 0;
}