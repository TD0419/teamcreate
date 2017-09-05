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

	//Door�I�u�W�F�N�g���쐬����
	CObjDoor* ObjDoor = new CObjDoor(3, 0);
	Objs::InsertObj(ObjDoor, OBJ_DOOR, 10);

	//�G�I�u�W�F�N�g���쐬����
	CObjEnemy* ObjEnemy = new CObjEnemy(10,10);
	Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 11);

	//test�{�X�I�u�W�F�N�g���쐬����
	//CObjBoss* ObjBoss = new CObjBoss(10,15);
	//Objs::InsertObj(ObjBoss, OBJ_BOSS, 11);

	//���t�g�I�u�W�F�N�g���쐬����
	CObjLift* Obj_lift = new CObjLift(6, 5);
	Objs::InsertObj(Obj_lift, OBJ_LIFT, 10);

	//�ŔI�u�W�F�N�g���쐬����
	CObjSign* Obj_sign = new CObjSign(6, 7);
	Objs::InsertObj(Obj_sign, OBJ_SIGN, 10);

	//���o�[�X�C�b�`�I�u�W�F�N�g���쐬����
	CObjLeverSwich* ObjLeverSwich = new CObjLeverSwich(7, 7);
	Objs::InsertObj(ObjLeverSwich, OBJ_LEVER_SWICH, 10);

	//test�͂����I�u�W�F�N�g���쐬����i�f�o�b�N�p�j
	/*CObjLadders* ObjLadders = new CObjLadders(6, 3);
	Objs::InsertObj(ObjLadders, OBJ_LADDERS, 10);
	CObjLadders* ObjLadders2 = new CObjLadders(6, 2);
	Objs::InsertObj(ObjLadders2, OBJ_LADDERS, 10);
	CObjLadders* ObjLadder3 = new CObjLadders(6, 1);
	Objs::InsertObj(ObjLadder3, OBJ_LADDERS, 10);*/

	////�؂̃e�X�g�I�u�W�F�N�g
	//CObjWood* ObjWood = new CObjWood(12, 0);
	//Objs::InsertObj(ObjWood, OBJ_WOOD, 10);

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

	//p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�O���f�[�^�ǂݍ���

	p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�{�X�`����m�F���������́A�������ǂݍ���ł�������
	
	if (p == nullptr)
	{
		MessageBox(0, L"�}�b�v�f�[�^��������܂���ł����B", L"�G���[�R�b�`��", MB_OK);
		return;
	}
	//�O���̃}�b�v��񂸂炷���
	int count = 1;

	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//�}�b�v��������
			int w = 0;
			//�}�b�v���擾
			swscanf_s(&p.get()[count], L"%d", &w);
			
			//�}�b�v������
			map[i][j] = w;

			//-1���������炷
			while (w/10 != 0)
			{
				count++;
				w /= 10;
			}
			count += 2;
		}
	}
	int a = 0;
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
	//Draw::LoadImageW(L"image2.jpg", 1, TEX_SIZE_512);
	// debug�pblock�摜
	//Draw::LoadImageW(L"testblock.png", 2, TEX_SIZE_512);

	// block�摜
	Draw::LoadImageW(L"block.png", 2, TEX_SIZE_128);

	//hero�摜
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_256);

	//debug�pBoss�摜
	Draw::LoadImageW(L"image3.png", 4, TEX_SIZE_512);
	//Draw::LoadImageW(L"image3.jpg", 4, TEX_SIZE_512);

	//Ladders�摜
	Draw::LoadImageW(L"Ladders.png", 5, TEX_SIZE_64);

	//Door & Padlock�摜
	Draw::LoadImageW(L"Door & Padlock.png", 6, TEX_SIZE_256);

	//Wood�摜
	Draw::LoadImageW(L"Wood.png", 7, TEX_SIZE_64);

	//Enemy�摜
	Draw::LoadImageW(L"Snake.png", 8, TEX_SIZE_128);

	//Lever�摜
	Draw::LoadImageW(L"Lever.png", 9, TEX_SIZE_128);
}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
	//���y�o�^ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}