#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//------------------------------------------

//�I�u�W�F�N�g�F��܃X�e�[�W�̃{�X�̘r
class CObjStage5BossArms :public CObj
{
public:
	CObjStage5BossArms(int x, int y);      //�R���X�g���N�^
	~CObjStage5BossArms() {};	//�f�X�g���N�^
	void Init();	        //�C�j�V�����C�Y
	void Action();	        //�A�N�V����
	void Draw();	        //�h���[
private:
	float m_px;	 // ��܃{�X�̘rX���W
	float m_py;	 // ��܃{�X�̘rY���W
	float m_vx;  // ��܃{�X�̘rX���ړ��x�N�g��
	float m_vy;  // ��܃{�X�̘rY���ړ��x�N�g��

	int m_hp;    // ��܃{�X�̘r�̂g�o
};