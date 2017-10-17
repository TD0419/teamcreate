#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�e��
class CObjBullet :public CObj
{
public:
    CObjBullet(float x,float y) ;		//�R���X�g���N�^
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
	bool m_window_check;//��ʓ����ǂ����̃`�F�b�N�p true:��ʓ� false:��ʊO

};