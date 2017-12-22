#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;
//�R���X�g���N�^
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //��5�{�X�̂g�o(���ɂg�o��[100]�Ɛݒ�)

	m_right_arm_down_flag = false;
	m_left_arm_down_flag = false;

	//����������(�������Ă��Ȃ�)
	m_attack_mode = 0;

	m_lastwall_hit_flag=false;

	//�����݂񂮊Ǘ�
	m_time = 0;

	//�U���p�^�[��3
	m_attack3_flag = false;
	m_attack3_count = 0;

	//�U���p�^�[��4
	m_attack4_flag = false;
	m_attack4_scroll = 0.0f;
	m_block_down_flag = false;
	m_attack4_count = 0;

	//���S�t���O��OFF�ɂ���
	m_death_flag = false;

	//���y
	Audio::Start(BOSS);
	Audio::Stop(STAGE);

	m_ani_frame_death = 0;//�`��t���[��(���S)
	m_ani_time_death = 0;	//�A�j���[�V�����t���[������Ԋu(���S)
	m_ani_max_time_death =8;//�A�j���[�V�����t���[������Ԋu�ő�l(���S)

	//���E�̘r�쐬�[------------------
	//�E�r�I�u�W�F�N�g�쐬								���{�X�̓��̂ɖ�������ʒu
	m_boos_arm_right = new CObjStage5BossArms((m_px+ STAGE5_BOSS_BODY_SIZE)+60.0f, m_py - 100.0f, 1);
	Objs::InsertObj(m_boos_arm_right, OBJ_STAGE5_BOSS_ARMS, 8);

	//���r�I�u�W�F�N�g�쐬								���{�X�̓��̂ɖ�������ʒu		
	m_boos_arm_left = new CObjStage5BossArms((m_px-  STAGE5_BOSS_ARMS_WIDTH_SIZE)-60.0f, m_py - 100.0f, 2);
	Objs::InsertObj(m_boos_arm_left, OBJ_STAGE5_BOSS_ARMS, 8);

	//-------------------------------
	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//�A�N�V����
