#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBoss::CObjBoss(int x,int y)
{
	m_x = x * BOSS_SIZE;
	m_y = y * BOSS_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
   
    m_vx = 300.0f;
    m_vy = 200.0f;
	m_r = 0.0f;
	m_hp = 10; //�{�X�̂g�o(���ɂg�o��[ 10 ]�Ɛݒ�)

	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, BOSS_SIZE , BOSS_SIZE , ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//�A�N�V����
void CObjBoss::Action()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//��������f�o�b�O�p�ł��B
	//A�L�[�������ꂽ�Ƃ��F���ړ�
	if (Input::GetVKey('J') == true)
	{
		m_vx -= 0.5f;
	}

	//D�L�[�������ꂽ�Ƃ��F�E�ړ�
	if (Input::GetVKey('L') == true)
	{
		m_vx += 0.5f;
	}

	//���L�[�������ꂽ�Ƃ��F�㏸
	if (Input::GetVKey('I') == true)
	{
		m_vy = -10.0f;
	}
	//���L�[�������ꂽ�Ƃ��F���~
	//if (Input::GetVKey('M') == true)
	//{
	//	m_vy = 20.0f;
	//}
	//----------------------------------

	//���C
	m_vx += -(m_vx * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_x += m_vx;
	m_y += m_vy;


	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	block-> BlockHit(&m_x,&m_y,BOSS_SIZE,BOSS_SIZE,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);

	

	//�e�ۂƂ���������HP-1
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);

}

//�h���[
void CObjBoss::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_y - map->GetScrollY();
	dst.m_left = 0.0f + m_x - map->GetScrollX();
	dst.m_right = dst.m_left  + BOSS_SIZE;
	dst.m_bottom = dst.m_top  + BOSS_SIZE;

	//�`��
	Draw::Draw(14, &src, &dst, color, m_r);

}