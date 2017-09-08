//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{
	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE_WIDTH, ROCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	
	//�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�@//ObjEnemy�Ɠ����悤�ɂ����ق������������m��Ȃ��B
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
		return;
	}
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
				obj_hero->SetPosX(m_px + ROCK_SIZE_WIDTH);//��l���̈ʒu��؂̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{

				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py - ROCK_SIZE_HEIGHT-58.0);//��l���̈ʒu��؂̏㑤�܂ł��炷
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
				obj_hero->SetPosY(m_py + ROCK_SIZE_HEIGHT);//��l���̈ʒu��؂̉����܂ł��炷
			}
		}
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py-128);

}

//�h���[
void CObjRock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	
	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY()-128;
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROCK_SIZE_HEIGHT;

	//�`��
	Draw::Draw(10, &src, &dst, color, 0.0f);
}