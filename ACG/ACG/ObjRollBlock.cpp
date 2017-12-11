//�g�p����w�b�_�[
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"
#include"GameL\Audio.h"
#include "GameL\HitBoxManager.h"

//�R���X�g���N�^
//����1,2	map�̗v�f�ԍ�
CObjRollBlock::CObjRollBlock(int x,int y,int pattan)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_pattan = pattan;
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjRollBlock::Init()
{
	m_count = 0;//�J�E���^�[�̏�����
	m_r = 0.0f;	//�p�x������

	m_roll_flag = false;//��]�̃t���O��������
	m_pos_adjustment_flag = false;

	m_audio_time = 29;//���y����p�̃^�C��������

	switch (m_pattan)
	{
		case 1:	//90f���Ƃɉ�]
		{	
			//����������X�^�[�g
			m_situation_width_flag = true;

			//��]�̒��S�ʒu�����߂�
			m_center_x = m_px + ROLL_BLOCK_SIZE_WIDTH / 2.0f;
			m_center_y = m_py + ROLL_BLOCK_SIZE_HEIGHT / 2.0f;

			//��]��̃|�W�V�����ƒ��S�ʒu�̍���
			m_difference_x = ROLL_BLOCK_SIZE_HEIGHT / 2.0f;
			m_difference_y = ROLL_BLOCK_SIZE_WIDTH / 2.0f;

			//�����蔻��Z�b�g
			Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
			break;
		}
		case 2:	//�����������Ƃ��Ɉ�x�̂݉�]
		{
			//�c��������X�^�[�g
			m_situation_width_flag = false;

			//��]�p�̃X�C�b�`���쐬
			CObjRollBlockSwitch* objrollblockswitch = new CObjRollBlockSwitch(m_px - ROLL_BLOCK_SWITCH_SIZE_WIDTH, m_py,(CObjRollBlock*)this);
			Objs::InsertObj(objrollblockswitch, OBJ_ROLL_BLOCK_SWITCH,10);

			//�c�Ɖ������ւ��ē����蔻��Z�b�g
			Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
			break;
		}
	}

	
}

//�A�N�V����
void CObjRollBlock::Action()
{
	
	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	
	switch (m_pattan)
	{
		case 1:	//90f���Ƃɉ�]
		{

			if (m_count <= 90)//90�ȉ��Ȃ�
				m_count++;//�J�E���g�𑝂₷

			//90f�ɂȂ�����
			if (m_count == 90)
			{
				m_roll_flag = true;//��]�̃t���O���I���ɂ���
			}

			if (m_roll_flag == true)//��]�����Ƃ�
			{
				m_r += 90.0f;	//�p�x�����Z

				//������ς���
				m_situation_width_flag = !(m_situation_width_flag);

				if (m_r >= 360.0f)	//360�x�ȏ�ɂȂ�Ȃ��悤�ɂ���
					m_r = 0.0f;

				//��]��̃|�W�V����������
				m_px = m_center_x - m_difference_x;
				m_py = m_center_y - m_difference_y;

				//�����̍X�V�ix��y�̓���ւ��j������
				float tmp = m_difference_x;
				m_difference_x = m_difference_y;
				m_difference_y = tmp;

				m_roll_flag = false;	//�t���O���I�t�ɂ���
				m_count = 0;			//�J�E���g��0�ŏ���������
			}
			break;

		}
		case 2:	//�����������Ƃ��Ɉ�x�̂݉�]
		{
			if (m_roll_flag == true)//��]�̃t���O���I���ɂȂ��Ă����
			{
				m_audio_time+=1;//���y����̂��߂�1���v���X���Ă���
				if (m_audio_time % 40 == 0)
				{
					Audio::Start(ROLLBLOCK);
				}
				m_r += 2.0f;//�܂킷
			}
			if (m_r > 90.0f)
			{
				m_r = 90.0f;//90�𒴂��Ȃ��悤�ɂ���
				m_situation_width_flag = true; //�������ɂ���
				Audio::Stop (ROLLBLOCK);
			}
			break;
		}
	}
	
	//�q�[���[�I�u�W�F�N�g�Ɠ������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//�Փˏ��������������
	}

	switch (m_pattan)
	{
		case 1:
		{
			if ( m_situation_width_flag == true)	//�������Ȃ�
			{
				//�����ƕ������̂܂܂œ����蔻��̍X�V
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH,ROLL_BLOCK_SIZE_HEIGHT);
			}
			else 	//�c�����Ȃ�
			{
				//�����ƕ����t�ɂ��Ă����蔻��̍X�V
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
			}
			break;
		}
		case 2:
		{
			if (m_situation_width_flag == true)	//�������i��]�I����
			{
				//�ŏ��̈�x�݈̂ʒu�̍X�V������
				if (m_pos_adjustment_flag == false)
				{
					m_px -= ROLL_BLOCK_SIZE_WIDTH;
					m_py += (ROLL_BLOCK_SIZE_WIDTH - ROLL_BLOCK_SIZE_HEIGHT);
					m_pos_adjustment_flag = true;
				}
				//�����ƕ������̂܂܂œ����蔻��̍X�V
				HitBoxUpData(hit, m_px , m_py , ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT);
			}
			else 	//�c�����Ȃ�
			{
				//�����ƕ����t�ɂ��Ă����蔻��̍X�V
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
			}

		}
	}
}

