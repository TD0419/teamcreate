#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//���[�h0,1��p
//����1		int px			:�}�b�v�̐��l(X�ʒu)
//����2		int py			:�}�b�v�̐��l(Y�ʒu)
//����3		int direction	:�ړ�����(���[�h���蓮�̂Ƃ��͎����œ�������)�@�O���E�F�P�����F�Q����F�R����
//����4		int	width_max	:	X�����ւ̍ő�ړ���(�����ʒu�`�ő�ړ��ʕ������܂��B)
//����5		int mode			:���t�g�̓������[�h
//			�O���蓮���[�h(���R�X�C�b�`�ɓ��ĂĈړ����郂�[�h)
//			�P�����R�ړ����[�h(�����ʒuX����ő�X�ʒu�̊Ԃ������ړ�)
//			�Q�������ړ����[�h(��܂��͉��ɍs����ʊO�ɍs���Ə�Ȃ牺����A���Ȃ�ォ��o�Ă���)
CObjLift::CObjLift(int px,int py,int direction,float width_max,int mode)
{
	//�����ʒu�����߂�
 	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;
	
	//�ړ������Ə����ړ����������߂�
	m_direction = direction;
	m_initial_direction = direction;

	//�ő�ړ��ʂ����߂�
	//�l�����̐��Ȃ琳�̐��ɂ���
	if (width_max < 0)
		width_max *= -1;

	//X�����̍ő�ړ��ʂ��Z�b�g
	m_width_max = width_max;

	//�ړ����[�h�����߂�
	m_move_mode = mode;

	//�}�b�v�����擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//���߂̃u���b�N�̈ʒu�܂ł��ړ���ԂƂ��邩�̌�
	int block_count = 0;
	int block_max_count = (int)(LIFT_SIZE_WIDTH / BLOCK_SIZE);//MAX�l

	//�ړ������Ə����ړ������ƍő�ړ��ʂ����߂�
	//�}�b�v�̈ʒu(���t�g)�̍�������C�Ȃ珉���ړ������͉E
	if (objmap->GetMap(px - 1, py + 1)== MAP_SPACE)
	{
		if (mode == 0)
		{
			//�ړ������Ə����ړ����������߂�
			m_direction = 0;
			m_initial_direction = 0;
		}
		else
		{
			//�ړ������Ə����ړ����������߂�
			m_direction = 1;
			m_initial_direction = 1;
		}
		//�ő�ړ��ʂ����߂�
		for (int i = px-1; i >= 0; i--)
		{
			//�}�b�v�̈ʒu(���t�g)�������獶���߂��ق����璲�ׂĂ���
			//���t�g�̕�/BLOCK_SIZE�߂ɂ���u���b�N�ʒu�܂ł��ړ���ԂƂ���
			if (objmap->GetMap(i, py + 1) == MAP_BLOCK)
			{
				//�J�E���g��i�߂�
				block_count++;
				if (block_count >= block_max_count)
				{
					m_width_max = (px * BLOCK_SIZE) - (i*BLOCK_SIZE);
					break;
				}
			}
		}
	}
	//�}�b�v�̈ʒu(���t�g)�̉E������C�Ȃ̂ŏ����ړ���������
	else
	{
		if (mode == 0)
		{
			//�ړ������Ə����ړ����������߂�
			m_direction = 1;
			m_initial_direction = 1;
		}
		else
		{
			//�ړ������Ə����ړ����������߂�
			m_direction = 0;
			m_initial_direction = 0;
		}
		//�ő�ړ��ʂ����߂�
		for (int i = px + block_max_count; i < MAP_X_MAX; i++)
		{
			//�}�b�v�̈ʒu(���t�g)�E��block_max_count,����1����E���߂��ق����璲�ׂĂ���
			//���t�g�̕�/BLOCK_SIZE�߂ɂ���u���b�N�ʒu�܂ł��ړ���ԂƂ���
			if (objmap->GetMap(i, py + 1)== MAP_BLOCK)
			{
				//�J�E���g��i�߂�
				block_count++;
					
				m_width_max = (i*BLOCK_SIZE) - (px * BLOCK_SIZE);
				break;
			}
		}
	}
	
}

