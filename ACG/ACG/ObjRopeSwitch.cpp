#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRopeSwitch.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRopeSwitch::CObjRopeSwitch(int x, int y)
{
	m_px = x * ROPE_SWITCH_SIZE;
	m_py = y * ROPE_SWITCH_SIZE;

	m_rope_flag = false;
}

//�C�j�V�����C�Y
void CObjRopeSwitch::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, 20, 20, ELEMENT_GIMMICK, OBJ_ROPE_SWITCH, 1);
}

//�A�N�V����
void CObjRopeSwitch::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//���[�v���������Ă����
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		m_rope_flag = true;//�t���O��ON�ɂ���
	}
	else if(hit->CheckObjNameHit(OBJ_ROPE) == nullptr)
	{
		m_rope_flag = false;//�t���O��OFF�ɂ���
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+23.0f, m_py+32.0f);
}

//�h���[
void CObjRopeSwitch::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROPE_SWITCH_SIZE;
	dst.m_bottom = dst.m_top + ROPE_SWITCH_SIZE;

	//�`��
	Draw::Draw(13, &src, &dst, color, 0);
}