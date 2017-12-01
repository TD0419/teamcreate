#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�U�e
class CObjDiffusionBullet :public CObj
{
public:
	CObjDiffusionBullet(float x, float y, int r);  //�R���X�g���N�^
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
	bool m_window_check;//��ʓ����ǂ����̃`�F�b�N�p true:��ʓ� false:��ʊO

};