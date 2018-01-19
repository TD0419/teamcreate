#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDiffusionBullet.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^(�C��p)
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r)
{
	m_px = x ;
	m_py = y ;
	m_r  = (float)r;
	m_type = CANNON;
	m_speed = 5.5f;

}

//�R���X�g���N�^(�{�X�p)
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, int r, CObjDiffusionSource* p)
{
	m_px = x;
	m_py = y;
	m_r = (float)r;
	m_type = BOSS;
	mp_base = p;
	m_speed = 3.0f;
}

//�C�j�V�����C�Y
void CObjDiffusionBullet::Init()
{
	//���ł��������̌v�Z
	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 16.0f, 16.0f, ELEMENT_ENEMY, OBJ_DIFFUSION_BULLET, 1);
}

//�A�N�V����
void CObjDiffusionBullet::Action()
{
	//�ړ�
	m_px += m_vx * m_speed;
	m_py -= m_vy * m_speed;

	//��ʊO�Ȃ�
	if( WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE) == false )
	{
		switch (m_type)
		{
			case CANNON:
			{
				//��l���Ɗg�U�C��̃I�u�W�F�N�g�������Ă���
				CObjDiffusionCannon* objcannon = (CObjDiffusionCannon*)Objs::GetObj(OBJ_DIFFUSION_CANNON);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				if (objcannon != nullptr)//�C�䂪�����
				{
					//��l���Ɗg�U�C���Y�̈ʒu�������Ă���
					float cannon_y = objcannon->GetPosY();
					float hero_y = objhero->GetPosY();

					//�g�U�C��ƒe�̋����@���@�g�U�C��ƃq�[���[�̋����@���傫�����
					if (abs(cannon_y - m_py) > abs(cannon_y - hero_y))
					{
						WindowOutDelete(this);//�폜����
						return;
					}
				}
				else	//�C�䂪�Ȃ����
				{
					WindowOutDelete(this);//�폜����
					return;
				}
				break;
			}
			case BOSS:
			{
				//��l���̃I�u�W�F�N�g�������Ă���
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//��l���Ƒł��o�����̈ʒuY�������Ă���
				float base_y = mp_base->GetPosY();
				float hero_y = objhero->GetPosY();

				//�g�U�C��ƒe�̋����@���@�g�U�C��ƃq�[���[�̋����@���傫�����
				if (abs(base_y - m_py) > abs(base_y - hero_y))
				{
					WindowOutDelete(this);//�폜����
					return;
				}
				break;
			}
		}
	}

	//�g�U�eHitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//Hero�ɓ�����΍폜
	if ( DeleteCheckObjNameHit (hit, this, OBJ_HERO))
		return;

	// �u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//�u���b�N�Ƃ������Ă���΍폜����
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//��l���Ƃ������������
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}
	//������u���b�N�Ɠ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
	{
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
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
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 16.0f;
	dst.m_bottom = dst.m_top + 16.0f;

	if (m_type == CANNON)
		Draw::Draw(GRA_CANNON_BEAM, &src, &dst, color, m_r);
	
	if (m_type == BOSS)
		Draw::Draw(GRA_BOSS_DIFFUSION, &src, &dst, color, m_r);
}