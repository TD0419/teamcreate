//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{
	
}

//���������\�b�h
void CSceneGameOver::InitScene()
{
	
	//�Q�[���I�[�o�[�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\BackGround\\Scene_Game_Over.png", GRA_GAME_OVER, TEX_SIZE_1024);

	//���y���̓ǂݍ���
	//BGM�|�|�|�|
	Audio::LoadAudio(GAMEOVER, L"BGM\\GameOver.wav", BACK_MUSIC);	//�Q�[���I�[�o�[��
	//																

	//SE�|�|�|�|�|

	//Audio::LoadAudio(1, L".wav", EFFECT);			//���艹
																
	//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	CObjGameOver* objgame_over = new CObjGameOver();
	Objs::InsertObj(objgame_over, OBJ_GAME_OVER, 10);
}

//���s�����\�b�h
void CSceneGameOver::Scene()
{

}