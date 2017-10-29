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
	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{	
}

//�A�N�V����
void CObjBlock::Action()
{
	
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��ʓ������ׂ�
	bool wincheck_flag =WindowCheck(m_px,m_py,BLOCK_SIZE,BLOCK_SIZE);

	//��ʊO�Ȃ�
	if (wincheck_flag == false)
	{
		//�폜����̂Ŏ��ɗ����Ƃ��ɐ�������悤�Ƀt���O���I���ɂ���
		objmap->SetMapCreate(m_map_x, m_map_y, true);
		this->SetStatus(false);		//���g���폜
	}

}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//map_num�Ƀ}�b�v���̈��̏��𑗂�
	int map_num = objmap->GetMap(m_map_x, m_map_y - 1);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�u���b�N�̈��Ƀu���b�N�����鎞�`��ύX
	if (map_num==MAP_BLOCK)
	{
		src.m_top = 0.0f;
		src.m_left = 65.0f;
		src.m_right = 128.0f;
		src.m_bottom = 64.0f;
	}
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(2, &src, &dst, color, 0.0f);
}

//�u���b�N�ƃI�u�W�F�N�g�̓����蔻��
void CObjBlock::BlockHit(
	float* x, float* y, float width, float height,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//�}�b�v���������Ă���
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�Փˏ�񏉊���
	*up = false;
	*left = false;
	*right = false;
	*down = false;

	//���ƍ����𔼕��ɂ���
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//�u���b�N�̕��ƍ����𔼕��ɂ���
	float block_width_half = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//���t���[���ł̈ړ��ꏊ
	float new_y = *y + *vy;
	float new_x = *x + *vx;

	//�͂ݏo�����e�͈�
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//���肵�����u���b�N
			if (map->GetMap(j, i) == MAP_BLOCK)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//�u���b�N�Ƃ̓����蔻��
				if (abs((bx + block_width_half) - (*x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y + height_half)) <= block_height_half + height_half)
					{
						//���Ɉړ����Ă���
						if (*vx < 0.0f)
						{
							//���ɂ���u���b�N
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉E�����Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE;
									*right = true;
								}
							}
						}
						//�E�Ɉړ����Ă���
						else if (*vx > 0.0f)
						{
							//�E�ɂ���u���b�N
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x + width + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̍������Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width;
									*left = true;
								}
							}
						}

						//���Ɉړ����Ă���
						if (*vy > 0.0f)
						{
							//���ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + height + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̏㑤���Փ˂��Ă���ꍇ(�u���b�N(1))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE - height;
									*down = true;
								}
							}
						}
						//��Ɉړ����Ă���
						else if (*vy < 0.0f)
						{
							//��ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉������Փ˂��Ă���ꍇ(�u���b�N(1))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE;
									*up = true;
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

//�S�Ẵu���b�N�ƃI�u�W�F�N�g�̓����蔻��
void CObjBlock::AllBlockHit(
	float* x, float* y, float width, float height,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//�}�b�v���������Ă���
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�Փˏ�񏉊���
	*up = false;
	*left = false;
	*right = false;
	*down = false;

	//���ƍ����𔼕��ɂ���
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//�u���b�N�̕��ƍ����𔼕��ɂ���
	float block_width_half = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//���t���[���ł̈ړ��ꏊ
	float new_y = *y + *vy;
	float new_x = *x + *vx;

	//�͂ݏo�����e�͈�
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//���肵�����u���b�N
			if (map->GetMap(j, i) == MAP_BLOCK || map->GetMap(j, i) == MAP_THROUGH_BLOCK)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//�u���b�N�Ƃ̓����蔻��
				if (abs((bx + block_width_half) - (*x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y + height_half)) <= block_height_half + height_half)
					{
						//���Ɉړ����Ă���
						if (*vx < 0.0f)
						{
							//���ɂ���u���b�N
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉E�����Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK || map->GetMap(map_b_x, i) == MAP_THROUGH_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE;
									*right = true;
								}
							}
						}
						//�E�Ɉړ����Ă���
						else if (*vx > 0.0f)
						{
							//�E�ɂ���u���b�N
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x + width + *vx) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̍������Փ˂��Ă���ꍇ(�������Ă���̂�0�ȊO)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK || map->GetMap(map_b_x, i) == MAP_THROUGH_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width;
									*left = true;
								}
							}
						}

						//���Ɉړ����Ă���
						if (*vy > 0.0f)
						{
							//���ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + height + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̏㑤���Փ˂��Ă���ꍇ(�u���b�N(1)�ƃX���[�u���b�N(12))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK || map->GetMap(i, map_b_y) == MAP_THROUGH_BLOCK)
								{
									*vy = 0.0f; 
									*y = map_b_y * BLOCK_SIZE - height;
									*down = true;
								}
								//�i�ސ悪�u���b�N�̏㑤���Փ˂��Ă���ꍇ(�͂���(2))
								if (map->GetMap(i, map_b_y) == MAP_LADDERS)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE - height;
									*down = true;
								}
							}
						}
						//��Ɉړ����Ă���
						else if (*vy < 0.0f)
						{
							//��ɂ���u���b�N��S�Ē��ׂ�
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + *vy) / BLOCK_SIZE);
								//�i�ސ悪�u���b�N�̉������Փ˂��Ă���ꍇ(�u���b�N(1))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK || map->GetMap(i, map_b_y) == MAP_THROUGH_BLOCK)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE;
									*up = true;
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


//Hero�I�u�W�F�N�g�Ƃ��������Ƃ��̏���
void CObjBlock::HeroHit()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�������Ă��鐔���܂킷�B
	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0.0f < r && r < 45.0f || 315.0f < r && r < 360.0f)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45.0f < r && r < 125.0f)
			{
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125.0f < r && r < 225.0f)
			{
				objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				objhero->SetPosX(m_px - HERO_SIZE_WIDTH);//��l���̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225.0f < r && r < 315.0f)
			{
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosY(m_py + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}