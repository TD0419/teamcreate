//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneTitle.h"
#include "GameHead.h"

//���������\�b�h
void CSceneTitle::InitScene()
{
	InageDataLoading();
	//�I�u�W�F�N�g���쐬����
	CObjTitle* objtitle = new CObjTitle();
	Objs::InsertObj(objtitle, OBJ_TITLE, 10);
}

//���s�����\�b�h
void CSceneTitle::Scene()
{
	
}

//�摜�f�[�^�ǂݍ��݊֐�
void CSceneTitle::InageDataLoading()
{
	//�^�C�g���摜�ǂݍ���
	Draw::LoadImageW(L"Image\\BackGround\\Scene_Title.png", GRA_TITLE, TEX_SIZE_1024);
}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneTitle::AudioDataLoading()
{
}

