#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackGround::Init()
{
	 m_px=0.0f;	// �w�iX���W
	 m_py=0.0f;	// �w�iY���W
}

//�A�N�V����
void CObjBackGround::Action()
{
}

//�h���[
void CObjBackGround::Draw()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left =0.0f;
	src.m_right =src.m_left + 1536.0f;
	src.m_bottom = src.m_top + 1536.0f;

	//�`��ʒu
	dst.m_top =  WINDOW_SIZE_H - src.m_bottom - src.m_top - objmap->GetScrollY() + 15.0f;//���������p(+15)
	dst.m_left = 1536.0f - src.m_right - src.m_left;
	dst.m_right = 1536.0f;
	dst.m_bottom = WINDOW_SIZE_H - objmap->GetScrollY() + 900.0f;//�����p(�{900.0f)

	//�`��
	Draw::Draw(GRA_BACKGROUND, &src, &dst, color, 0.0f);
	
}