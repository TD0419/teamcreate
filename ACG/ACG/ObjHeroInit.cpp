
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjHero.h"

void CObjHero::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //�E����0.0f ������1.0f
	m_r = 0.0f;
	m_radius = 768.0f;
	m_gravity_flag = true;		// true:�d�͂��� false:�d�͂Ȃ�
	m_goal_flag = false;		// true:�S�[������ false:�S�[�����Ă��Ȃ�

	m_mous_x = 0.0f;            //�}�E�X�̈ʒuX
	m_mous_y = 0.0f;		    //�}�E�X�̈ʒuX
	m_rope_moux = 0.0f;			//R���������Ƃ��̃}�E�X�̈ʒuX
	m_rope_mouy = 0.0f;		    //R���������Ƃ��̃}�E�X�̈ʒuY

	m_bullet_control = false;	//�e�۔��ː���p
	m_rope_control = false;		//���[�v���ː���p
	m_rope_ani_con = false;
	m_rope_delete = false;    //���[�v�����������ǂ������ׂ�ϐ�
	m_rope_delete_r_kye = false;//�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	m_hero_die_flag = false;

	m_hero_die_water = false;
	m_hero_die_enemy = false;
	m_hero_die_screen_out = false;
	m_screen_out = 0.0f;
	
	m_ladder_updown = 0;
	m_ladder_ani_updown = 0;

	m_ani_max_time_move = 6;	//move�A�j���[�V�����Ԋu��
	m_ani_time_move = 0;
	m_ani_frame_move = 1;		//move�Î~�t���[���������ɂ���
	m_rope_delete_control = false;
	m_ani_max_time_ladders = 9; //ladders�A�j���[�V�����Ԋu�� 
	m_ani_time_ladders = 0;
	m_ani_frame_ladders = 0;	//ladders�Î~�t���[���������ɂ���

	m_ani_max_time_rope = 25; //rope�A�j���[�V�����Ԋu�� 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope�Î~�t���[���������ɂ���

	m_ani_max_time_water_die = 25;         //��l�������ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_water_die = 0;
	m_ani_frame_water_die = 0;//��l�������ɓ����������Î~�t���[���������ɂ���

	m_ani_max_time_enemy_die = 18;         //��l�����G�ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_enemy_die = 0;
	m_ani_frame_enemy_die = 0;//��l�����G�ɓ����������Î~�t���[���������ɂ���

	m_block_type = 0;//��l���̂����̃u���b�N���

					 //�u���b�N�Ƃ̏Փ˂������(�ꏊ)�m�F�p
	m_hit_up = false;
	m_hit_left = false;
	m_hit_right = false;
	m_hit_down = false;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, ELEMENT_PLAYER, OBJ_HERO, 1);
}
