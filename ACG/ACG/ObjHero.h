#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y,int remaining); 		//�R���X�g���N�^
	~CObjHero() {};					//�f�X�g���N�^
	void Init();					//�C�j�V�����C�Y
	void Action();					//�A�N�V����
	void Draw();					//�h���[
	void Scroll();					//�X�N���[�������̊֐�
	void LandingCheck();			//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
	bool HitUpCheck(int obj_name);	//�w�肵���I�u�W�F�N�g�̏㑤�Ɠ������Ă��邩����ׂ�֐�

	//�A�N�Z�T------------------------------------------
	void SetVecX(float x) { m_vx = x; };							//�x�N�g��X���Z�b�g����
	void SetVecY(float y) { m_vy = y; };							//�x�N�g��Y���Z�b�g����
	void SetPosX(float x) { m_px = x; };							//�|�W�V����X���Z�b�g����
	void SetPosY(float y) { m_py = y; };							//�|�W�V����Y���Z�b�g����
	void SetHitDown(bool b) { m_hit_down = b; };					//�q�b�g�_�E�����Z�b�g����
	void SetLaddersUpdown(int x) { m_ladder_updown = x; };			//�͂����̏�̏󋵂��Z�b�g����
	void SetLaddersAniUpdown(int x) { m_ladder_ani_updown = x; };	//�͂����̏���Ă�󋵂��Z�b�g����
	void SetLadderJump(int x) { m_ladder_jump=x; };					//�͂����̏�̏󋵂��Z�b�g����
	float GetPosX() { return m_px; }								//�|�W�V����X��Ԃ�
	float GetPosY() { return m_py; }								//�|�W�V����X��Ԃ�
	float GetVecX() { return m_vx; }								//�x�N�g��X��n��
	float GetVecY() { return m_vy; }								//�x�N�g��Y��n��
	float GetPosture() { return m_posture; }						//���̎�l���̎p����n��
	float GetRopeDeleteAniCon() { return m_rope_delete_ani_con; }   //�A�j���[�V�����p���[�v�����������ǂ������Ǘ�����ϐ���n��
	int GetBlockType() { return m_block_type; }						//���̃u���b�N(����ł���)����n��

private:
	float m_px;		//X���W
	float m_py;		//Y���W
	float m_vx;		//X�������̃x�N�g��
	float m_vy;		//Y�������̃x�N�g��
	float m_posture;//�p�� //�E�F0.0���@���F1.0��
	float m_r;		//��l���̉�]�p�x
	int   m_block_type;//����ł�u���b�N�̒l��ۑ�����
	int   m_black_radius; //��l�������񂾎��A���肩�獕�����锼�a�̕ϐ�

	float m_mous_x;	    //�}�E�X�̈ʒuX
	float m_mous_y;     //�}�E�X�̈ʒuX
	float m_rope_moux;	//R���������Ƃ��̃}�E�X�̈ʒuX
	float m_rope_mouy;  //R���������Ƃ��̃}�E�X�̈ʒuX
	  
	bool  m_bullet_control;       //�e�۔��ː���p
	bool  m_rope_control;	      //���[�v���ː���p
	bool  m_rope_ani_con;         //���[�v�A�j���[�V��������
	bool  m_rope_delete;          //���[�v�����������ǂ������ׂ�ϐ�
	bool  m_rope_delete_ani_con;  //�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	bool  m_hero_die_water;       //��l�������ɂ����������ǂ����𒲂ׂ�ϐ��i���j
	bool  m_hero_die_enemy;		  //��l�����G�ɂ����������ǂ����𒲂ׂ�ϐ��i���j

	int m_ladder_updown; //�͂���Hit�Ǘ�
	int m_ladder_ani_updown; //�͂����A�j���[�V�����Ǘ�
	int m_ladder_jump;			//�͂����W�����v�Ǘ�

	//----------------------�A�j���[�V�����֌W
	int m_ani_time_move;	    //�ړ��A�j���[�V�����t���[�����슴�o
	int m_ani_frame_move;	    //�ړ��`��t���[��
	int m_ani_frame_stop_move;  //�~�܂������̈ړ��`��𒲐�
	int m_ani_max_time_move;    //�ړ��A�j���[�V��������Ԋu�ő�l

	int m_ani_time_ladders;		//�͂����A�j���[�V�����t���[�����슴�o
	int m_ani_frame_ladders;	//�͂����`��t���[��
	int m_ani_max_time_ladders; //�͂����A�j���[�V��������Ԋu�ő�l

	int m_ani_time_rope;	    //���[�v�A�j���[�V�����t���[�����슴�o
	int m_ani_frame_rope;	    //���[�v�`��t���[��
	int m_ani_max_time_rope;    //���[�v�A�j���[�V��������Ԋu�ő�l

	int m_ani_time_water_die;         //��l�������ɂ����������A�j���[�V�����t���[�����슴�o
	int m_ani_frame_water_die;        //��l�������ɂ�����������l���`��t���[��
	int m_ani_max_time_water_die;     //��l�������ɂ�����������l���A�j���[�V��������Ԋu�ő�l
	
	int m_ani_time_enemy_die;         //��l�����G�ɂ����������A�j���[�V�����t���[�����슴�o
	int m_ani_frame_enemy_die;        //��l�����G�ɂ�����������l���`��t���[��
	int m_ani_max_time_enemy_die;     //��l�����G�ɂ�����������l���A�j���[�V��������Ԋu�ő�l

	//------------------------------------------

	int m_remaining;//�c�@�Ǘ�

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	
};