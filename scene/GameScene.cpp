#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	//3Dモデル生成
	model_ = Model::Create();
	// X,Y,Z方向のスケーリングを設定
	worldtransform_.scale_ = {5.0f, 5.0f, 5.0f};
	//X,Y,Z軸周りの回転角を設定
	worldtransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f,0.0f};
	//X,Y,Z軸周りの平行移動を設定
	worldtransform_.translation_ = {10.0f, 10.0f, 10.0f};
	//ワールドトランスフォームの初期化
	worldtransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {
	
	//値を含んだ文字列
	std::string strDebug = std::string("translation:(10.000000,10.000000,10.000000)");
	//デバッグテキストの表示
	debugText_->Print(strDebug, 50, 50, 1.0f);
	std::string strDebug2 = std::string("rotation:(0.785398,0.785398,0.000000)");
	//デバッグテキストの表示
	debugText_->Print(strDebug2, 50, 70, 1.0f);
	std::string strDebug3 = std::string("scale:(5.000000,5.000000,5.000000)");
	//デバッグテキストの表示
	debugText_->Print(strDebug3, 50, 90, 1.0f);
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
	// 3Dモデル描画
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
