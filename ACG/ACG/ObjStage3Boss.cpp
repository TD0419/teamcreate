#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjStage3Boss.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStage3Boss::CObjStage3Boss()
{

}

//�C�j�V�����C�Y
void CObjStage3Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 8; //��O�{�X�̂g�o(���ɂg�o��[ 8 ]�Ɛݒ�)

}

//�A�N�V����
void CObjStage3Boss::Action()
{
	//���C
	//m_vx += -(m_vx * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);
}

//�h���[
void CObjStage3Boss::Draw()
{

}