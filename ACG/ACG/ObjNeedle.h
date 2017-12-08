#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�Q
class CObjNeedle:public CObj
{
public:
	CObjNeedle(int x, int y);	// �R���X�g���N�^
	~CObjNeedle() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[

private:
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY
	//�}�b�v�̗v�f��
	int m_map_x;
	int m_map_y;
	float m_needle_gauge; //�j�̒��ޑ��x
	int   m_time;         //�j�̒��񂾂��Ƃ̃^�C��
};
