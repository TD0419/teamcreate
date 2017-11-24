#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTarzanPoint.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjTarzanPoint::CObjTarzanPoint(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjTarzanPoint::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT, ELEMENT_GIMMICK, OBJ_TARZAN_POINT, 1);
}

//�A�N�V����
void CObjTarzanPoint::Action()
{

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjTarzanPoint::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = TARZAN_POINT_WIDTH;
	src.m_bottom = TARZAN_POINT_HEIGHT;

	//�`��ʒu
	dst.m_top    = m_py - objmap->GetScrollY();
	dst.m_left   = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + TARZAN_POINT_WIDTH;
	dst.m_bottom = dst.m_top + TARZAN_POINT_HEIGHT;

	//�`��
	Draw::Draw(GRA_TARZAN_POINT, &src, &dst, color, 0.0f);

}