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
	CObjRope(float arm_x, float arm_y, float mous_x, float mous_y);		// �R���X�g���N�^
	~CObjRope() {};					// �f�X�g���N�^
	void Init();					// �C�j�V�����C�Y
	void Action();					// �A�N�V����
	void Draw();					// �h���[
	void RopeDraw(float color[]);				// ���[�v�̕`��֐�
	bool GetCaughtFlag() { return m_caught_flag; }//���[�v�X�C�b�`�Ɉ��������������𒲂ׂ�p�̕ϐ���Ԃ�
	bool GetDelete() { return m_delete; }         //���[�v����ʊO�ɍs�������ǂ����𑗂�

private:
	float m_px;			// ���[�vX���W
	float m_py;			// ���[�vY���W
	float m_hero_arm_x;	//��l���̘r�̈ʒuX
	float m_hero_arm_y;	//��l���̘r�̈ʒuY
	float m_vx;			// X�������̃x�N�g��
	float m_vy;			// Y�������̃x�N�g��
	float m_moux;      //R�������Ƃ��̃}�E�X�̈ʒuX������ϐ�
	float m_mouy;      //R�������Ƃ��̃}�E�X�̈ʒuY������ϐ�
	float m_speed;		// ���ˑ��x
	float m_r;			// ���[�v�̊p�x	
	bool m_caught_flag; //���[�v�X�C�b�`�Ɉ��������������𒲂ׂ�p
	bool m_delete;      //���[�v�������Ă��邩�ǂ������ׂ�ϐ�

	//�u���b�N�Ƃ̓����蔻��p�t���O
	bool m_hit_left;
	bool m_hit_right;
	bool m_hit_up;
	bool m_hit_down;
};
