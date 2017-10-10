#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero(int x, int y)
{
	m_px = x * HERO_SIZE_WIDTH;
	m_py = y * HERO_SIZE_HEIGHT;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 10.0f;
	m_py = 5.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //�E����0.0f ������1.0f
	m_r = 0.0f;

	m_mous_x = 0.0f;//�}�E�X�̈ʒuX
	m_mous_y = 0.0f;//�}�E�X�̈ʒuX
	
	m_bullet_control = false;	//�e�۔��ː���p
	m_rope_control = false;		//���[�v���ː���p
	m_rope_ani_con = false;

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
	objblock->BlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	LandingCheck();//���n�t���O�̍X�V

	//�͂���-------------------------------------------------
	//�͂����I�u�W�F�N�g�������Ă���
	CObjLadders* objladders = (CObjLadders*)Objs::GetObj(OBJ_LADDERS);

	if(objladders != nullptr)
		objladders->HeroHit(m_px, m_py);//�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�

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
	//A�L�[�������ꂽ�Ƃ��F�E�ړ�
	if (Input::GetVKey('D') == true)
	{
		m_vx += 0.5f;
		m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���
		m_posture = 0.0f;		    //��l���̌���
		m_ani_time_move += 1;
	}
	//D�L�[�������ꂽ�Ƃ��F���ړ�
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

	if (Input::GetVKey(VK_SPACE) == true && m_ladder_jump == 0)
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

	if (m_hit_down == true)
 		int a = 0;

	//���R�����^��
	m_vy += 9.8 / (16.0f);
	
		
	if (m_ladder_jump==1)
	{
		if (m_ladder_updown == 0)
		{
			m_vy += 160.0 / (32.0f);
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
	//���N���b�N����������
	if (Input::GetMouButtonL() == true)
	{
		
		//��l�����N���b�N���Ă����ꍇ
		if (m_px <= m_mous_x && m_mous_x <= (m_px + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}
		else
		{
			//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
			float mous_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

			if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
				mous_way = 1.0f;

			if (m_bullet_control == true)
			{
				//�����Ă�������ƃN���b�N���Ă�������������Ȃ�
				if (m_posture == mous_way)
				{
					if (m_posture == 0.0f)//��l�����E�������Ă���Ƃ��E�����甭��
					{
						//�e�ۍ쐬
						CObjBullet* objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
					else//��l�������������Ă���Ƃ��E�����甭��
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
	//�E�N���b�N����������
	if (Input::GetMouButtonR() == true)
	{
		if (m_rope_ani_con == false) //false�Ȃ�true�ɕς���
		{
			m_rope_ani_con = true;
		}
	}
	
	if (m_rope_ani_con == true) 
	{
		//���[�v�̃A�j���[�V�����t���[����3�ȊO�Ȃ�A�j���[�V������i�߂�
		if (m_ani_frame_rope != 3)
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
			if (m_rope_control == true)
			{
				//���[�v�쐬
				if (m_posture == 0.0f)//��l�����E�������Ă���Ƃ��E�����甭��
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
		}
		else
			m_rope_control = true;

		//���[�v�̃A�j���[�V�����t���[����3�Ȃ�A�j���[�V�����t���[����0�ɖ߂�
		if (m_ani_frame_rope == 3)
		{
			
			m_rope_ani_con = false;
			m_ani_frame_rope = 0;
		}
	}

	//�ˏo�I��------------------------------------------------

	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//���g���폜
		Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

		//���C���ֈڍs
		Scene::SetScene(new CSceneMain());
		return;
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
	//�{��---------------------------------
	//�؂���ʒu
	//�~�܂��Ă��鎞
	
	if (m_ladder_updown == 1)//�͂����ɏ���Ă��鎞
	{
		src.m_top = 256.0f;
		src.m_left = 0.0f + m_ani_frame_ladders * 64;
		src.m_right = 64.0f + m_ani_frame_ladders * 64;
		src.m_bottom = 384.0f;
		
		//��l���̍����A�^���A�E���Ƀu���b�N������Ǝ~�܂��Ă���A�j���[�V�����ɂ���
		for (int i = 0; i <= HERO_SIZE_WIDTH; i+=HERO_SIZE_WIDTH/2)
		{
			int x = (m_px + i) / BLOCK_SIZE;
			int y = (m_py + 1 + HERO_SIZE_HEIGHT) / BLOCK_SIZE;
			int a = objmap->GetMap(x, y);
			//�����A�^���A�E���Ƀu���b�N������Ǝ~�܂��Ă���A�j���[�V�����ɂ���
			if (objmap->GetMap(x, y) == MAP_BLOCK)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 128.0f;
			}
		}
		
	}
	else if (m_ladder_updown == 2)//�͂�������肫��Ƃ�
	{
		src.m_top = 256.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 384.0f;
	}
	else if (m_rope_ani_con == true) //���[�v�𓊂���Ƃ�
	{
		src.m_top = 512.0f;
		src.m_left = 0.0f + m_ani_frame_rope * 64;
		src.m_right = 64.0f + m_ani_frame_rope * 64;
		src.m_bottom = 640.0f;
	}
	else if (m_ladder_updown == 0 && m_hit_down == false)  //�W�����v���Ă��鎞
	{
		src.m_top = 128.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 256.0f;
	}
	else if (m_ani_frame_stop_move == 1 && m_ladder_updown == 0)  //�~�܂��Ă���Ƃ�
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 128.0f;
	}
	else if (m_ani_frame_stop_move == 0 && m_ladder_updown == 0)//�����Ă���Ƃ�
	{
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
		src.m_bottom = 256.0f;
	}
	
	

	//�`��ʒu
	dst.m_top		= m_py - objmap->GetScrollY();
	dst.m_left		= (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_right	    = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom	= dst.m_top  + HERO_SIZE_HEIGHT;

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
	
	//�`��
	if (m_rope_ani_con == true || m_ladder_updown != 0)//���[�v�̕`�撆��
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
}

//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
void CObjHero::LandingCheck()
{
	bool c1,c2;//�`�F�b�N���ʂ�ۑ����邽�߂̕ϐ�:�`�F�b�N���ڂ𑝂₷���тɐ��𑝂₷�K�v������
	
	c1=HitUpCheck(OBJ_LIFT); //���t�g�Ƃ̒��n�`�F�b�N
	c2 = HitUpCheck(OBJ_WOOD); //�؂Ƃ̒��n�`�F�b�N
								 
	//�`�F�b�N���ڂ̂ǂꂩ��ł�true�Ȃ�
	if (c1 == true||c2 ==true)
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

