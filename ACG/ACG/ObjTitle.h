#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle :public CObj
{
public:
	CObjTitle() {}; 	//�R���X�g���N�^
	~CObjTitle() {};	//�f�X�g���N�^
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
};
