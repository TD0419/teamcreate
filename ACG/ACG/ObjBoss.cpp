#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBoss::CObjBoss(int x,int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
    m_vx = 0;
    m_vy = 0;
	m_r = 0.0f;
	m_hp = 20; //�{�X�̂g�o
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 2; //�A�j���[�V�����Ԋu��
	
	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE , BOSS_SIZE , ELEMENT_ENEMY, OBJ_BOSS, 1);
}

//�A�N�V����
void CObjBoss::Action()
{
	m_ani_time++;//�A�j���[�V�����͗V�тȂ̂ŏ����Ă�����Ă������ł�
	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɂ���
	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//���C
	m_vx += -(m_vx * 0.098f);

	//���R�����^��
	m_vy += 9.8f / (16.0f);

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;
	
	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* objblock = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	objblock-> BlockHit(&m_px,&m_py,BOSS_SIZE,BOSS_SIZE,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);
	
	CObjLastWall* objlastwall = (CObjLastWall*)Objs::GetObj(OBJ_LAST_WALL);
	//�e�ۂƂ���������HP-1
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	if (m_hp == 0)
	{
		Hits::DeleteHitBox(this);	//boss�����L����HitBox�ɍ폜����
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		objlastwall->GateOpenflag = true;
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjBoss::Draw()
{
	//�摜�̐؂���z��
	int AniData[8] =
	{
		0, 1, 2, 3, 4, 5, 6, 7,
	};
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = AniData[m_ani_frame] * 128.0-128.0;
	src.m_right = src.m_left-128.0f;
	src.m_bottom = src.m_top + 128.0f;;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left  + BOSS_SIZE;
	dst.m_bottom = dst.m_top  + BOSS_SIZE+3;

	//�`��
	Draw::Draw(4, &src, &dst, color, m_r);

}