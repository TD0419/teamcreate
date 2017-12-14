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
	
	Audio::Start(CLEAR);
	//�����̃O���t�B�b�N�쐬
	Font::SetStrTex(L"GAME CLEAR!!");	
	Font::SetStrTex(L"TITLE:PUSH ENTER KEY");
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
	float back_color [4] = { 1.0f,1.0f,1.0f,1.0f };//�w�i�p�J���[
	float text_color [4] = { 0.0f,0.0f,0.0f,1.0f };//�����p�J���[(��)

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1024.0f;
	dst.m_bottom = 1024.0f;

	//�w�i�`��
	Draw::Draw(GRA_GAME_CLEAR, &src, &dst, back_color, 0.0f);

	//�����`��                              x      y     size
	Font::StrDraw(L"GAME CLEAR!!"       , 220.0f, 46.0f, 105.0f, text_color);
	Font::StrDraw(L"TITLE:PUSH ENTERKEY", 580.0f, 710.0f, 45.0f, text_color);

}