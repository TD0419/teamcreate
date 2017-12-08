#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�e��(�G�p)
class CObjEnemyBullet :public CObj
{
public:
	CObjEnemyBullet(float x, float y, float rad);  //�R���X�g���N�^
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
	float m_r;					//�e�ۂ̊p�x				
};