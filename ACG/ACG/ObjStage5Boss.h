#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"
#include "ObjStage5BossArms.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��ʒu�̕␳�p�}�N��--------------------

//���r�ڑ��d�C(���r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_L_CORRECTION_HEIGHT   (14.0f)		//�c
#define ELECTRIC_L_CORRECTION_WIDTH	 (226.0f)		//��

//���r�ڑ��d�C(�E�r����)�̕`��ʒu�̕␳�l
#define ELECTRIC_R_CORRECTION_HEIGHT  (4.0f)		//�c
#define ELECTRIC_R_CORRECTION_WIDTH	 (185.0f)		//��

//�ዅ�̕`��ʒu�̕␳�l
#define EYE_CORRECTION_HEIGHT		 (102.0f)		//�c
#define EYE_CORRECTION_WIDTH	      (64.0f)		//��

//------------------------------------------

//�I�u�W�F�N�g�F��܃X�e�[�W�̃{�X
class CObjStage5Boss :public CObj
{
public:
	CObjStage5Boss(int x, int y);      //�R���X�g���N�^
	~CObjStage5Boss() {};	//�f�X�g���N�^
	void Init();	        //�C�j�V�����C�Y
	void Action();	        //�A�N�V����
	void Draw();	        //�h���[

	void LastWallHit();//���X�g�E�H�[���Ɠ��������Ƃ��̏���

	//�A�N�Z�T
	float GetPosY() { return m_py; }
	float GetPosX() { return m_px; }
	void SetVecX(float x) { m_vx = x; }	
	int GetAttackMode() { return m_attack_mode; }
	bool GetBlockDownFlag() { return m_block_down_flag; }
	void SetArmDownFlagRight() { m_right_arm_down_flag = false; }
	void SetArmDownFlagLeft() { m_left_arm_down_flag = false; }
	bool GetArmDownFlagRight() { return m_right_arm_down_flag; }
	bool GetArmDownFlagLeft() { return m_left_arm_down_flag; }
	bool GetBossDeathFlag() { return m_death_flag; }
	//�U��4�J�E���^�[��300�t���[���o�߂�����������
	bool GetBlockRetuenFlag() { return m_progress_atk4_count; }
	

private:
	float m_px;	 // ��܃{�XX���W
	float m_py;	 // ��܃{�XY���W
	float m_vx;  // ��܃{�XX���ړ��x�N�g��
	float m_vy;  // ��܃{�XY���ړ��x�N�g��
	int m_hp;    // ��܃{�X�̂g�o

	int m_arm_break_count;//�r����ꂽ�񐔂��L�^����

	int m_attack3_count;//�U���p�^�[��3�p�̃J�E���^�[
	bool m_attack3_flag;//�U���p�^�[��3�p�̃t���O
	bool m_attack4_flag;//�U���p�^�[��4�p�̃t���O
	bool m_block_down_flag;//�u���b�N�𗎂Ƃ����ǂ����̃t���O
	float m_attack4_scroll;//�U���p�^�[���S�p�̃X�N���[���l
	int m_attack4_count;//�U���p�^�[��3�p�̃J�E���^�[

	//�E�A�[���I�u�W�F�N�g�̏��
	CObjStage5BossArms* m_boos_arm_right;
	//���A�[���I�u�W�F�N�g�̏��
	CObjStage5BossArms* m_boos_arm_left;

	bool m_death_flag;//���S�t���O�@true=���S���Ă���	false=�����Ă���

	//��܃{�X�̍U�����[�h
	//0:�������Ȃ�
	//1:��l���̂���ʒu������ďォ��n�ʂ܂łɓ�����Ǝ��ʍU���𗎂Ƃ�
	//2:�ł��o���Ă��烉���_���Ȏ��Ԍo�߂Ŋg�U�e(15�x�ق�)�ɂȂ�e���o��
	//3:�{�X���g�������Ȃ����l���̈ʒu�ɒe������(���[�U�[)
	//4:3�n�_�ɓ�������|����I�u�W�F�N�g���o�������A���̌�n�ʂ�������U��������B
	int m_attack_mode;

	int m_time;//�U���̃^�C�~���O�Ǘ��p

	//�r�������Ă��邩�ǂ����̃t���O
	bool m_right_arm_down_flag;
	bool m_left_arm_down_flag;

	bool m_lastwall_hit_flag;//���X�g�E�H�[���Ƃ̏����p�t���O
	
	bool m_progress_atk4_count;//�U��4�p�̃J�E���^�[��120�t���[���o�߂������ǂ����𔻕ʂ��邽�߂̕ϐ�

	int m_ani_frame_death[4];	//�`��t���[��(���S)						�ڍׂ�Init�֐��̒��̏���������
	int m_ani_time_death[4];	//�A�j���[�V�����t���[������Ԋu(���S)		�ڍׂ�Init�֐��̒��̏���������
	int m_ani_max_time_death[2];//�A�j���[�V�����t���[������Ԋu�ő�l(���S)�ڍׂ�Init�֐��̒��̏���������

	//�{�X�̎��S�A�j���[�V���������p�֐�(�A�N�V�����p)
	bool ActionDeathAnimation();
	//�{�X�̎��S�A�j���[�V���������p�֐�(�h���[�p)
	void DrawDeathAnimation();

	//�����_���Œl�����߂�֐�
	int GetRandom(int min, int max);
};