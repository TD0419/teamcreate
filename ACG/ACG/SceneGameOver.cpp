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
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�~1024�s�N�Z��)
	//Draw::LoadImageW(L"", 0, TEX_SIZE_1024);

	//png",10, TEX_SIZE_512);

	////���y���̓ǂݍ���
	////BGM�|�|�|�|
	//Audio::LoadAudio(0, L".wav", BACK_MUSIC);	//�Q�[���I�[�o�[��
	//																
	////�O�Ԃ̉��y�X�^�[�g
	//Audio::Start(0);

	////SE�|�|�|�|�|
	//Audio::LoadAudio(1, L".wav", EFFECT);			//���艹

	//																	
	////�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	//CObjGameOver* obj = new CObjGameOver();
	//Objs::InsertObj(obj, OBJ_GAME_OVER, 10);
}

//���s�����\�b�h
void CSceneGameOver::Scene()
{

}