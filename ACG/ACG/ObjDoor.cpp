#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjDoor.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDoor::CObjDoor(int x, int y)
{
	m_px = x * DOOR_SIZE_WIDTH;
	m_py = y * DOOR_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjDoor::Init()
{
	m_px = 100;//�h�AX���W
	m_py = 384;//�h�AY���W
}

//�A�N�V����
void CObjDoor::Action()
{
}

//�h���[
void CObjDoor::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 128.0f;

	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + DOOR_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + DOOR_SIZE_HEIGHT;

	//�`��
	Draw::Draw(6, &src, &dst, color, 0);
}