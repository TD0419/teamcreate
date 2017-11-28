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
CObjBullet::CObjBullet(float x, float y,float r)
{
	//�����ʒu�����߂�
	m_px = x;
	m_py = y;

	// �p�x(�x���@)������(��]���������΂Ȃ̂�-�ɂ���)
	m_r = -r;

	// ���W�A���p�ɕϊ�
	r = r * 3.14f / 180.f; 

	// �p�x����ړ��x�N�g�������߂�
	m_vx = cos(r);
	m_vy = sin(r);
}

//�C�j�V�����C�Y
void CObjBullet::Init()
{
	m_speed = 8.0f; // �e�ۂ̃X�s�[�h

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
	if (DeleteCheckObjNameHit(hit, this, OBJ_ENEMY))
	{
		return;
	}
	//BOSS�Ɠ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_BOSS))
	{
		return;
	}
	//��Ƃ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}
	//Lastwall(��)�ɂ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//Water(��)�Ƃ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}
	// ���t�g�������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_LIFT))
	{
		return;
	}
	//�؂Ɠ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WOOD))
	{
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
				if (45.0f <= r && r < 135.0f || 225.0f <= r && r < 315.0f)
				{
					m_vy *= (-1.0f);//�ړ��x�N�g���̏㉺�𔽓]����
				}
				else //���܂��͉E�ŏՓ˂��Ă���ꍇ
				{
					m_vx *= (-1.0f);//�ړ��x�N�g���̍��E�𔽓]����
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
	m_px += m_vx * m_speed;
	m_py += m_vy * m_speed;

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