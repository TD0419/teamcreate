#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"


#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = (float)x * 64.0f;
	m_py = (float)y * 64.0f;
}

//�C�j�V�����C�Y
void CObjLastWall::Init()
{
	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, 32, 512, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
	m_wall_gauge = 0;
	m_wall_gauge2 = 0;
	m_look_unlock_flag = false;
	a = false;
	m_hero_hit_flag = false;
	switch (((UserData*)Save::GetData())->stagenum)
	{
		//�X�e�[�W�P
	case 1:
		m_wall_type = 1;
		break;
		//�X�e�[�W�Q
	case 2:
		m_wall_type = 2;
		break;
		//�X�e�[�W�R
	case 3:
		m_wall_type = 3;
		break;
		//�X�e�[�W�T
	case 5:
		m_wall_type = 5;
		break;
	default:

		break;
	}
}

//�A�N�V����
void CObjLastWall::Action()
{
	
	//HitBox�̈ʒu�̕ύX
	//�����Ŏ����Ă����I�u�W�F�N�g�Ƃ������Ă��邩���ׂ�
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�G�I�u�W�F�N�Ǝ����Ă���
	CObjEnemy*objenemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HIT_DATA** hit_data;		//��l���̏Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(OBJ_HERO);//��l���̏Փ˂̏���hit_data�ɓ����
		for (int i=0;i < hit->GetCount();i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r=0.0f;
				
				r=hit_data[i]->r;
				if (0 < r && r < 85 || 275 < r && r < 360)
				{
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
					objhero->SetPosX(m_px + 62.0f);//��l���̈ʒu��LastWall�̉E���܂ł��炷
				}

				//LastWall�̏㑤���Փ˂��Ă���ꍇ
				else if (85 < r && r < 94)
				{

					objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
					objhero->SetPosY(m_py - 60.0f);//��l���̈ʒu��LastWall�̏㑤�܂ł��炷
				}

				//LastWall�̍������Փ˂��Ă���ꍇ
				else if (94 < r && r < 266)
				{
					objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
										   //objhero->SetPosX(m_px - HERO_SIZE_WIDTH+28.0f);//��l���̈ʒu��LastWall�̍����܂ł��炷
					m_hero_hit_flag = true;


				}

				//LastWall�̉������Փ˂��Ă���ꍇ
				else if (266 < r && r < 275)
				{
					objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
					objhero->SetPosY(m_py + 512.0f);//��l���̈ʒu��LastWall�̉����܂ł��炷
					
				}

			}
		}
	}
	else if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		HIT_DATA** hit_data_enemy;	//�G�̏Փ˂̏�������\����
		hit_data_enemy = hit->SearchObjNameHit(OBJ_ENEMY);//�G�̏Փ˂̏���hit_data�ɓ����

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data_enemy[i] != nullptr)
			{
				float r = 0.0f;
				r = hit_data_enemy[i]->r;


				//LastWall�̉E�����Փ˂��Ă���ꍇ
				if (0 < r && r < 85 || 275 < r && r < 360)
				{
					objenemy->SetVX(2.0f);//��l����X�����̈ړ����O�ɂ���
					objenemy->SetPosture(1.0f);
				}
				else if (94 < r && r < 266)
				{
					objenemy->SetVX(-2.0f);//��l����X�����̈ړ����O�ɂ���
					objenemy->SetPosture(0.0f);//��l���̈ʒu��LastWall�̍����܂ł��炷
				}

			}
		}
	}
	
	

	

	
	

	
	
	//// �{�^���I�u�W�F�N�g�������Ă���
	//CObjButton* objbutton = (CObjButton*)Objs::GetObj(OBJ_BUTTON);
	
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	int map_num = objmap->GetMap(m_map_x, m_map_y);

	//�{�X�̏����ĂԂ�
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
	


		////�{�^���������Ă�������J���t���O�I��
		//if (objbutton->GetTrickFlag() == true)
		//{
		//	m_look_unlock_flag = true;
		//}

		// m_wall_gauge��512���z�����珈���X�g�b�v
		if (m_wall_gauge >= 512)
		{
			a = true;
			Audio::Stop(WALL);//���y�X�g�b�v
			m_wall_gauge = 0;
		}
		else
		{
			//hero�������ɐU��Ă��牟����Ă�����
			if (m_hero_hit_flag == true && a == false&&objenemy==nullptr)
			{
				m_wall_gauge += 3; // 3�����₵�Ă���
				Audio::Start(WALL);//�J��̉��y�X�^�[�g
			}
		}

		if (a == false)
		{
			// hitbox���������Ȃ�
			HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32, 512 - m_wall_gauge);
		}

		if (m_wall_gauge2 >= 512)
		{
			Audio::Stop(WALL);//���y�X�g�b�v
		}
		else
		{
			if (a == true)
			{
				m_wall_gauge2 += 8;
				// hitbox���������Ȃ�
				Audio::Start(WALL);//�J��̉��y�X�^�[�g
				HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32, 0 + m_wall_gauge2);

			}
		}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px+29, m_py+65);
}

