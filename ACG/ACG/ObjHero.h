#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y); 	//�R���X�g���N�^
	~CObjHero() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void Scroll();	//�X�N���[�������̊֐�

private:
	float m_px;	//X���W
	float m_py;	//Y���W
	float m_vx;	//X�������̃x�N�g��
	float m_vy;	//Y�������̃x�N�g��
	float m_r;//��l���̉�]�p�x
	float m_mouse_angle;	//�}�E�X�̊p�x

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//����ł���u���b�N�̎�ނ��m�F�p
	int m_block_type;
};