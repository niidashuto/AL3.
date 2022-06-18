#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"DebugCamera.h"
#include"Player.h"
#define PI 3.1415926535
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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//自キャラ
	Player* player_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	
	//ビュープロジェクション
	ViewProjection viewprojection_;
	//デバッグカメラ
	//DebugCamera* debugCamera_ = nullptr;
	//頂点
	Vector3 vertex[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
	  {0.0f, 0.0f, 5.0f},
      {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
	  {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };

	float vertexMoved[8][4] = {};
	float vertexScale[8][4] = {};
	float vertexRotate[8][4] = {};

	float ver[8][4] = {
	  {0.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 5.0f, 1.0f},
	  {0.0f, 0.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 0.0f, 1.0f},
      {5.0f, 5.0f, 0.0f, 1.0f},
	  {5.0f, 5.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 5.0f, 1.0f}
    };
	
	//辺
	int edgeList[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      {4, 5},
      {5, 6},
	  {6, 7},
      {7, 4},
      {0, 4},
      {1, 5},
      {2, 6},
      {3, 7}
    };
	float affinMove[4][4] = {
	  {1.0f, 0.0f, 0.0f, 5.0f},
	  {0.0f, 1.0f, 0.0f, 5.0f},
	  {0.0f, 0.0f, 1.0f, 5.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
	};
	float affinScale[4][4] = {
	  {2.0f, 0.0f, 0.0f, 0.0f},
	  {0.0f, 2.0f, 0.0f, 0.0f},
	  {0.0f, 0.0f, 2.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };
	double affinRotate[4][4] = {
	  {1.0f,0.0f,0.0f,0.0f},
      {0.0f,cos(PI / 4),-sin(PI/4),0.0f},
	  {0.0f, sin(PI / 4),cos(PI/4),0.0f},
	  {0.0f,0.0f,0.0f,1.0f}
	};
	Vector4 color = {1.0f, 1.0f, 1.0f, 1.0f};
	Vector4 color2 = {1.0f, 0.0f, 0.0f, 1.0f};
	Vector4 color3 = {0.0f, 1.0f, 0.0f, 1.0f};
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
};
