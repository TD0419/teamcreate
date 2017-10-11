//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneGameClear.h"
#include "GameHead.h"

//���������\�b�h
void CSceneGameClear::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImageW(L".png", 0, TEX_SIZE_512);

	//���y�ǂݍ���
	Audio::LoadAudio(0, L".wav", BACK_MUSIC);

	//�{�����[����1.0�ɖ߂�
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((1.0 - v));

	//���y�X�^�[�g
	Audio::Start(0);

	//SE------------------------------
	Audio::LoadAudio(1, L".wav", EFFECT);			//���艹

	CObjGameClear* objgame_clear = new CObjGameClear();	//�N���A�I�u�W�F�N�g�쐬
	Objs::InsertObj(objgame_clear, OBJ_GAME_CLEAR, 10);	//�N���A�I�u�W�F�N�g�o�^
}

//���s�����\�b�h
void CSceneGameClear::Scene()
{
}