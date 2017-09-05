//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{	
	//�}�b�v�I�u�W�F�N�g�������Ă���
	//CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	////�����蔻��
	//Hits::SetHitBox(this, m_px-obj_m->GetScrollX(), m_py - obj_m->GetScrollY(), BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
	m_b = false;
}

//�A�N�V����
void CObjBlock::Action()
{
	////���g��HitBox�������Ă���
	//CHitBox*hit = Hits::GetHitBox(this);

	//��l���I�u�W�F�N�g�ƏՓ˂��Ă����
	/*if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//�����蔻��̏������s��
	}*/
	
	////�{�X�I�u�W�F�N�g�ƏՓ˂��Ă����
	//if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	//{
	//	BossHit();//�����蔻��̏������s��
	//}

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��ʓ������ׂ�
	bool wincheck_flag =WindowCheck(m_px,m_py,BLOCK_SIZE,BLOCK_SIZE);

	//��ʂȂ��Ȃ�
	if (wincheck_flag == true)
	{
		//HitBox�̈ʒu���X�V����
//		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}
	else
	{
		//�}�b�v�v�f�ɐ��l������
		//obj_m->SetMap((m_px / BLOCK_SIZE), (m_py / BLOCK_SIZE), MAP_BLOCK);
	
		//�폜����̂Ŏ��ɗ����Ƃ��ɐ�������悤�Ƀt���O���I���ɂ���
		obj_m->SetMapCreate(int(m_px / BLOCK_SIZE), int(m_py / BLOCK_SIZE), true);

		this->SetStatus(false);		//���g���폜
	//	Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜
	}

}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	if (m_b==true)
	{
		src.m_top = 0.0f;
		src.m_left = 65.0f;
		src.m_right = 128.0f;
		src.m_bottom = 64.0f;
	}
	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(2, &src, &dst, color, 0.0f);
}

//�u���b�N�ƃI�u�W�F�N�g�̓����蔻��
void CObjBlock::BlockHit(
	float* x, float* y, float width, float height, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//�}�b�v���������Ă���
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	
	//�`��
	Draw::Draw(2, &src, &dst, color, 0.0f);
	//�Փˏ�񏉊���
	*up		= false;
	*left	= false;
	*right	= false;
	*down	= false;

	//���ƍ����𔼕��ɂ���
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//�u���b�N�̕��ƍ����𔼕��ɂ���
	float block_width_half  = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//���t���[���ł̈ړ��ꏊ
	float new_y = *y + *vy;
	float new_x = *x + *vx;
	
	scroll_on = false;
	//�X�N���[���������邩(��{��l���̂�)
	float scroll_x = scroll_on ? map->GetScrollX() : 0.0f;
	float scroll_y = scroll_on ? map->GetScrollY() : 0.0f;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//���肵�����u���b�N
			if (map->GetMap(j,i) == MAP_BLOCK/*100*/)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//�u���b�N�Ƃ̓����蔻��
				if (abs((bx + block_width_half) - (*x - scroll_x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y - scroll_y + height_half)) <= block_height_half + height_half)
					{
						//���Ɉړ����Ă���
						if (*vx < 0.0f)
						{
							//���ɂ���u���b�N
							for (int i = (int)((*y - scroll_y + 10.0f) / BLOCK_SIZE);
								i <= (int)((*y - scroll_y + height - 20.0f) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x - scroll_x + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉E�����Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (0 < map->GetMap(map_b_x, i) ||
									0 < map->GetMap(map_b_x, i))
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE + scroll_x;
									*right = true;
								}
							}
						}
						//�E�Ɉړ����Ă���
						else if (*vx > 0.0f)
						{
							//�E�ɂ���u���b�N
							for (int i = (int)((*y - scroll_y + 10.0f) / BLOCK_SIZE);
								i <= (int)((*y - scroll_y + height - 20.0f) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x - scroll_x + width + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̍������Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (0 < map->GetMap(map_b_x, i) ||
									0 < map->GetMap(map_b_x, i))
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width + scroll_x;
									*left = true;
								}
							}
						}

						//���Ɉړ����Ă���
						if (*vy > 0.0f)
						{
							//���ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x - scroll_x + 5.0f) / BLOCK_SIZE);
								i <= (int)((*x - scroll_x + width - 5.0f) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + height - scroll_y + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̏㑤���Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (0 < map->GetMap(i, map_b_y) ||
									0 < map->GetMap(i, map_b_y))
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE - height + scroll_y;
									*down = true;
								}
							}
						}
						//��Ɉړ����Ă���
						else if (*vy < 0.0f)
						{
							//��ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x - scroll_x + 5.0f) / BLOCK_SIZE);
								i <= (int)((*x - scroll_x + width - 5.0f) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y - scroll_y + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉������Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (0 < map->GetMap(i, map_b_y) ||
									0 < map->GetMap(i, map_b_y))
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE + scroll_y;
									*up = true;
									m_b = true;
								}
								
							}
						}
						return;
					}
				}
			}
		}
	}
}

void CObjBlock::HeroHit()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0.0f < r && r < 45.0f || 315.0f < r && r < 360.0f)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45.0f < r && r < 125.0f)
			{
				obj_hero->SetPosY(m_py - HERO_SIZE_Y);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125.0f < r && r < 225.0f)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px - HERO_SIZE_X);//��l���̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225.0f < r && r < 315.0f)
			{
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}
//�m�F�p�Ƀ{�X�ł�p�ӂ��܂����B����A�폜�ύX���Ă����܂��܂���B
void CObjBlock::BossHit()
{
	//���g��HitBox���擾
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;						//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_BOSS); //�Փ˂̏���hit_data�ɓ����

												//�f�o�b�O�p�{�X�I�u�W�F�N�g�����擾
	CObjBoss* obj_boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^����
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�Ԃ����Ă���p�x�������Ă���

									 //�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}