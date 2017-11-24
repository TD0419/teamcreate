#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//����1,2�@�����ۂ������
//����3	�c�@��
CObjHero::CObjHero(int x, int y, int remaining)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	//�c�@���̏�����
	m_remaining = remaining;	
}

//�A�N�V����
void CObjHero::Action()
{

	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��l���̍����A�^���A�E���ɂ���u���b�N�����擾
	//�^���̃u���b�N����D�悷��
	for (int i = 0; i < 3; i++)
	{
		//��l����X�ʒu(���� = 0;�^�� = HERO_SIZE_WIDTH/2;�E�� = HERO_SIZE_WIDTH)
		int pos_x = 0;
		//�E��
		if (i == 1)
		{
			pos_x = (int)HERO_SIZE_WIDTH;
		}
		//����
		else if (i == 2)
		{
			pos_x = (int)HERO_SIZE_WIDTH / 2;
		}
		//��l����X�ʒu(�}�b�v�̗v�f��)
		int x = ((int)m_px + pos_x) / (int)BLOCK_SIZE;
		//��l����Y�ʒu(�}�b�v�̗v�f��)
		//�������ɂ���
		int y = ((int)m_py + 1 + (int)HERO_SIZE_HEIGHT) / (int)BLOCK_SIZE;
		//�u���b�N���0�Ŗ����Ȃ�擾
		if (objmap->GetMap(x, y) != 0)
		{
			m_block_type = objmap->GetMap(x, y);
		}
	}
	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��2000�ȉ��Ȃ烊�X�^�[�g����
	if (m_hero_die_screen_out == true)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain(-1));
	}

	//�}�E�X�̈ʒu���擾
	m_mous_x = (float)Input::GetPosX();
	m_mous_y = (float)Input::GetPosY();

	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	LandingCheck();//���n�t���O�̍X�V


	//�͂���-------------------------------------------------LadderScene()
	//�͂����I�u�W�F�N�g�������Ă���
	CObjLadders* objladders = (CObjLadders*)Objs::GetObj(OBJ_LADDERS);

	if (objladders != nullptr)
	{
		//��l���̂����ɒʏ�u���b�N����������͂����ɏ���Ă��Ȃ�����ɂ���
		if (m_block_type == MAP_BLOCK)
		{
			//�͂����ɓo���Ă��Ȃ�
			m_ladder_updown = 0;
		}

		objladders->HeroHit(m_px, m_py);//�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	}

	//�͂����̃A�j���[�V�����^�C����i�߂�
	m_ani_time_ladders += m_ladder_ani_updown;//�͂����������Ă���

	//�͂�����MAXTIME�𒴂���ƃA�j���[�V������i�߂�
	if (m_ani_time_ladders > m_ani_max_time_ladders)
	{
		m_ani_frame_ladders += 1;
		m_ani_time_ladders = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame_ladders == 4)
	{
		m_ani_frame_ladders = 0;
	}


	//�͂����I��---------------------------------------------

	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[MoveScene
	//���[�v���o���Ă��鎞�Ɛ��ɓ����������ƓG�ɓ����������͓����Ȃ�
	if (m_rope_ani_con == false && m_hero_die_water == false && m_ani_frame_enemy_die == false && m_py < 2000.0f)
	{
		//D�L�[�������ꂽ�Ƃ��F�E�ړ��@
		if (Input::GetVKey('D') == true)
		{
			m_vx += 0.5f;
			m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���
			m_posture = 0.0f;		    //��l���̌���
			m_ani_time_move += 1;
		}
		//A�L�[�������ꂽ�Ƃ��F���ړ��@
		else if (Input::GetVKey('A') == true)
		{
			m_vx -= 0.5f;
			m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���

			if (m_ladder_updown == 1)   //�͂����ɓo���Ă�Ƃ��͌�����ς��Ȃ�
				m_posture = 0.0f;		//��l���̌���
			else
				m_posture = 1.0f;		//��l���̌���
			m_ani_time_move += 1;
		}
		else
		{
			m_ani_frame_stop_move = 1;	//�L�[���͂���������1������
			m_ani_frame_move = 1;		//�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
			m_ani_time_move = 0;
		}
	}

	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time_move > m_ani_max_time_move)
	{
		m_ani_frame_move += 1;
		m_ani_time_move = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame_move == 4)
	{
		m_ani_frame_move = 0;
	}

	//�W�����v--------------------------------------------------------------------
	//���[�v���o���Ă��鎞�͓����Ȃ�  �͂���������Ă��鎞�������Ȃ��@�@���ɓ������Ă���Ƃ��ƓG�Ɠ����������������Ȃ�
	if (Input::GetVKey(VK_SPACE) == true &&
		m_rope_ani_con == false && m_hero_die_water == false &&
		m_ani_frame_enemy_die == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -17.0f;
		}
	}

	//�W�����v�I��-------------------------------------------------------------------------------------


	//���L�[�������ꂽ�Ƃ��F���ɉ�����i�f�o�b�O�j
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}
	//���L�[�������ꂽ�Ƃ��F��ɉ�����i�f�o�b�O�j
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy = -20.0f;
	}

	//���C
	m_vx += -(m_vx * 0.098f);

	//���R�����^��
	// �t���O�������Ă�����d�͂�������
	if (m_gravity_flag == true)
		m_vy += 9.8f / (16.0f);

	//�ő嗎���X�s�[�h�𒴂��Ȃ��悤�ɂ���
	if (m_gravity_flag == true && m_vy > m_fall_speed_max)
		m_vy = m_fall_speed_max;

	Scroll();	//�X�N���[�������������Ȃ�

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��I���-----------------------------------------


	//�r�̊p�x�����߂�-----------------------

	//�}�E�X�|�C���^�Ƃ̋��������߂�

	float x = m_mous_x - (m_px - objmap->GetScrollX() + (HERO_SIZE_WIDTH / 2.0f));	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY() + (HERO_SIZE_HEIGHT / 2.0f));//Y
	float inclination = sqrt(x * x + y * y);				//�Ε�

	////�p�x�����߂�
	//float rad = acosf(x / inclination);
	//m_r = rad* 180.0f / 3.14f;

	if (y > 0.0f)	//y�̒l��0���傫���Ȃ�p�x�𐳂����l�ɏC��
		m_r = 360.0f - m_r;

	//���W�A���l�����߂�
	float rad = asinf(-y / inclination);
	//�p�x�����߂�
	m_r = rad * 180.0f / 3.14f;
	//--------------------------------------------------------


	//���C---------------------------------------------------Shot()
	Shot();

	//���[�v�ˏo---------------------------------------------RopeThrow
	RopeThrow();

	//-------HitScene()
	//�j�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_NEEDLE) != nullptr)
	{
		m_hero_die_enemy = true; //��l���̐j�ɂ��������Ƃ��̎��S�t���O��ON�ɂ���
	}
	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_die_water = true; //��l���̐��ɂ��������Ƃ��̓M���t���O��ON�ɂ���
	}

	//�G�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		m_hero_die_enemy = true; //��l���̓G�ɂ��������Ƃ��̎��S�t���O��ON�ɂ���
	}

	//��l���̓G�ɓ��������Ƃ��̎��S�t���O��ON�Ȃ玀�S�A�j���[�V����������
	if (m_hero_die_enemy == true)
	{
		//��l�����G�ɓ����������̃A�j���[�V�����^�C����i�߂�
		m_ani_time_enemy_die += 1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time_enemy_die > m_ani_max_time_enemy_die)
		{
			m_ani_frame_enemy_die += 1;
			m_ani_time_enemy_die = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƎ�l���폜
		if (m_ani_frame_enemy_die == 4)
		{
			this->SetStatus(false);		//���g���폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

			return;
		}
	}

	//��l���̐��ɓ��������Ƃ��̓M���t���O��ON�Ȃ�M���A�j���[�V����������
	if (m_hero_die_water == true)
	{
		//������̂��������ɂ���i���R�����̂������ł������ɂȂ�j
		m_vy = 0.0f;
		//��l�������ɓ����������̃A�j���[�V�����^�C����i�߂�
		m_ani_time_water_die += 1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time_water_die > m_ani_max_time_water_die)
		{
			m_ani_frame_water_die += 1;
			m_ani_time_water_die = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƎ�l���폜
		if (m_ani_frame_water_die == 3)
		{
			this->SetStatus(false);		//���g���폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

			return;
		}
	}
	
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py + 14);
}

