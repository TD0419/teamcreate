#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWood::CObjWood(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWood::Init()
{
	m_r = 0.0f;
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, WOOD_SIZE, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
	
	// �p�x�ϐ�������
	m_r = 0.0f;
}

//�A�N�V����
void CObjWood::Action()
{	
	//90�x�ȏ��]���Ă����
	if (m_r <= -90.0f)
	{
		HeroHit(m_px + WOOD_SIZE, m_py);//��l���Ƃ̓����蔻��
	
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px + WOOD_SIZE, m_py);
		return;
	}
	else
	{
		HeroHit(m_px, m_py);//��l���Ƃ̓����蔻��
		//�؂��܂킷
		m_r -= 1.0f;

		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px , m_py);
	}
}

//�h���[
void CObjWood::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WOOD_SIZE;
	dst.m_bottom = dst.m_top + WOOD_SIZE;

	//�`��
	Draw::Draw(7, &src, &dst, color, m_r,-1.0f,-1.0f);
}

//��l�����G�ꂽ�Ƃ��̏���
//����1,2 �؂̃|�W�V����
void CObjWood::HeroHit(float px, float py)
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	 //��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(px + WOOD_SIZE);//��l���̈ʒu��؂̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{

				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(py - HERO_SIZE_HEIGHT);//��l���̈ʒu��؂̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(px - HERO_SIZE_WIDTH);//��l���̈ʒu��؂̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(py + WOOD_SIZE);//��l���̈ʒu��؂̉����܂ł��炷
			}
		}
	}
}