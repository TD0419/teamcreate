#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionSource.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDiffusionSource::CObjDiffusionSource(float x, float y, int limit)
{
	m_px = x;
	m_py = y;
	m_limit = limit;
}

//�C�j�V�����C�Y
void CObjDiffusionSource::Init()
{
	m_vx = 0.0f;
	m_vy = 0.2f;

	//�����蔻��Z�b�g
	Hits::SetHitBox(this, m_px, m_py, DIFFUSION_SOURCE_SIZE, DIFFUSION_SOURCE_SIZE, ELEMENT_ENEMY, OBJ_DIFFUSION_SOURCE, 1);
}

//�A�N�V����
void CObjDiffusionSource::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);
	
	m_limit--;

	if (m_limit < 0)//���~�b�g�^�C����0�ȉ��Ȃ�
	{
		//5����������
		CObjDiffusionBullet* p;
		for (int i = 210; i<360; i += 30)
		{
			//��30�p�x�Ŋp�x�e�۔���
			p = new CObjDiffusionBullet(m_px + 28.0f, m_py + 20.0f, i,this);
			Objs::InsertObj(p, OBJ_DIFFUSION_BULLET, 100);
			Audio::Start(DIFFUSION);
		}
		
		this->SetStatus(false);		//���g���폜
		Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜
		return;
	}

	//������u���b�N�Ɠ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
	{
		return;
	}

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//�����蔻��̍X�V
	HitBoxUpData(hit, m_px, m_py);
}

//�h���[
void CObjDiffusionSource::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + DIFFUSION_SOURCE_SIZE;
	src.m_bottom = src.m_top + DIFFUSION_SOURCE_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DIFFUSION_SOURCE_SIZE;
	dst.m_bottom = dst.m_top + DIFFUSION_SOURCE_SIZE;

	//�`��
	Draw::Draw(GRA_DIFFUSION_SOURCE, &src, &dst, color, 0.0f);
}