//�R���X�g���N�^
//���[�h�Q��p
//����1		int px			:�}�b�v�̐��l(X�ʒu)
//����2		int py			:�}�b�v�̐��l(Y�ʒu)
//����3		int direction	:�ړ�����(���[�h���蓮�̂Ƃ��͎����œ�������)�@�O���E�F�P�����F�Q����F�R����
CObjLift::CObjLift(int px, int py, int direction)
{
	//�����ʒu�����߂�
	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;

	//�ړ������Ə����ړ����������߂�
	m_direction = direction;
	m_initial_direction = direction;

	//�ړ����[�h�Z�b�g
	m_move_mode = 2;

	//���[�h�Q�̂Ƃ��͎g��Ȃ����Ǐ��������Ă���
	m_width_max = 0.0f;
}
//�C�j�V�����C�Y
void CObjLift::Init()
{
	//�ړ��ʂ�0�ɂ���
	m_move_x = 0.0f;
	m_move_y = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	
	//���t�g�̃J�E���g������
	m_lift_audio_count = 47;

	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		case 2:
		{
			//�����蔻��
			Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE_WIDTH, LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);
			break;
			
		}
		case 5:
		{
			//�����蔻��
			Hits::SetHitBox(this, m_px, m_py, STAGE5_LIFT_SIZE_WIDTH, STAGE5_LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);
			break;
		}
	}

	
}

//�A�N�V����
void CObjLift::Action()
{
	
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	
	//��l�����������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//��l�����悹�鏈��������
	}

	//�e�ړ����[�h(m_move_mode)�ɂ��ړ�
	ModeMove();
	
	//�ʒu�����X�V
	m_px += m_vx;
	m_py += m_vy;

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
}

//�h���[
void CObjLift::Draw()
{	
	//map�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��F�����߂�
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	
	
	//�`��̈ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();

	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		case 2:
		{
			//�؂���
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 32.0f;

			//�`��
			dst.m_right = dst.m_left + LIFT_SIZE_WIDTH;
			dst.m_bottom = dst.m_top + LIFT_SIZE_HEIGHT;

			break;
		}
		case 5:
		{
			//�؂���
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 320.0f;
			src.m_bottom = 16.0f;

			//�`��
			dst.m_right = dst.m_left + STAGE5_LIFT_SIZE_WIDTH;
			dst.m_bottom = dst.m_top + STAGE5_LIFT_SIZE_HEIGHT;

			break;
		}
	}
	
	//���t�g�̕`��
	Draw::Draw(GRA_LIFT, &src, &dst, color, 0.0f);
}

//��l�����悹�鏈��������
void CObjLift::HeroRide()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_px = objhero->GetPosX();//��l���̈ʒuX�������Ă���

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�㑤���������Ă���΂�
			if (30.0f <= r && r <= 155.0f)
			{
				objhero->SetHitDown(true);//���t�g�̏�Ɏ�l��������Ă�����m_hit_down��true��Ԃ�

				//���t�g�ɏ悹�鏈��
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
				objhero->SetPosX(h_px + m_vx);//��l���̈ʒu�����Ƃ��Ǝ�l���������ʒu�{���t�g�̈ړ��ʂɂ���
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 2.5f + m_vy);//��l���̃|�W�V���������t�g�̏�ɂ���
			}
			//�E�����������Ă���΂�
			if (0.0f <= r && r < 30.0f)
			{
				switch (((UserData*)Save::GetData())->stagenum)
				{
				case 1:
				case 2:
				{
					if (objhero->GetPosture() == 1.0f)//������
					{
						//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
						objhero->SetPosX(m_px + LIFT_SIZE_WIDTH - 14.5f);//��l�������t�g�̉E�ɍs���悤�ɂ���
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						break;
					}
					else//�E����
					{
						//�����蔻��̂��ꂩ��U���������߂荞��ł��܂��̂ŁA-14.5f���폜
						objhero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
						objhero->SetPosX(m_px + LIFT_SIZE_WIDTH);
						break;
					}
				}
				case 5:
				{
					
					break;
				}
				}
			}
			//�������������Ă���΂�
			if (155.0f < r && r < 180.0f)
			{
				switch (((UserData*)Save::GetData())->stagenum)
				{
					case 1:
					case 2:
						//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
						if (objhero->GetPosture() == 0.0f)//�E����
						{
							objhero->SetPosX(m_px - 48.5f);//��l�������t�g�̍��ɍs���悤�ɂ���
						}
						else//������
						{
							//�߂荞�ݖh�~�̂��ߍ������̂Ƃ���-64.0f�ɂ���
							objhero->SetPosX(m_px - 64.0f);//��l�������t�g�̍��ɍs���悤�ɂ���
						}
					case 5:
					{
						break;
					}
				}
			}
		}
	}
}

