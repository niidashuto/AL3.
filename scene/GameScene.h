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
#include <DirectXMath.h>

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

	enum PartId {
		Root,
		Spine,
		Chest,
		Head,
		ArmL,
		ArmR,
		Hip,
		LegL,
		LegR,
	};
  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//テクスチャハンドル
	uint_fast32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldtransform_[100];
	//ビュープロジェクション
	ViewProjection viewProjection_;
	int32_t value_ = 0;
	float translationValX_ = 10.0f;
	float translationValY_ = 10.0f;
	float translationValZ_ = 10.0f;

	float rotationValX_ = 0.785398f;
	float rotationValY_ = 0.785398f;
	float rotationValZ_ = 0.0f;

	float scaleValX_ = 5.0f;
	float scaleValY_ = 5.0f;
	float scaleValZ_ = 5.0f;
	//カメラ上方向の角度
	float viewAngle = 0.0f;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
