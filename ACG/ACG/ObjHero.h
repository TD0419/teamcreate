#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHero :public CObj
{
public:
	CObjHero(); 	//�R���X�g���N�^
	~CObjHero() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	float m_px;	//X���W
	float m_py;	//Y���W
	float m_vx;	//X�������̃x�N�g��
	float m_vy;	//Y�������̃x�N�g��
	float m_scroll_x;//X���X�N���[��
	float m_scroll_y;//Y���X�N���[��
	float m_r;//��l���̉�]�p�x
};