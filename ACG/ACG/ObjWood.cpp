#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjWood.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
bool UnitVec(float* vx, float* vy);
//�R���X�g���N�^
CObjWood::CObjWood(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjWood::Init()
{
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, WOOD_SIZE_WIDTH, WOOD_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WOOD, 1);

	// �؂̈ړ��ʕϐ�������
	v_px = 0.0f;
	v_py = 0.0f;
	
	// �p�x�ϐ�������
	m_r  = 0.0f;
}

//�A�N�V����
void CObjWood::Action()
{
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px + WOOD_SIZE_WIDTH);//��l���̈ʒu��؂̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{

				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py - HERO_SIZE_HEIGHT);//��l���̈ʒu��؂̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px - HERO_SIZE_WIDTH);//��l���̈ʒu��؂̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py + WOOD_SIZE_HEIGHT);//��l���̈ʒu��؂̉����܂ł��炷
			}
		}
	}

	if (Input::GetMouButtonL() == true)
	{
		//�}�E�X�̈ʒu���擾
		float mous_x = Input::GetPosX();
		float mous_y = Input::GetPosY();
	}
}

//�h���[
void CObjWood::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	m_r = 90.0f;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + 320.0f;
	dst.m_bottom = dst.m_top + 320.0f;
	//�`��
	Draw::Draw(16, &src, &dst, color, m_r);
	
	wchar_t str[256];
	swprintf_s(str, L"X:%d,Y:%d", Input::GetPosX(), Input::GetPosY());
	Font::StrDraw(str, 0.0f, 0.0f, 32.0f, color);
}

//---UnitVec�֐�
//����1�@float* vx :�x�N�g���̂w�����̃|�C���^
//����1�@float* vx :�x�N�g���̂x�����̃|�C���^
//�߂�l bool�@�@  :true=�v�Z���� flase=�v�Z���s
//���e
//�����̃x�N�g���̐��K�����A���̒l��vx,vy�ɕύX���܂�
bool UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);
	r = sqrt(r);// r�����[�g�����߂�

				//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		;//0�Ȃ牽�����Ȃ�
	}
	else
	{
		//���K�����s��
		(*vx) = 1.0f / r*(*vx);
		(*vy) = 1.0f / r*(*vy);
	}

	//�v�Z����
	return true;
}
