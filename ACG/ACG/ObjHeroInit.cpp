
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
	m_fall_speed_max = 26.0f;	// ��l���̍ő嗎���X�s�[�h

	m_mous_x = 0.0f;            //�}�E�X�̈ʒuX
	m_mous_y = 0.0f;		    //�}�E�X�̈ʒuX
	m_rope_moux = 0.0f;			//R���������Ƃ��̃}�E�X�̈ʒuX
	m_rope_mouy = 0.0f;		    //R���������Ƃ��̃}�E�X�̈ʒuY

	m_count = 0;	//�J�E���^�[�̏�����
	m_before_shot_time = -50;	//�e�̔��ˎ��Ԃ̏������i�X�^�[�g����ɑłĂ�悤�ɑ傫�߂̕��̐��ŏ������j

	m_bullet_control = true;	//�e�۔��ː���p
	m_rope_control = false;		//���[�v���ː���p
	m_rope_ani_con = false;
	m_rope_delete = false;    //���[�v�����������ǂ������ׂ�ϐ�
	m_rope_delete_r_kye = false;//�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	m_hero_die_flag = false;

	m_hero_die_water = false;
	m_hero_die_enemy = false;
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

	m_ani_max_time_rope = 4; //rope�A�j���[�V�����Ԋu�� 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope�Î~�t���[���������ɂ���

	m_ani_max_time_water_die = 25;         //��l�������ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_water_die = 0;
	m_ani_frame_water_die = 0;//��l�������ɓ����������Î~�t���[���������ɂ���

	m_ani_max_time_enemy_die = 18;         //��l�����G�ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_enemy_die = 0;
	m_ani_frame_enemy_die = 0;//��l�����G�ɓ����������Î~�t���[���������ɂ���

	l_jump = false;

	m_block_type = 0;//��l���̂����̃u���b�N���
	m_block_type_up = 0;

	//�u���b�N�Ƃ̏Փ˂������(�ꏊ)�m�F�p
	m_hit_up = false;
	m_hit_left = false;
	m_hit_right = false;
	m_hit_down = false;

	pendulum_data.gravity = 0.98f;//�d�͉����x��ݒ�(�{����9.8�ɂ��������ǌv�Z�����������̂������Ȃ�)
	pendulum_data.length = 0.0f;	//�U��q�̒���
	pendulum_data.pretend_width = 0.0f;//�ӂ蕝
	pendulum_data.time = 0.0f;//����(����)
	pendulum_data.find_value_flag = true;//�l�����߂邩�ǂ����̃t���ONO
	
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, 46, 112, ELEMENT_PLAYER, OBJ_HERO, 1);
}
