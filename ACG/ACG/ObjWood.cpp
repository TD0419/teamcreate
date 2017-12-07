#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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

	//�}�b�v���̖؂̈ʒu���؂̉����w���Ă����̂Œ���
	m_px -= WOOD_SIZE - 64.0f;
	m_py -= WOOD_SIZE - 64.0f;

	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjWood::Init()
{	
	// �p�x�ϐ�������
	m_r = 0.0f;

	//�����̖؂̉摜�̈ʒu
	m_wood_image_x = m_px + (WOOD_SIZE - 64.0000f);
	m_wood_image_y = m_py;
	m_audio_start_flag = false;//�؂̉���炷�t���O

	//�����蔻��
	Hits::SetHitBox(this, m_wood_image_x, m_wood_image_y, 64, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
}

//�A�N�V����
void CObjWood::Action()
{	
	//��ʊO�Ȃ�
	if (WindowCheck(m_px, m_py, 64.0f, WOOD_SIZE) == false)
	{
		WindowOutDelete(this, m_map_x, m_map_y);//�폜����(��������)
		return;
	}

	//��l���I�u�W�F�N�g���������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	//HitBox�̕��A����
	float hit_w, hit_h;

	//90�x�ȏ��]���Ă����
	if (m_r <= -90.0f)
	{
		//�؂̉摜�̈ʒu���X�V
		m_wood_image_x = m_px + WOOD_SIZE;
		m_wood_image_y = m_py + (WOOD_SIZE - 64.0000f);

		//HitBox�̕��A�����ݒ�
		hit_w = WOOD_SIZE;
		hit_h = 64.0f;
	}
	else
	{
		CObjLeverSwich* objlever_swich = (CObjLeverSwich*)Objs::GetObj(OBJ_LEVER_SWICH);
		
		// ���o�[�X�C�b�`�������
		if (objlever_swich != nullptr)
		{
			// ��]�t���O�������Ă����
			if (objlever_swich->GetWood() == true)
			{
				if (m_audio_start_flag == false)
				{
					Audio::Start(TREE);
					m_audio_start_flag = true;
				}
				m_r -= 1.0f;//�؂��܂킷
			}
		}
		//�؂̉摜�̈ʒu�X�V
		m_wood_image_x = m_px + (WOOD_SIZE - 64.0000f);
		m_wood_image_y = m_py;

		//HitBox�̕��A�����ݒ�
		hit_w = 64.0f;
		hit_h = WOOD_SIZE;
	}

	//��l���Ƃ̓����蔻��
	//�Փ˂������l���̈ʒu���X�V����
	if (HitTestOfAB(m_wood_image_x, m_wood_image_y, hit_w, hit_h,
		&hero_x, &hero_y, 42, 120, &hero_vx, &hero_vy)
		)
	{
		//��l���̈ʒu���X�V
		objhero->SetPosX(hero_x);
		objhero->SetPosY(hero_y+2.0f);
		objhero->SetVecX(hero_vx);
		objhero->SetVecY(hero_vy);
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_wood_image_x, m_wood_image_y, hit_w, hit_h);	
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
	//���ɖ؂������Ă��������̂ō��E���]������
	src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = 0.0f;
	src.m_bottom = 320.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WOOD_SIZE;
	dst.m_bottom = dst.m_top + WOOD_SIZE;

	//�`��
	Draw::Draw(GRA_WOOD, &src, &dst, color, m_r,-1.0f,-1.0f);
}
