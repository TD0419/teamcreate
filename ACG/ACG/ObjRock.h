#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��
class CObjRock :public CObj
{
public:
	CObjRock(float x, float y); 	//�R���X�g���N�^
	~CObjRock() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_rock_x;	//��X���W
	float m_rock_y;	//��Y���W
};