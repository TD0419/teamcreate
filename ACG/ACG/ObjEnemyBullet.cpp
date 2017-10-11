#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float rad)
{
	
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�����ʒu�����߂�
	m_px = x;
	m_py = y;
	m_r = rad;

	//���������߂�
	m_speed = 2.5f;

	//��l���@�ƓG�p�e�ۂŊp�x�����
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���Ƃ̊p�x�̌v�Z���s��
	double hero_x = objhero->GetPosX();		//��l���̈ʒu���X�擾
	double hero_y = objhero->GetPosY();		//��l���̈ʒu���Y�擾

	//��l�����{������ʒu�ɕύX
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();

	//�����ʒu�����߂�
	m_px = x;
	m_py = y;

	//���������߂�
	m_speed = 6.5f;

	//��l���̈ʒu�̃x�N�g�����擾
	double Hvector_x = hero_x - x ;
	double Hvector_y = hero_y - y ;

	//�Εӎ擾
	double hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//�p�x�����߂�
	m_r = acos(Hvector_x / hypotenuse);

	//�p�x�����Ɉړ�
	m_vx = cos(m_r) * m_speed;
	m_r = m_r * 180.0 / 3.14;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (hero_y > y)
	{
		//180���`360���̒l�ɂ���
		m_r = 360 - abs(m_r);
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
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);
}

//�A�N�V����
void CObjEnemyBullet::Action()
{
	//�ړ�
	m_px += m_vx*1.0f;
	m_py += m_vy*1.0f;

	//Scroll();	//�X�N���[�������������Ȃ�

	//��ʊO�ւ����������
	if (m_px < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//���@
		m_px > WINDOW_SIZE_W ||						//�E
		m_py < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//��@
		m_py > WINDOW_SIZE_H							//��
		)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}
	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);


	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

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
	dst.m_top = m_py;
	dst.m_left = m_px;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(18, &src, &dst, color, m_r);

}