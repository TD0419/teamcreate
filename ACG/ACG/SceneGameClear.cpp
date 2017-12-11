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
#include "SceneGameClear.h"
#include "GameHead.h"

//���������\�b�h
void CSceneGameClear::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^
	Draw::LoadImageW(L"Image\\BackGround\\Ending.png", GRA_GAME_CLEAR, TEX_SIZE_1024);
	
	//BGM----------------------------------
	//���y�ǂݍ���
	Audio::LoadAudio(CLEAR, L"BGM\\Clear.wav", BACK_MUSIC);

	//SE------------------------------
	//Audio::LoadAudio(1, L".wav", EFFECT);			//���艹

	//�Q�[���N���A�I�u�W�F�N�g�쐬
	CObjGameClear* objgame_clear = new CObjGameClear();	
	Objs::InsertObj(objgame_clear, OBJ_GAME_CLEAR, 10);	//�N���A�I�u�W�F�N�g�o�^
}

//���s�����\�b�h
void CSceneGameClear::Scene()
{

}