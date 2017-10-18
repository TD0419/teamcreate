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
	m_px = x * BOSS_SIZE;
	m_py = y * BOSS_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
    m_vx = 300.0f;
    m_vy = 200.0f;
	m_r = 0.0f;
	m_hp = 20; //�{�X�̂g�o

	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE , BOSS_SIZE , ELEMENT_ENEMY, OBJ_BOSS, 1);
}

//�A�N�V����
void CObjBoss::Action()
{
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
	
	//�e�ۂƂ���������HP-1
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	if (m_hp == 0)
	{
		Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

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
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left  + BOSS_SIZE;
	dst.m_bottom = dst.m_top  + BOSS_SIZE;

	//�`��
	Draw::Draw(14, &src, &dst, color, m_r);

}