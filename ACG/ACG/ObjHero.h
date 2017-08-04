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

	/*-----------------------�A�N�Z�T-------------------------*/
	float GetX() { return m_Hero_x; }    // X�ʒu���擾�֐�
	float GetY() { return m_Hero_y; }    // Y�ʒu���擾�֐�
	float GetVX() { return m_Hero_vx; }  // X�ړ����x�擾�֐�
	float GetVY() { return m_Hero_vy; }  // Y�ړ����x�擾�֐�
	void SetX(float x) { m_Hero_x = x; } // X�ʒu�ύX�֐�
	void SetY(float y) { m_Hero_y = y; } // Y�ʒu�ύX�֐�
	void SetVX(float vx) { m_Hero_vx = vx; } // X�ړ����x�ύX�֐�
	void SetVY(float vy) { m_Hero_vy = vy; } // Y�ړ����x�ύX�֐�
private:
	float m_Hero_x;	 //��l��X���W
	float m_Hero_y;	 //��l��Y���W
	float m_Hero_vx; //��l��X�������̃x�N�g��
	float m_Hero_vy; //��l��Y�������̃x�N�g��

};