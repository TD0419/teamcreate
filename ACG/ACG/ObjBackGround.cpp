#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBackGround::CObjBackGround(int x, int y)
{

}

//�C�j�V�����C�Y
void CObjBackGround::Init()
{
	 m_x=0;	// �w�iX���W
	 m_y=0;	// �w�iY���W
}

//�A�N�V����
void CObjBackGround::Action()
{
	
}

//�h���[
void CObjBackGround::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	
}