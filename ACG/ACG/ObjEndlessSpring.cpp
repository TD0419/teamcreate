#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEndlessSpring.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEndlessSpring::CObjEndlessSpring()
{

}

//�C�j�V�����C�Y
void CObjEndlessSpring::Init()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_timelag = 180.0f;//�G�����Ԋu(180�t���[��)
	

}

//�A�N�V����
void CObjEndlessSpring::Action()
{
	//�G��������(��)
	m_timelag +=TIME ;

	if (m_timelag>=180.0f)
	{
		m_timelag = 0;

	}

	

}

//�h���[
void CObjEndlessSpring::Draw()
{

}