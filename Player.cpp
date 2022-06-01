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
	//行列更新
	worldTransform_
};

void Player::Draw(){

};