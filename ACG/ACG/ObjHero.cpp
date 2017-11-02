#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
CObjHero::CObjHero(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //�E����0.0f ������1.0f
	m_r = 0.0f;
	m_rope_delete_ani_con = false;

	m_mous_x = 0.0f;            //�}�E�X�̈ʒuX
	m_mous_y = 0.0f;		    //�}�E�X�̈ʒuX
	m_rope_moux = 0.0f;			//R���������Ƃ��̃}�E�X�̈ʒuX
	m_rope_mouy = 0.0f;		    //R���������Ƃ��̃}�E�X�̈ʒuY
	
	m_bullet_control = false;	//�e�۔��ː���p
	m_rope_control = false;		//���[�v���ː���p
	m_rope_ani_con = false;
	m_rope_delete = false;    //���[�v�����������ǂ������ׂ�ϐ�
	m_rope_delete_ani_con = false;//�A�j���[�V�����p���[�v�����������ǂ������Ǘ����� 
	m_hero_water_delete = false;

	m_ladder_updown = 0;
	m_ladder_ani_updown = 0;
	m_ladder_jump = 0;

	m_ani_max_time_move = 6;	//move�A�j���[�V�����Ԋu��
	m_ani_time_move = 0;
	m_ani_frame_move = 1;		//move�Î~�t���[���������ɂ���

	m_ani_max_time_ladders = 9; //ladders�A�j���[�V�����Ԋu�� 
	m_ani_time_ladders = 0;
	m_ani_frame_ladders = 0;	//ladders�Î~�t���[���������ɂ���

	m_ani_max_time_rope = 25; //rope�A�j���[�V�����Ԋu�� 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope�Î~�t���[���������ɂ���

	m_ani_max_time_water_die = 25;         //��l�������ɓ����������A�j���[�V�����Ԋu�� 
	m_ani_time_water_die  = 0;
	m_ani_frame_water_die = 0;//��l�������ɓ����������Î~�t���[���������ɂ���


	m_remaining = 2;//���񂫏�����

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
		//�u���b�N��񂪂O�Ŗ����Ȃ�擾
		if (objmap->GetMap(x, y)!= 0)
		{
			//�擾
			m_block_type = objmap->GetMap(x, y);
		}
	}
	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��1000�ȉ��Ȃ烊�X�^�[�g����
	if (m_py > 1000.0f)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain());
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
	//D�L�[�������ꂽ�Ƃ��F�E�ړ��@�@���[�v���o���Ă��鎞�Ɛ��ɓ����������͓����Ȃ�
	if (Input::GetVKey('D') == true && m_rope_ani_con == false && m_hero_water_delete == false)
	{
		m_vx += 0.5f;
		m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���
		m_posture = 0.0f;		    //��l���̌���
		m_ani_time_move += 1;
	}
	//A�L�[�������ꂽ�Ƃ��F���ړ��@�@���[�v���o���Ă��鎞�Ɛ��ɓ����������͓����Ȃ�
	else if (Input::GetVKey('A') == true && m_rope_ani_con == false && m_hero_water_delete == false)
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
	//���[�v���o���Ă��鎞�͓����Ȃ�  �͂���������Ă��鎞�������Ȃ��@�@���ɓ������Ă���Ƃ��������Ȃ�
	if (Input::GetVKey(VK_SPACE) == true && m_ladder_jump == 0 && m_rope_ani_con == false && m_hero_water_delete == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -16.0f;
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
	float x = m_mous_x - (m_px - objmap->GetScrollX());	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY());	//Y
	float inclination = sqrt(x * x + y * y);				//�Ε�

	//���W�A���l�����߂�
	float rad = asin( - y / inclination);
	//�p�x�����߂�
	m_r = rad * 180.0f / 3.14f;
	
	//--------------------------------------------------------
	

	//���C---------------------------------------------------
	//���N���b�N����������   ���ɓ������Ă���Ƃ��͓����Ȃ�
	if (Input::GetMouButtonL() == true && m_hero_water_delete == false)
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
						CObjBullet* objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//��l�������������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						//�e�ۍ쐬
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
	
	bool rope_caught; //���[�v�����[�v�X�C�b�`�Ɠ������Ă��邩�ǂ������m���߂�ϐ�
	bool rope_delete; //���[�v�������Ă邩���������m���߂�ϐ�

	//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
	float mous_rope_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

	if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
		mous_rope_way = 1.0f;

	//�E�N���b�N����������̕�������ɕύX�����̂Ń}�[�W���鎞�͌��̓z�������Ă��������c���Ă�������
	//�E�N���b�N����������   ���ɓ������Ă���Ƃ��͓����Ȃ�
	if (Input::GetMouButtonR() == true && m_hero_water_delete == false)
	{
		//��l�����N���b�N���Ă����ꍇ
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}       //�}�E�X�̈ʒu����낶��Ȃ��@���[�v�A�j���̃t���O���Ȃ��@���[�v�̍폜�t���O���Ȃ�
		else if (m_posture == mous_rope_way && m_rope_ani_con == false && m_rope_delete_ani_con == false)
		{
			m_rope_moux = Input::GetPosX(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuX������
			m_rope_mouy = Input::GetPosY(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuY������
			m_rope_ani_con = true;
		}
	}

	if (obj_rope != nullptr)//���[�v�I�u�W�F�N�g���o�Ă���ꍇ
	{
		rope_caught = obj_rope->GetCaughtFlag();//���[�v�����[�v�X�C�b�`�ɓ������Ă��邩�̏������炤
		rope_delete = obj_rope->GetDelete();    //���[�v�������Ă��邩�ǂ����𒲂ׂ�
	}
	else //���[�v�I�u�W�F�N�g���o�Ă��Ȃ��ꍇ
	{
		rope_caught = false;
		rope_delete = false;
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
					CObjRope* objrope = new CObjRope(m_px + 64.0f, m_py + 50.0f);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
				}
				else if (m_posture == 1.0f)//��l�������������Ă���Ƃ��������甭��
				{
					CObjRope* objrope = new CObjRope(m_px - 16.0f, m_py + 50.0f);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
				}
			}
			if (m_rope_control == false) //���[�v���o���Ă��鎞
			{
				m_ani_frame_rope = 2;//�A�j���[�V�������Q�Ŏ~�߂�
				if (rope_delete == true)//���[�v�������Ă���ꍇ
				{
					m_rope_delete_ani_con = true;
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
		m_rope_delete_ani_con = false;

	//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
	if (rope_caught == true)
	{
		m_rope_delete_ani_con = false;
		if (Input::GetMouButtonR() == false)////�E�N���b�N���Ă��Ȃ��Ƃ�true�ɂ���
		m_rope_delete_ani_con = true;
	}

	//�ˏo�I��------------------------------------------------

	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_water_delete = true; //��l���̐��ɂ��������Ƃ��̎��S�t���O��ON�ɂ���
	}

	//�G�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr) //���ł��B�G�������悤�Ȃ�Element�ɕς��܂�
	{
		this->SetStatus(false);		//���g���폜
		Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

		//���C���ֈڍs
		Scene::SetScene(new CSceneMain());
		return;
	}
	//��l���̐��ɓ��������Ƃ��̎��S�t���O��ON�Ȃ玀�S�A�j���[�V����������
	if (m_hero_water_delete == true)
	{
		m_vy = 0.0f;
		//��l�������ɓ����������̃A�j���[�V�����^�C����i�߂�
		m_ani_time_water_die += 1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time_water_die > m_ani_max_time_water_die)
		{
			m_ani_frame_water_die += 1;
			m_ani_time_water_die = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
		if (m_ani_frame_water_die == 3)
		{
			this->SetStatus(false);		//���g���폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜
			//���C���ֈڍs
			Scene::SetScene(new CSceneMain());
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
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN &&
		objmap->GetScrollY() < 0)
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
	//�{��---------------------------------
	//�؂���ʒu

	//���ɂ���������
	if ( m_hero_water_delete == true )
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
	if (m_ani_frame_water_die != 2)//���ɓ����������̉��ɓ|���A�j���[�V�����ȊO�͂�������ʂ�
	{
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + HERO_SIZE_HEIGHT;
	}
	else if (m_ani_frame_water_die == 2)  //���ɂ����������̃A�j���[�V�����ŉ��ɓ|���t���[���p
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + 64.0f;
	}

	//�`��
	Draw::Draw(3, &src, &dst, color, 0.0f);
	//�{��-------------------------------------

	//�r---------------------------------------
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 64.0f;
	src.m_right = 128.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top += 48.0f;
	dst.m_left += 33.0f - (HERO_SIZE_WIDTH * m_posture);
	dst.m_right +=33.0f - (HERO_SIZE_WIDTH * m_posture);
	dst.m_bottom = dst.m_top +64.0f;
	
	//�`��    ���[�v���o�Ă鎞�A�͂����ɓo���Ă鎞�A���[�v�ƃ��[�v�X�C�b�`���������Ă��鎞  ��l�������ɓ���������
	if (m_rope_ani_con == true || m_ladder_updown != 0 || rope_caught == true || m_hero_water_delete == true)
	{
		;    //�����`�悵�Ȃ�
	}
	else
		Draw::Draw(3, &src, &dst, color, m_r,-0.2f,-0.25f);
	//-----------------------------------------


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
	if (false)
	{
		//�����ʒu�ݒ�
		static int ball_x = WINDOW_SIZE_W / 2;
		static int ball_y = WINDOW_SIZE_H / 2;
		//���a����
		static int ball_r = 768 ;
		//���a�����񂾂�Z������
		ball_r -= 3;
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
				if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= ball_r * ball_r)
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
	Draw::Draw(23, &src, &dst, color, 0.0f);
}

//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
void CObjHero::LandingCheck()
{
	bool c1,c2,c3;//�`�F�b�N���ʂ�ۑ����邽�߂̕ϐ�:�`�F�b�N���ڂ𑝂₷���тɐ��𑝂₷�K�v������
	
	c1 = HitUpCheck(OBJ_LIFT); //���t�g�Ƃ̒��n�`�F�b�N
	c2 = HitUpCheck(OBJ_WOOD); //�؂Ƃ̒��n�`�F�b�N
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //�؂Ƃ̒��n�`�F�b�N

	//�`�F�b�N���ڂ̂ǂꂩ��ł�true�Ȃ�
	if (c1 == true || c2 ==true || c3 == true)
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
				float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

				 //Hero�̉������������Ă����
				if (225.0f < r && r < 315.0f)
				{
					return true;//���n���Ă���
				}
			}
		}
	}
	return false;//���n���Ă��Ȃ�
}