void CObjStage5Boss::Action()
{
	//�����Ă���Ƃ�
	if (m_death_flag == false)
	{
		m_time++;

		if (m_time > 10000)
			m_time = 0;

		//HitBox�X�V�p�|�C���^�[�擾
		CHitBox* hit = Hits::GetHitBox(this);

		switch (m_attack_mode)
		{
			//�������Ă��Ȃ����
			case 0:
			{
				if (m_time % 100 == 0)
				{
					//�������Ă��Ȃ��̂ōU�����[�h�������_���Ō��߂�
					m_attack_mode = 0;// GetRandom(1, 4);
					m_time = 0;
				}
				break;
			}
			//��l���̂���ʒu������ďォ��n�ʂ܂łɓ�����Ǝ��ʍU���𗎂Ƃ��U��
			case 1:
			{
				//��l���I�u�W�F�N�g�����擾
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				if (m_time == 200)
				{
					//�r�����낷�U��������(���r)
					m_boos_arm_left->ArmLowerAttack(objhero->GetPosX());
					m_left_arm_down_flag = true;
				}
				else if(m_time == 300)
				{
					//�r�����낷�U��������(�E�r)
					m_boos_arm_right->ArmLowerAttack(objhero->GetPosX());
					m_right_arm_down_flag = true;
				}

			if (m_time >= 400)
			{
				m_attack_mode = 3;//�r�����낵����͍U���R�ɂ���
			}
			break;
		}
		case 2:	//�ł��o���Ă��烉���_���Ȏ��Ԍo�߂Ŋg�U�e�ɂȂ�e���o���U��
		{
			if (m_time % 300 == 150)
			{
				m_boos_arm_left->DiffusionAttack(GetRandom(60, 180));
			}
			else if (m_time % 300 == 0)
			{
				m_boos_arm_right->DiffusionAttack(GetRandom(60, 180));
				m_attack_mode = 0;
			}
			break;
		}
		case 3://�{�X���g�������Ȃ����l���̈ʒu�ɒe������(���[�U�[)�U��
		{
			if (m_attack3_flag == false)//�t���O���I�t�Ȃ�
			{
				m_attack3_count = 0;
				m_vx = -1.0f;//�ړ��ʂ����ɐݒ�
				m_attack3_flag = true;//�t���O���I��
			}

			//60�t���[���Ɉ�x
			if (m_time % 60 == 0)
			{
				CObjEnemyBullet* p = new CObjEnemyBullet(m_px + EYE_CORRECTION_WIDTH + STAGE5_BOSS_EYE_SIZE / 2.0f, m_py + EYE_CORRECTION_HEIGHT + STAGE5_BOSS_EYE_SIZE / 2.0f);
				Objs::InsertObj(p, OBJ_ENEMY_BULLET, 11);

					m_attack3_count++;
				}

				if (m_attack3_count == 10)//10��U��������
				{
					m_attack3_flag = false;//�t���O���I�t
					m_vx = 0.0f;//�ړ����Ƃ߂�

					//�r���n�ʂɎc���Ă��Ȃ����
					if (m_right_arm_down_flag == false && m_left_arm_down_flag == false)
						m_attack_mode = 0;
					else
						m_attack_mode = 3;
				}
				//�r�ɂ��ړ��ʂ�n��
				if (m_right_arm_down_flag == false)	//�r�������Ă��Ȃ����
					m_boos_arm_right->SetVecX(m_vx);
				if (m_left_arm_down_flag == false)		//�r�������Ă��Ȃ����
					m_boos_arm_left->SetVecX(m_vx);
				break;
			}
			//3�n�_�ɓ�������|����I�u�W�F�N�g���o�������A���̌�n�ʂ�������U��������B
			case 4:
			{
				//�}�b�v�I�u�W�F�N�g�������Ă���
				CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

				//�U�����n�܂��Ĉ��̂�
				if (m_attack4_flag == false)
				{
					m_attack4_scroll = objmap->GetScrollX();//�X�N���[���lX�������Ă���
					m_attack4_flag = true;

					//�r���ړ������ė��Ƃ�

					//���r�����낷X�ʒu
					//�����l�̓��X�g�E�H�[���̉�
					float left_down_x = 94 * BLOCK_SIZE;
					//�E�r�����낷�ʒu
					//�����l�̓��X�g�E�H�[���̉�
					float right_down_x = 108 * BLOCK_SIZE;
					//���X�g�E�H�[���̉�����ʍ��[���傫��������
					//���낷�ʒu����ʍ��[�ɂ���
					if (left_down_x < m_attack4_scroll)
						left_down_x = m_attack4_scroll;
					//���X�g�E�H�[���̉�����ʉE�[��������������
					//���낷�ʒu����ʉE�[�ɂ���
					if (right_down_x > m_attack4_scroll + WINDOW_SIZE_W - STAGE5_BOSS_ARMS_WIDTH_SIZE)
						right_down_x = m_attack4_scroll + WINDOW_SIZE_W - STAGE5_BOSS_ARMS_WIDTH_SIZE;

					//�r�����낷�U��������
					m_boos_arm_left->ArmLowerAttack(left_down_x);
					m_boos_arm_right->ArmLowerAttack(right_down_x);
				}
			//���E�̘r���n�ʂ܂ŗ����Ă��邩�ǂ����𒲂ׂ�
			bool left_arm_down = m_boos_arm_left->GetBlockHit();
			bool right_arm_down = m_boos_arm_right->GetBlockHit();

			//�����̘r���n�ʂ܂ł����Ă����
			if (left_arm_down == true && right_arm_down == true)
			{
				m_block_down_flag = true;	//�u���b�N��������l�ɂ���
			}			
			else
			{
				m_block_down_flag = false;	//�u���b�N�������Ȃ��l�ɂ���
			}

			//������u���b�N�̎擾
			CObjFallingBlock* objfallingblock = (CObjFallingBlock*)Objs::GetObj(OBJ_FALLING_BLOCK);

			//������u���b�N���Ȃ����
			if (objfallingblock == nullptr)
				m_attack4_count++;

			if (m_attack4_count >= 120)//�u���b�N�̖�����Ԃ�120�t���[���o�߂����
			{
				//�r�̈ʒu�������ʒu�ɖ߂�
				m_boos_arm_left->SetInitPosFlagON();
				m_boos_arm_right->SetInitPosFlagON();

				objmap->CreateFallingBloack();//������u���b�N���쐬����
				m_attack4_flag = false;
				
				m_attack4_count = 0;		//�J�E���^�[�̏�����
				m_attack4_scroll = 0.0f;	//�X�N���[���ʂ̏�����
				m_attack_mode = 0;			
			}
			break;
		}
	}

		//�ړ�
		m_px += m_vx;

		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

		//���X�g�E�H�[���Ɠ���������
		if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
		{
			//���X�g�E�H�[���̃q�b�g�t���O�I�t�Ȃ�
			if (m_lastwall_hit_flag == false)
			{
				LastWallHit();//�q�b�g�������s��
				m_lastwall_hit_flag = true; //���X�g�E�H�[���̃q�b�g�t���O�I���ɂ���
			}
		}
		else
			m_lastwall_hit_flag = false;//���X�g�E�H�[���̃q�b�g�t���O�I�t

		//��l���̒e�ۂƂԂ�������g�o��-1�ɂ���
		//�e�ۂƂ���������g�o��1���炷
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			m_hp -= 1;
		}

		//�g�o��0�ɂȂ�����A
		//���r�����ł����AHIT_BOX�������A���S�t���O��ON�ɂ���
		if (m_hp == 0)
		{
			//���r����������
			m_boos_arm_right->Delete();
			m_boos_arm_left->Delete();

			//BOSS�����L����HitBox���폜����
			Hits::DeleteHitBox(this);	

			//���S�t���O��ON�ɂ���
			m_death_flag = true;

			return;
		}
	}
	//����ł���Ƃ�
	else
	{
		//�A�j���[�V�����t���[������Ԋu(���S)��i�߂�
		m_ani_time_death++;

		//�A�j���[�V�����t���[������Ԋu(���S)���ő�l�ȏ�Ȃ�
		if (m_ani_time_death >= m_ani_max_time_death)
		{
			//�`��t���[��(���S)��i�߂�
			m_ani_frame_death++;
			
			//�A�j���[�V�����t���[������Ԋu(���S)��0�ɂ���
			m_ani_time_death = 0;
		}
		
		//���S�A�j���[�V�������I�������玩�g������
		if (m_ani_frame_death == 16)
		{
			//�X�e�[�W�T�{�X���ŃA�j���[�V������̃I�u�W�F�N�g�쐬
			CObjAfterBossDisappearance* objafter_boss_disappearance = new CObjAfterBossDisappearance();
			Objs::InsertObj(objafter_boss_disappearance, OBJ_AFTER_BOSS_DISAPPEARANCE, 9);
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			return;
		}
	}

}

