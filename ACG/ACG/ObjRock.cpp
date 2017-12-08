//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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
	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��
	m_ani_start_flag = false;//�A�j���t���OOFF

	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE_WIDTH, ROCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//�A�N�V����
void CObjRock::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	
	//�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		Audio::Start(ROCK);//��̉��y�X�^�[�g
		m_ani_start_flag = true;//�A�j���t���OON
	}
	//�A�j���t���OON����
	if (m_ani_start_flag == true)
	{
		m_ani_time+=1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƑ��݂�����
		if (m_ani_frame == 4)
		{
			Hits::DeleteHitBox(this);	//�₪���L����HitBox�ɍ폜����
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			return;
		}
	}

	//��l���I�u�W�F�N�g���������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	//HitBox�̕��A����
	float hit_w, hit_h;

	//HitBox�̕��A�����ݒ�
	hit_w = ROCK_SIZE_WIDTH;
	hit_h = ROCK_SIZE_HEIGHT;
	//��l���Ƃ̓����蔻��
	//�Փ˂������l���̈ʒu���X�V����
	m_rock_determine = HitTestOfAB(m_px - 7.0f, m_py - 8.0f, hit_w - 8.0f, hit_h + 12.0f, &hero_x, &hero_y, 42, 120, &hero_vx, &hero_vy);

	switch (m_rock_determine)
	{
	case 1://�����������Ă���
		   //��l���̈ʒu���X�V
		objhero->SetPosY(hero_y);
		objhero->SetVecY(hero_vy);
		break;
	case 2://�オ�������Ă���
		   //��l���̈ʒu���X�V
		objhero->SetPosY(hero_y);
		objhero->SetVecY(hero_vy);
		break;
	case 3://�E���������Ă���
		   //��l���̈ʒu���X�V
		objhero->SetPosX(hero_x);
		objhero->SetVecX(hero_vx);
		break;
	case 4://�����������Ă���
		   //��l���̈ʒu���X�V
		objhero->SetPosX(hero_x);
		objhero->SetVecX(hero_vx);
		break;
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py- ROCK_SIZE_WIDTH);

}

//�h���[
void CObjRock::Draw()
{
	//�摜�̐؂���z��
	int AniData[4] =
	{
		0, 1, 2, 3
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 1.0f;
	src.m_left = AniData[m_ani_frame] * 128.0f - 128.0f;
	src.m_right = src.m_left + 128.0f;
	src.m_bottom = src.m_top + 198.0f;
	
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()- ROCK_SIZE_WIDTH;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROCK_SIZE_HEIGHT;

	
	//�`��
	Draw::Draw(GRA_ROCK, &src, &dst, color, 0.0f);
}