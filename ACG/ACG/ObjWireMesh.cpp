#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWireMesh.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWireMesh::CObjWireMesh(float x, float y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWireMesh::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, WIRE_MESH_SIZE_WIDTH, WIRE_MESH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WIRE_MESH, 1);
}

//�A�N�V����
void CObjWireMesh::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)//�q�b�g�f�[�^�������
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

									 //��l���I�u�W�F�N�g�������Ă���
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//�㑤���������Ă����
			if (5.5f < r && r < 174.5f)
			{

				objhero->SetHitDown(true);//��l��������Ă�����m_hit_down��true��Ԃ�

				//�悹�鏈��
				objhero->SetPosY(m_py - 126.0f);//�u���b�N�̏㑤�ɒ��߂���
				//��l���̈ړ��x�N�g�����������Ȃ�
				if (objhero->GetVecY() > 0.0f)
					objhero->SetVecY(0.0f);//��l����Y�����̈ړ���0�ɂ���
			}
			//�������������Ă����
			else if (174.5f <= r && r <= 185.5f)
			{
				//���ɔ������鏈��
				objhero->SetPosX(m_px - 64.8f);//��l���̈ʒu���u���b�N�̍��ɂ���
				objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
			}
			//�E�����������Ă����
			else if (0.0f < r && r < 5.5f || 355.0f < r && r < 360.0f)
			{
				//�c�����Ȃ�
				objhero->SetPosX(m_px + ROLL_BLOCK_SIZE_HEIGHT);//��l���̈ʒu���u���b�N�̉E�ɂ���
				objhero->SetVecX(objhero->GetVecX());//��l����X�����̈ړ��ʂ𔽓]����
			}
		}
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjWireMesh::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 640.0f;
	src.m_bottom = src.m_top + 64.0f;

	//�`��ʒu
	dst.m_top =  m_py - objmap->GetScrollY() ;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WIRE_MESH_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WIRE_MESH_SIZE_HEIGHT;

	//�`��
	Draw::Draw(GRA_WIRE_MASH, &src, &dst, color, 0.0f);
	//-------------------------------------------------------
}