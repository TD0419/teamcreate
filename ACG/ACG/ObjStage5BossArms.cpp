#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"

#include "ObjStage5BossArms.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//�X�e�[�W5�{�Xcpp����̕`��̓s���ŁAx��y�̌^��int����float�ɕύX���Ă��܂��B(�`��ōׂ����l���g����������)
CObjStage5BossArms::CObjStage5BossArms(float x, float y, int type)
{
	m_px = x;
	m_py = y;
	m_arms_type = type;//type = 1�c���C�g�A�[��  2�c���t�g�A�[��
}

//�C�j�V�����C�Y
void CObjStage5BossArms::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_arm_hp = 10; //��5�{�X�A�[���̂g�o(���ɂg�o��[10]�Ɛݒ�A���E�̃A�[������)

	m_ani_flag_claw = false;//�܂̊J�A�j���[�V���������Ȃ�

	m_arm_down_flag = false;//�����͗����Ă��Ȃ�

	m_ani_frame_claw = 0;	//�`��A�j���[�V����(��)
	m_ani_max_time_claw = 5;//�A�j���[�V�����t���[������Ԋu�ő�l(��)
	m_ani_time_claw = 0;		//�A�j���[�V�����t���[������Ԋu(��)

	m_arm_lower_marker_px = 0.0f;	//�r�����낷X�ʒu
	m_arm_down_marker = false;		//�r�����낷�ʒu�������Ȃ�

	m_armdown_time=0;//�r�����낷�Ƃ��̊Ǘ��p�^�C��

	m_time=0;			//�����݂񂮊Ǘ��p
	m_shot_hit_time = 0;//�e�ۂ��������������݂񂮂̕ۑ��p
	m_draw_flag=false;//�`��p�̃t���O
	m_damage_flag=false;//�_���[�W�t���O

	m_wall_hit_flag = false;

	m_block_hit_flag = false;
	m_initpos_flag = false;

	m_arm_down_attack_flag = false;	//�ŏ��͘r���낵�U���t���O��OFF

	//�r�̐ڑ������̓d����\������/���Ȃ����𔻒f���邽�߂̕ϐ�----------------------
	//�ڑ������̕`���ObjStage5Boss.cpp�ɂ�

	m_left_arm_move = false; //false�c�����ʒu���瓮���Ă��Ȃ��@true�c�����Ă���(���t�g�A�[���p)
	m_right_arm_move = false;//false�c�����ʒu���瓮���Ă��Ȃ��@true�c�����Ă���(���C�g�A�[���p)

	//-------------------------------------------------------------------------------

	//type�̒l��1�̂Ƃ����C�g�A�[���̓����蔻��\��
	if (m_arms_type == RIGHT_ARM)
	{
		//�����蔻��pHitBox���쐬(HITBOX�̃T�C�Y�����p�ɕ␳�l�������Ă��܂�)
		//																���T�C�Y�␳�l						   �c�T�C�Y�␳�l
		Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
		
	}
	//type�̒l��1�̂Ƃ����t�g�A�[���̓����蔻��\��
	else if (m_arms_type == LEFT_ARM)
	{
		//�����蔻��pHitBox���쐬(HITBOX�̃T�C�Y�����p�ɕ␳�l�������Ă��܂�)
		//																���T�C�Y�␳�l						   �c�T�C�Y�␳�l
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE-5.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}
}

