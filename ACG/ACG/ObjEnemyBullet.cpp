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

//�R���X�g���N�^�iBOSS�p��l���̕����ցj
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

//�R���X�g���N�^(�M�~�b�N�p�@�w�肵��������)
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
	m_delete_flag = false;

	m_hit_up = false;
	m_hit_right = false;
	m_hit_left = false;
	m_hit_down = false;
	
	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 5://�X�e�[�W�T
		{
			//�����蔻��pHitBox���쐬
			Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BULLET_SIZE, STAGE5_BOSS_BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
			break;
		}
		default:
		{
			//�����蔻��pHitBox���쐬
			Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
			break;
		}
	}

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
		switch ((((UserData*)Save::GetData())->stagenum))
		{
			case 2:	//�X�e�[�W2(�{�X)
			{
				//��l���ƃ{�X�̃I�u�W�F�N�g�������Ă���
				CObjBoss* objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//��l���ƃ{�X��X�̈ʒu�������Ă���(���S���Ă��Ȃ��Ƃ�)
				float boss_x = 0.f; 
				if (objboss != nullptr)
				{
					objboss->GetPosX();
				}
				
				float hero_x = objhero->GetPosX();

				//�{�X�ƒe�̋����@���@�{�X�ƃq�[���[�̋����@���傫�����
				if (abs(boss_x - m_px) > abs(boss_x - hero_x))
					m_delete_flag = true;//�폜�t���O���I���ɂ���

				break;
			}
			case 3:	//�X�e�[�W3
			{
				CObjStage5Boss* objboss5 = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

				//��l���ƃ{�X5��X�̈ʒu�������Ă���(���S���Ă��Ȃ��Ƃ�)
				float boss_y = 0.f;
				if (objboss5!=nullptr)
				{
					objboss5->GetPosY();
				}
					
				float hero_y = objhero->GetPosY();

				//�{�X�ƒe�̋����@���@�{�X�ƃq�[���[�̋����@���傫�����
				if (abs(boss_y - m_py) > abs(boss_y - hero_y))
					m_delete_flag = true;//�폜�t���O���I���ɂ���

				break;
			}
		}
	}

	if (m_delete_flag == true)	//�폜�t���O���I���Ȃ�
	{
		WindowOutDelete(this);//�폜����
		return;
	}
	
	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	if(((UserData*)Save::GetData())->stagenum == 3)	//�X�e�[�W5
	{
		objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_BULLET_SIZE, STAGE5_BOSS_BULLET_SIZE,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}
	else
	{
		objblock->BlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}

	//�u���b�N�Ƃ������Ă���΍폜����
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
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
	//������u���b�N�ɂ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_FALLING_BLOCK))
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
	
	if (((UserData*)Save::GetData())->stagenum == 2)//�X�e�[�W2�Ȃ�
	{
		dst.m_right = dst.m_left + BULLET_SIZE;
		dst.m_bottom = dst.m_top + BULLET_SIZE;

		Draw::Draw(GRA_COCONUT, &src, &dst, color, m_r);
	}
	else
	{
		dst.m_right = dst.m_left + STAGE5_BOSS_BULLET_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_BULLET_SIZE;

		Draw::Draw(GRA_STAGE5_BOSS_BULLET, &src, &dst, color, m_r);
	}
}