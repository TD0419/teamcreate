#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�G
class CObjEnemy : public CObj
{
public:
	CObjEnemy(int x, int y); 	//�R���X�g���N�^
	~CObjEnemy(){}; //�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

   /*-----------------------�A�N�Z�T-------------------------*/
	float GetX() { return m_px; }    // X�ʒu���擾�֐�
	float GetY() { return m_py; }    // Y�ʒu���擾�֐�
	float GetVX() { return m_vx; }  // X�ړ����x�擾�֐�
	float GetVY() { return m_vy; }  // Y�ړ����x�擾�֐�
	void SetX(float x) { m_px = x; } // X�ʒu�ύX�֐�
	void SetY(float y) { m_py = y; } // Y�ʒu�ύX�֐�
	void SetVX(float vx) { m_vx = vx; } // X�ړ����x�ύX�֐�
	void SetVY(float vy) { m_vy = vy; } // Y�ړ����x�ύX�֐�
private:
	float m_px;	//�GX���W
	float m_py;	//�GY���W
	float m_vx;	//�GX�������̃x�N�g��
	float m_vy;	//�GY�������̃x�N�g��
	float m_r;  //�G�̉�]�p�x
	float m_posture;//�p��

	//�A�j���[�V�����֌W
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l

	int	  m_first_x;//�ŏ��ɐ������ꂽ�Ƃ��̃}�b�v��X�̗v�f��
	int	  m_first_y;//�ŏ��ɐ������ꂽ�Ƃ��̃}�b�v��Y�̗v�f��
};