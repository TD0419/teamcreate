//STL�f�o�b�N�@�\��OFF�ɂ���
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
#include "SceneTitle.h"
#include "GameHead.h"

//���������\�b�h
void InitScene()
{
}

//���s�����\�b�h
void Scene()
{
	//�I�u�W�F�N�g���쐬����
	CObjTitle* ObjTitle = new CObjTitle();
	Objs::InsertObj(ObjTitle, OBJ_TITLE, 10);
}

//�摜�f�[�^�ǂݍ��݊֐�
void InageDataLoading()
{
}

//���y�f�[�^�ǂݍ��݊֐�
void AudioDataLoading()
{
}