//�A�N�V����
void CObjStage5BossArms::Action()
{
	m_time++;

	//�����ʒu���X�V����
	UpdateInitial();

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//������u���b�N�Ɠ������
	if (hit->CheckObjNameHit(OBJ_FALLING_BLOCK) != nullptr)
	{
		m_py -= m_vy;
		m_vx = 0.0f;
		m_vy = 0.0f;

		m_block_hit_flag = true;
	}
	//������u���b�N�Ɠ������Ă��Ȃ����
	else
		m_block_hit_flag = false;//������u���b�NHit�t���O��OFF�ɂ���

	//�r�����낷�U���t���O��ON�Ȃ�s��
	if (m_arm_down_attack_flag == true)
	{
		ArmLowerAttack();
		m_left_arm_move = true; //���t�g�A�[�����u�����ʒu���瓮���Ă���v������o��
		m_right_arm_move = true;//���C�g�A�[�����u�����ʒu���瓮���Ă���v������o��

		
	}
	//�{�X�I�u�W�F�N�g�̎擾
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	//�X�e�[�W�T�̃{�X�����݂��Ă�����
	if (objboss != nullptr)
	{
		if ( objboss->GetAttackMode() == 3)//�U���p�^�[���R�Ȃ�
		{
			MoveShotAttack();
		}
	}

	if ( m_arms_type == RIGHT_ARM )//�E�r
		m_arm_down_flag = objboss->GetArmDownFlagRight();
	else
		m_arm_down_flag = objboss->GetArmDownFlagLeft();
	
	//�r�������Ă�Ƃ� ���@�����ɖ߂��t���O���I�t�@�Ȃ�
	if ( m_arm_down_flag == true && m_initpos_flag == false )
	{
		//�e�ۂƂ���������g�o��1���炷
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			m_damage_flag = true;
			m_shot_hit_time = m_time;
			m_draw_flag = true;

			m_arm_hp -= 1;
		}
	}

	//�g�o��0�ɂȂ�����I�u�W�F�N�g�������ʒu�ɖ߂����߂̃t���O���I���ɂ���
	if (m_arm_hp <= 0)
	{
		//�r�̕����ʒu��2�{�̒��̓����ɂ����
		if (6100.0f < m_initial_px && m_initial_px + STAGE5_BOSS_ARMS_WIDTH_SIZE < 7000.0f)
		{
			//�r�̃t���O���X�V����
			if (m_arms_type == RIGHT_ARM)//�E�r
				objboss->SetArmDownFlagRight();
			else
				objboss->SetArmDownFlagLeft();

			m_initpos_flag = true;
		}
	}

	//�����ʒu�t���O���I���Ȃ�
	if (m_initpos_flag == true)
	{
		
		m_left_arm_move = false; //���t�g�A�[�����u�����ʒu���瓮���Ă��Ȃ��v������o��
		m_right_arm_move = false;//���C�g�A�[�����u�����ʒu���瓮���Ă��Ȃ��v������o��

		//�����ʒu�ɖ߂�
		m_px = m_initial_px;
		m_py = m_initial_py;

		//HP��߂�
		m_arm_hp = 10;
		m_initpos_flag = false;
		m_block_hit_flag = false;

		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
		return;
	}
	
	//�܂̃A�j���[�V��������-----------------------------------
	//�܂̃A�j���[�V����������
	if (m_ani_flag_claw == true)
	{
		//�A�j���[�V��������Ԋu��i�߂�
		m_ani_time_claw++;
		//�A�j���[�V��������Ԋu�ő�l�ȏ�Ȃ�
		if (m_ani_time_claw >= m_ani_max_time_claw)
		{
			//�A�j���[�V��������Ԋu��0�ɂ���
			m_ani_time_claw = 0;
			m_ani_frame_claw++;
			
		}
		if (m_ani_frame_claw == 5)
		{
			m_ani_frame_claw = 0;
			m_ani_flag_claw = false;
		}
	}
	//---------------------------------------------------------

	//�����蔻��X�V
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjStage5BossArms::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	float transparent[4] = { 0.0f,0.0f,0.0f, 0.0f };//�����ɕ`�悷��

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//�{�X�I�u�W�F�N�g�������Ă���
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);


	int time = m_time - m_shot_hit_time;

	//�_���[�W�������Ă���Ȃ�
	if (m_damage_flag == true)
	{
		if (time % 5 == 0)//5�t���[���Ɉ�x�t���O��؂�ւ���
			m_draw_flag = !m_draw_flag;
	}

	if (time > 15)//15�t���[���o�߂Ń_���[�W�t���O���I�t�ɂ���
	{
		//�t���O�̏�����
		m_damage_flag = false;
		m_draw_flag = false;
		//�^�C���̏�����
		m_time = 0;
		m_shot_hit_time = 0;
	}

	//���r�ڑ��d�C-------------------------------

	if (m_arms_type == LEFT_ARM)
	{
		//���r����																//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//�`��ʒu
		dst.m_top = objboss->GetPosY()+ ELECTRIC_L_CORRECTION_HEIGHT-objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX() ;
		dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//�`��
		//���t�g�A�[���������Ă���Ƃ��́A�����ɕ`�悷��B
		if (m_left_arm_move == true)//���t�g�A�[�����u�����Ă���v���肪�łĂ���Ƃ�
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, transparent, 0.0f);//�����ɕ`�悷��B
		}
		else//���t�g�A�[�����u�����ʒu(�`��)���瓮���Ă��Ȃ��v���肪�łĂ��� 
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);//�ʏ�̕`�������B
		}
	}
	else
	{
		//�E�r����
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ELECTRIC_HEIGHT;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//�`��ʒu

		dst.m_top = objboss->GetPosY() + ELECTRIC_L_CORRECTION_HEIGHT-objmap->GetScrollY();		
		dst.m_left = m_px - objmap->GetScrollX() - STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
		//�`��
		//���C�g�A�[���������Ă���Ƃ��́A�����ɕ`�悷��B
		if (m_right_arm_move == true)//���C�g�A�[�����u�����Ă���v���肪�łĂ���Ƃ�
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, transparent, 0.0f);//�����ɕ`�悷��B
		}
		else//���C�g�A�[�����u�����ʒu(�`��)���瓮���Ă��Ȃ��v���肪�łĂ���Ƃ�
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);//�ʏ�̕`�������B
		}
	}
	//�܂̊J�A�j���[�V����������Ƃ��̔z��
	//�v�f����m_ani_frame_claw
	int ani_claw[3] = { 1,2,0 };

	//�E�r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��1�̂Ƃ��̓��C�g�A�[����`��
	if (m_arms_type == RIGHT_ARM)
	{
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		
		if(m_ani_flag_claw == true)//�܂̊J�A�j���[�V����������Ȃ�
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*ani_claw[m_ani_frame_claw];
		else
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*1;

		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		
		//�`��̃t���O���I���Ȃ甒���\��
		if (m_draw_flag == true)
			Draw::Draw(GRA_STAGE5_BOSS_WHITE_ARMS, &src, &dst, color, 0.0f);
		else
			Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}

	//���r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��2�̂Ƃ��̓��t�g�A�[����`��
	if (m_arms_type == LEFT_ARM)
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		if (m_ani_flag_claw == true)//�܂̊J�A�j���[�V����������Ȃ�
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*ani_claw[m_ani_frame_claw];
		else
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE * 1;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left =   m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	
		//�`��̃t���O���I���Ȃ甒���\��
		if (m_draw_flag == true)
			Draw::Draw(GRA_STAGE5_BOSS_WHITE_ARMS, &src, &dst, color, 0.0f);
		else
			Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}

	//�r�����낷�ʒu�������Ȃ玦��
	if (m_arm_down_marker == true)
	{
		//�J���[���
		float marker_color[4] = { 1.0f,0.0f,0.0f,0.2f };

		//�r�����낷X�ʒu���}�b�v�ԍ��ɓ��Ă͂߂��Ƃ���X�ʒu
		int map_x = (int)(m_arm_lower_marker_px / BLOCK_SIZE);

		//�}�[�J�[���l�p�`�ŏo���̂ł��̍���
		float marker_h= WINDOW_SIZE_H;

		//X�ʒu���ő�l�����Ȃ�
		if (map_x < MAP_X_MAX)
		{
			//Y�ʒu��0�`�ő�l�܂Œ��ׂ�
			for (int map_y = 0; map_y < MAP_Y_MAX; map_y++)
			{
				//�u���b�N�����邩���ׂĂ���Ȃ炻�̈ʒu�܂ł������Ƃ���
				if (objmap->GetMap(map_x, map_y) == MAP_FALLING_BLOCK)
				{
					marker_h = map_y * BLOCK_SIZE-m_py;
					break;
				}
			}
		}
		//�}�[�J�[(�l�p�`)��\������
		Draw::DrawHitBox(m_arm_lower_marker_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(), marker_h, STAGE5_BOSS_ARMS_WIDTH_SIZE, marker_color);
	}
}

