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
	
	
	// �p�x�ϐ�������
	m_r = 0.0f;

	// ��]�t���O������
	m_rota_flag = false;

	//�����̖؂̉摜�̈ʒu
	m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
	m_wood_y = m_py;

	//�����蔻��
	Hits::SetHitBox(this, m_wood_x, m_wood_y, 64, WOOD_SIZE, ELEMENT_GIMMICK, OBJ_WOOD, 1);
}

//�A�N�V����
void CObjWood::Action()
{	
	//��l���I�u�W�F�N�g���������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	// ��]�t���O�������Ă����
	if (m_rota_flag == true)
	{
		//90�x�ȏ��]���Ă����
		if (m_r <= -90.0f)
		{
			//�؂̉摜�̈ʒu���X�V
			m_wood_x = m_px + WOOD_SIZE;
			m_wood_y = m_py + (WOOD_SIZE - 64.0000f);
			//��l���Ƃ̓����蔻��
			if (HeroHit(m_wood_x, m_wood_y, WOOD_SIZE, 64.0000f,
				&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
				)
			{
				//��l���̈ʒu���X�V
				objhero->SetPosX(hero_x);
				objhero->SetPosY(hero_y);
				objhero->SetVecX(hero_vx);
				objhero->SetVecY(hero_vy);
			}
			
			//HitBox�̈ʒu���X�V����
			HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y, 64.0f, WOOD_SIZE);
			
			return;
		}
		else
		{
			//�؂̉摜�̈ʒu�X�V
			m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
			m_wood_y = m_py;
			//��l���Ƃ̓����蔻��
			if (HeroHit(m_wood_x, m_wood_y, 64.0000f, WOOD_SIZE,
				&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
				)
			{
				//��l���̈ʒu���X�V
				objhero->SetPosX(hero_x);
				objhero->SetPosY(hero_y);
				objhero->SetVecX(hero_vx);
				objhero->SetVecY(hero_vy);
			}
			//�؂��܂킷
			m_r -= 1.0f;
			HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y);
			return;
		}
	}
	else
	{
		//�؂̉摜�̈ʒu�X�V
		m_wood_x = m_px + (WOOD_SIZE - 64.0000f);
		m_wood_y = m_py;
		//��l���Ƃ̓����蔻��
		if (int hit = HeroHit(m_wood_x, m_wood_y, 64.0000f, WOOD_SIZE,
			&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, &hero_vx, &hero_vy)
			)
		{
			//��l���̈ʒu���X�V
			objhero->SetPosX(hero_x);
			objhero->SetPosY(hero_y);
			objhero->SetVecX(hero_vx);
			objhero->SetVecY(hero_vy);
		}
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_wood_x, m_wood_y);
		return;
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

//�u���b�NA�ƃu���b�NB�̓����蔻��
//�u���b�NA���ړ����Ȃ��u���b�N
//�u���b�NB�����������ꍇ�ړ�����u���b�N
//����1  float  ax		:�u���b�NA��X�ʒu
//����2  float  ay		:�u���b�NA��Y�ʒu
//����3  float  aw		:�u���b�NA�̕�
//����4  float  ah		:�u���b�NA�̍���
//����5  float* bx		:�u���b�NB��X�ʒu �|�C���^
//����6  float* by		:�u���b�NB��Y�ʒu �|�C���^
//����7  float  bw		:�u���b�NB�̕�
//����8  float  bh		:�u���b�NB�̍���
//����9  float* bvx		:�u���b�NB��X�ړ��� �|�C���^
//����10 float* bvy		:�u���b�NB��Y�ړ��� �|�C���^
//�߂�l	int			:�����������ǂ���||�ǂ��ɓ����������@0=�����薳���F1=B���猩�ď�F2=B���猩�ĉ��F3=B���猩�ĉE:4=B���猩�č�
int CObjWood::HeroHit(float ax,float ay,float aw,float ah,
						float* bx,float* by,float bw,float bh,
						float* bvx,float* bvy)
{
	float ax_min = ax;			//�u���b�NA��X���W�ŏ�
	float ay_min = ay;			//�u���b�NA��Y���W�ŏ�
	float ax_max = ax_min + aw;	//�u���b�NA��X���W�ő�
	float ay_max = ay_min + ah;	//�u���b�NA��Y���W�ő�

	float bx_min = *bx;			//�u���b�NB��X���W�ŏ�
	float by_min = *by;			//�u���b�NB��Y���W�ŏ�
	float bx_max = bx_min + bw;	//�u���b�NB��X���W�ő�
	float by_max = by_min + bh;	//�u���b�NB��Y���W�ő�

	//�͂ݏo�����e�͈�
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//�����蔻��`�F�b�N
	if (ax_max < bx_min);//A���B���E
	else if (bx_max < ax_min);//A���B����
	else if (ay_max < by_min);//A���B����
	else if (by_max < ay_min);//A���B����
	else	//�����肠��B
	{
		//�u���b�NA�̏�
		if (by_max - ay_min < bleed_y)
		{
			if(*bvy > 0.0f)
   				*bvy = 0.00000f;//Y�ړ��ʂ�0�ɂ���
			*by -= by_max - ay_min;
			return 2;
		}
		//�u���b�NA�̉�
		if (ay_max - by_min < bleed_y)
		{
   			if(*bvy < 0.0f)
				*bvy = 0.00000f;//Y�ړ��ʂ�0�ɂ���
			*by += ay_max - by_min;
			return 1;
		}
		//�u���b�NA�̍�
		if (bx_max - ax_min < bleed_x)
		{
			if(*bvx > 0.0f)
				*bvx = 0.00000f;//X�ړ��ʂ�0�ɂ���
			*bx -= bx_max - ax_min;
			return 3;
		}
		//�u���b�NA�̉E
		if (ax_max - bx_min < bleed_x)
		{
			if(*bvx < 0.0f)
				*bvx = 0.00000f;//X�ړ��ʂ�0�ɂ���
			*bx += ax_max - bx_min;
			return 4;
		}
	}
	return 0;
}
