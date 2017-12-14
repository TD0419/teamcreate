#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^�i�v���C���[�̕����Ɂj
CObjEnemyBullet::CObjEnemyBullet(float x, float y)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�����ʒu�����߂�
	m_px = x;
	m_py = y;
	
	//���������߂�
	m_speed = 6.5f;

	//�G�p�e�ۂɃX�N���[���̉e����K�p������
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();

	//��l���Ƃ̊p�x�̌v�Z���s��-----------------------------
	//��l���̃I�u�W�F�N�g���������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX() - objmap->GetScrollX();		//��l���̈ʒu���X�擾
	float hero_y = objhero->GetPosY() - objmap->GetScrollY();		//��l���̈ʒu���Y�擾

																	//��l���̈ʒu�x�N�g�����擾
	float Hvector_x = hero_x - x;
	float Hvector_y = hero_y - y;

	//�Εӎ擾
	float hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//�p�x�����߂�
	m_r = acosf(Hvector_x / hypotenuse);

	//----------------------------------------------------------

	//�p�x�����ɒe�ۂ��ړ�������
	m_vx = cosf(m_r) * m_speed;
	m_r = m_r * 180.0f / 3.14f;

	//��l����Y�ʒu���ゾ�����ꍇ�̔��ˊp�x
	if (hero_y > y)
	{
		//180���`360���̒l�ɂ���
		m_r = 360 - abs(m_r);
	}
	//��l����Y�ʒu�����������ꍇ�̔��ˊp�x
	if (hero_y < y)
	{
		m_vy = -sin(acosf(Hvector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acosf(Hvector_x / hypotenuse)) * m_speed;
	}

}

//�R���X�g���N�^(�w�肵��������)
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float rad)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�����ʒu�����߂�
	m_px = x;
	m_py = y;
	m_r = rad;

	//���������߂�
	m_speed = 6.5f;

	//�G�p�e�ۂɃX�N���[���̉e����K�p������
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();
}

//�C�j�V�����C�Y
void CObjEnemyBullet::Init()
{
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
}

//�A�N�V����
void CObjEnemyBullet::Action()
{
	//�ړ�
	m_px += m_vx*1.0f;
	m_py += m_vy*1.0f;

	//��ʊO�Ȃ�
	if(WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE)==false)
	{
		if ((((UserData*)Save::GetData())->stagenum) == 2)
		{
			//��l���ƃ{�X�̃I�u�W�F�N�g�������Ă���
			CObjBoss* objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//��l���ƃ{�X��X�̈ʒu�������Ă���
			float boss_x = objboss->GetPosX();
			float hero_x = objhero->GetPosX();

			//�{�X�ƒe�̋����@���@�{�X�ƃq�[���[�̋����@���傫�����
			if (abs(boss_x - m_px) > abs(boss_x - hero_x))
			{
				WindowOutDelete(this);//�폜����
				return;
			}
		}
	}

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ƃ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_HERO))
	{
		return;
	}
	//��Ƃ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}
	//Water(��)�Ƃ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}
	//Lastwall(��)�ɂ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjEnemyBullet::Draw()
{
	// �}�b�v���������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(GRA_COCONUT, &src, &dst, color, m_r);

}