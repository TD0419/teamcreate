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

	Font::SetStrTex(L"     CLEAR!!");//

	Font::SetStrTex(L"GAME");//

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

	Font::StrDraw(L"GAME"   , WINDOW_SIZE_W - 799.0f, WINDOW_SIZE_H - 722.0f, 107.0f, text_color);
	Font::StrDraw(L"CLEAR!!", WINDOW_SIZE_W - 534.0f, WINDOW_SIZE_H - 722.0f, 107.0f, text_color);


	Font::StrDraw(L"GAME CLEAR!!"       , WINDOW_SIZE_W - 804.0f, WINDOW_SIZE_H - 722.0f, 106.0f, back_color);
	Font::StrDraw(L"TITLE:PUSH ENTERKEY", WINDOW_SIZE_W - 444.0f, WINDOW_SIZE_H - 58.0f, 45.0f, text_color);

}