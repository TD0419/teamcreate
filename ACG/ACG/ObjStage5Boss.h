#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"
#include "ObjStage5BossArms.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��ʒu�̕␳�p�}�N��--------------------

//���r�ڑ��d�C(���r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_L_CORRECTION_HEIGHT   (14.0f)		//�c
#define ELECTRIC_L_CORRECTION_WIDTH	 (226.0f)		//��

//���r�ڑ��d�C(�E�r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_R_CORRECTION_HEIGHT  (4.0f)		//�c
#define ELECTRIC_R_CORRECTION_WIDTH	 (185.0f)		//��

//�ዅ�̕`��ʒu�̕␳�l
#define EYE_CORRECTION_HEIGHT		 (102.0f)		//�c
#define EYE_CORRECTION_WIDTH	      (64.0f)		//��

//------------------------------------------

//�I�u�W�F�N�g�F��܃X�e�[�W�̃{�X
class CObjStage5Boss :public CObj
{
public:
	CObjStage5Boss(int x, int y);      //�R���X�g���N�^
	~CObjStage5Boss() {};	//�f�X�g���N�^
	void Init();	        //�C�j�V�����C�Y
	void Action();	        //�A�N�V����
	void Draw();	        //�h���[
private:
	float m_px;	 // ��܃{�XX���W
	float m_py;	 // ��܃{�XY���W
	float m_vx;  // ��܃{�XX���ړ��x�N�g��
	float m_vy;  // ��܃{�XY���ړ��x�N�g��

	int m_hp;    // ��܃{�X�̂g�o

	//�E�A�[���I�u�W�F�N�g�̏��
	CObjStage5BossArms* m_boos_arm_right;
	//���A�[���I�u�W�F�N�g�̏��
	CObjStage5BossArms* m_boos_arm_left;

	//��܃{�X�̍U�����[�h
	//0:�������Ȃ�
	//1:��l���̂���ʒu������ďォ��n�ʂ܂łɓ�����Ǝ��ʍU���𗎂Ƃ�
	//2:�ł��o���Ă��烉���_���Ȏ��Ԍo�߂Ŋg�U�e(15�x�ق�)�ɂȂ�e���o��
	//3:�{�X���g�������Ȃ����l���̈ʒu�ɒe������(���[�U�[)
	//4:3�n�_�ɓ�������|����I�u�W�F�N�g���o�������A���̌�n�ʂ�������U��������B
	int m_attack_mode;
};