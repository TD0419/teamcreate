#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjNeedle.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNeedle::CObjNeedle(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjNeedle::Init()
{
	m_needle_gauge = 0.0f;
	m_time = 0;

    //�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_NEEDLE, 1);

}

//�A�N�V����
void CObjNeedle::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�j���Ō�܂ŏo�Ă��Ȃ���
	if (m_needle_gauge != 64)
		m_needle_gauge++;
	else //�j���Ō�܂ŏo���ꍇ
	{
		m_time++;
		hit->SetInvincibility(true);//�j�̔�����Ȃ���
		if (m_time == 120) //120�t���[���o������j���o��
		{
			m_needle_gauge = 0;
 			m_time = 0;
			hit->SetInvincibility(false);//�j�̔��������
		}
		
	}
	// hitbox���������Ȃ�
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - 64.0f - objmap->GetScrollY() + m_needle_gauge / 2  , NEEDLE_SIZE_WIDTH, NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2 );

}

//�h���[
void CObjNeedle::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�j-------------------------------------------------------
	//�؂���ʒu
	src.m_top = 32.0f;
	src.m_left = 0.0f; 
	src.m_right = src.m_left + 32.0f;
	src.m_bottom = src.m_top - 32.0f  + m_needle_gauge / 2;

	//�`��ʒu
	dst.m_top = m_py + m_needle_gauge / 2 - objmap->GetScrollY() - NEEDLE_SIZE_WIDTH;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + NEEDLE_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + NEEDLE_SIZE_HEIGHT - m_needle_gauge / 2;

	//�`��
	Draw::Draw(GRA_NEEDLE, &src, &dst, color, 0.0f);

	//------------------------------------------------------------
}