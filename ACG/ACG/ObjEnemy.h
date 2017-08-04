#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjEnemy : public CObj
{
public:
	CObjEnemy(); 	//�R���X�g���N�^
	~CObjEnemy(){}; //�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

   /*-----------------------�A�N�Z�T-------------------------*/
	float GetX() { return m_Enemy_x; }    // X�ʒu���擾�֐�
	float GetY() { return m_Enemy_y; }    // Y�ʒu���擾�֐�
	float GetVX() { return m_Enemy_vx; }  // X�ړ����x�擾�֐�
	float GetVY() { return m_Enemy_vy; }  // Y�ړ����x�擾�֐�
	void SetX(float x) { m_Enemy_x = x; } // X�ʒu�ύX�֐�
	void SetY(float y) { m_Enemy_y = y; } // Y�ʒu�ύX�֐�
	void SetVX(float vx) { m_Enemy_vx = vx; } // X�ړ����x�ύX�֐�
	void SetVY(float vy) { m_Enemy_vy = vy; } // Y�ړ����x�ύX�֐�
private:
	float m_Enemy_x;	//�GX���W
	float m_Enemy_y;	//�GY���W
	float m_Enemy_vx;	//�GX�������̃x�N�g��
	float m_Enemy_vy;	//�GY�������̃x�N�g��

};