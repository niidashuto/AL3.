#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"PrimitiveDrawer.h"
#include"AxisIndicator.h"
#include"Vector3.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	//3Dモデルの生成
	model_ = Model::Create();
	//ワールドトランスフォームの初期化
	worldtransform_.Initialize();
	//ビュープロジェクションの初期化
	viewprojection_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(100, 100);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	
}

void GameScene::Update() { debugCamera_->Update(); }

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
	//3Dモデル描画
	//model_->Draw(worldtransform_, viewprojection_, textureHandle_);
	model_->Draw(worldtransform_, debugCamera_->GetViewProjection(), textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	for (int i = 0; i < 8; i++) {
		//平行移動
		vertexMoved[i][0] = (affinMove[0][0] * ver[i][0]) + (affinMove[0][1] * ver[i][1]) +
		                    (affinMove[0][2] * ver[i][2]) + (affinMove[0][3] * ver[i][3]);
		vertexMoved[i][1] = (affinMove[1][0] * ver[i][0]) + (affinMove[1][1] * ver[i][1]) +
		                    (affinMove[1][2] * ver[i][2]) + (affinMove[1][3] * ver[i][3]);
		vertexMoved[i][2] = (affinMove[2][0] * ver[i][0]) + (affinMove[2][1] * ver[i][1]) +
		                    (affinMove[2][2] * ver[i][2]) + (affinMove[2][3] * ver[i][3]);
		vertexMoved[i][3] = (affinMove[3][0] * ver[i][0]) + (affinMove[3][1] * ver[i][1]) +
		                    (affinMove[3][2] * ver[i][2]) + (affinMove[3][3] * ver[i][3]);
		//拡大
		vertexScale[i][0] = (affinScale[0][0] * ver[i][0]) + (affinScale[0][1] * ver[i][1]) +
		                    (affinScale[0][2] * ver[i][2]) + (affinScale[0][3] * ver[i][3]);
		vertexScale[i][1] = (affinScale[1][0] * ver[i][0]) + (affinScale[1][1] * ver[i][1]) +
		                    (affinScale[1][2] * ver[i][2]) + (affinScale[1][3] * ver[i][3]);
		vertexScale[i][2] = (affinScale[2][0] * ver[i][0]) + (affinScale[2][1] * ver[i][1]) +
		                    (affinScale[2][2] * ver[i][2]) + (affinScale[2][3] * ver[i][3]);
		vertexScale[i][3] = (affinScale[3][0] * ver[i][0]) + (affinScale[3][1] * ver[i][1]) +
		                    (affinScale[3][2] * ver[i][2]) + (affinScale[3][3] * ver[i][3]);
		//回転
		vertexRotate[i][0] = (affinRotate[0][0] * ver[i][0]) + (affinRotate[0][1] * ver[i][1]) +
		                     (affinRotate[0][2] * ver[i][2]) + (affinRotate[0][3] * ver[i][3]);
		vertexRotate[i][1] = (affinRotate[1][0] * ver[i][0]) + (affinRotate[1][1] * ver[i][1]) +
		                     (affinRotate[1][2] * ver[i][2]) + (affinRotate[1][3] * ver[i][3]);
		vertexRotate[i][2] = (affinRotate[2][0] * ver[i][0]) + (affinRotate[2][1] * ver[i][1]) +
		                     (affinRotate[2][2] * ver[i][2]) + (affinRotate[2][3] * ver[i][3]);
		vertexRotate[i][3] = (affinRotate[3][0] * ver[i][0]) + (affinRotate[3][1] * ver[i][1]) +
		                     (affinRotate[3][2] * ver[i][2]) + (affinRotate[3][3] * ver[i][3]);

		

	}
	for (int i = 0; i < 4; i++) {
		//平行移動
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexMoved[i % 4][0], vertexMoved[i % 4][1], vertexMoved[i % 4][2]),
		  Vector3(vertexMoved[(i + 1) % 4][0], vertexMoved[(i + 1) % 4][1], vertexMoved[(i + 1) % 4][2]),
		  Vector4(255, 0, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexMoved[i % 4 + 4][0], vertexMoved[i % 4 + 4][1], vertexMoved[i % 4 + 4][2]),
		  Vector3(vertexMoved[(i + 1) % 4 + 4][0], vertexMoved[(i + 1) % 4 + 4][1],vertexMoved[(i + 1) % 4 + 4][2]),
		  Vector4(255, 0, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexMoved[i % 4][0], vertexMoved[i % 4][1], vertexMoved[i % 4][2]),
		  Vector3(vertexMoved[i % 4 + 4][0], vertexMoved[i % 4 + 4][1], vertexMoved[i % 4 + 4][2]),
		  Vector4(255, 0, 0, 255));
		//拡大
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexScale[i % 4][0], vertexScale[i % 4][1], vertexScale[i % 4][2]),
		  Vector3(vertexScale[(i + 1) % 4][0], vertexScale[(i + 1) % 4][1], vertexScale[(i + 1) % 4][2]),
		  Vector4(0, 0, 255, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexScale[i % 4 + 4][0], vertexScale[i % 4 + 4][1], vertexScale[i % 4 + 4][2]),
		  Vector3(vertexScale[(i + 1) % 4 + 4][0], vertexScale[(i + 1) % 4 + 4][1],
		    vertexScale[(i + 1) % 4 + 4][2]),
		  Vector4(0, 0, 255, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexScale[i % 4][0], vertexScale[i % 4][1], vertexScale[i % 4][2]),
		  Vector3(vertexScale[i % 4 + 4][0], vertexScale[i % 4 + 4][1], vertexScale[i % 4 + 4][2]),
		  Vector4(0, 0, 255, 255));
		//回転
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexRotate[i % 4][0], vertexRotate[i % 4][1], vertexRotate[i % 4][2]),
		  Vector3(vertexRotate[(i + 1) % 4][0], vertexRotate[(i + 1) % 4][1], vertexRotate[(i + 1) % 4][2]),
		  Vector4(0, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexRotate[i % 4 + 4][0], vertexRotate[i % 4 + 4][1], vertexRotate[i % 4 + 4][2]),
		  Vector3(vertexRotate[(i + 1) % 4 + 4][0], vertexRotate[(i + 1) % 4 + 4][1],vertexRotate[(i + 1) % 4 + 4][2]),
		  Vector4(0, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  Vector3(vertexRotate[i % 4][0], vertexRotate[i % 4][1], vertexRotate[i % 4][2]),
		  Vector3(vertexRotate[i % 4 + 4][0], vertexRotate[i % 4 + 4][1], vertexRotate[i % 4 + 4][2]),
		  Vector4(0, 255, 0, 255));
	}

	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(vertex[edgeList[i][0]], vertex[edgeList[i][1]], color);
	}
	
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

