
#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�C��
class CObjCannon :public CObj
{
public:
	CObjCannon(int x,int y); 	//�R���X�g���N�^
	~CObjCannon() {};			//�f�X�g���N�^
	void Init();				//�C�j�V�����C�Y
	void Action();				//�A�N�V����
	void Draw();				//�h���[
private:
	float m_px;	//X���W
	float m_py;	//Y���W
	float m_r;  //�C��̉�]�p�x
	int m_rec;	//�e�ۃ��L���X�g
	int m_map_x;	//�}�b�v�̗v�f�ԍ�
	int m_map_y;	//�}�b�v�̗v�f�ԍ�
};