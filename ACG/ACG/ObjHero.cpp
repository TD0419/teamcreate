#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"

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
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //�E����0.0f ������1.0f
	m_r = 0.0f;

	m_bullet_control = false;	//�e�۔��ː���p
	
	m_rope_control = false;		//���[�v���ː���p
	m_ani_time = 0;
	m_ani_frame = 1;			//�Î~�t���[���������ɂ���
	m_ani_max_time = 6;			//�A�j���[�V�����Ԋu��

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
	CObjMap* obj_map = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��1000�ȉ��Ȃ烊�X�^�[�g����
	if (m_py > 1000.0f)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain());
	}
	
	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* obj_b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	LandingCheck();//���n�t���O�̍X�V

	//�͂���-------------------------------------------------
	//�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//�v���C���[�̈ʒu���}�b�v�̗v�f�ԍ��ɒ���
	int map_num_x = (int)((m_px + BLOCK_SIZE / 2) / BLOCK_SIZE);//��������ɒ��ׂ�
	int map_num_y = (int)(m_py / BLOCK_SIZE);	//��l���̏�[����Œ��ׂ�

	int map_num_up = obj_map->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���

	map_num_y = (int)((m_py) / BLOCK_SIZE) + 1;//��l���̒�������ɒ��ׂ�
	int map_num_center = obj_map->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���	

	map_num_y = (int)((m_py + BLOCK_SIZE) / BLOCK_SIZE) + 1;//��l���̉��[����ɒ��ׂ�
	int map_num_down = obj_map->GetMap(map_num_x, map_num_y);//��l���i�㔼���j�̃}�b�v�̒l�������ė���	

	//�}�b�v�̒l���͂����Ȃ�
	if (map_num_up == MAP_LADDERS || map_num_center == MAP_LADDERS || map_num_down == MAP_LADDERS)
	{
		//y�̈ړ�������������
		m_vy = 0.0f;

		//W�L�[�������ꂽ�Ƃ� ���Ƃ�
 		if (Input::GetVKey('W') == true)
		{
   			m_vy = -2.0f;
			m_hit_down = true;//���n��Ԃɂ���
		}
		
		//S�L�[�������ꂽ�Ƃ��@����Ƃ�
		if (Input::GetVKey('S') == true)
		{
			m_vy = 2.0f;
			m_hit_down = true;//���n��Ԃɂ���

		}	

	}
	else
	{
		//�u���b�N�Ƃ̓����蔻��
		obj_b->BlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}
	
	//�͂����I��---------------------------------------------

	

	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//A�L�[�������ꂽ�Ƃ��F�E�ړ�
	if (Input::GetVKey('D') == true)
	{
		m_vx += 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 0.0f;		//��l���̌���
		m_ani_time += 1;
	}
	//D�L�[�������ꂽ�Ƃ��F���ړ�
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 1.0f;		//��l���̌���
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame_stop = 1;	//�L�[���͂���������1������
		m_ani_frame = 1;		//�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
		m_ani_time = 0;
	}

	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}
	
	

	//�W�����v--------------------------------------------------------------------

	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_hit_down == true)
		{
			m_vy = -20.0f;
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
	if(m_hit_down==false)//���n���Ă��Ȃ����
		m_vy += 9.8 / (16.0f);
	

	Scroll();	//�X�N���[�������������Ȃ�
	//�u���b�N�Ƃ̓����蔻��
	obj_b->BlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
					&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	Scroll();	//�X�N���[�������������Ȃ�
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��x�N�g����������
	
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//�ړ��I���-----------------------------------------

	//���C---------------------------------------------------
	//���N���b�N����������
	if (Input::GetMouButtonL() == true)
	{
		//�}�b�v�I�u�W�F�N�g�̌Ăяo��
		CObjMap* obj_map = (CObjMap*)Objs::GetObj(OBJ_MAP);

		//�}�E�X�̈ʒu���擾
		float mous_x = Input::GetPosX();
		//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
		float mous_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

		if ( (mous_x - ( m_px - obj_map->GetScrollX() ) ) < 0)//��l����荶���N���b�N�����Ƃ�
			mous_way = 1.0f;

		if (m_bullet_control == true)
		{
			//�����Ă�������ƃN���b�N���Ă�������������Ȃ�
			if (m_posture == mous_way)
			{
				if (m_posture == 0.0f)//��l�����E�������Ă���Ƃ��E�����甭��
				{
					//�e�ۍ쐬
					CObjBullet* Objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
					Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
					m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
				}
				else//��l�������������Ă���Ƃ��E�����甭��
				{
					//�e�ۍ쐬
					CObjBullet* Objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
					Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
					m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
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
		if (m_rope_control == true)
		{
			//���[�v�쐬
			CObjRope* Objrope = new CObjRope(m_px, m_py);
			Objs::InsertObj(Objrope, OBJ_ROPE, 10);
			m_rope_control = false;
		}
	}
	else
		m_rope_control = true; //�E�N���b�N�������Ă��Ȃ���΃��[�v���o��t���O�𗧂Ă�B
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

	//�؃I�u�W�F�N�g�ƏՓ˂��Ă��
	if (hit->CheckObjNameHit(OBJ_WOOD) != nullptr)
	{
		
	}



	////���I�u�W�F�N�g�ƏՓ˂��Ă����
	//if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	//{
	//	this->SetStatus(false);		//���g���폜
	//	Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

	//								//���C���ֈڍs
	//	Scene::SetScene(new CSceneMain());
	//}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�X�N���[�������̊֐�
void CObjHero::Scroll()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�E�ɃX�N���[���ł�
	//���_���E�ɂ���
	if ((m_px + HERO_SIZE_WIDTH) - obj_m->GetScrollX() > SCROLL_LINE_RIGHT)
	{
		//�����𒲂ׂ�
		float scroll =  ((m_px + HERO_SIZE_WIDTH) - obj_m->GetScrollX())-SCROLL_LINE_RIGHT;
		//�X�N���[���ɉe����^����
		obj_m->SetScrollX(scroll);
	}
	//���ɃX�N���[���ł�
	if (m_px - obj_m->GetScrollX() < SCROLL_LINE_LEFT &&
		obj_m->GetScrollX() > 0)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_LEFT - (m_px - obj_m->GetScrollX());
		//�X�N���[���ɉe����^����
		obj_m->SetScrollX(-scroll);
	}

	//��ɃX�N���[���ł�
	if (m_py - obj_m->GetScrollY() < SCROLL_LINE_UP)
	{
		//�����𒲂ׂ�
		float scroll = (m_py - obj_m->GetScrollY()) - SCROLL_LINE_UP;
		//�X�N���[���ɉe����^����
		obj_m->SetScrollY(scroll);
	}
	
	//���ɃX�N���[���ł�
	//���_�����ɂ���
	if ((m_py + HERO_SIZE_HEIGHT) - obj_m->GetScrollY() > SCROLL_LINE_DOWN &&
		obj_m->GetScrollY() < 0)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_DOWN - ((m_py + HERO_SIZE_HEIGHT) - obj_m->GetScrollY());
		//�X�N���[���ɉe����^����
		obj_m->SetScrollY(-scroll);
	}
}

//�h���[
void CObjHero::Draw()
{
	//�摜�̐؂���z��
	int AniData[3] =
	{
		0  , 1 , 2
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	//�~�܂��Ă��鎞
	if (m_ani_frame_stop == 1)  //��
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 128.0f;
	}
	else//�����Ă���Ƃ�
	{
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64;
		src.m_bottom = 256.0f;
	}

	//�`��ʒu
	dst.m_top		= 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left		= (HERO_SIZE_WIDTH * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_right	    = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_bottom	= dst.m_top  + HERO_SIZE_HEIGHT;

	//�`��
	Draw::Draw(3, &src, &dst, color, m_r);

	////��ʑS�̂��Â�����ł��B
	//Draw::SetFill(true);
	////��ʑS�̂����̐F�ɂ���
	////static�Ȃ̂͏�����������Ȃ�����
	//static float col[4] = { 0.0f };
	//col[0] -= 0.01f;
	//col[1] -= 0.01f;
	//col[2] -= 0.01f;
	//Draw::SetColor(col);
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

