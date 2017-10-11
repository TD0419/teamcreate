#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(int x, int y)
{
	//�}�b�v�̗v�f������
	m_map_x = x;
	m_map_y = y;
	m_px = x * ENEMY_SIZE;
	m_py = y * ENEMY_SIZE;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_posture = 0.0f; //�E����1.0f ������0.0f

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 4; //�A�j���[�V�����Ԋu��

	m_speed = 0.5f;	//�����X�s�[�h

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, ENEMY_SIZE,ENEMY_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�}�b�v��������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//��ʓ������ׂ�
	m_window_check = WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE);

	//��ʊO�Ȃ����
	if (m_window_check == false)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B

		//�߂��Ă����Ƃ��ɕ�������悤�ɂ���
		objmap->SetMapCreate(m_map_x, m_map_y, true);
		
		return;
	}
	
	//�ړ�----------------------------------------------

	//���Ɍ����Ă���Ȃ獶�ֈړ�����
	if (m_posture == 0.0)
	{
		m_vx -= m_speed;
		m_ani_time += 1;
	}
	//�E�Ɍ����Ă���Ȃ�E�ֈړ�����
	else
	{
		m_vx += m_speed;
		m_ani_time += 1;
	}

	//�A�j���[�V�����̊Ԋu�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}
	
	//���C
	m_vx += -(m_vx * 0.098f);

	//���R�����^��
	m_vy += 9.8f / (16.0f);

	//�ړ��I���-----------------------------------------

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�e�ۂƂ������������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�G����������HitBox�������B
	
		return;
	}
	
	//�u���b�N�Ƃ̂����蔻��
	objblock->BlockHit(
		&m_px, &m_py, ENEMY_SIZE, ENEMY_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, 
		&m_vx, &m_vy
	);

	//�E�ɏՓ˔��肪�������獶�����ɂ���
	if (m_hit_left == true)
	{
		m_posture = 0.0f;
	}
	//���ɏՓ˔��肪��������E�����ɂ���ł�
	if (m_hit_right == true)
	{
		m_posture = 1.0f;
	}

	//���ɏՓ˔��肪����
	if (m_hit_down == true)
	{
		//�ړ����悤�Ƃ��Ă���Ƃ��낪�R�Ȃ�����]��
		//�E�ɓ����Ă��� && 
		//�E���Ƀu���b�N������������
		if (m_vx > 0 && objmap->GetMap((m_px / BLOCK_SIZE + 1), (m_py / BLOCK_SIZE + 1)) != MAP_BLOCK)
		{
			//���������ɂ���
			m_posture = 0.0f;
		}
		//���Ɉړ����Ă��� &&
		//�����Ƀu���b�N������������		�����_����
		if (m_vx < 0 && objmap->GetMap(((m_px+ENEMY_SIZE) / BLOCK_SIZE - 1), (m_py / BLOCK_SIZE + 1)) != MAP_BLOCK)
		{
			//�������E�ɂ���
			m_posture = 1.0f;
		}
	}

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	
}

//�h���[
void CObjEnemy::Draw()
{
	//�摜�̐؂���z��
	int AniData[2] =
	{
		0  , 1 , 
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = (ENEMY_SIZE * m_posture) + m_px - objmap->GetScrollX();
	dst.m_right = (ENEMY_SIZE - ENEMY_SIZE * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//�`��
	Draw::Draw(8, &src, &dst, color, m_r);

}