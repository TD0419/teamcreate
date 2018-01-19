#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�e��(�G�p)
class CObjEnemyBullet :public CObj
{
public:
	CObjEnemyBullet(float x, float y);				//�R���X�g���N�^�iBOSS�p��l���̕����ցj
	~CObjEnemyBullet() {};	        //�f�X�g���N�^
	void Init();	                //�C�j�V�����C�Y
	void Action();	                //�A�N�V����
	void Draw();	                //�h���[
	
private:
	float m_px;						// �e��(�G�p)X���W
	float m_py;						// �e��(�G�p)Y���W
	float m_vx;						// X�������̃x�N�g��
	float m_vy;						// Y�������̃x�N�g��
	float m_speed;					//�e�ۂ̑��x
	float m_r;						//�e�ۂ̊p�x
	
	bool m_delete_flag;//�폜���邩�ǂ����̃t���O

	//�u���b�N�Ƃ̓����蔻��p
	bool m_hit_up;
	bool m_hit_right;
	bool m_hit_left;
	bool m_hit_down;
};