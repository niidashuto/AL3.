#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>

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
	
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
	
	
	//キャラクターの大元
	worldtransform_[PartId::Root].Initialize();
    //脊髄----------------------------------------------------------------------
    worldtransform_[PartId::Spine].translation_ = {0,4.5f,0};
	worldtransform_[PartId::Spine].parent_ = &worldtransform_[PartId::Root];
	worldtransform_[PartId::Spine].Initialize();
	//上半身---------------------------------------------------------------------
	//胸
	worldtransform_[PartId::Chest].Initialize();
	worldtransform_[PartId::Chest].parent_ = &worldtransform_[PartId::Spine];
	worldtransform_[PartId::Chest].translation_={0, 0, 0};
	//頭
	worldtransform_[PartId::Head].Initialize();
	worldtransform_[PartId::Head].parent_ = &worldtransform_[PartId::Chest];
	worldtransform_[PartId::Head].translation_ = {0, 4.5, 0};
	//左上
	worldtransform_[PartId::ArmL].Initialize();
	worldtransform_[PartId::ArmL].parent_ = &worldtransform_[PartId::Chest];
	worldtransform_[PartId::ArmL].translation_ = {-4.5, 0, 0};
	//右上
	worldtransform_[PartId::ArmR].Initialize();
	worldtransform_[PartId::ArmR].parent_ = &worldtransform_[PartId::Chest];
	worldtransform_[PartId::ArmR].translation_ = {4.5, 0, 0};
	//下半身---------------------------------------------------------------------
	//尻
	worldtransform_[PartId::Hip].Initialize();
	worldtransform_[PartId::Hip].parent_ = &worldtransform_[PartId::Spine];
	worldtransform_[PartId::Hip].translation_ = {0, -4.5, 0};
	//左足
	worldtransform_[PartId::LegL].Initialize();
	worldtransform_[PartId::LegL].parent_ = &worldtransform_[PartId::Hip];
	worldtransform_[PartId::LegL].translation_ = {-4.5, -4.5, 0};
	//右足
	worldtransform_[PartId::LegR].Initialize();
	worldtransform_[PartId::LegR].parent_ = &worldtransform_[PartId::Hip];
	worldtransform_[PartId::LegR].translation_ = {4.5, -4.5, 0};
	viewProjection_.eye = {0, 0, -50};
	//カメラ注視点座標を設定
	viewProjection_.target = {0, 0, 0};
	//カメラ上方向ベクトルを設定
	viewProjection_.up = {0,1,0};
	//カメラ垂直方向視野角を設定
	//viewProjection_.fovAngleY = XMConvertToRadians(10.0f);
	//アスペクト比を設定
	//viewProjection_.aspectRatio = 1.0f;
	
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	
	
}

void GameScene::Update() {

	//視点移動処理
	{
		//視点の移動のベクトル
		XMFLOAT3 move = {0, 0, 0};

		//視点の移動速度
		const float kCharacterSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move = {-kCharacterSpeed,0,0};
		} else if (input_->PushKey(DIK_RIGHT)) {
			move = {kCharacterSpeed,0,0};
		}
		//視点移動(ベクトルの加算)
		worldtransform_[PartId::Root].translation_.x += move.x;
		worldtransform_[PartId::Root].translation_.y += move.y;
		worldtransform_[PartId::Root].translation_.z += move.z;
		worldtransform_[PartId::Root].UpdateMatrix();
		worldtransform_[PartId::Spine].UpdateMatrix();
		worldtransform_[PartId::Chest].UpdateMatrix();
		worldtransform_[PartId::Head].UpdateMatrix();
		worldtransform_[PartId::ArmL].UpdateMatrix();
		worldtransform_[PartId::ArmR].UpdateMatrix();
		worldtransform_[PartId::Hip].UpdateMatrix();
		worldtransform_[PartId::LegL].UpdateMatrix();
		worldtransform_[PartId::LegR].UpdateMatrix();
		//デバッグ用表示
		debugText_->SetPos(50, 150);
		debugText_->Printf(
		  "Character:(%f,%f,%f)", worldtransform_[PartId::Root].translation_.x,
		  worldtransform_[PartId::Root].translation_.y,
		  worldtransform_[PartId::Root].translation_.z);
	}
	//上半身回転処理
	{
		//上半身の回転速度
		const float kChestRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			worldtransform_[PartId::Chest].rotation_.y -= kChestRotSpeed;
		} else if (input_->PushKey(DIK_I)) {
			worldtransform_[PartId::Chest].rotation_.y += kChestRotSpeed;
		}
	}
	//下半身回転処理
	{
		//下半身の回転速度
		const float kHipRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			worldtransform_[PartId::Hip].rotation_.y -= kHipRotSpeed;
		} else if (input_->PushKey(DIK_K)) {
			worldtransform_[PartId::Hip].rotation_.y += kHipRotSpeed;
		}
	}
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
	
	//model_->Draw(worldtransform_[PartId::Root], viewProjection_, textureHandle_);
	//model_->Draw(worldtransform_[PartId::Spine], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::Chest], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::Head], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::ArmL], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::ArmR], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::Hip], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::LegL], viewProjection_, textureHandle_);
	model_->Draw(worldtransform_[PartId::LegR], viewProjection_, textureHandle_);
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
