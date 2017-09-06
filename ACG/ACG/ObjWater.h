#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FWater
class CObjWater :public CObj
{
public:
	CObjWater(int x, int y); 	//�R���X�g���N�^
	~CObjWater() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_px;	//X���W
	float m_py;	//Y���W

	//�A�j���[�V�����֌W
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	float m_water_gauge; // ���ʊǗ�
};