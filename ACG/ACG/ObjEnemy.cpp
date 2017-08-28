#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(int x,int y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64.0f, 64.0f, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy::Action()
{
	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);//HitBox�̈ʒu���X�V

	//�e�ۂƂ������������		���e�ۂ̑����ɂ���
	if (hit->SearchElementHit(ELEMENT_PLAYER) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�G����������HitBox�������B
	}
}

//�h���[
void CObjEnemy::Draw()
{
}