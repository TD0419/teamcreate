#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjCannon.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCannon::CObjCannon(float x, float y)
{
	m_x = x * CANNON_SIZE_HEIGHT;
	m_y = y * CANNON_SIZE_WIDTH;
}

//�C�j�V�����C�Y
void CObjCannon::Init()
{

	m_x = 100.0f;
	m_y = 100.0f;
	m_r = 0.0f;
	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, CANNON_SIZE_WIDTH, CANNON_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_CANNON, 1);

}

//�A�N�V����
void CObjCannon::Action()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);

}

//�h���[
void CObjCannon::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top	 = 0.0f;
	src.m_left	 = 0.0f;
	src.m_right	 = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_y - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_x - obj_m->GetScrollX();
	dst.m_right = dst.m_left + CANNON_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + CANNON_SIZE_HEIGHT;

	//�`��
	Draw::Draw(14, &src, &dst, color, m_r);

}