//�e�ړ����[�h(m_move_mode)�ɂ��ړ��֐�
void CObjLift::ModeMove()
{
	//�e�ړ����[�h�ɂ��ړ�
	switch (m_move_mode)
	{
		//------------------------------���R�X�C�b�`�ɓ��ĂĈړ����郂�[�h------------------------------
	case 0:
		//���[�v�I�u�W�F�N�g�������Ă���
		CObjRopeSwitch* objrope_switch;
		objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
		//���[�v�X�C�b�`��񂪂��邩��
		//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
		if (objrope_switch != nullptr && objrope_switch->GetRopeFlag() == true)
		{
			//A�L�[�������ꂽ��
			if (Input::GetVKey('A'))
			{
				//�����ʒu���瓮����������MAX������������ړ�
				if (m_move_x < m_width_max)
				{
					//�����ʒu���瓮���������𑝂₷
					m_move_x += SPEED;
					//�����̈ړ��������E�̂Ƃ�
					if (m_initial_direction == 0)
					{
						//���ɐi��
						m_vx = -SPEED;
						m_lift_audio_count++;
						if (m_lift_audio_count % 50 == 0)
						{
							Audio::Start(PULLLIFT);
						}
					}
					//�����̈ړ����������̂Ƃ�
					else
					{
						//�E�ɐi��
						m_vx = SPEED;
					}

				}
			}
			//A�L�[��������Ă��Ȃ��Ȃ�X�ړ��O
			else
			{
				m_vx = 0.0f;
			}
		}
		else//���[�v�ƃ��[�v�X�C�b�`���������Ă��Ȃ��Ƃ�
		{
			//�����ʒu���瓮�����������O�𒴂��Ă�����ړ�
			if (m_move_x > 0)
			{
				//�����ʒu�ɋ߂Â��̂Ō��Z
				m_move_x -= SPEED;

				//�����̈ړ��������E��������
				if (m_initial_direction == 0)
				{
					//�E�Ɉړ�
					m_vx = SPEED;
					m_lift_audio_count++;
					if (m_lift_audio_count % 50 == 0)
					{
						Audio::Start(RELEASELIFT);
					}
				}
				//�����̈ړ������͍���������
				else
				{
					//���Ɉړ�
					m_vx = -SPEED;
				}
			}
		}

		//�����ʒu���瓮�����������ő�ʂ𒴂����
		if (m_move_x > m_width_max)
		{
			//�����̈ړ��������E��������
			if (m_initial_direction == 0)
			{
				//�s���߂��������v�Z
				m_vx = m_move_x - m_width_max;
			}
			//�����̈ړ�����������������
			else
			{
				//�s���߂��������v�Z
				m_vx = m_move_x - m_width_max;
			}
			m_move_x = m_width_max;//�ړ��ʂ̏�����
		}
		//�����ʒu���瓮�����������O������������
		if (m_move_x < 0)
		{
			//�����̈ړ��������E��������
			if (m_initial_direction == 0)
			{
				//�s���߂��������v�Z
				m_vx = m_move_x;
			}
			//�����̈ړ�����������������
			else
			{
				//�s���߂��������v�Z
				m_vx = m_move_x;
			}
			m_move_x = 0;
		}

		//�����ʒu���瓮�����������O�܂���MAX�Ȃ�ړ��x�N�g�����O�ɂ���
		if (m_move_x == 0 || m_move_x == m_width_max)
			m_vx = 0.0f;
		break;
		//------------------------------���R�ړ����[�h(�ő�EX�ʒu����ő�l��X�ʒu�̊Ԃ������ړ�)---------------
	case 1:
		//�ړ��������E�̎�
		if (m_direction == 0)
		{
			//�ړ��x�N�g��X�����Z
			m_vx = SPEED;
			//�����ړ��������E�Ȃ�
			if (m_initial_direction == 0)
				m_move_x += SPEED;//�����ʒu�ɋ߂Â��̂ŉ��Z
								  //�����ړ����������Ȃ�
			else
				m_move_x -= SPEED;//�����ʒu���痣���̂Ō��Z
		}
		//�ړ����������̎�
		else
		{
			//�ړ��x�N�g��X�����Z
			m_vx = -SPEED;
			//�����ړ��������E�Ȃ�
			if (m_initial_direction == 0)
				m_move_x -= SPEED;//�����ʒu���痣���̂Ō��Z
								  //�����ړ����������Ȃ�
			else
				m_move_x += SPEED;//�����ʒu�ɋ߂Â��̂ŉ��Z
		}

		//�����ʒu���瓮�����������O�܂���MAX�l��������
		//���݂̈ړ����������E�t�ɂ���
		if (m_move_x == 0 || m_move_x == m_width_max)
		{
			//���݂̈ړ��������E�Ȃ獶��
			if (m_direction == 0)
				m_direction = 1;
			//���Ȃ�E�ɂ���
			else
				m_direction = 0;
		}

		//�����ʒu���瓮����������MAX�z���܂��͂O�ȉ���������
		//�s���߂������𒲐����Č��݂̈ړ����������E�t�ɂ���
		else if (m_move_x > m_width_max || m_move_x < 0)
		{
			//�s���߂�����
			//�����ʒu���瓮����������MAX�z���Ȃ�
			if (m_move_x > m_width_max) 
			{
				//���݂̈ړ��������E
				if (m_direction == 0)
				{
					//�܂������ʒu���瓮����������MAX�ɂȂ�ʒu�܂Ői�߂�
					m_vx = m_width_max - (m_move_x - SPEED);
					//�����������ړ�������
					m_vx -= m_move_x - m_width_max;
				}
				//���݂̈ړ���������
				else
				{
					//�܂������ʒu���瓮����������MAX�ɂȂ�ʒu�܂Ői�߂�
					m_vx = (m_width_max - (m_move_x - SPEED))*-1;
					//�����������ړ�������
					m_vx += m_move_x - m_width_max;

				}
				//�����ʒu���瓮�����������v�Z
				m_move_x -= (m_move_x - m_width_max) * 2;
			}
			//�����ʒu���瓮�����������O�����Ȃ�
			else
			{
				//���݂̈ړ��������E
				if (m_direction == 0)
				{
					//�܂������ʒu���瓮�����������O�̂Ƃ��̈ʒu�܂Ői�߂�
					m_vx = m_move_x + SPEED;
					//�����������ړ�������
					m_vx += m_move_x;
				}
				//���݂̈ړ���������
				else
				{
					//�܂������ʒu���瓮�����������O�̂Ƃ��̈ʒu�܂Ői�߂�
					m_vx = (m_move_x + SPEED)*-1;
					//�����������ړ�������
					m_vx += m_move_x*-1;
				}
				////�����ʒu���瓮�����������v�Z
				m_move_x *= -1;
			}
			//���݂̈ړ����������E�t�ɂ���
			if (m_direction == 0)
				m_direction = 1;
			else
				m_direction = 0;
		}
		break;
		//--------------------�����ړ����[�h(��܂��͉��ɍs����ʊO�ɍs���Ə�Ȃ牺����A���Ȃ�ォ��o�Ă���)--------
	case 2:
		//��̌��EY�ʒu
		//���̒l����ɍs�����牺�̌��EY�ʒu����o�Ă���
		float up_limti;
		up_limti = (MAP_Y_MAX - 12)*BLOCK_SIZE - LIFT_SIZE_HEIGHT;
		//���̌��EY�ʒu
		//���̒l��艺�ɍs�������̌��EY�ʒu����o�Ă���
		float down_limti;
		down_limti = MAP_Y_MAX*BLOCK_SIZE;
		//���݂̈ړ������ɂ��ړ�
		if (m_direction == 2)
		{
			m_vy = -SPEED;
		}
		else
		{
			m_vy = SPEED;
		}
		//��̌��EY�ʒu���ゾ������
		if (m_py < up_limti)
		{
			//���݂̈ړ��������ゾ������
			//�Ӗ��������������ǈꉞ���������͂���
			if (m_direction == 2)
			{
				//�s���߂�������vy�ɓ����
				m_vy = m_py - up_limti;
				//Y�ʒu�����̌��EY�ʒu�ɂ���
				m_py = down_limti;
			}
		}
		//���̌��EY�ʒu��艺��������
		if (m_py > down_limti)
		{
			//���݂̈ړ�����������������
			//�Ӗ��������������ǈꉞ���������͂���
			if (m_direction == 3)
			{
				//�s���߂�������vy�ɓ����
				m_vy = m_py - down_limti;
				//Y�ʒu����̌��EY�ʒu�ɂ���
				m_py = up_limti;
			}
		}
		break;
	default:
		break;
	}
}