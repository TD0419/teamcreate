#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStageClear.h"

//�R���X�g���N�^
CObjStageClear::CObjStageClear(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjStageClear::Init()
{
}

//�A�N�V����
void CObjStageClear::Action()
{
	//�X�N���[���̈ʒu���擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	m_scroll_x = objmap->GetScrollX();
	m_scroll_y = objmap->GetScrollY();
}

//�h���[
void CObjStageClear::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"STAGE CLEAR", m_px-m_scroll_x, m_py - m_scroll_y, 140.0f, color);
}