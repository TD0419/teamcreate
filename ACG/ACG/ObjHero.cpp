#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
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

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //�E����0.0f ������1.0f
	m_r = 0.0f;
	m_black_radius = 768;

	m_mous_x = 0.0f;            //�}�E�X�̈ʒuX
	m_mous_y = 0.0f;		    //�}�E�X�̈ʒuX
	m_rope_moux = 0.0f;			//R���������Ƃ��̃}�E�X�̈ʒuX
	m_rope_mouy = 0.0f;		    //R���������Ƃ��̃}�E�X�̈ʒuY
	
	m_bullet_control = false;	//�e�۔��ː���p
	m_rope_control = false;		//���[�v���ː���p
	m_rope_ani_con = false;
	m_rope_delete = false;    //���[�v�����������ǂ������ׂ�ϐ�
	m_rope_delete_r_kye = false;//�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	m_hero_die_water = false;
	m_hero_die_enemy = false;

	m_ladder_updown = 0;
	m_ladder_ani_updown = 0;
	m_ladder_jump = 0;

	m_ani_max_time_move = 6;	//move�A�j���[�V�����Ԋu��
	m_ani_time_move = 0;
	m_ani_frame_move = 1;		//move�Î~�t���[���������ɂ���
	m_rope_delete_control = false;
	m_ani_max_time_ladders = 9; //ladders�A�j���[�V�����Ԋu�� 
	m_ani_time_ladders = 0;
	m_ani_frame_ladders = 0;	//ladders�Î~�t���[���������ɂ���

	m_ani_max_time_rope = 25; //rope�A�j���[�V�����Ԋu�� 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope�Î~�t���[���������ɂ���

	m_ani_max_time_water_die = 25;         //��l�������ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_water_die  = 0;
	m_ani_frame_water_die = 0;//��l�������ɓ����������Î~�t���[���������ɂ���

	m_ani_max_time_enemy_die = 18;         //��l�����G�ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_enemy_die = 0;
	m_ani_frame_enemy_die = 0;//��l�����G�ɓ����������Î~�t���[���������ɂ���

	m_block_type = 0;//��l���̂����̃u���b�N���

	//�u���b�N�Ƃ̏Փ˂������(�ꏊ)�m�F�p
	m_hit_up	= false;
	m_hit_left  = false;
	m_hit_right = false;
	m_hit_down  = false;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, ELEMENT_PLAYER, OBJ_HERO, 1);
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
		int pos_x=0;
		//�E��
		if (i == 1)
		{
			pos_x = HERO_SIZE_WIDTH;
		}
		//����
		else if(i == 2)
		{
			pos_x = HERO_SIZE_WIDTH / 2;
		}
		//��l����X�ʒu(�}�b�v�̗v�f��)
		int x = (m_px + pos_x) / BLOCK_SIZE;
		//��l����Y�ʒu(�}�b�v�̗v�f��)
		//�������ɂ���
		int y = (m_py + 1 + HERO_SIZE_HEIGHT) / BLOCK_SIZE;
		//�u���b�N���0�Ŗ����Ȃ�擾
		if (objmap->GetMap(x, y)!= 0)
		{
			m_block_type = objmap->GetMap(x, y);
		}
	}
	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��1000�ȉ��Ȃ烊�X�^�[�g����
	if (m_py > 2000.0f)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain(-1));
	}
	
	//�}�E�X�̈ʒu���擾
	m_mous_x = Input::GetPosX();
	m_mous_y = Input::GetPosY();

	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	LandingCheck();//���n�t���O�̍X�V

	//�͂���-------------------------------------------------
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

	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//���[�v���o���Ă��鎞�Ɛ��ɓ����������ƓG�ɓ����������͓����Ȃ�
	if (m_rope_ani_con == false && m_hero_die_water == false && m_ani_frame_enemy_die == false)
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
	if (Input::GetVKey(VK_SPACE) == true && m_ladder_jump == 0 && m_rope_ani_con == false && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -18.0f;
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
	m_vx += -(m_vx * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);
	
		
	if (m_ladder_jump==1)
	{
		if (m_ladder_updown == 0)
		{
			m_vy += 160.0f / (32.0f);
		}
	}

	Scroll();	//�X�N���[�������������Ȃ�
	
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��I���-----------------------------------------


	//�r�̊p�x�����߂�-----------------------
	
	//�}�E�X�|�C���^�Ƃ̋��������߂�

	float x = m_mous_x  - (m_px - objmap->GetScrollX() + (HERO_SIZE_WIDTH / 2.0f));	//X
	float y = m_mous_y  - (m_py - objmap->GetScrollY() + (HERO_SIZE_HEIGHT / 2.0f));//Y
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
	

	//���C---------------------------------------------------
	//���N���b�N����������   ���ɓ������Ă���Ƃ��ƓG�ɓ������Ă��鎞�͓����Ȃ�
	if (Input::GetMouButtonL() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		
		//��l�����N���b�N���Ă����ꍇ
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}
		else
		{
			//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
			float mous_bullet_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

			if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
				mous_bullet_way = 1.0f;

			if (m_bullet_control == true)
			{
				//�����Ă�������ƃN���b�N���Ă�������������ŏ����A���[�v�̃A�j���[�V�����̃t���O��false�̏ꍇ
				if (m_posture == mous_bullet_way && m_rope_ani_con == false)
				{
					if (m_posture == 0.0f && m_ladder_updown == 0)//��l�����E�������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						//�e�ۍ쐬
						Audio::Start(FIRING);//���y�X�^�[�g
						CObjBullet* objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//��l�������������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						//�e�ۍ쐬
						Audio::Start(FIRING);//���y�X�^�[�g
						CObjBullet* objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
				}
			}
		}
	}
	else
		m_bullet_control = true; //���N���b�N���ĂȂ���Βe�ۂ��ł�t���O�ɂ���B

	//���C�I��-----------------------------------------------


