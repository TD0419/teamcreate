#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionBullet.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r)
{
	m_px = x ;
	m_py = y ;
	m_r  = (float)r;
}

//�C�j�V�����C�Y
void CObjDiffusionBullet::Init()
{
	
	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	m_speed = 5.5f;
	m_window_check = true;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 12.0f, 12.0f, ELEMETN_ITEM, OBJ_DIFFUSION_BULLET, 1);
}

//�A�N�V����
void CObjDiffusionBullet::Action()
{
	//�ړ�
	m_px += m_vx* m_speed;
	m_py -= m_vy* m_speed;

	//��ʓ������ׂ�
	m_window_check = WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE);

	//��ʊO�Ȃ����
	if (m_window_check == false)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ƃ������������
	if (hit->CheckElementHit(OBJ_HERO) == true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//lastwall�Ɠ������������
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px + 30.0f, m_py);
}

//�h���[
void CObjDiffusionBullet::Draw()
{
	// �}�b�v���������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 12.0f;
	dst.m_bottom = dst.m_top + 12.0f;

	Draw::Draw(GRA_CANNON_BEAM, &src, &dst, color, m_r);

}