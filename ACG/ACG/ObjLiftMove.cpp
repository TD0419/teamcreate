#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLiftMove.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLiftMove::CObjLiftMove(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjLiftMove::Init()
{
	m_vx = 2.0f;
	m_vy = 0.0f;

	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, LIFT_MOVE_SIZE_WIDTH, LIFT_MOVE_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT_MOVE, 1);

}

//�A�N�V����
void CObjLiftMove::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l�����������Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//��l�����悹�鏈��������
	}

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�������t�g�̍����������u���b�N�������ꍇ�E�ɓ���       
	if (objmap->GetMap(((m_px+64.0f ) / BLOCK_SIZE - 1), (m_py / BLOCK_SIZE + 1)) == MAP_BLOCK)
	{
		m_vx =   2.0f;
	}
	//�������t�g�̉E���������u���b�N�������ꍇ�E�ɓ��� 
	if (objmap->GetMap(((m_px+64.0f) / BLOCK_SIZE + 1), (m_py / BLOCK_SIZE + 1)) == MAP_BLOCK)
	{
 		m_vx =  -2.0f;
	}

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjLiftMove::Draw()
{
}

//��l�����悹�鏈��������
void CObjLiftMove::HeroRide()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

									 //�㑤���������Ă���΂�
			if (45.0f <= r && r <= 135.0f)
			{
				//��l���I�u�W�F�N�g�������Ă���
				CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
				float h_px = objhero->GetPosX();//��l���̈ʒuX�������Ă���

				objhero->SetHitDown(true);//���t�g�̏�Ɏ�l��������Ă�����m_hit_down��true��Ԃ�

										  //���t�g�ɏ悹�鏈��
				objhero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				objhero->SetPosX(h_px + m_vx);//��l���̈ʒu�����Ƃ��Ǝ�l���������ʒu�{���t�g�̈ړ��ʂɂ���
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 1.0f);//��l���̃|�W�V���������t�g�̏�ɂ���
			}
		}
	}
}