//�X�N���[�������̊֐�
void CObjHero::Scroll()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�E�ɃX�N���[���ł�
	//���_���E�ɂ���
	if ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX() > SCROLL_LINE_RIGHT)
	{
		//�����𒲂ׂ�
		float scroll =  ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX())-SCROLL_LINE_RIGHT;
		//�X�N���[���ɉe����^����
		objmap->SetScrollX(scroll);
	}
	//���ɃX�N���[���ł�
	if (m_px - objmap->GetScrollX() < SCROLL_LINE_LEFT &&
		objmap->GetScrollX() > 0)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_LEFT - (m_px - objmap->GetScrollX());
		//�X�N���[���ɉe����^����
		objmap->SetScrollX(-scroll);
	}

	//��ɃX�N���[���ł�
	if (m_py - objmap->GetScrollY() < SCROLL_LINE_UP)
	{
		//�����𒲂ׂ�
		float scroll = (m_py - objmap->GetScrollY()) - SCROLL_LINE_UP;
		//�X�N���[���ɉe����^����
		objmap->SetScrollY(scroll);
	}
	
	//���ɃX�N���[���ł�
	//���_�����ɂ���
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN&& objmap->GetScrollY() < WINDOW_SIZE_H)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_DOWN - ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY());
		//�X�N���[���ɉe����^����
		objmap->SetScrollY(-scroll);
	}
}

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
	src.m_top = 0.0f;
	src.m_left = 64.0f;
	src.m_right = 128.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu 
	dst.m_top = m_py - objmap->GetScrollY() + 48.0f;
	//�@��l�����E�������Ă��鎞�̘r�̕`��ʒu
	if(m_posture == 0.0f)
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	//�@��l�����E�������Ă��鎞�̘r�̕`��ʒu
	if (m_posture == 0.0f)
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);

	dst.m_bottom = dst.m_top + 64.0f;

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
	if(m_hero_die_enemy == true)
	{
		//�G���������ė����̎��̃A�j���[�V����
		if (m_ani_frame_enemy_die == 0 || m_ani_frame_enemy_die == 1)
		{
			src.m_top = 832.0f;
			src.m_left = 0.0f + m_ani_frame_enemy_die * 64;
			src.m_right = 64.0f + m_ani_frame_enemy_die * 64;
			src.m_bottom = 958.0f;
		}
		//�t���[�����Q�ƂR�̎��|���A�j���[�V����
		else if (m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3) 
		{
			if (m_ani_frame_enemy_die == 2)
			{
				src.m_top = 960.0f;
				src.m_left = 0.0f ;
				src.m_right = 128.0f ;
				src.m_bottom = 1024.0f;
			}
			else
			{
				src.m_top = 960.0f;
				src.m_left = 0.0f + 128;
				src.m_right = 128.0f + 128;
				src.m_bottom = 1024.0f;
			}
		}
	}

	//���ɂ���������
	else if (m_hero_die_water == true )
	{
		//�t���[����0��1�Ȃ�������A�j���[�V����
		if (m_ani_frame_water_die == 0 || m_ani_frame_water_die == 1)
		{
			src.m_top = 640.0f;
			src.m_left = 0.0f + m_ani_frame_water_die * 64;
			src.m_right = 64.0f + m_ani_frame_water_die * 64;
			src.m_bottom = 768.0f;
		}
		else if (m_ani_frame_water_die == 2) //�t���[����2�Ȃ�|���A�j���[�V����
		{
			src.m_top = 769.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 826.0f;
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
		src.m_top = 256.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 384.0f;
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
		src.m_top = 128.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 256.0f;
	}
	else if (m_ani_frame_stop_move == 1 && m_ladder_updown == 0 && rope_caught == false)  //�~�܂��Ă���Ƃ�
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 128.0f;
	}
	else if (m_ani_frame_stop_move == 0 && m_ladder_updown == 0 && rope_caught == false)//�����Ă���Ƃ�
	{
		src.m_top = 129.0f;
		src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
		src.m_bottom = 256.0f;
	}
	
	//�`��ʒu
	//   ���ɂ���������l�����|��Ă鎞�@�@�G�ɓ������ē|��Ă��鎞
	if (m_ani_frame_water_die == 2 || m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)  //���ɂ����������̃A�j���[�V�����ŉ��ɓ|���t���[���p
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX() -64.0f;
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


	////��ʑS�̂��Â�����ł��B
	//Draw::SetFill(true);
	////��ʑS�̂����̐F�ɂ���
	////static�Ȃ̂͏�����������Ȃ�����
	//static float col[4] = { 0.0f };
	//col[0] -= 0.001f;
	//col[1] -= 0.001f;
	//col[2] -= 0.001f;
	//Draw::SetColor(col);

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

