#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjHero.h"

//�h���[
void CObjHero::Draw()
{
	//�摜�̐؂���z��
	int AniData[4] =
	{
		1 , 0 , 1 ,2
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

	// ���[�v�ƃ��[�v�X�C�b�`���������Ă��邩�ǂ���������ϐ�
	bool rope_caught;

	if (obj_rope != nullptr)//���[�v�I�u�W�F�N�g���o�Ă���ꍇ
		rope_caught = obj_rope->GetCaughtFlag();//���[�v�����[�v�X�C�b�`�ɓ������Ă��邩�̏������炤
	else
		rope_caught = false;


	//�r---------------------------------------
	//�؂���ʒu
	src.m_top = 0.5f;
	src.m_left = 128.0f;
	src.m_right = 192.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu 
	dst.m_top = m_py - objmap->GetScrollY() + 43.0f;
	//�@��l�����E�������Ă��鎞�̘r�̕`��ʒu
	if (m_posture == 0.0f)
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	//�@��l�����E�������Ă��鎞�̘r�̕`��ʒu
	if (m_posture == 0.0f)
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);

	dst.m_bottom = dst.m_top + 59.0f;

	//�`��    ���[�v���o�Ă鎞�A�͂����ɓo���Ă鎞�A���[�v�ƃ��[�v�X�C�b�`���������Ă��鎞  ��l�������ɓ���������
	if (m_rope_ani_con == true || m_ladder_updown != 0 || rope_caught == true || m_hero_die_water == true || m_hero_die_enemy == true)
	{
		;    // �����`�悵�Ȃ�
	}
	else
		Draw::Draw(GRA_HERO, &src, &dst, color, m_r, -0.2f, -0.4f);
	//-----------------------------------------
	
	//�{��---------------------------------
	//�؂���ʒu

	//�G�ɓ���������
	if (m_hero_die_enemy == true)
	{
		//�G���������ė����̎��̃A�j���[�V����
		if (m_ani_frame_enemy_die == 0 || m_ani_frame_enemy_die == 1)
		{
			//�@��l�����E�������Ă��鎞�̕`��ʒu
			if (m_posture == 0.0f)
			{
				src.m_top = 832.0f;
				src.m_left = 0.0f + m_ani_frame_enemy_die * 64;
				src.m_right = 64.0f + m_ani_frame_enemy_die * 64;
				src.m_bottom = 958.0f;
			}
			//�@��l�������������Ă��鎞�̕`��ʒu
			else
			{
				src.m_top = 832.0f;
				src.m_left = 128.0f + m_ani_frame_enemy_die * 64;
				src.m_right = 190.0f + m_ani_frame_enemy_die * 64;
				src.m_bottom = 958.0f;
			}
		}
		//�t���[�����Q�ƂR�̎��|���A�j���[�V����
		else if (m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)
		{
			if (m_ani_frame_enemy_die == 2)
			{
				//�@��l�����E�������Ă��鎞�̕`��ʒu
				if (m_posture == 0.0f)
				{
					src.m_top = 960.0f;
					src.m_left = 0.0f;
					src.m_right = 128.0f;
					src.m_bottom = 1024.0f;
				}
				//�@��l�������������Ă��鎞�̕`��ʒu
				else
				{
					src.m_top = 960.0f;
					src.m_left = 256.0f;
					src.m_right = 374.0f;
					src.m_bottom = 1024.0f;
				}
			}
			else
			{
				//�@��l�����E�������Ă��鎞�̕`��ʒu
				if (m_posture == 0.0f)
				{
					src.m_top = 960.0f;
					src.m_left = 128.0f;
					src.m_right = 256.0f;
					src.m_bottom = 1024.0f;
				}
				//�@��l�������������Ă��鎞�̕`��ʒu
				else
				{
					src.m_top = 960.0f;
					src.m_left = 384.0f;
					src.m_right = 520.0f;
					src.m_bottom = 1024.0f;
				}
			}
		}
	}

	//���ɂ���������
	else if (m_hero_die_water == true)
	{
		//�t���[����0��1�Ȃ�������A�j���[�V����
		if (m_ani_frame_water_die == 0 || m_ani_frame_water_die == 1)
		{
			//�@��l�����E�������Ă��鎞�̕`��ʒu
			if (m_posture == 0.0f)
			{
				src.m_top = 641.0f;
				src.m_left = 0.0f + m_ani_frame_water_die * 64;
				src.m_right = 64.0f + m_ani_frame_water_die * 64;
				src.m_bottom = 768.0f;
			}
			//�@��l�������������Ă��鎞�̕`��ʒu
			else
			{
				src.m_top = 641.0f;
				src.m_left = 128.0f + m_ani_frame_water_die * 64;
				src.m_right = 190.0f + m_ani_frame_water_die * 64;
				src.m_bottom = 768.0f;
			}
		}
		else if (m_ani_frame_water_die == 2) //�t���[����2�Ȃ�|���A�j���[�V����
		{
			//�@��l�����E�������Ă��鎞�̕`��ʒu
			if (m_posture == 0.0f)
			{
				src.m_top = 769.0f;
				src.m_left = 0.0f;
				src.m_right = 128.0f;
				src.m_bottom = 826.0f;
			}
			//�@��l�������������Ă��鎞�̕`��ʒu
			else
			{
				src.m_top = 769.0f;
				src.m_left = 128.0f;
				src.m_right = 256.0f;
				src.m_bottom = 826.0f;
			}
		}
	}
	else if (m_ladder_updown == 1)//�͂����ɏ���Ă��鎞
	{
		src.m_top = 256.0f;
		src.m_left = 0.0f + m_ani_frame_ladders * 64;
		src.m_right = 64.0f + m_ani_frame_ladders * 64;
		src.m_bottom = 384.0f;
	}
	else if (m_ladder_updown == 2)//�͂�������肫��Ƃ�
	{
		//�����������ď��
		if (m_ani_frame_ladders == 0 || m_ani_frame_ladders == 3)
		{
			src.m_top = 256.0f;
			src.m_left = 320.0f;
			src.m_right = 384.0f;
			src.m_bottom = 384.0f;
		}
		//�E�����グ�ď��
		else if (m_ani_frame_ladders == 1 || m_ani_frame_ladders == 2)
		{
			src.m_top = 256.0f;
			src.m_left = 256.0f;
			src.m_right = 320.0f;
			src.m_bottom = 384.0f;
		}
	}
	else if (m_rope_ani_con == true || rope_caught == true) //���[�v�𓊂���Ƃ�
	{
		src.m_top = 515.0f;
		src.m_left = 0.0f + m_ani_frame_rope * 64;
		src.m_right = 64.0f + m_ani_frame_rope * 64;
		src.m_bottom = 640.0f;
	}
	else if (m_ladder_updown == 0 && m_hit_down == false && rope_caught == false)  //�W�����v���Ă��鎞
	{
		//�@��l�����E�������Ă��鎞�̕`��ʒu
		if (m_posture == 0.0f)
		{
			src.m_top = 128.0f;
			src.m_left = 256.0f;
			src.m_right = 320.0f;
			src.m_bottom = 256.0f;
		}
		//�@��l�������������Ă��鎞�̕`��ʒu
		else
		{
			src.m_top = 128.0f;
			src.m_left = 578.0f;
			src.m_right = 640.0f;
			src.m_bottom = 256.0f;
		}
	}
	else if (m_ani_frame_stop_move == 1 && m_ladder_updown == 0 && rope_caught == false)  //�~�܂��Ă���Ƃ�
	{
		//�@��l�����E�������Ă��鎞�̕`��ʒu
		if (m_posture == 0.0f)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 128.0f;
		}
		//�@��l�������������Ă��鎞�̕`��ʒu
		else
		{
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;
		}
	}
	else if (m_ani_frame_stop_move == 0 && m_ladder_updown == 0 && rope_caught == false)//�����Ă���Ƃ�
	{
		//�@��l�����E�������Ă��鎞�̕`��ʒu
		if (m_posture == 0.0f)
		{
			src.m_top = 129.0f;
			src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
			src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
			src.m_bottom = 256.0f;
		}
		//�@��l�������������Ă��鎞�̕`��ʒu
		else
		{
			src.m_top = 129.0f;
			src.m_left = 320.0f + AniData[m_ani_frame_move] * 64;
			src.m_right = 384.0f + AniData[m_ani_frame_move] * 64;
			src.m_bottom = 256.0f;
		}
	}

	//�`��ʒu
	//   ���ɂ���������l�����|��Ă鎞�@�@�G�ɓ������ē|��Ă��鎞
	if (m_ani_frame_water_die == 2 || m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)  //����G�ɂ����������i���񂾂Ƃ��j�̃A�j���[�V�����ŉ��ɓ|���t���[���p
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
		dst.m_bottom = dst.m_top + 64.0f;
	}
	else
	{
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + HERO_SIZE_HEIGHT;
	}

	//�`��
	Draw::Draw(GRA_HERO, &src, &dst, color, 0.0f);
	//�{��-------------------------------------

	//��ʑS�̂����񂾂�Â����鏈��----------------------------------
	//���񂾂��Ƃ��m�肵���ꍇ
	if (m_hero_die_water == true || m_hero_die_enemy == true || m_py > 2000.0f)
	{
		// ���F
		float radius_color[4] = { 0.f, 0.f, 0.f, 1.f };
		// �~�`��
		CircleDraw(-11.0f, radius_color, Die);
	}
	//----------------------------------------------------------------

	//---�~�̒����甒�����鏈��----------------------------------------
	// �S�[��������
	if (m_goal_flag == true)
	{
		// ���F
		float radius_color[4] = { 1.f, 1.f, 1.f, 1.f };
		// �~�`��
		CircleDraw(20.0f, radius_color, Clear);
	}
	//-----------------------------------------------------------------

	//�c�@�`��----------------------------------------------------------

	//�c�@����`�悷��
	wchar_t str2[128];//�`�悷��p��wchar_t�^��錾
	swprintf_s(str2, L"�~%d", m_remaining);//int�^��wcahr_t�^�ɕϊ�
	Font::StrDraw(str2, 48, 15, 30, color);//�`��

										   //�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 48.0f;
	dst.m_bottom = 50.0f;

	//�`��
	Draw::Draw(GRA_LIFE, &src, &dst, color, 0.0f);
}