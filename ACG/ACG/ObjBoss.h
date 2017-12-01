#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�X
class CObjBoss :public CObj
{
	public:
		CObjBoss(int x,int y);  //�R���X�g���N�^
		~CObjBoss() {};			//�f�X�g���N�^
		void Init();	        //�C�j�V�����C�Y
		void Action();	        //�A�N�V����
		void Draw();	        //�h���[
		
	private:
		float m_px;		 // �{�XX���W
		float m_py;		 // �{�XY���W
		float m_vx;		 // �{�XX�������̃x�N�g��
		float m_vy;		 // �{�XY�������̃x�N�g��
		float m_posture; // �p�� �E�F0.0f�@���F1.0f
		float m_speed;	 // ���x

		int m_hp;		 // �{�X�̂g�o

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_wall_hit_flag;		//�{�X���ǂɓ��������Ƃ��̃t���O
	int m_ani_time_walk;		//�����A�j���[�V�����t���[�����슴�o
	int m_ani_time_throw;		//������A�j���[�V�����t���[�����슴�o
	int m_ani_frame_walk;		//�`��t���[�������p(�������[�V����)
	int m_ani_frame_throw;		//�`��t���[��������p(�����郂�[�V����)

	int m_ani_walk_max_time;	//�A�j���[�V������������Ԋu�ő�l
	int m_ani_throw_max_time;	//�A�j���[�V���������铮��Ԋu�ő�l
	bool m_ani_throw_start_flag;//������A�j���[�V�����J�n�t���O
};
