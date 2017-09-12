#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float angle)
{
	
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�����ʒu�����߂�
	m_x = x;
	m_y = y;
	m_angle = angle;

	//���������߂�
	m_speed = 2.5f;

	//��l���@�ƓG�p�e�ۂŊp�x�����
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���Ƃ̊p�x�̌v�Z���s��
	double hero_x = obj_hero->GetPosX();		//��l���̈ʒu���X�擾
	double hero_y = obj_hero->GetPosY();		//��l���̈ʒu���Y�擾

	//��l�����{������ʒu�ɕύX
	x -= obj_m->GetScrollX();
	y -= obj_m->GetScrollY();

	//�����ʒu�����߂�
	m_x = x;
	m_y = y;

	//���������߂�
	m_speed = 6.5f;

	//��l���̈ʒu�̃x�N�g�����擾
	double Hvector_x = hero_x - x ;
	double Hvector_y = hero_y - y ;

	//�Εӎ擾
	double hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//�p�x�����߂�
	m_angle = acos(Hvector_x / hypotenuse);

	//�p�x�����Ɉړ�
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (hero_y > y)
	{
		//180���`360���̒l�ɂ���
		m_angle = 360 - abs(m_angle);
	}
	//�}�E�X��Y�ʒu������Y�ʒu����
	if (hero_y < y)
	{
		m_vy = -sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	
}

//�C�j�V�����C�Y
void CObjEnemyBullet::Init()
{
	/*
	m_vx = 0.0f;
	m_vy = 1.0f;
	m_speed = 0.0f;
	
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;
	*/

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);

}

//�A�N�V����
void CObjEnemyBullet::Action()
{
	/*
	//��l���@�ƓG�p�e�ۂŊp�x�����
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	
	//��l�����������Ă���ꍇ�A�p�x�̌v�Z���s��
	if (obj_hero != nullptr)
	{
		float hero_x = obj_hero->GetPosX() - m_x;		//��l���̈ʒu���X�擾
		float hero_y = obj_hero->GetPosY() - m_y;		//��l���̈ʒu���Y�擾
		float r_ar = atan2(-hero_y, hero_x)*180.0f / 3.14f;
		if (r_ar < 0)
		{
			r_ar = 360 - abs(r_ar);
		}


		
		//�e�ۂ̌��݂̌����ł̊p�x�����
		float r_br = atan2(-m_vy, m_vx)*180.0f / 3.14f;
		if (r_br < 0)
		{
			r_br = 360 - abs(r_br);
		}


		if (r_ar - r_br > 20)
		{
			//�ړ���������l���̕����ɂ���
			m_vx = cos(3.14 / 180.0*r_ar);
			m_vy = -sin(3.14 / 180.0*r_ar);

		}

		float r = 3.14 / 180.0f;
		if (r_ar<r_br)
		{
			//�ړ�������+1�x������
			m_vx = m_vx*cos(r) - m_vy*sin(r);
			m_vy = m_vy*cos(r) + m_vx*sin(r);

		}
		else
		{
			//�ړ�������-1�x������
			m_vx = m_vx*cos(-r) - m_vy*sin(-r);
			m_vy = m_vy*cos(-r) + m_vx*sin(-r);

		}
		
	}
	*/
	//�ړ�
	m_x += m_vx*1.0f;
	m_y += m_vy*1.0f;

	//��ʊO�ւ����������
	if (m_x < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//���@
		m_x > WINDOW_SIZE_W ||						//�E
		m_y < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//��@
		m_y > WINDOW_SIZE_H							//��
		)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);//HitBox�̈ʒu���X�V

	//��l���Ƃ������������
	if (hit->CheckElementHit(OBJ_HERO) == true)
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

	//Water(��)�Ƃ������������
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}


}

//�h���[
void CObjEnemyBullet::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_y;
	dst.m_left = m_x;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(17, &src, &dst, color, m_angle);

}