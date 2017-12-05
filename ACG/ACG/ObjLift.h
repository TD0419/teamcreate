#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���t�g�̃X�s�[�h�}�N��
//�e�X�g�p
#define SPEED (1.5f)


//�I�u�W�F�N�g�F���t�g
class CObjLift :public CObj
{
public:
	CObjLift(int px, int py, int direction, float width_max, int mode);
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
	
	//���݂̈ړ�����
	//�O���E�F�P�����F�Q����F�R����
	int m_direction;

	//�����̈ړ�����
	//�O���E�F�P�����F�Q����F�R����
	//���t�g�̓������[�h���O�̂Ƃ����̕ϐ��͏����̈ړ��������w��(���������Ă��Ȃ����̈ړ�����)
	int m_initial_direction;

	float m_move_x;//�����ʒu���瓮��������X
	float m_move_y;//�����ʒu���瓮��������Y

	//���t�g�̓������[�h
	//�O���蓮���[�h(���R�X�C�b�`�ɓ��ĂĈړ����郂�[�h)
	//�P�����R�ړ����[�h(�����ʒuX����ő�X�ʒu�̊Ԃ������ړ�)
	//�Q�������ړ����[�h(��܂��͉��ɍs����ʊO�ɍs���Ə�Ȃ牺����A���Ȃ�ォ��o�Ă���)
	int m_move_mode;	

	//���𐧌䂷�邽�߂̕ϐ� �ړ����鎞�ɃJ�E���g�𑝂₵�A��b���Ƃɉ���炷
	int m_lift_audio_count;

	//�e�ړ����[�h(m_move_mode)�ɂ��ړ��֐�
	void ModeMove();
};
