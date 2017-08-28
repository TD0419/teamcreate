#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(float x,float y)
{
	

}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_x = WINDOW_SIZE_W / 2.0f;
	m_y = WINDOW_SIZE_H / 2.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64.0f, 64.0f, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy::Action()
{
	//�ړ�----------------------------------------------

	//�f�o�b�O�p�Ƀ{�^������œ����悤�ɂ��Ă܂��B
	//�K���Ɉړ��������������Ă����܂��܂���B

	//A�L�[�������ꂽ�Ƃ��F���ړ�
	if (Input::GetVKey('J') == true)
	{
		m_vx -= 5.0f;
	}

	//D�L�[�������ꂽ�Ƃ��F�E�ړ�
	if (Input::GetVKey('L') == true)
	{
		m_vx += 5.0f;
	}

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_x += m_vx;
	m_y += m_vy;

	//�ړ��x�N�g����������
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�ړ��I���-----------------------------------------


	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);//HitBox�̈ʒu���X�V

	//�e�ۂƂ������������
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�G����������HitBox�������B
	}

	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_x, m_y);
}

//�h���[
void CObjEnemy::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_y /*- obj_m->GetScrollY()*/;
	dst.m_left = 0.0f + m_x /*- obj_m->GetScrollX()*/;
	dst.m_right = dst.m_left + ENEMY_SIZE;
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//�`��
	Draw::Draw(1, &src, &dst, color, m_r);

}