//���[�v�ˏo---------------------------------------------

	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	
	bool rope_caught = false; //���[�v�����[�v�X�C�b�`�Ɠ������Ă��邩�ǂ������m���߂�ϐ�
	bool rope_delete = false; //���[�v�������Ă邩���������m���߂�ϐ�

	//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
	float mous_rope_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

	if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
		mous_rope_way = 1.0f;

	//�E�N���b�N����������̕�������ɕύX�����̂Ń}�[�W���鎞�͌��̓z�������Ă��������c���Ă�������
	//�E�N���b�N����������   ���ɓ������Ă���Ƃ��ƓG�ɓ������Ă���Ƃ��͓����Ȃ�
	if (Input::GetMouButtonR() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		//��l�����N���b�N���Ă����ꍇ
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}
		//�}�E�X�̈ʒu����낶��Ȃ��@���[�v�A�j���̃t���O���Ȃ��@���[�v�̍폜�t���O���Ȃ�
		else if (m_posture == mous_rope_way && m_rope_ani_con == false && m_rope_delete_r_kye == false)
		{
			m_rope_moux = Input::GetPosX(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuX������
			m_rope_mouy = Input::GetPosY(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuY������
			m_rope_ani_con = true;
			
		}
	}

	if (obj_rope != nullptr)//���[�v�I�u�W�F�N�g���o�Ă���ꍇ
	{
		rope_caught = obj_rope->GetCaughtFlag();//���[�v�����[�v�X�C�b�`�ɓ������Ă��邩�̏������炤
		rope_delete = false; //���[�v�͏����Ă��Ȃ�
		m_rope_delete_control = true;
	}
	else //���[�v�I�u�W�F�N�g���o�Ă��Ȃ��ꍇ
	{
		rope_caught = false;
		//���[�v��������悤�ɂ���
		if (m_rope_delete_control == true)
		{
			rope_delete = true; //���[�v��������
			m_rope_delete_control = false;
		}
	}

	//true�Ȃ�A�j���[�V������i�߂� �@�͂����ɓo���Ă���Ƃ��͓����Ȃ�
	if (m_rope_ani_con == true && m_ladder_updown == 0)
	{
		//���[�v�̃A�j���[�V�����t���[����2�ȊO�Ȃ�A�j���[�V������i�߂�
		if (m_ani_frame_rope != 2)
		{
			//���[�v�̃A�j���[�V�����^�C����i�߂�
			m_ani_time_rope += 1;

			 //���[�v��MAXTIME�𒴂���ƃA�j���[�V������i�߂�
			if (m_ani_time_rope > m_ani_max_time_rope)
			{
				m_ani_frame_rope += 1;
				m_ani_time_rope = 0;
			}
		}
		//���[�v�̃A�j���[�V�����t���[�����Q�Ȃ烍�[�v���o��
		if (m_ani_frame_rope == 2)
		{
			if (m_rope_control == true)//true�Ȃ烍�[�v���o����
			{
				//���[�v�쐬
				if (m_posture == 0.0f )//��l�����E�������Ă���Ƃ��E�����甭��
				{
					CObjRope* objrope = new CObjRope(m_px + 64.0f, m_py + 80.0f,m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//���[�v�̉��y�X�^�[�g
				}
				else if (m_posture == 1.0f)//��l�������������Ă���Ƃ��������甭��
				{
					CObjRope* objrope = new CObjRope(m_px , m_py + 80.0f,m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//���[�v�̉��y�X�^�[�g
				}
			}
			if (m_rope_control == false) //���[�v���o���Ă��鎞
			{
				m_ani_frame_rope = 2;//�A�j���[�V�������Q�Ŏ~�߂�
				if (rope_delete == true)//���[�v�������Ă���ꍇ
				{
					m_rope_delete_r_kye = true;
					m_ani_frame_rope = 0;//�A�j���[�V�����̃t���[����߂��B
					m_rope_ani_con = false;
				}
			}
		}
		else
			m_rope_control = true;
	}
	//�͂����ɓo���Ă���Ƃ��ɉE�N���b�N��������I�������Ɍ����Ă����̂ł�����C������
	else if (m_ladder_updown != 0)
	{
		m_rope_ani_con = false;
	}

	//�E�N���b�N���Ă��Ȃ��Ƃ�false�ɂ���
	if (Input::GetMouButtonR() == false)
		m_rope_delete_r_kye = false;

	//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
	if (rope_caught == true)
	{
		m_rope_delete_r_kye = true; //���[�v��������悤�ɂ���i���[�v���ŏ����j
	}

	//�ˏo�I��------------------------------------------------

	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_die_water = true; //��l���̐��ɂ��������Ƃ��̓M���t���O��ON�ɂ���
	}

	//�G�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr) //���ł��B�G�������悤�Ȃ�Element�ɕς��܂�
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

			//���C���ֈڍs
			Scene::SetScene(new CSceneMain(-1));
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

			//���C���ֈڍs
			Scene::SetScene(new CSceneMain(-1));
			return;
		}
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

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
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN&& objmap->GetScrollY() < 770)
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
	dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);
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
		src.m_top = 128.0f;
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
	if (m_hero_die_water == true | m_hero_die_enemy == true)
	{
		//�����ʒu�ݒ�       
		int ball_x = (int)(m_px + HERO_SIZE_WIDTH / 2.f - objmap->GetScrollX()); 
		 int ball_y = (int)(m_py + HERO_SIZE_HEIGHT /1.5f  - objmap->GetScrollY());
		//���a����
		
		//���a�����񂾂�Z������
		 m_black_radius -= 10;
		//�J���[
		float c[4] = {0.0f,0.0f,0.0f,1.0f};
		//���l�p�`�̂P�ӂ̒���
		//������Β����قǌy��
		//�Z����ΒZ���قǏd����
		int one_side = 6;

		//�~�O���l�p�`�Ŗ��ߐs����
		for (int y = 0; y < WINDOW_SIZE_H; y+= one_side)
		{
			for (int x = 0; x < WINDOW_SIZE_W; x+= one_side)
			{
				//�~�̒�
				if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= m_black_radius * m_black_radius)
				{

				}
				//�~�O
				else
				{
					Draw::DrawHitBox(x, y, one_side, one_side, c);
				}				
			}
		}
	}
	//----------------------------------------------------------------
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

//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
void CObjHero::LandingCheck()
{
	bool c1,c2,c3,c4;//�`�F�b�N���ʂ�ۑ����邽�߂̕ϐ�:�`�F�b�N���ڂ𑝂₷���тɐ��𑝂₷�K�v������
	
	c1 = HitUpCheck(OBJ_LIFT); //���t�g�Ƃ̒��n�`�F�b�N
	c2 = HitUpCheck(OBJ_WOOD); //�؂Ƃ̒��n�`�F�b�N
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //�������t�g�Ƃ̒��n�`�F�b�N
	c4 = HitUpCheck(OBJ_ROLL_BLOCK);//��]����u���b�N

	//�`�F�b�N���ڂ̂ǂꂩ��ł�true�Ȃ�
	if (c1 == true || c2 ==true || c3 == true||c4 ==true)
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

