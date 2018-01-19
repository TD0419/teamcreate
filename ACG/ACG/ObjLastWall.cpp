#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjLastWall::Init()
{
	//�����蔻��																
	Hits::SetHitBox(this, m_px, m_py, 32.0f, 512.0f, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
	
	m_wall_gauge = 0;
	m_wall_down_gauge = 0;
	m_wall_unlock_flag = false;
	m_wall_down_flag = false;
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
	//BOSS�I�u�W�F�N�g�Ǝ����Ă���
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
	//BOSS�I�u�W�F�N�g�Ǝ����Ă���
	CObjStage5Boss*objstage5boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HIT_DATA** hit_data;		//��l���̏Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(OBJ_HERO);//��l���̏Փ˂̏���hit_data�ɓ����
		for (int i=0;i < hit->GetCount();i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r=0.0f;
				
				r =hit_data[i]->r;
				//��l�����E���ɏՓ�
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					//�ǂɂ߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						objhero->SetPosX(m_px + 61.0f);//��l���̈ʒu��LastWall�̉E���܂ł��炷
					}
					else//������
					{
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						objhero->SetPosX(m_px + 47.0f);//��l���̈ʒu��LastWall�̉E���܂ł��炷
					}
				}

				//LastWall�̏㑤���Փ˂��Ă���ꍇ
				else if (85.0f < r && r < 94.0f)
				{
					objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
					objhero->SetPosY(m_py - 60.0f);//��l���̈ʒu��LastWall�̏㑤�܂ł��炷
				}

				//LastWall�̍������Փ˂��Ă���ꍇ
				else if (94.0f < r && r < 266.0f)
				{
					//�ǂɂ߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						objhero->SetPosX(m_px - 63.0f + 42.0f);//��l���̈ʒu��LastWall�̍����܂ł��炷
					}
					else//������
					{
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						objhero->SetPosX(m_px - 63.0f + 28.0f);//��l���̈ʒu��LastWall�̍����܂ł��炷
					}
					
					m_hero_hit_flag = true;
				}

				//LastWall�̉������Փ˂��Ă���ꍇ
				else if (266.0f < r && r < 275.0f)
				{
					objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
					objhero->SetPosY(m_py + 512.0f - m_wall_gauge +65.0f);//��l���̈ʒu��LastWall�̉����܂ł��炷
				}
			}
		}
	}
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
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
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					objenemy->SetVecX(2.0f);//�G��X�����̈ړ���2�ɂ���
					objenemy->SetPosture(1.0f);//�����ύX
				}
				else if (94.0f < r && r < 266.0f)
				{
					objenemy->SetVecX(-2.0f);//�G��X�����̈ړ���-2�ɂ���
					objenemy->SetPosture(0.0f);//�����ύX
				}
			}
		}
	}
	if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	{
		HIT_DATA** hit_data_boss;	//�G�̏Փ˂̏�������\����
		hit_data_boss = hit->SearchObjNameHit(OBJ_BOSS);//�G�̏Փ˂̏���hit_data�ɓ����

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data_boss[i] != nullptr)
			{
				float r = 0.0f;
				r = hit_data_boss[i]->r;
				//LastWall�̉E�����Փ˂��Ă���ꍇ
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					objboss->SetVecX(2.0f);//BOSS��X�����̈ړ���2�ɂ���
					objboss->SetPosture(0.0f);//BOSS�����ύX
				}
				//LastWall�̍������Փ˂��Ă���ꍇ
				else if (94.0f < r && r < 266.0f)
				{
					objboss->SetPosX(m_px-BOSS_SIZE_WIDTH);//�{�X�̈ʒu��ǂ̍����ɂ��炷�B
					objboss->SetHitF(true);//�����̃t���O�𗧂Ă�
				}
			}
		}
	}

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	int map_num = objmap->GetMap(m_map_x, m_map_y);

	// m_wall_gauge��512���z�����珈���X�g�b�v
	if (m_wall_gauge >= 512)
	{
		// ��l�����ǂ̉E���ɂ��Ȃ��ƕǂ����܂�Ȃ��悤�ɂ���
		if (objhero->GetPosX() > m_px + BLOCK_SIZE)
		{
			//��l�����E���ɂ������̂ŁA�ǂ�������t���O��true�ɂ���
			m_wall_down_flag = true;

			//�ǂ̃Q�[�W��0�ɂ���
			m_wall_gauge = 0;
		}
				
		Audio::Stop(WALL);//���y�X�g�b�v
	}
	else
	{
		//hero�������ɐU��Ă���
		if (m_hero_hit_flag == true && m_wall_down_flag == false)
		{
			m_wall_gauge += 3; // 3�����₵�Ă���
			Audio::Start(WALL);//�J��̉��y�X�^�[�g
		}
	}

	//�ǂ̂��܂�t���O��false�̂Ƃ�
	if (m_wall_down_flag == false)
	{
		// �ǂ�hitbox������������
		HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32.0f, 512.0f - m_wall_gauge);
	}

	// �{�X���o�Ă����狭���I�ɕ߂鏈��
	if (objboss != nullptr || objenemy != nullptr||objstage5boss!=nullptr)
	{
		m_wall_down_flag = true;//�؂�ւ��t���O�I��
		m_wall_gauge = 0;		//wall������
		Audio::Stop(WALL);		//���y�X�g�b�v
	}

	//�ǂ����܂�����
	if (m_wall_down_gauge >= 512)
	{
		Audio::Stop(WALL);//���y�X�g�b�v
		m_wall_unlock_flag = false;
	}
	//�ǂ��J���Ă���Ƃ�
	else
	{
		//�ǂ�������t���O�I��
		if (m_wall_down_flag == true)
		{
			m_wall_down_gauge += 512;	//��ԉ��܂ŉ�����
			Audio::Start(WALL);		//�J��̉��y�X�^�[�g

			//hitbox���������Ȃ�
			HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32.0f,(float) m_wall_down_gauge);
		}
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px+29.0f, m_py+65.0f);
}

//�h���[
void CObjLastWall::Draw()
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
	src.m_bottom = 256.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY() - 190.0f;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 256.0f;

	//�`��(��̕���)
	Draw::Draw(GRA_LAST_WALL, &src, &dst, color, 0.0f);

	//�؂���ʒu
	src.m_top = (float)m_wall_gauge;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY() + 65.0f;
	dst.m_left = m_px - objmap->GetScrollX() + 30.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 512.0f - (float)m_wall_gauge;

	//�`��(���̕���)
	Draw::Draw(GRA_OPEN_WALL, &src, &dst, color, 0.0f);

	//-----------------------------------------------------
}