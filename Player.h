#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include"Vector3.h"
#include"Matrix4.h"
class Player {
  public:
	Player();

	~Player();

	void Initialaze(Model*model,uint32_t textureHandle);

	void Update();

	void Draw();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};