//�h���[
void CObjRollBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);


	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left= m_px - objmap->GetScrollX();

	switch (m_pattan)
	{
		case 1:
		{
			//�؂���ʒu�̐ݒ�
			src.m_right = ROLL_BLOCK_SIZE_WIDTH;
			src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;

			if ( m_situation_width_flag == true)	//������
			{
				//�`��ʒu�̐ݒ�
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
			}
			else//�c����
			{
				//�`��ʒu�̐ݒ�
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_HEIGHT;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;
			}

			//�`��
			Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r,-0.5f,-0.5f);
			break;
		}
		case 2:
		{
			if (m_situation_width_flag == true) //�������i��]�I����Ȃ�j
			{
				// �؂���ʒu�̐ݒ�
				src.m_right = ROLL_BLOCK_SIZE_HEIGHT;
				src.m_bottom = ROLL_BLOCK_SIZE_WIDTH;

				//�`��ʒu�̐ݒ�
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;

				//�`��
				Draw::Draw(GRA_ROLL_BLOCK2, &src, &dst, color, m_r);
			}
			else 
			{
				 //�؂���ʒu�̐ݒ�
				src.m_right = ROLL_BLOCK_SIZE_WIDTH;
				src.m_bottom = ROLL_BLOCK_SIZE_WIDTH;

				//�`��ʒu�̐ݒ�
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;

				//�`��
				Draw::Draw(GRA_ROLL_BLOCK2, &src, &dst, color, m_r,0.0f,-1.0f);
			}
			break;
		}
	}
}

//�q�[���[�����������Ƃ��̏���
void CObjRollBlock::HeroHit()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)//�q�b�g�f�[�^�������
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//��l���I�u�W�F�N�g�������Ă���
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//�������̂Ƃ��̓����蔻��
			if (m_situation_width_flag == true)
			{
				//�㑤���������Ă����
				if (35.0f < r && r < 145.0f)
				{
					objhero->SetHitDown(true);//��l��������Ă�����m_hit_down��true��Ԃ�

					 //�悹�鏈��
					objhero->SetPosY(m_py - 126.0f);//�u���b�N�̏㑤�ɒ��߂���

					//��l���̈ړ��x�N�g�����������Ȃ�
					if (objhero->GetVecY() > 0.0f)
						objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
				}
				//�������������Ă����
				else if (145.0f <= r && r <= 210.0f)
				{
					//���ɔ������鏈��
					//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetPosX(m_px - 48.5f);//��l���̈ʒu���u���b�N�̍��ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
					else
					{
						objhero->SetPosX(m_px - 60.5f);//��l���̈ʒu���u���b�N�̍��ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
				}
				//�E�����������Ă����
				else if (0.0f <= r && r <= 35.0f || 360.0f > r && 340.0f < r)
				{
					//�E�ɔ������鏈��
					//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetPosX(m_px + 190.5f);//��l���̈ʒu���u���b�N�̍��ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
					else
					{
						objhero->SetPosX(m_px + 180.5f);//��l���̈ʒu���u���b�N�̍��ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
				}

				//�������������Ă����
				else if (180.0f < r && r < 340.0f)
				{
					//���ɔ������鏈��
					objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_HEIGHT);//��l���̈ʒu���u���b�N�̉��ɂ���
					objhero->SetVecY(objhero->GetVecY());//��l����Y�����̈ړ��ʂ𔽓]����
				}
			}
			//�c�����̂Ƃ��̓����蔻��
			else
			{
				//�㑤���������Ă����
				if (68.0f < r && r < 112.0f)
				{
					objhero->SetHitDown(true);//��l��������Ă�����m_hit_down��true��Ԃ�
					//�悹�鏈��
					objhero->SetPosY(m_py - 126.0f);//�u���b�N�̏㑤�ɒ��߂���

					//��l���̈ړ��x�N�g�����������Ȃ�
					if (objhero->GetVecY() > 0.0f)
						objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
				}
				//�������������Ă����
				else if (112.0f <= r && r <= 250.0f)
				{
					//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetPosX(m_px - 48.5f);//��l�������t�g�̍��ɍs���悤�ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
					else//������
					{
						//�߂荞�ݖh�~�̂��ߍ������̂Ƃ���-64.0f�ɂ���
						//���ɔ������鏈��
						objhero->SetPosX(m_px - 60.5f);//��l���̈ʒu���u���b�N�̍��ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
				}
				//�E�����������Ă����
				else if (0.0f < r && r < 68.0f || 290.0f < r && r < 360.0f)
				{
					//�c�����Ȃ�
					//���t�g�ɂ̂߂肱�܂Ȃ��悤�ɂ��鏈��
					if (objhero->GetPosture() == 0.0f)//�E����
					{
						objhero->SetPosX(m_px + 60.5);//��l���̈ʒu���u���b�N�̉E�ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
					else//������
					{
						objhero->SetPosX(m_px + 48.5f);//��l���̈ʒu���u���b�N�̉E�ɂ���
						objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
					}
				}

				//�������������Ă����
				if (250.0f < r && r < 290.0f)
				{
					
					//�c�����Ȃ�
					objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_WIDTH);//��l���̈ʒu���u���b�N�̉��ɂ���
					objhero->SetVecY(objhero->GetVecY());//��l����Y�����̈ړ��ʂ𔽓]����
				}
			}
		}

	}
}