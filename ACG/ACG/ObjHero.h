#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define SHOT_INTERVAL (50.0f)	//�e�����Ԋu

//�U��q�̓���������Ƃ��Ɏg���f�[�^
struct Pendulum
{
	float length;		//�U��q�̒���
	float pretend_width;//�ӂ蕝
	float time;			//����(����)
	float gravity;		//�d�͉����x
};

//�I�u�W�F�N�g�F��l��
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y,int remaining); 		//�R���X�g���N�^
	~CObjHero() {};					//�f�X�g���N�^
	void Init();					//�C�j�V�����C�Y
	void Action();					//�A�N�V����
	void Shot();                //���C�֐�
	void RopeThrow();			//Rope �X���[�֐�


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
	void SetGravityFlag(bool flag) { m_gravity_flag = flag; }		//��l���ɏd�͂����邩�ǂ����̃t���O true:����� false:����Ȃ�
	float GetPosX() { return m_px; }								//�|�W�V����X��Ԃ�
	float GetPosY() { return m_py; }								//�|�W�V����X��Ԃ�
	float GetVecX() { return m_vx; }								//�x�N�g��X��n��
	float GetVecY() { return m_vy; }								//�x�N�g��Y��n��
	float GetPosture() { return m_posture; }						//���̎�l���̎p����n��
	bool GetRopeAniCon() { return m_rope_ani_con; }					//���[�v�̃A�j���[�V�������n�܂��Ă��邩�ǂ�����Ԃ�
	bool GetRopeDeleteRKey() { return m_rope_delete_r_kye; }		//�A�j���[�V�����p���[�v�����������ǂ������Ǘ�����t���O��n��
	int GetBlockType() { return m_block_type; }						//���̃u���b�N(����ł���)����n��
	int GetLadderUpdown() { return m_ladder_updown; }				//��l�����͂����̂ǂ̃A�j���[�V����������Ԃ�

	void HeroGoal() { m_goal_flag = true; m_radius = 0.0f; }		//��l���̃S�[�������؂�ւ��֐�(�S�[���t���O�𗧂Ă�)

private:
	void CircleDraw(float add_radius,float color[4],int type);		// ���S���ƃS�[�����p�̉~��`�悷��֐�

private:
	float m_px;		//X���W
	float m_py;		//Y���W
	float m_vx;		//X�������̃x�N�g��
	float m_vy;		//Y�������̃x�N�g��
	float m_posture;//�p�� //�E�F0.0���@���F1.0��
	float m_r;		//��l���̉�]�p�x
	int m_remaining;//�c�@�Ǘ�
	int   m_block_type;//����ł�u���b�N�̒l��ۑ�����
	float m_fall_speed_max;//��l���̗����X�s�[�h�ő呬�x
	float m_radius; //��l�������񂾎��A���肩�獕�����锼�a�̕ϐ�
	bool  m_gravity_flag; // ��l���̏d�͗����t���O true:�d�͂��� false:�d�͂Ȃ�
	bool  m_goal_flag;	  // �S�[���t���O true:�S�[������ false:�S�[�����Ă��Ȃ�		
	float m_mous_x;	    //�}�E�X�̈ʒuX
	float m_mous_y;     //�}�E�X�̈ʒuY
	float m_rope_moux;	//R���������Ƃ��̃}�E�X�̈ʒuX
	float m_rope_mouy;  //R���������Ƃ��̃}�E�X�̈ʒuY
	Pendulum pendulum_data;	//�U��q�̓���������Ƃ��Ɏg���f�[�^
	//�[�[�[�[����n---------
	int	  m_count;				  //����p�̃J�E���^�[
	int	  m_before_shot_time;	  //�Ō�ɒe�����������Ԃ�ۑ�����	
	bool  m_bullet_control;       //�e�۔��ː���p
	bool  m_rope_control;	      //���[�v���ː���p
	bool  m_rope_ani_con;         //���[�v�A�j���[�V��������
	bool  m_rope_delete;          //���[�v�����������ǂ������ׂ�ϐ�
	bool  m_rope_delete_r_kye;    //�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	bool  m_rope_delete_control;  //���[�v�����������̔���𐧌䂷��ϐ�
	bool  m_hero_die_flag;        //��l�������񂾎��̍����𐧌䂷�邽�߂̃t���O
	//-----------
	//-------Hero�����ʌn---------
	bool   m_hero_die_water;       //��l�������ɂ����������ǂ����𒲂ׂ�ϐ��i���j
	bool   m_hero_die_enemy;	   //��l�����G�ɂ����������ǂ����𒲂ׂ�ϐ��i���j
	bool   m_hero_die_screen_out;  //��l������ʊO�i���������j�ɍs�������ǂ������ׂ�ϐ��i���j�i�V�[���ڍs�p�j
	float  m_screen_out;           //��l�������񂾎��̂��ʒu���L�����邽�߂̕ϐ�
	//-----------------
	int m_ladder_updown; //�͂���������Ă��邩�ǂ����𒲂ׂ�i0�A����ĂȂ��P�A����Ă���@2�A�͂�������肫��Ƃ��j
	int m_ladder_ani_updown; //�͂����A�j���[�V�����Ǘ�

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

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	// ��l���̏��
	enum HeroState
	{
		Normal,		// �ʏ�
		Die,		// ���S
		Clear,		// �N���A
	};
};