//�ړ����Ȃ���e�����U��
void CObjStage5BossArms::MoveShotAttack()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//���X�g�E�H�[���Ɠ������Ă����
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		//�Փ˂ӂ炮���I�t�Ȃ�
		if (m_wall_hit_flag == false)
		{
			//�{�X�̃I�u�W�F�N�g�������Ă���
			CObjStage5Boss* objbossbase = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
			if(objbossbase != nullptr)	//�X�e�[�W�T�̃{�X�����݂��Ă�����
				objbossbase->LastWallHit();//���X�g�E�H�[���Ɠ����������̏���������

			m_wall_hit_flag = true;//�ӂ炮��true��
		}
	}
	else
	{
		m_wall_hit_flag = false;//�ӂ炮��false��
	}
}

//�g�U�e��łU��
//�����F�����܂ł̎���
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//�g�U�e�̌����쐬
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px + STAGE5_BOSS_ARMS_WIDTH_SIZE / 2.0f, m_py + STAGE5_BOSS_ARMS_HEIGHT_SIZE, limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//�r�����낷�U��
//����1	float x		:�r�����낷X�ʒu
//����2 bool marker	:�r�����낷�ʒu���������ǂ���
void CObjStage5BossArms::ArmLowerAttack(float x,bool marker)
{
	//�r�����낷�U���t���O��ON�ɂ���
	m_arm_down_attack_flag = true;
	//�r�����낷�Ƃ��̊Ǘ��p�^�C�����O�ɂ���
	m_armdown_time = 0;
	//�r�����낷X�ʒu�����߂�
	m_arm_lower_marker_px = x;
	//�r�����낷�ʒu���������ǂ��������߂�
	m_arm_down_marker = marker;
	//

}
//�r�����낷�U��
void CObjStage5BossArms::ArmLowerAttack()
{
	m_armdown_time++;

	//120�t���[���̊ԂɎ�l����X�ʒu�Ɠ����ɂȂ�悤�Ƀx�N�g��X�𒲐�
	if (m_armdown_time < 120)
	{
		m_vx = (m_arm_lower_marker_px - m_px) / (float)(120 - m_armdown_time);
	}
	//120�ȏ�Ȃ�r�����낷�̂�X�ړ��ʂ�0.0f�ɂ���
	else
	{
		m_vx = 0.0f;
	}

	//���Ԃ�120�ɂȂ�����r�����낷�U��������
	if (m_armdown_time >= 120)
	{
		
		//�r�����낷�ʒu�������Ȃ�
		m_arm_down_marker = false;
		m_arm_lower_marker_px = 0.0f;

		//���C�g�A�[���܂��̓��t�g�A�[�����w�������ʒu���瓮�����A�x�������ʒu�̒�����
		//�r�����낵���ꍇ�Ɂu�r�������Ă���v������o������---------------------------
		if (m_right_arm_move == false)	//���C�g�A�[�����u�����ʒu���瓮���Ă��Ȃ��v���肪�o�Ă���Ƃ�
		{
			m_right_arm_move = true;	//�u���C�g�A�[���������Ă���v������o��
		}
		if(m_left_arm_move == false)	//���C�g�A�[�����u�����ʒu���瓮���Ă��Ȃ��v���肪�o�Ă���Ƃ�
		{
			m_left_arm_move = true;		//�u���t�g�A�[���������Ă���v������o��
		}
		//---------------------------------------------------------------------------------

		//�u���b�N�Ɠ�����܂�
		if (m_block_hit_flag == false)
		{
			//�r�����낷
			m_vy = 10.0f;
		}
		//�u���b�N�ɓ���������r�����낷�U������߂�
		else
		{
			m_arm_down_attack_flag = false;
		}
	}
}

