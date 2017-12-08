#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�e��
class CObjBullet :public CObj
{
public:
    CObjBullet(float x,float y,float r) ;		//�R���X�g���N�^
    ~CObjBullet() {};	            //�f�X�g���N�^
    void Init();	                //�C�j�V�����C�Y
    void Action();	                //�A�N�V����
    void Draw();	                //�h���[
private:
    float m_px;		// �e��X���W
    float m_py;		// �e��Y���W
    float m_vx;		// X�������̃x�N�g��
    float m_vy;		// Y�������̃x�N�g��
	float m_speed;	// �e�ۂ̑��x
	float m_r;	// �e�ۂ̊p�x	
	float m_scroll_x;	//�X�N���[���̒lX 
	float m_scroll_y;	// �X�N���[���̒lY
	
	//�u���b�N�Ƃ̓����蔻��p�t���O
	bool m_hit_left;	
	bool m_hit_right;	
	bool m_hit_up;		
	bool m_hit_down;	
};