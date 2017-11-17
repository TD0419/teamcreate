#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjBullet.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//����1	float x		:�����ʒuX
//����2	float y		:�����ʒuY
//����3	float angle	:�ړ�����p�x
CObjBullet::CObjBullet(float x, float y)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//�����ʒu�����߂�
	m_px = x;
	m_py = y;

	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();

	//���������߂�
	m_speed = 6.5f;

	//�}�E�X�̈ʒu�Ǝ�l���̈ʒu����}�E�X�̊p�x�����߂�
	//�}�E�X�̈ʒu���擾
	float mous_x = Input::GetPosX();
	float mous_y = Input::GetPosY();

	//��l���̈ʒu����}�E�X�̈ʒu�̃x�N�g�����擾
	float vector_x = mous_x - x;
	float vector_y = mous_y - y;

	//�Εӎ擾
	float hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�p�x�����߂�
	m_r = acos(vector_x / hypotenuse);
	//�p�x�����Ɉړ�
	m_vx = cos(m_r) * m_speed;
	m_r = m_r * 180.0f / 3.14f;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (mous_y > y )
	{
		//180���`360���̒l�ɂ���
		m_r = 360 - abs(m_r);
	}
	//�}�E�X��Y�ʒu������Y�ʒu����
	if (mous_y < y)
	{
		m_vy = -sin(acos(vector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(vector_x / hypotenuse)) * m_speed;
	}
}

//�C�j�V�����C�Y
void CObjBullet::Init()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	m_window_check = true;

	//�u���b�N�Ƃ̓����蔻��t���O�̏�����
	m_hit_up	= false;
	m_hit_down	= false;
	m_hit_left	= false;
	m_hit_right = false;


	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_BULLET, 1);
}

//�A�N�V����
void CObjBullet::Action()
{	
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//��ʓ������ׂ�
	m_window_check=WindowCheck(m_px,m_py,BULLET_SIZE,BULLET_SIZE);

	//��ʊO�Ȃ����
	if(m_window_check==false)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}
	
	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�G�Ƃ������������
	if (hit->CheckElementHit(ELEMENT_ENEMY)==true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//��Ƃ������������
	if (hit->CheckObjNameHit(OBJ_ROCK) != nullptr)//���@ElementHit�ɕς��邩��
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//Lastwall(��)�ɂ������������
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//Water(��)�Ƃ������������
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//���t�g�Ƃ������������
	if (hit->CheckObjNameHit(OBJ_LIFT) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//���˂���u���b�N�Ƃ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_REFLECT_BLOCK) != nullptr)
	{
		HIT_DATA** hit_data;	//�Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(OBJ_BLOCK);//�Փ˂̏���hit_data�ɓ����

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;

				//��@�܂��́@���ŏՓ˂��Ă���ꍇ
				if (45 <= r && r < 135 || 225 <= r && r < 315)
				{
					m_vy *= (-1);//�ړ��x�N�g���̏㉺�𔽓]����
				}
				else //���܂��͉E�ŏՓ˂��Ă���ꍇ
				{
					m_vx *= (-1);//�ړ��x�N�g���̍��E�𔽓]����
				}
			}
		}
	}

	// �u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, BULLET_SIZE, BULLET_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//�u���b�N�Ƃ������Ă���΍폜����
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}
	
	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjBullet::Draw()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	
	//�`��ʒu
	dst.m_top    = m_py - objmap->GetScrollY();
	dst.m_left   = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(GRA_HERO_BULLET, &src, &dst, color, m_r);
}