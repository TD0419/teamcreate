//�g�p����w�b�_�[�t�@�C��
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFallingBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFallingBlock::CObjFallingBlock(int x, int y)
{

	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
	m_return_block_y = m_py;//Y���W������
}

//�C�j�V�����C�Y
void CObjFallingBlock::Init()
{
	m_falling_time = 10;	//�u���b�N��������܂ł̎���
	m_fallint_start_flag = false;

	
	m_screen_out = false;		//�u���b�N����ʊO�ɏo�Ă��邩�𒲂ׂ�


	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_GIMMICK, OBJ_FALLING_BLOCK, 1);
}

//�A�N�V����
void CObjFallingBlock::Action()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�}�b�v�̊O���܂ł�����
	if (m_py > BLOCK_SIZE * MAP_Y_MAX)
	{
		Audio::Stop(GROUND);
		m_screen_out = true;//��ʊO�Ƀu���b�N���o�Ă���
	}
	else
	{
		m_screen_out = false;//��ʊO�Ƀu���b�N���o�Ă��Ȃ�
	}

	//�X�e�[�W5�{�X�̃I�u�W�F�N�g�̎擾
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	bool stage5boss_atk4_count = false;//�X�e�[�W5�{�X�̍U���S�p�J�E���^�[�̏��擾�p
	bool stage5boss_death_flag = false;//�X�e�[�W5�{�X�̎��S�t���O�̏��擾�p

	if (objboss != nullptr)//�{�X�I�u�W�F�N�g�������
	{
		//�X�e�[�W5�{�X�̎��S�t���O�̏����擾����
		stage5boss_death_flag = objboss->GetBossDeathFlag();
		
		//�u���b�N�������ʒu�ɖ߂����߂̃t���O
		stage5boss_atk4_count = objboss->GetBlockRetuenFlag();

		//���������邩�̃t���O���X�V
		m_fallint_start_flag = objboss->GetBlockDownFlag();
	}
	
	//�{�X�̍U��4�̃J�E���^�[��300�t���[���o�߂�����A�u���b�N�������ʒu�ɖ߂�
	if (stage5boss_atk4_count == true || stage5boss_death_flag == true)
	{
		m_py = m_return_block_y;//�����ʒu�Ƀu���b�N��߂�
		m_falling_time = 10;	//�u���b�N��������܂ł̎���
		m_fallint_start_flag = false;//�����t���O���I�t�ɂ���
		hit->SetInvincibility(false);//���g�̓����蔻�������
	}
	

	if (m_fallint_start_flag == true)//�����J�n�t���O���I���Ȃ�
		m_falling_time--;
	

	//�^�C����0�ɂȂ�Ɖ��ɗ�����
	if (m_falling_time < 0)
	{
		m_py += 1.0f;
		Audio::Start(GROUND);
		
	}
	//������u���b�N����苗����������A���g�̓����蔻����Ȃ���
	if (m_py>PERDECISION_CLEAR_POINT)
	{
		hit->SetInvincibility(true);//�����蔻����Ȃ���
	}

	//�q�[���[�I�u�W�F�N�g�Ɠ������Ă����
	if (hit != nullptr)
	{
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			HeroHit();//�Փˏ���������
		}
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(hit, m_px, m_py);
	}
}

//�h���[
void CObjFallingBlock::Draw()
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
	if (map_num == MAP_FALLING_BLOCK)
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
	Draw::Draw(GRA_BLOCK, &src, &dst, color, 0.0f);
}

//��l�������������Ƃ��̏���
void CObjFallingBlock::HeroHit()
{
	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;										//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);					//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)								//�q�b�g�f�[�^�������
		{
			float r = hit_data[i]->r;							//�������Ă���p�x�������Ă���

			//�㑤���������Ă����
			if (45.0f < r && r < 135.0f)
			{
				objhero->SetHitDown(true);						//��l��������Ă�����m_hit_down��true��Ԃ�
																//�悹�鏈��
				objhero->SetPosY(m_py - BLOCK_SIZE - 63.0f);				//�u���b�N�̏㑤�ɒ��߂���

																//��l���̈ړ��x�N�g�����������Ȃ�
				if (objhero->GetVecY()>1.0f)
					objhero->SetVecY(1.0f);						//��l����Y�����̈ړ���0�ɂ���
			}
			//�������������Ă����
			else if (135.0f <= r && r <= 180.0f)
			{
				//block�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
				if (objhero->GetPosture() == 0.0f)//�E����
				{
					//���ɔ������鏈��
					objhero->SetPosX(m_px - 49.0f);	//��l���̈ʒu���u���b�N�̍��ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ��ʂ𔽓]����
				}
				else
				{
					//�E�ɔ������鏈��
					objhero->SetPosX(m_px - 61.5f);	//��l���̈ʒu���u���b�N�̍��ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ��ʂ𔽓]����
				}
			}
			//�E�����������Ă����
			else if (0.0f <= r && r <= 45.0f)
			{
				//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
				if (objhero->GetPosture() == 0.0f)//�E����
				{
					//���ɔ������鏈��
					objhero->SetPosX(m_px + 61.5f);	//��l���̈ʒu���u���b�N�̉E�ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ��ʂ𔽓]����
				}
				else
				{
					//�E�ɔ������鏈��
					objhero->SetPosX(m_px + 49.7f);	//��l���̈ʒu���u���b�N�̉E�ɂ���
					objhero->SetVecX(0.0f);//��l����X�����̈ړ��ʂ𔽓]����
				}
			}

			//�������������Ă����
			else if (180.0f < r && r < 360.0f)
			{
				//���ɔ������鏈��
				objhero->SetPosY(m_py + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̉��ɂ���
				objhero->SetVecY(-1.0f * objhero->GetVecY());	//��l����Y�����̈ړ��ʂ𔽓]����
			}
		}
	}
}