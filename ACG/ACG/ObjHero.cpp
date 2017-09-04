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
	m_px = x * HERO_SIZE_X;
	m_py = y * HERO_SIZE_Y;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f ������1.0f
	m_r = 0.0f;

	m_f  = false;
	m_rf = false;
	m_jf = false;//�W�����v����

	bu = false;
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 6; //�A�j���[�V�����Ԋu��

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_X, HERO_SIZE_Y, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��1000�ȉ��Ȃ烊�X�^�[�g����
	if (m_py > 1000.0f)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain());
	}

	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//A�L�[�������ꂽ�Ƃ��F�E�ړ�
	if (Input::GetVKey('D') == true)
	{
		m_vx += 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 0.0f;//��l���̌���
		m_ani_time += 1;
	}
	//D�L�[�������ꂽ�Ƃ��F���ړ�
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 1.0f;//��l���̌���
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame_stop = 1; //�L�[���͂���������1������
		m_ani_frame = 1; //�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
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
	CObjBlock* obj_b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�W�����v--------------------------------------------------------------------------------
	//SPACE�L�[�������ꂽ�Ƃ��F�W�����v
	if (/*bu == true&&*/Input::GetVKey(VK_SPACE)==true&&m_vy==0)
	{
		if (m_jf == true)
		{
			m_vy = -20.0f;
			m_jf = false;
		}
	}
	else
		m_jf = true; //�X�y�[�X�����ĂȂ���΃W�����v�ł�t���O�ɂ���B

	//���L�[�������ꂽ�Ƃ��F���ɉ�����i�f�o�b�O�j
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}

	//�͂���-------------------------------------------------
	////�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	if (hit->CheckObjNameHit(OBJ_LADDERS) != nullptr)
	{
		//W�L�[�������ꂽ�Ƃ� ���Ƃ�
		if (Input::GetVKey('W') == true)
		{
			m_vy = -2.0f;
		}

		//S�L�[�������ꂽ�Ƃ��@����Ƃ�
		if (Input::GetVKey('S') == true)
		{
			m_vy = 2.0f;
		}
	}
	//�͂����I��---------------------------------------------
	

	//���C
	m_vx += -(m_vx * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);  //�u���b�N�ɒ��n�ł���悤�ɂȂ�����͂����Ă�������

	//Scroll();	//�X�N���[�������������Ȃ�

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;

	////�ړ��x�N�g����������
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//�ړ��I���-----------------------------------------



	//���C---------------------------------------------------
	//���N���b�N����������
	if (Input::GetMouButtonL() == true)
	{
		if (m_f == true)
		{
			if (m_posture == 0)//��l�����E�������Ă���Ƃ��E�����甭��
			{
				//�e�ۍ쐬
				CObjBullet* Objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
				Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
				m_f = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
			}
			else//��l�������������Ă���Ƃ��E�����甭��
			{
				//�e�ۍ쐬
				CObjBullet* Objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
				Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
				m_f = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
			}
		}
	}
	else
		m_f = true; //���N���b�N���ĂȂ���Βe�ۂ��ł�t���O�ɂ���B

	//���C�I��-----------------------------------------------


	//���[�v�ˏo---------------------------------------------
	//�E�N���b�N����������
	if (Input::GetMouButtonR() == true)
	{
		if (m_rf == true)
		{
			//���[�v�쐬
			CObjRope* Objrope = new CObjRope(m_px, m_py);
			Objs::InsertObj(Objrope, OBJ_ROPE, 10);
			m_rf = false;
		}
	}
	else
		m_rf = true; //�E�N���b�N�������Ă��Ȃ���΃��[�v���o��t���O�𗧂Ă�B
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

	//��l�������܂��͉E�̃X�N���[�����C���𒴂������Ȃ�
	if ((m_px + m_vx) < SCROLL_LINE_LEFT || (m_px + m_vx) > SCROLL_LINE_RIGHT)
	{
		obj_m->SetScrollX(m_vx);	//�ړ��ʂ��X�N���[���ɃZ�b�g
	}

	//��l������܂��͉��̃X�N���[�����C���𒴂������Ȃ�
	if ((m_py + m_vy) < SCROLL_LINE_UP || (m_py + m_vy) > SCROLL_LINE_DOWN) 
	{
		obj_m->SetScrollY(m_vy);	//�ړ��ʂ��X�N���[���ɃZ�b�g
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
	dst.m_left		= (HERO_SIZE_X * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_right	    = (HERO_SIZE_X - HERO_SIZE_X * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_bottom	= dst.m_top  + HERO_SIZE_Y;

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



