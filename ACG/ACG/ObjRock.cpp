//�g�p����w�b�_�[�t�@�C���@
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRock::CObjRock(float x, float y)
{
	m_rock_x = x;
	m_rock_y = y;
}

//�C�j�V�����C�Y
void CObjRock::Init()
{

}

//�A�N�V����
void CObjRock::Action()
{
	//////�e�ƐڐG���Ă��邩�ǂ����𒲂ׂ�
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	//�₪����A�j���[�V����������

	//	//----//

	//	this->SetStatus(false);		//���g�ɍ폜���߂��o��
	//	Hits::DeleteHitBox(this);	//�G�����L����HitBox�ɍ폜����
	//}
}

//�h���[
void CObjRock::Draw()
{

}