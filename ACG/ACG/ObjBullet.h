#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�e��
class CObjBullet :public CObj
{
public:
    CObjBullet(int x, int y) ;  //�R���X�g���N�^
    ~CObjBullet() {};	            //�f�X�g���N�^
    void Init();	                //�C�j�V�����C�Y
    void Action();	                //�A�N�V����
    void Draw();	                //�h���[
private:
    float m_px;	// �e��X���W
    float m_py;	// �e��Y���W
    float m_vx;	// X�������̃x�N�g��
    float m_vy;	// Y�������̃x�N�g��
	float m_speed;					//����
	float m_angle;					//�e�ۂ̊p�x			

};