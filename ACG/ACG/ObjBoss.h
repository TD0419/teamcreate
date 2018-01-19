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

	void SetPosture(float ps) { m_posture = ps; };//�|�W�V�����̌����擾
	void SetHitF(bool wall_hit) { m_wall_hit_flag = wall_hit; }; //�ǂ̍����ɓ��������Ƃ��̃t���O
	
	//�A�N�Z�T
	void SetVecX(float x) { m_vx = x; };	//�x�N�g��X���擾�p
	void SetVecY(float y) { m_vy = y; };	//�x�N�g��Y���擾�p
	void SetPosX(float x) { m_px = x; };	//�|�W�V����X���擾�p
	void SetPosY(float y) { m_py = y; };	//�|�W�V����Y���擾�p
	float GetPosX() { return m_px; }		//�|�W�V����X��Ԃ�
	float GetPosY() { return m_py; }		//�|�W�V����Y��Ԃ�
		
private:
	float m_px;		 // �{�XX���W
	float m_py;		 // �{�XY���W
	float m_vx;		 // �{�XX�������̃x�N�g��
	float m_vy;		 // �{�XY�������̃x�N�g��
	float m_posture; // �p�� �E�F0.0f�@���F1.0f
	float m_speed;	 // ���x

	int m_hp;		 // �{�X�̂g�o
	int m_time;			//�����݂񂮊Ǘ��p
	int m_shot_hit_time;//�e�ۂ��������������݂񂮂̕ۑ��p

	bool m_draw_flag;//�`��p�̃t���O
	
	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	int m_ani_time_walk;		//�����A�j���[�V�����t���[�����슴�o
	int m_ani_time_throw;		//������A�j���[�V�����t���[�����슴�o
	int m_ani_frame_walk;		//�`��t���[�������p(�������[�V����)
	int m_ani_frame_throw;		//�`��t���[��������p(�����郂�[�V����)

	int m_ani_walk_max_time;	//�A�j���[�V������������Ԋu�ő�l
	int m_ani_throw_max_time;	//�A�j���[�V���������铮��Ԋu�ő�l
	bool m_ani_throw_start_flag;//������A�j���[�V�����J�n�t���O
	bool m_throw_bullet_flag;   //������R�R�i�b�c�̐���t���O
	bool m_wall_hit_flag;		//�{�X���ǂɓ��������Ƃ��̃t���O
	bool m_down_check_flag;		//�����̃`�F�b�N�����邩�ǂ����̃t���O

	bool m_damage_flag;	//�_���[�W���󂯂Ă��邩�ǂ����̃t���O

};
