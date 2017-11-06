#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���t�g
class CObjLift :public CObj
{
public:
	CObjLift(int x, int y); // �R���X�g���N�^
	CObjLift(int px, int py, float vx, float vy, float width_max, float length_max);//�R���X�g���N�^
	~CObjLift() {};			// �f�X�g���N�^
	void Init();			// �C�j�V�����C�Y
	void Action();			// �A�N�V����
	void Draw();			// �h���[
	void HeroRide();		//�@��l��������Ă���Ƃ��̏���
	//�A�N�Z�T-----------------------------------------
	float GetVecX() { return m_vx; }	//�ړ��x�N�g��X��Ԃ�
	float GetVecY() { return m_vy; }	//�ړ��x�N�g��Y��Ԃ�

private:
	float m_px;		// ���t�gX���W
	float m_py;		// ���t�gY���W
	float m_vx;		// ���t�g�̈ړ��x�N�g��X
	float m_vy;		// ���t�g�̈ړ��x�N�g��Y
	float m_width_max;	//���E�̍ő�ړ���
	float m_length_max;	//�㉺�̍ő�ړ���

	float m_move_x;//����������X
	float m_move_y;//����������Y

};
