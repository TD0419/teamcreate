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

	m_ani_frame = 0;	//�`��A�j���[�V����
	m_ani_max_time = 10;//�A�j���[�V�����t���[������Ԋu�ő�l
	m_ani_time = 0;		//�A�j���[�V�����t���[������Ԋu

	m_arm_lower_marker_px = 0.0f;	//�r�����낷�ʒu���������ǂ����Ƃ���X�ʒu

	m_hit_flag = false;

	//type�̒l��1�̂Ƃ����C�g�A�[���̓����蔻��\��
	if (m_arms_type == 1)
	{
		//�����蔻��pHitBox���쐬(HITBOX�̃T�C�Y�����p�ɕ␳�l�������Ă��܂�)
		//																���T�C�Y�␳�l						   �c�T�C�Y�␳�l
		Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
		
	}
	//type�̒l��1�̂Ƃ����t�g�A�[���̓����蔻��\��
	else if (m_arms_type == 2)
	{
		//�����蔻��pHitBox���쐬(HITBOX�̃T�C�Y�����p�ɕ␳�l�������Ă��܂�)
		//																���T�C�Y�␳�l						   �c�T�C�Y�␳�l
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}

}

//�A�N�V����
void CObjStage5BossArms::Action()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�A�[���^�C�v��1�̂Ƃ��A���C�g�A�[���p�̓����蔻��\��
	if (m_arms_type == 1)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}
	//�A�[���^�C�v��2�̂Ƃ��A���t�g�A�[���p�̓����蔻��\��
	else if (m_arms_type == 2)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}

	//�ړ�
	m_px += m_vx;

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

	//�e�ۂƂ���������g�o��1���炷
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_arm_hp -= 1;
	}

	//�g�o��0�ɂȂ�����I�u�W�F�N�g����
	if (m_arm_hp == 0)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�A�[������������HitBox�������B
		return;
	}
	
	//���͎p�ƌ��݂̎p���Ⴄ
	if (m_posture != m_input_posture)
	{
		//�A�j���[�V��������Ԋu��i�߂�
		m_ani_time++;
		//�A�j���[�V��������Ԋu�ő�l�ȏ�Ȃ�
		if (m_ani_time >= m_ani_max_time)
		{
			//�A�j���[�V��������Ԋu���O�ɂ���
			m_ani_time = 0;
			//���͎p���J���Ă���
			if (m_input_posture == true)
			{
				//�`��t���[����߂�
				m_ani_frame++;
			}
			//���͎p�����Ă���
			else
			{
				//�`��t���[����i�߂�
				m_ani_frame--;
			}
		}
	}
	//�`��t���[�����O�Ȃ���Ă���
	if (m_ani_frame == 0)
	{
		m_posture = false;
	}
	//�`��t���[���͂Q�Ȃ�J���Ă���
	if(m_ani_frame == 2)
	{
		m_posture = true;
	}

}

//�g�U�e��łU��
//�����F�����܂ł̎���
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//�g�U�e�̌����쐬
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px+ STAGE5_BOSS_ARMS_WIDTH_SIZE /2.0f, m_py+ STAGE5_BOSS_ARMS_HEIGHT_SIZE-10.0f,limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//�r�����낷�U��
//����1	float x	:�r�����낷X�ʒu
//����3 int time:
//�܂��쐬���Ȃ̂ő҂��Ă��������B
void CObjStage5BossArms::ArmLowerAttack(float x, int time)
{
	static float xx = x;
	//120�t���[���̊ԂɎ�l����X�ʒu�Ɠ����ɂȂ�悤�Ƀx�N�g��X�𒲐�
	if (time < 120)
	{
		m_vx = (xx - m_px) / (120 - time);
	}
	else
	{
		m_vx=0.0f;
	}

	//���Ԃ�120�ɂȂ�����r�����낷�U��������
	if (time >= 120)
	{
		m_arm_lower_marker_px = 0.0f;
		m_vy = 10.0f;
		//�u���b�N�I�u�W�F�N�g�������Ă���
		CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		bool hit_up, hit_down, hit_left, hit_right;
		//�u���b�N�Ƃ̓����蔻��
		objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE,
			&hit_up, &hit_down, &hit_left, &hit_right, &m_vx, &m_vy);

		
	}
	//���Ԃ�120�ɂȂ�܂Řr�����낷�ʒu���}�[�N����
	else
	{
		m_arm_lower_marker_px = xx;
	}
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
	if (m_arms_type == 1)
	{
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame;
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
	if (m_arms_type == 2)
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame;
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

		//�r���Ȃ̂ł����Ƃ��Ă��������B
		/*int map_x = (int)m_arm_lower_marker_px / BLOCK_SIZE;
		float 
		if (map_x < MAP_X_MAX)
		{
			for (int i = 0;i < MAP_Y_MAX; i++)
			{
				objmap->GetMap(map_x, i)
			}
		}*/
		//
		Draw::DrawHitBox(m_arm_lower_marker_px, 0.0f, 1000.0f, 100.0f, marker_color);
	}
}