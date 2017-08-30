#include "GameL\DrawTexture.h"
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
	m_px = x * BOSS_SIZE;
	m_py = y * BOSS_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
   
    m_vx = 0.0f;
    m_vy = 0.0f;

	m_hp = 10; //�{�X�̂g�o(���ɂg�o��[ 10 ]�Ɛݒ�)

	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE, BOSS_SIZE, ELEMENT_ENEMY, OBJ_BOSS, 1);

}

//�A�N�V����
void CObjBoss::Action()
{
	
	//���C
	//m_vx += -(m_vx * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjBoss::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BOSS_SIZE;
	dst.m_bottom = dst.m_top + BOSS_SIZE;

	//�`��
	Draw::Draw(4, &src, &dst, color, m_r);

}