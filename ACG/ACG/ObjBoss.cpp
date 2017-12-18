#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBoss::CObjBoss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
	m_vx = -1.0f;		// �ړ��x�N�g��
	m_hp = 20;			//�{�X�̂g�o
	m_posture = 1.0f;	// ������
	m_speed = 3.0f;		// ���x

	m_ani_time_walk = 0;
	m_ani_time_throw = 0;

	m_ani_frame_walk = 1;		//�Î~�t���[���������ɂ���(�������[�V����)
	m_ani_frame_throw = 1;		//�Î~�t���[���������ɂ���(�����郂�[�V����)
	m_ani_walk_max_time = 10;	//�����A�j���[�V�����Ԋu��
	m_ani_throw_max_time = 5;	//������A�j���[�V�����Ԋu��

	m_ani_throw_start_flag = false;//������A�j���[�V�����J�n�t���O false=�I�t ture=�I��
	m_throw_bullet_flag = false;   //������R�R�i�b�c�̐���t���O
	m_down_check_flag = false;//����������ŏ��͂��Ȃ��ɐݒ�

	m_wall_hit_flag = false;
	// block�Ƃ̏Փˊm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py + 100.0f, 150.0f, 150.0f, ELEMENT_ENEMY, OBJ_BOSS, 1);

	Audio::Stop(STAGE);
	Audio::Start(BOSS);

}

//�A�N�V����
void CObjBoss::Action()
{

	m_ani_time_walk++;
	m_ani_time_throw++;

	//�����A�j���[�V�����̊Ԋu�Ǘ�(������A�j���[�V�����t���O���n�e�e�̂Ƃ�)
	if (m_ani_throw_start_flag == false && (m_ani_time_walk > m_ani_walk_max_time))
	{
		m_ani_frame_walk += 1;
		m_ani_time_walk = 0;
	}
	//������A�j���[�V�����̊Ԋu�Ǘ�(������A�j���[�V�����t���O���n�m�̂Ƃ�)
	else if (m_ani_throw_start_flag == true && (m_ani_time_throw > m_ani_throw_max_time))
	{
		m_ani_frame_throw += 1;
		m_ani_time_throw = 0;
	}

	//(�����A�j���[�V����)�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɂ���
	if (m_ani_frame_walk == 10)
	{
		m_ani_frame_walk = 1;
	}

	//(�A�j���[�V����)�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɂ���
	if (m_ani_frame_throw == 13)
	{
		m_ani_throw_start_flag = false;
		m_ani_frame_throw = 1;
		m_throw_bullet_flag = false;
	}


	// �G�e�ۍ쐬
	if (m_ani_frame_throw == 9)//�r���グ���Ƃ�
	{
		//�R�R�i�b�c�𓊂���B
		if (m_throw_bullet_flag == false) //�����
		{
			//���y�X�^�[�g
			Audio::Start(GORILLATHROW);
			if (m_posture == 0.0f)    // �E�����̎�
			{
				CObjEnemyBullet* objenemy = new CObjEnemyBullet(m_px + 80.0f, m_py + 11.0f);
				Objs::InsertObj(objenemy, OBJ_ENEMY_BULLET, 10);
			}
			else if (m_posture == 1.0f)// �������̎�
			{
				CObjEnemyBullet* objenemy = new CObjEnemyBullet(m_px + 64.0f, m_py + 11.0f);
				Objs::InsertObj(objenemy, OBJ_ENEMY_BULLET, 10);
			}
		}
		m_throw_bullet_flag = true;
	}

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);


	if (m_posture == 0.0f)		// �E�����Ȃ�
		m_vx = m_speed;			// �E�ɐi��
	else if (m_posture == 1.0f) // �������Ȃ�
		m_vx = -m_speed;		// ���ɐi��


//���C
	m_vx += -(m_vx * 0.098f);

	m_vy = 9.8f / (16.0f);//���R����

	//������A�j���[�V�������͓����Ȃ��悤�ɂ���
	if (m_ani_throw_start_flag == false)
	{
		//�ړ�
		m_px += m_vx;
		m_py += m_vy;
	}

	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	objblock->BlockHit(&m_px, &m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	if (m_hit_down == false)//���Ƀu���b�N���Ȃ����
	{
		if (m_down_check_flag = true)
		{
			m_posture = 1.0f;//�������ɂ���
			m_px -= m_vx;		//�ړ��O�̈ʒu�ɖ߂�
		}
	}
	else //��x���n������
	{
		m_down_check_flag = true;//����������I���ɂ���
	}

	if (m_hit_right == true)    // �u���b�N�̉E���ɓ������Ă����� 
	{
		m_posture = 0.0f;		// �E�����ɂ���

		//�������[�V�������łȂ���΁i���d������h���j
		if (m_ani_throw_start_flag == false)
		{
			//������A�j���[�V�����J�n�t���O���n�m�ɂ���
			m_ani_throw_start_flag = true;
		}

	}
	else if (m_hit_left == true || m_wall_hit_flag == true)// �u���b�N�̍����ɓ������Ă�����
	{
		//�E�����̎���
		if (m_posture == 0.0f)
		{
			m_posture = 1.0f;//�������ɂ���

			//�������[�V�������łȂ���΁i���d������h���j
			if (m_ani_throw_start_flag == false)
			{
				//�ǃq�b�g�t���O��false�ɂ���B
				m_wall_hit_flag = false;

				//������A�j���[�V�����J�n�t���O���n�m�ɂ���
				m_ani_throw_start_flag = true;
			}
		}
	}

	CObjDoor* objdoor = (CObjDoor*)Objs::GetObj(OBJ_DOOR);

	//�e�ۂƂ���������HP-1
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		Audio::Start(LANDING);
		m_hp -= 1;
	}

	//���Ƃ������
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		CObjLastWall* objlastwall = (CObjLastWall*)Objs::GetObj(OBJ_LAST_WALL);

		m_px = objlastwall->GetPosX() - BOSS_SIZE_WIDTH;//���̍�����
	}
	// �̗͂�0�ȉ��Ȃ�
	if (m_hp <= 0)
	{
		Hits::DeleteHitBox(this);	//BOSS�����L����HitBox�ɍ폜����
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		return;
	}

	if (m_posture == 1.0f)
	{
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px + 30.0f, m_py + 100.0f);
	}
	else
	{
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px + 20.0f, m_py + 100.0f);
	}
}

//�h���[
void CObjBoss::Draw()
{

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	//�����A�j���[�V����
	if (m_ani_throw_start_flag == false)
	{
		src.m_top = 0.0f;
		src.m_left = m_ani_frame_walk * 96.0f - 96.0f;
		src.m_right = src.m_left + 96.0f;
		src.m_bottom = src.m_top + 72.0f;
	}
	//������A�j���[�V����
	else if (m_ani_throw_start_flag == true)
	{
		src.m_top = 82.0f;
		src.m_left = m_ani_frame_throw * 96.0f - 96.0f;
		src.m_right = src.m_left + 96.0f;
		src.m_bottom = src.m_top + 72.0f;
	}

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = BOSS_SIZE_WIDTH * m_posture + m_px - objmap->GetScrollX();
	dst.m_right = (BOSS_SIZE_WIDTH - BOSS_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + BOSS_SIZE_HEIGHT + 2;

	//�`��
	Draw::Draw(GRA_BOSS, &src, &dst, color, 0.0f);

}