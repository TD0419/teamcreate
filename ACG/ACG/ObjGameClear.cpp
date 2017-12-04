//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjGameClear.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_key_flag = false;

	//�����̃O���t�B�b�N�쐬
	Font::SetStrTex(L"GAMECLEAR");	
}

//�A�N�V����
void CObjGameClear::Action()
{
	//�G���^�[�L�[�������ꂽ��
	if (Input::GetVKey(VK_RETURN) == true)
	{
		//�V�[���^�C�g���Ɉړ�
		Scene::SetScene(new CSceneTitle());
		return;
	}
}

//�h���[
void CObjGameClear::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�ݒ�
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 1024.0f;
	//src.m_bottom = 1024.0f;

	//////�\���ʒu�ݒ�
	//dst.m_top = 0.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 1024.0f;
	//dst.m_bottom = 1024.0f;

	//�w�i�`��
//	Draw::Draw(GRA_GAME_OVER, &src, &dst, color, 0.0f);

	//�����`��
	Font::StrDraw(L"GAMECLEAR", 2.f, WINDOW_SIZE_H / 3.f, 45.0f, color);

}