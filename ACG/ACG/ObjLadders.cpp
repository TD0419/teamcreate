#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLadders.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLadders::CObjLadders(float x,float y)
{
	 m_x = x;		
	 m_y = y;
}

//�C�j�V�����C�Y
void CObjLadders::Init()
{
	//Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_GREEN, OBJ_LADDEERS, 1);
}

//�A�N�V����
void CObjLadders::Action()
{
	;
}

//�h���[
void CObjLadders::Draw()
{
	//�`��J���[���@R=RED G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 64.0f;
	//src.m_bottom = 256.0f;

	//dst.m_top = 0.0f + m_y;
	//dst.m_left = 0.0f + m_x;
	//dst.m_right = 64.0f + m_x;
	//dst.m_bottom = 64.0f + m_y;

	////10�Ԗڂɓo�^�����O���t�B�b�N��stc�Edst�Ec�̏������ɕ`��
	//Draw::Draw(10, &src, &dst, c, 0.0f);

}