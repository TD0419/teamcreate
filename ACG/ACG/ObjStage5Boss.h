#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��ʒu�̕␳�p�}�N��--------------------

//���r�ڑ��d�C(���r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_L_CORRECTION_HEIGHT   (2.0f)		//�c
#define ELECTRIC_L_CORRECTION_WIDTH	 (248.0f)		//��

//���r�ڑ��d�C(�E�r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_R_CORRECTION_HEIGHT  (15.0f)		//�c
#define ELECTRIC_R_CORRECTION_WIDTH	 (208.0f)		//��

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
};