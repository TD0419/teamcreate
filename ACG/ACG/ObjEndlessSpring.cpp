#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEndlessSpring.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjEndlessSpring::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_timelag = 180.0f;//�G�����Ԋu(180�t���[��)
}

//�A�N�V����
void CObjEndlessSpring::Action()
{
	//�G��������(��)
	m_timelag +=TIME;

	if (m_timelag>=180.0f)
	{
		m_timelag = 0.0f;
	}
}

//�h���[
void CObjEndlessSpring::Draw()
{

}