//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"

//�R���g���X�g
CSceneMain::CSceneMain()
{

}
//�f�X�g���X�g
CSceneMain::~CSceneMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//�}�b�v���i�[�p�ϐ��e�X�g�p
	int map[MAP_Y_MAX][MAP_X_MAX] = { 0 };

	//�}�b�v����ǂݍ���
	MapDataLoading(map);

	ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�

    //Map�I�u�W�F�N�g���쐬����
	CObjMap* ObjMap = new CObjMap(map);
	Objs::InsertObj(ObjMap, OBJ_MAP, 10);

	//��l���I�u�W�F�N�g���쐬����
	CObjHero* ObjHero = new CObjHero(3,5);
	Objs::InsertObj(ObjHero, OBJ_HERO, 10);

	//test�G�I�u�W�F�N�g���쐬����
	CObjEnemy* ObjEnemy = new CObjEnemy(10,10);
	Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 11);

	//block�I�u�W�F�N�g�쐬
	CObjBlock* obj_block = new CObjBlock();
	Objs::InsertObj(obj_block, OBJ_BLOCK, 9);
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}
//�}�b�v�f�[�^�ǂݍ��݊֐�
void CSceneMain::MapDataLoading(int map[MAP_Y_MAX][MAP_X_MAX])
{
	
	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;	//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��

	p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�O���f�[�^�ǂݍ���

	
	if (p == nullptr)
	{
		MessageBox(0, L"�}�b�v�f�[�^��������܂���ł����B", L"�G���[�R�b�`��", MB_OK);
		return;
	}

	int count = 1;

	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			
			map[i][j] = w;

			while (w/10 != 0)
			{
				count++;
				w /= 10;
			}
			
			count += 2;
		}
	}	
}

//�摜�f�[�^�ǂݍ��݊֐�
void CSceneMain::ImageDataLoading()
{
	//�摜�o�^ID
	//int id = 0;
	//�O���t�B�b�N�ǂݍ���
	//Draw::LoadImageW(L"", id++, TEX_SIZE_???);
	
	//debug�phero�摜
	//Draw::LoadImageW(L"image.jpg",0, TEX_SIZE_512);
	//debug�penemy�摜
	Draw::LoadImageW(L"image2.jpg", 1, TEX_SIZE_512);
	// debug�pblock�摜
	Draw::LoadImageW(L"testblock.png", 2, TEX_SIZE_512);

	//hero�摜
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_256);

}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
	//���y�o�^ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}