#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��O�X�e�[�W�̃{�X
class CObjStage3Boss :public CObj
{
public:
	CObjStage3Boss(int x ,int y);       //�R���X�g���N�^
	~CObjStage3Boss() {};	//�f�X�g���N�^
	void Init();	        //�C�j�V�����C�Y
	void Action();	        //�A�N�V����
	void Draw();	        //�h���[
private:
	float m_x;	 // ��O�{�XX���W
	float m_y;	 // ��O�{�XY���W
	float m_vx;  // ��O�{�XX�������̃x�N�g��
	float m_vy;  // ��O�{�XY�������̃x�N�g��

	int m_hp;    // ��O�{�X�̂g�o

};