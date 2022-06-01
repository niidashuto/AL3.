#include"Player.h"
#include <cassert>

Player::Player(){};

Player::~Player(){};

void Player::Initialaze(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
};

void Player::Update() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};

	//�L�����N�^�[�̈ړ����x
	const float kCharactorSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_A)) {
		move = {-kCharactorSpeed, 0, 0};
	} else if (input_->PushKey(DIK_D)) {
		move = {kCharactorSpeed, 0, 0};
	}
	//�����_�ړ�(�x�N�g���̉��Z)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
	//�s��X�V
	worldTransform_
};

void Player::Draw(){

};