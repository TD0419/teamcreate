#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�Q
class CObjNeedleStand :public CObj
{
public:
	CObjNeedleStand(int x, int y);	// �R���X�g���N�^
	~CObjNeedleStand() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[
	void HeroHit();	//��l���Ƃ̓����蔻��
private:
	//map�̗v�f��
	int m_map_x;
	int m_map_y;
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY
};
