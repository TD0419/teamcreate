#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���[�v
class CObjRope :public CObj
{
public:
	CObjRope(int x, int y); // �R���X�g���N�^
	~CObjRope() {};			// �f�X�g���N�^
	void Init();			// �C�j�V�����C�Y
	void Action();			// �A�N�V����
	void Draw();			// �h���[
private:
	float m_px;			// ���[�vX���W
	float m_py;			// ���[�vY���W
	float m_vx;			// X�������̃x�N�g��
	float m_vy;			// Y�������̃x�N�g��
	float m_speed;		// ���ˑ��x
	float m_r;			// ���[�v�̊p�x	
	bool m_caught_flag; //���[�v�X�C�b�`�Ɉ��������������𒲂ׂ�p

};
