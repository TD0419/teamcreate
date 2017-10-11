#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjLadders.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLadders::CObjLadders(int x, int y)
{
	m_px = x * LADDERS_SIZE;
	m_py = y * LADDERS_SIZE;
	m_map_x = x;
	m_map_y = y;	
}

//�C�j�V�����C�Y
void CObjLadders::Init()
{
}

//�A�N�V����
void CObjLadders::Action()
{
}

//�h���[
void CObjLadders::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = LADDERS_SIZE;
	src.m_bottom = LADDERS_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LADDERS_SIZE;
	dst.m_bottom = dst.m_top + LADDERS_SIZE;

	//�`��
	Draw::Draw(5, &src, &dst, color, 0);
}

//�v���C���[�����������Ƃ��̏���
void CObjLadders::HeroHit(float px, float py)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��l���̃I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�v���C���[�̈ʒu���}�b�v�̗v�f�ԍ��ɒ���
	int map_num_x = (int)((px + BLOCK_SIZE / 2) / BLOCK_SIZE);//��������ɒ��ׂ�
	int map_num_y = (int)(py / BLOCK_SIZE);	//��l���̏�[����Œ��ׂ�
	int map_num_up = objmap->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���
	
	map_num_y = (int)((py) / BLOCK_SIZE) + 1;//��l���̒�������ɒ��ׂ�
	int map_num_center = objmap->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���	

	map_num_y = (int)((py + BLOCK_SIZE) / BLOCK_SIZE) + 1;//��l���̉��[����ɒ��ׂ�
	int map_num_down = objmap->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���	

	//��l�����͂�������肫�鎞�ɔ��肷��p
	int map_num_ladder = (int)(py / BLOCK_SIZE) + 1;	//��l���̏�[����Œ��ׂ�
	int map_num_ladder_up = objmap->GetMap(map_num_x, map_num_ladder);

	//�}�b�v�̒l���͂����Ȃ�
	if (map_num_up == MAP_LADDERS || map_num_center == MAP_LADDERS || map_num_down == MAP_LADDERS)
	{

		objhero->SetVecY(0.0f);//y�̈ړ�������������
		objhero->SetHitDown(true);//���n��Ԃɂ���
		objhero->SetLadderJump(1);//1��n��
		//W�L�[�������ꂽ�Ƃ� ���Ƃ�
		if (Input::GetVKey('W') == true)
		{
			objhero->SetVecY(-2.0f);

			//�͂�������肫�鎞��2��n��
			if (map_num_ladder_up == MAP_SPACE)
			{
				objhero->SetLaddersUpdown(2);
			}
			else
			{
				objhero->SetLaddersUpdown(1);//�͂���������Ă���Ƃ���1��n��
			}
			objhero->SetLaddersAniUpdown(1);//�A�j���[�V������i�߂�
		}

		//S�L�[�������ꂽ�Ƃ��@����Ƃ�
		else if (Input::GetVKey('S') == true)
		{
			objhero->SetVecY(2.0f);
			objhero->SetLaddersUpdown(1);//�͂����������Ă���Ƃ���1��n��
			objhero->SetLaddersAniUpdown(1);//�A�j���[�V������i�߂�
		}
		//����ȊO�̎�
		else
		{
			objhero->SetLaddersAniUpdown(0);//�A�j���[�V�������~�߂�
		}
		
	}
	else
	{
		objhero->SetLaddersUpdown(0);//��l�����͂����ɓ������ĂȂ��Ƃ���0��n��
		objhero->SetLadderJump(0);//�[����n��
	}
	
}