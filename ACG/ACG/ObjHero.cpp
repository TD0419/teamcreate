#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero()
{

}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = WINDOW_SIZE_W/2.0f;
	m_py = WINDOW_SIZE_H / 2.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_mouse_angle = 0.0f;
}

//�A�N�V����
void CObjHero::Action()
{
	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//���L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= 3.0f;
	}

	//�E�L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += 3.0f;
	}
	
	//��L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy -= 3.0f;
	}

	//���L�[�������ꂽ�Ƃ�
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy += 3.0f;
	}
	
	Scroll();	//�X�N���[�������������Ȃ�

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��x�N�g����������
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�ړ��I���-----------------------------------------

	//�}�E�X�̈ʒu�Ǝ�l���̈ʒu����}�E�X�̊p�x�����߂�------
	//�}�E�X�̈ʒu���擾
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//��l���̈ʒu����}�E�X�̈ʒu�̃x�N�g�����擾
	double vector_x = mous_x - m_px;
	double vector_y = mous_y - m_py;

	//�Εӎ擾
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�p�x�����߂�
	m_mouse_angle = acos(vector_x / hypotenuse) * 180.0/3.14;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������[�ɂ���
	if (mous_y > m_py)
	{
		m_mouse_angle *= -1;
	}
	//-------------------------------------------------------

	//�͂���-------------------------------------------------

	////�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_LADDERS) != nullptr)
	//{
	//	//W�L�[�������ꂽ�Ƃ�
	//	if (Input::GetVKey('W') == true)
	//	{
	//		m_vy -= 3.0f;
	//	}

	//	//S�L�[�������ꂽ�Ƃ�
	//	if (Input::GetVKey('S') == true)
	//	{
	//		m_vy += 3.0f;
	//	}
	//}

	//�͂����I��---------------------------------------------
}

//�X�N���[�������̊֐�
void CObjHero::Scroll()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��l�������܂��͉E�̃X�N���[�����C���𒴂������Ȃ�
	if ((m_px + m_vx) < SCROLL_LINE_LEFT || (m_px + m_vx) > SCROLL_LINE_RIGHT)
	{
		obj_m->SetScrollX(m_vx);	//�ړ��ʂ��X�N���[���ɃZ�b�g
	}

	//��l������܂��͉��̃X�N���[�����C���𒴂������Ȃ�
	if ((m_py + m_vy) < SCROLL_LINE_UP || (m_py + m_vy) > SCROLL_LINE_DOWN) 
	{
		obj_m->SetScrollY(m_vy);	//�ړ��ʂ��X�N���[���ɃZ�b�g
	}

}

//�h���[
void CObjHero::Draw()
{
	
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 512.0f;
	src.m_bottom	= 512.0f;

	//�`��ʒu
	dst.m_top		= 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left		= 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	Draw::Draw(0, &src, &dst, color, m_r);
}