// ����1 float : �~��1�t���[�����Ƃ̔��a�̕ω���
// ����2 color : �~�̐F
// ����3 type  : �~�̏�����
// ���S���ƃS�[�����p�̉~��`�悷��֐�
void CObjHero::CircleDraw(float add_radius, float color[4], int type)
{
	// �}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	// �����̂��ʒu�̏�����
	float ball_y = 0.0f;

	//�����ʒu�ݒ�       
	float ball_x = m_px + HERO_SIZE_WIDTH / 2.f - objmap->GetScrollX();

	// Hero������ł�����
	if (type == Die)
	{
		//�������̒����ʒu 
		if (m_hero_die_flag == false)
		{
			m_screen_out = m_py; //�Â��Ȃ钆���̈ʒu����l����ǂ�Ȃ����邽��
			m_hero_die_flag = true;
		}

		//�������̔��a�̒����ʒu
		if (m_py > 2000.0f)
			ball_y = m_screen_out - 1450.0f + HERO_SIZE_HEIGHT / 1.5f;
		//�������ȊO�̔��a�̒����ʒu
		else if (m_py < 2000.0f)
			ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}
	// Hero���X�e�[�W���N���A���Ă����ԂȂ�
	else if (type == Clear)
	{
		ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}

	//���a�����񂾂�Z������
	m_radius += add_radius;
	
	//���l�p�`�̂P�ӂ̒���
	//������Β����قǌy��
	//�Z����ΒZ���قǏd����
	float one_side = 6.0f;

	//���a���ŏ��ɂȂ�����V�[���ڍs����i��̂ق��ɂ���j
	// Hero������ł�����
	if (type == Die)
	{
		// ���a��0�ȉ��Ȃ烊�X�^�[�g
		if (m_radius <= 0.0f)
		{
			m_radius = 0.0f;
			Scene::SetScene(new CSceneMain(-1)); // ���X�^�[�g
		}
	}
	// Hero���X�e�[�W���N���A���Ă����ԂȂ�
	else if (type == Clear)
	{
		// ���a�����l�𒴂�����V�[���ڍs
		if (m_radius >= 768.0f)
		{
			//�X�e�[�W�J�E���g�𑝂₵�Ď��̃X�e�[�W�ɂ���
			((UserData*)Save::GetData())->stagenum += 1;
			Scene::SetScene(new CSceneMain());
		}
	}


	//�~�O���l�p�`�Ŗ��ߐs����
	for (float y = 0.0f; y < (float)WINDOW_SIZE_H; y += one_side)
	{
		for (float x = 0.0f; x < (float)WINDOW_SIZE_W; x += one_side)
		{
			//�~�̒�
			if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= m_radius * m_radius)
			{
				if (type == Clear) // �~�̒���h��
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
			//�~�O
			else
			{
				if (type == Die)	// �~�̊O��h��
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
		}
	}
}

//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
void CObjHero::LandingCheck()
{
	bool c1,c2,c3,c4;//�`�F�b�N���ʂ�ۑ����邽�߂̕ϐ�:�`�F�b�N���ڂ𑝂₷���тɐ��𑝂₷�K�v������
	
	c1 = HitUpCheck(OBJ_LIFT); //���t�g�Ƃ̒��n�`�F�b�N
	c2 = HitUpCheck(OBJ_WOOD); //�؂Ƃ̒��n�`�F�b�N
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //�������t�g�Ƃ̒��n�`�F�b�N
	c4 = HitUpCheck(OBJ_ROLL_BLOCK);//��]����u���b�N

	//�`�F�b�N���ڂ̂ǂꂩ��ł�true�Ȃ�
	if ( c1 == true || c2 ==true || c3 == true || c4 ==true)
		m_hit_down = true;//���n�t���O���I���ɂ���

}

//�w�肵���I�u�W�F�N�g�̏㑤�ɓ������Ă��邩����ׂ�
//�����@���ׂ����I�u�W�F�N�g�l�[��
//�߂�l�@���n���Ă����:true�@���Ă��Ȃ����:false
bool CObjHero::HitUpCheck(int obj_name)
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	
	//�����Ŏ����Ă����I�u�W�F�N�g�Ƃ������Ă��邩���ׂ�
	if (hit->CheckObjNameHit(obj_name) != nullptr)
	{
		HIT_DATA** hit_data;	//�Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(obj_name);//�Փ˂̏���hit_data�ɓ����

		//�������Ă��鐔�����ׂ�
		for (int i = 0; i < hit->GetCount(); i++)
		{
			//�f�[�^�������
  			if (hit_data[i] != nullptr)
			{
				//�Փ˂�������̈ʒu�A���A���������擾
				HIT_BOX* hit = Hits::GetHitBox(hit_data[i]->o)->GetHitBox();
				//�}�b�v�I�u�W�F�N�g�������Ă���
				CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

				//HitTestOfAB�֐����g���ƕύX����Ă��܂��̂ŉ��ϐ��쐬
				float hero_x = m_px;
				float hero_y = m_py;
				float hero_vx = m_vx;
				float hero_vy = m_vy;
				//�Փ˂����������擾
				int collision = HitTestOfAB(hit->x+objmap->GetScrollX(), hit->y+objmap->GetScrollY(), hit->w, hit->h,
					&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
					&hero_vx, &hero_vy
				);
				//��l�����猩�ĉ��ɏՓ˂����璅�n���Ă���
				if (collision == 2)
					return true;
			}
		}
	}
	return false;//���n���Ă��Ȃ�
}