//�����ʒu���v�Z����
//�����ʒu���{�X(����)�̈ʒu�����ɋ��߂�
void CObjStage5BossArms::UpdateInitial()
{
	//�{�X(����)�̏����擾
	CObjStage5Boss* objstage5_boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	
	//�X�e�[�W�T�̃{�X�����݂��Ă�����
	if (objstage5_boss != nullptr)
	{
		//���C�g�A�[���̎�
		if (m_arms_type == RIGHT_ARM)
		{	//										���{�X�̓��̂ɖ�������ʒu
			m_initial_px = (objstage5_boss->GetPosX() + STAGE5_BOSS_BODY_SIZE) + 60.0f;
			
		}
		//���t�g�A�[���̎�
		else
		{
			//										���{�X�̓��̂ɖ�������ʒu
			m_initial_px = (objstage5_boss->GetPosX() - STAGE5_BOSS_ARMS_WIDTH_SIZE) - 60.0f;
		
		}
		m_initial_py = objstage5_boss->GetPosY() - 100.0f;
	}
}

//���g(�r)��HIT_BOX����������
void CObjStage5BossArms::Delete()
{
	this->SetStatus(false);		//���g�ɍ폜���߂��o��
	Hits::DeleteHitBox(this);//���g�����L����HitBox���폜����
}