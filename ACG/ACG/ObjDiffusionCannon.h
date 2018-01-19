#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�U�e���ˑ��u
class CObjDiffusionCannon :public CObj
{
public:
	CObjDiffusionCannon(int x, int y);	// �R���X�g���N�^
	~CObjDiffusionCannon() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[

	//�A�N�Z�T
	float GetPosX(){ return m_px; }
	float GetPosY() { return m_py; }

private:
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY
	int m_time;   //�g�U�e�̏o��^�C��
	int m_map_x;	//�}�b�v�̗v�f�ԍ�
	int m_map_y;	//�}�b�v�̗v�f�ԍ�
};
