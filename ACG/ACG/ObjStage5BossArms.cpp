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

	m_input_posture = false;//���͂��ꂽ�p�̏������@�ŏ��͕��Ă���

	m_posture = false;//���݂̎p�@�ŏ��͕��Ă���

	m_ani_frame_claw = 0;	//�`��A�j���[�V����(��)
	m_ani_max_time_claw = 10;//�A�j���[�V�����t���[������Ԋu�ő�l(��)
	m_ani_time_claw = 0;		//�A�j���[�V�����t���[������Ԋu(��)

	m_arm_lower_marker_px = 0.0f;	//�r�����낷�ʒu���������ǂ����Ƃ���X�ʒu
	m_armdown_time=0;//�r�����낷�Ƃ��̊Ǘ��p�^�C��

	m_hit_flag = false;

	m_hit_down = false;
	m_hit_up = false;
	m_hit_right = false;
	m_hit_left = false;


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
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}
}

//�A�N�V����
void CObjStage5BossArms::Action()
{
	//�����ʒu���X�V����
	UpdateInitial();

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//�A�[���^�C�v��1�̂Ƃ��A���C�g�A�[���p�̓����蔻��\��
	if (m_arms_type == RIGHT_ARM)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}
	//�A�[���^�C�v��2�̂Ƃ��A���t�g�A�[���p�̓����蔻��\��
	else if (m_arms_type == LEFT_ARM)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//�{�X�I�u�W�F�N�g�̎擾
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	if (objboss->GetAttackMode() == 3)//�U���p�^�[���R�Ȃ�
	{
		MoveShotAttack();
	}

	//�e�ۂƂ���������g�o��1���炷
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_arm_hp -= 1;
	}

	//�g�o��0�ɂȂ�����I�u�W�F�N�g����
	if (m_arm_hp == 0)
	{
		//�����ʒu�ɖ߂�
		m_px = m_initial_px;
		m_py = m_initial_py;
		//HP��߂�
		m_arm_hp = 10;
		return;
	}
	
	//�܂̃A�j���[�V��������-----------------------------------
	//���͎p�ƌ��݂̎p���Ⴄ
	if (m_posture != m_input_posture)
	{
		//�A�j���[�V��������Ԋu��i�߂�
		m_ani_time_claw++;
		//�A�j���[�V��������Ԋu�ő�l�ȏ�Ȃ�
		if (m_ani_time_claw >= m_ani_max_time_claw)
		{
			//�A�j���[�V��������Ԋu���O�ɂ���
			m_ani_time_claw = 0;
			//���͎p���J���Ă���
			if (m_input_posture == true)
			{
				//�`��t���[����߂�
				m_ani_frame_claw++;
			}
			//���͎p�����Ă���
			else
			{
				//�`��t���[����i�߂�
				m_ani_frame_claw--;
			}
		}
	}
	//�`��t���[�����O�Ȃ���Ă���
	if (m_ani_frame_claw == 0)
	{
		m_posture = false;
	}
	//�`��t���[���͂Q�Ȃ�J���Ă���
	if(m_ani_frame_claw == 1)
	{
		m_posture = true;
	}
	//---------------------------------------------------------
}

//�h���[
void CObjStage5BossArms::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�E�r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��1�̂Ƃ��̓��C�g�A�[����`��
	if (m_arms_type == RIGHT_ARM)
	{
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame_claw;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

	}

	//���r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��2�̂Ƃ��̓��t�g�A�[����`��
	if (m_arms_type == LEFT_ARM)
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame_claw;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left =   m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}

	//�r�����낷�ʒu�������Ȃ玦��
	if (m_arm_lower_marker_px > 0.0f)
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
				if (objmap->GetMap(map_x, map_y) == MAP_BLOCK)
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
		if (m_hit_flag == false)
		{
			//�{�X�̃I�u�W�F�N�g�������Ă���
			CObjStage5Boss* objbossbase = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
			objbossbase->LastWallHit();//���X�g�E�H�[���Ɠ����������̏���������

			m_hit_flag = true;//�ӂ炮��true��
		}
	}
	else
	{
		m_hit_flag = false;//�ӂ炮��false��
	}
}

//�g�U�e��łU��
//�����F�����܂ł̎���
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//�g�U�e�̌����쐬
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px + STAGE5_BOSS_ARMS_WIDTH_SIZE / 2.0f, m_py + STAGE5_BOSS_ARMS_HEIGHT_SIZE - 10.0f, limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//�u���b�N�𗎂Ƃ��U��
//����1:�ړ����Ăق����n�_��X�l
void CObjStage5BossArms::BlockDownAttackMove(float px)
{

	//HitBox�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	
	if (m_arms_type == RIGHT_ARM)//�E�r�Ȃ�
	{
		//�ړI�n�܂ł��ǂ���ĂȂ��@���@���X�g�E�H�[���Ɠ������Ă��Ȃ����
		if ((px - m_px) > 0.0f && ( hit->CheckObjNameHit(OBJ_LAST_WALL) == nullptr ) )
		{
			m_vx = 1.0f;
		}
		else
		{
			m_vx = 0.0f;//x�̈ړ���0�ɂ���
			ArmLowerAttack(m_px);//�r�����낷����������
		}
	}
	else //���r�Ȃ�
	{
		//�ړI�n�܂ł��ǂ���ĂȂ��@���@���X�g�E�H�[���Ɠ������Ă��Ȃ���
		if ((px - m_px) < 0.0f && (hit->CheckObjNameHit(OBJ_LAST_WALL) == nullptr))
		{
			m_vx = -1.0f;
		}
		else
		{
			m_vx = 0.0f;//x�̈ړ���0�ɂ���
			ArmLowerAttack(m_px);//�r�����낷����������
		}
	}
}

//�r�����낷�U��
//����1	float x:�r�����낷X�ʒu
void CObjStage5BossArms::ArmLowerAttack(float x)
{
	m_armdown_time++;

	//�{�X�I�u�W�F�N�g�������Ă���
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	if (objboss->GetAttackMode() == 1)//�U���p�^�[���P�Ȃ�
	{
		//�U�����n�܂�u�Ԃɘr�����낷X�ʒu�����߂�
		if (m_armdown_time == 1)
		{
			m_arm_lower_marker_px = x;
		}
		//120�t���[���̊ԂɎ�l����X�ʒu�Ɠ����ɂȂ�悤�Ƀx�N�g��X�𒲐�
		if (m_armdown_time < 120)
		{
			m_vx = (m_arm_lower_marker_px - m_px) / (120 - m_armdown_time);
		}
		//120�ȏ�Ȃ�r�����낷�U��������̂�X�ړ��ʂ�0.0f�ɂ���
		else
		{
			m_vx = 0.0f;
		}
	}

	//���Ԃ�120�ɂȂ�����r�����낷�U��������
	if (m_armdown_time >= 120)
	{
		//�r�����낷�ʒu�������Ȃ�
		m_arm_lower_marker_px = 0.0f;
		//�r�����낷
		m_vy = 10.0f;
	}
}

//�����ʒu���v�Z����
//�����ʒu���{�X(����)�̈ʒu�����ɋ��߂�
void CObjStage5BossArms::UpdateInitial()
{
	//�{�X(����)�̏����擾
	CObjStage5Boss* objstage5_boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	
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