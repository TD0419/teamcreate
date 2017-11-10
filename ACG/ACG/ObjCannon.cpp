#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjCannon.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCannon::CObjCannon(float x, float y)
{
	m_px = x * CANNON_SIZE_HEIGHT;
	m_py = y * CANNON_SIZE_WIDTH;
}

//�C�j�V�����C�Y
void CObjCannon::Init()
{
	m_px = 700.0f;
	m_py = 100.0f;
	m_r = 0.0f;
	m_rec = 0.0f;
	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, CANNON_SIZE_WIDTH, CANNON_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_CANNON, 1);

}

//�A�N�V����
void CObjCannon::Action()
{
	
	m_rec++;//�e�۔��˃J�E���g�J�n

	if (m_rec == 200.0f)
	{
		//debug�e�ۍ쐬
		CObjEnemyBullet* objenemy_bullet = new CObjEnemyBullet(m_px + 20.0f, m_py, 0);
		Objs::InsertObj(objenemy_bullet, OBJ_ENEMY_BULLET, 10);

		m_rec = 0.0f;
		m_rec++;
	}

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjCannon::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top	 = 0.0f;
	src.m_left	 = 0.0f;
	src.m_right	 = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - objmap->GetScrollY();
	dst.m_left = 0.0f + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + CANNON_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + CANNON_SIZE_HEIGHT;

	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	
	//��l�����������Ă���ꍇ�A�p�x�̌v�Z���s��
	if (obj_hero != nullptr)
	{
		float hero_x = obj_hero->GetPosX() - m_px;		//��l���̈ʒu���X�擾
		float hero_y = obj_hero->GetPosY() - m_py;		//��l���̈ʒu���Y�擾
		m_r = atan2(-hero_y, hero_x)*180.0f / 3.14f;
		if (m_r < 0)
		{
			m_r = 360 - abs(m_r);
		}
	}

	//�`��
	Draw::Draw(GRA_CANNON, &src, &dst, color, m_r);

}