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
	float m_Rock_x;	//��X���W
	float m_Rock_y;	//��Y���W

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��
	int m_ani_max_time;	//�A�j���[�V�����t���[������Ԋu�̍ő�l
	int m_ani_max_frame;//�`��t���[���̍ő�l

};