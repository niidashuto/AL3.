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
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};
