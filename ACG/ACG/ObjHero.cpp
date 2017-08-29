#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero()
{

}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = WINDOW_SIZE_W / 2.0f;
	m_py = WINDOW_SIZE_H / 2.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f ������1.0f
	m_r = 0.0f;
	m_mouse_angle = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 6; //�A�j���[�V�����Ԋu��

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_X, HERO_SIZE_Y, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{


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
		m_vx += 3.0f;
		m_ani_frame_stop = 0;
		m_posture = 0.0f;//��l���̌���
		m_ani_time += 1;
	}
	//D�L�[�������ꂽ�Ƃ��F���ړ�
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 3.0f;
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
	
	//SPACE�L�[�������ꂽ�Ƃ��F�W�����v
	if (Input::GetVKey(VK_SPACE) == true)
	{
		//m_vy =- 8.0f; �u���b�N�ɒ��n�ł���悤�ɂȂ�����͂����Ă�������
	}

	//���C
	m_vx += -(m_vx * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);  //�u���b�N�ɒ��n�ł���悤�ɂȂ�����͂����Ă�������

	Scroll();	//�X�N���[�������������Ȃ�

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��x�N�g����������
	m_vx = 0.0f;

	//�ړ��I���-----------------------------------------

	//�}�E�X�̈ʒu�Ǝ�l���̈ʒu����}�E�X�̊p�x�����߂�------
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//�}�E�X�̈ʒu���擾
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//��l���̈ʒu����}�E�X�̈ʒu�̃x�N�g�����擾
	double vector_x = mous_x - m_px - obj_m->GetScrollX();
	double vector_y = mous_y - m_py - obj_m->GetScrollY();

	//�Εӎ擾
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�p�x�����߂�
	m_mouse_angle = acos(vector_x / hypotenuse) * 180.0/3.14;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (mous_y > m_py - obj_m->GetScrollY())
	{
		//180���`360���̒l�ɂ���
		m_mouse_angle = 360 - abs(m_mouse_angle);
	}
	//-------------------------------------------------------

	//�͂���-------------------------------------------------

	////�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_LADDERS) != nullptr)
	//{
	//	//W�L�[�������ꂽ�Ƃ� ���Ƃ�
	//	if (Input::GetVKey('W') == true)
	//	{
	//		m_vy -= 3.0f;
	//	}

	//	//S�L�[�������ꂽ�Ƃ��@����Ƃ�
	//	if (Input::GetVKey('S') == true)
	//	{
	//		m_vy += 3.0f;
	//	}
	//}

	//�͂����I��---------------------------------------------

	//���C---------------------------------------------------
	//���N���b�N����������
	if (Input::GetMouButtonL() == true)
	{
		//�e�ۍ쐬
		CObjBullet* Objbullet = new CObjBullet(m_px,m_py,m_mouse_angle);
		Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
	}
	//���C�I��-----------------------------------------------

	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//���g���폜
		Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

		//���C���ֈڍs
		Scene::SetScene(new CSceneMain());
	}

	/*	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* pb = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	pb -> BlockHit(&m_px,&m_py,true,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy,
	&m_block_type
	);*/

	
	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_px - obj_m->GetScrollX() , m_py - obj_m->GetScrollY());

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
	Draw::Draw(0, &src, &dst, color, m_r);

}