//�h���[
void CObjStage5Boss::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	float transparent[4] = { 0.0f,0.0f,0.0f, 0.0f };//�����ɕ`�悷��

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�����Ă���Ƃ��̕`��
	if(m_death_flag == false)
	{
		
		//����--------------------------------------
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);


		//�ዅ---------------------------------------
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_EYE_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_EYE_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY() + EYE_CORRECTION_HEIGHT;
		dst.m_left = m_px - objmap->GetScrollX() + EYE_CORRECTION_WIDTH;
		dst.m_right = dst.m_left + STAGE5_BOSS_EYE_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_EYE_SIZE;

		//��l���̃I�u�W�F�N�g�����擾
		CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

		//�ዅ����l���̕��֌����悤�ɂ���-----------------

		//��l�����������Ă���ꍇ�A�p�x�̌v�Z���s��
		float r = 0.0f;
		if (obj_hero != nullptr)
		{
			float hero_x = obj_hero->GetPosX() - m_px;		//��l���̈ʒu���X�擾
			float hero_y = obj_hero->GetPosY() - m_py;		//��l���̈ʒu���Y�擾
			r = atan2(-hero_y, hero_x)*180.0f / 3.14f;
			if (r < 0)
			{
				r = 360.0f - abs(r);
			}
		}
		//--------------------------------------------------

		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_EYE, &src, &dst, color, r);
	}
	//����ł���Ƃ��̕`��
	else
	{
		//�����A�j���[�V����--------------------------------
		//�؂���ʒu
		src.m_top = (m_ani_frame_death / 5) * 64.0f;
		src.m_left = (m_ani_frame_death % 5) * 64.0f;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
		//�`��
		Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
		//--------------------------------------------------
	}
}

//���X�g�E�H�[���Ɠ��������Ƃ��̏���
void CObjStage5Boss::LastWallHit()
{
	m_vx *= -1.0f;//�ړ��x�N�g�����t�ɂ���B
}

//�����_���Œl�����߂�֐�
//����1 int min	:�ŏ��l
//����2 int max	:�ő�l
//�߂�l int	:�ŏ��l�`�ő�l�̊Ԃ̐��l�������_���œn��(�ő�l�A�ŏ��l���܂�)
int CObjStage5Boss::GetRandom(int min, int max)
{
	//��񂾂�������������p
	static bool initialization = true;
	if (initialization == true)
	{
		srand((unsigned)time(NULL));  //�����n��̕ύX
		initialization = false;
	}
	return min + (int)(rand()*(max - min + 1.0f) / (1.0f + RAND_MAX));
}