//�h���[
void CObjLastWall::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	switch (m_wall_type)
	{
	case 1:
	case 2:
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY() - 190;
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + 96.0f;
		dst.m_bottom = dst.m_top + 256.0f;

		//�`��(��̕���)
		Draw::Draw(GRA_LAST_WALL, &src, &dst, color, 0.0f);

		//�؂���ʒu
		src.m_top = 0.0 + m_wall_gauge;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 512.0f;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY() + 65;
		dst.m_left = m_px - objmap->GetScrollX() + 30;
		dst.m_right = dst.m_left + 32;
		dst.m_bottom = dst.m_top + 512-m_wall_gauge;

		//�`��(���̕���)
		Draw::Draw(GRA_OPEN_WALL, &src, &dst, color, 0.0f);
		break;

	case 3:
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY() - 190;
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + 96.0f;
		dst.m_bottom = dst.m_top + 256.0f;

		//�`��(��̕���)
		Draw::Draw(GRA_LAST_WALL3, &src, &dst, color, 0.0f);

		//�؂���ʒu
		src.m_top = 0.0 + m_wall_gauge;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 512.0f;
		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY() + 65;
		dst.m_left = m_px - objmap->GetScrollX() + 30;
		dst.m_right = dst.m_left + 32;
		dst.m_bottom = dst.m_top + 512;

		//�`��(���̕���)
		Draw::Draw(GRA_OPEN_WALL3, &src, &dst, color, 0.0f);
		break;
	

	case 5:
		break;
	}
	

	//-----------------------------------------------------
	//if (a == false)
	//{
	//	//�؂���ʒu
	//	src.m_top = 0.0 + m_wall_gauge;
	//	src.m_left = 0.0f;
	//	src.m_right = 32.0f;
	//	src.m_bottom = 512.0f;
	//
	//	//�`��ʒu
	//	dst.m_top = m_py - objmap->GetScrollY() + 65;
	//	dst.m_left = m_px - objmap->GetScrollX() + 30;
	//	dst.m_right = dst.m_left + 32;
	//	dst.m_bottom = dst.m_top + 512 - m_wall_gauge;
	//}
	//else
	//{
	//	//�؂���ʒu
	//	src.m_top = 0.0;
	//	src.m_left = 0.0f;
	//	src.m_right = 32.0f;
	//	src.m_bottom = 0.0f+m_wall_gauge2;
	//	//�`��ʒu
	//	dst.m_top = m_py - objmap->GetScrollY() + 65;
	//	dst.m_left = m_px - objmap->GetScrollX() + 30;
	//	dst.m_right = dst.m_left + 32;
	//	dst.m_bottom = dst.m_top +  m_wall_gauge2;
	//}
	////�`��(���̕���)
	//Draw::Draw(GRA_OPEN_WALL, &src, &dst, color, 0.0f);
}
