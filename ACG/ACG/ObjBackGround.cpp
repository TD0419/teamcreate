#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBackGround::CObjBackGround()
{

}

//�C�j�V�����C�Y
void CObjBackGround::Init()
{
	 m_x=0;	// �w�iX���W
	 m_y=0;	// �w�iY���W
}

//�A�N�V����
void CObjBackGround::Action()
{
	
}

//�h���[
void CObjBackGround::Draw()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left =0.0f;
	src.m_right =src.m_left + 1024;
	src.m_bottom = src.m_top + 1024;

	//�`��ʒu
	dst.m_top =  WINDOW_SIZE_H - src.m_bottom - src.m_top - obj_m->GetScrollY();
	dst.m_left = WINDOW_SIZE_W - src.m_right - src.m_left;
	dst.m_right = WINDOW_SIZE_W;
	dst.m_bottom = WINDOW_SIZE_H - obj_m->GetScrollY();

	//�`��
	Draw::Draw(15, &src, &dst, color, 0.0f);
	
}