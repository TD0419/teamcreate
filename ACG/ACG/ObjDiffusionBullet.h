#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjDiffusionSource.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define CANNON 0
#define BOSS 1

//�I�u�W�F�N�g�F�g�U�e
class CObjDiffusionBullet :public CObj
{
public:
	CObjDiffusionBullet(float x, float y, int r);  //�R���X�g���N�^�i�C��p�j
	CObjDiffusionBullet(float x, float y, int r,CObjDiffusionSource* p);  //�R���X�g���N�^�i�{�X�p�j
	~CObjDiffusionBullet() {};	        //�f�X�g���N�^
	void Init();	                //�C�j�V�����C�Y
	void Action();	                //�A�N�V����
	void Draw();	                //�h���[

private:
	float m_px;						// �g�U�e(�G�p)X���W
	float m_py;						// �g�U�e(�G�p)Y���W
	float m_vx;						// X�������̃x�N�g��
	float m_vy;						// Y�������̃x�N�g��
	float m_speed;					//�g�U�e�̑��x
	float m_r;					//�g�U�e�̊p�x	
	int m_type;					//�{�X��p�ƖC��p�̋�ʗp

	CObjDiffusionSource* mp_base;//�ł��o�����̃|�C���^

	//�u���b�N�Ƃ̓����蔻��p�t���O
	bool m_hit_left;
	bool m_hit_right;
	bool m_hit_up;
	bool m_hit_down;
};