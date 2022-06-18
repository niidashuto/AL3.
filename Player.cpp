#include"Player.h"
#include <cassert>

Player::Player(){};

Player::~Player(){};

void Player::Initialaze(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ワールド変換の初期化
	worldTransform_.Initialize();
};

void Player::Update() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターの移動速度
	const float kCharactorSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		move = {-kCharactorSpeed, 0, 0};
	} else if (input_->PushKey(DIK_D)) {
		move = {kCharactorSpeed, 0, 0};
	}
	//注視点移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	//移動量を行列に設定する
	Matrix4 matTrans = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	worldTransform_.matWorld_ *= matTrans;
	//行列更新
	worldTransform_.TransferMatrix();

	//デバッグ用
	debugText_->SetPos(50, 150);
	debugText_->Printf("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,worldTransform_.translation_.z);
};

void Player::Draw(ViewProjection viewprojection_) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewprojection_, textureHandle_);
};