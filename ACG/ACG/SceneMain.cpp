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


//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	MapDataLoading(map);//�}�b�v����ǂݍ���
	ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�

    //Map�I�u�W�F�N�g���쐬����
	CObjMap* objmap = new CObjMap(map);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//��l���I�u�W�F�N�g���쐬����
	CObjHero* objhero = new CObjHero(0,0);
	Objs::InsertObj(objhero, OBJ_HERO, 10);

	//�w�i�I�u�W�F�N�g���쐬����
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

//�f�o�b�O�@�h�g���I�����������Ă��������I�h----------------
	//Door�I�u�W�F�N�g���쐬����
	CObjDoor* objdoor = new CObjDoor(3, 3);
	Objs::InsertObj(objdoor, OBJ_DOOR, 10);

	//�ŔI�u�W�F�N�g���쐬����
	CObjSign* objsign = new CObjSign(14, 7);
	Objs::InsertObj(objsign, OBJ_SIGN, 10);

	//���[�v�X�C�b�`�I�u�W�F�N�g���쐬����
	CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(7, 5);
	Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 10);

	//test�C��I�u�W�F�N�g���쐬����
	CObjCannon* objcannon = new CObjCannon(10, 5);
	Objs::InsertObj(objcannon, OBJ_CANNON, 10);


//�f�o�b�O-----------------------------------------------
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

	//Stage01�̃e�X�g�v���C���̂���Stage02.csv�̓ǂݍ��݂�ύX���Ă��܂�

	p = Save::ExternalDataOpen(L"Stage01a.csv", &size);//�O���f�[�^�ǂݍ���
	
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
}

//�摜�f�[�^�ǂݍ��݊֐�
void CSceneMain::ImageDataLoading()
{
	//�摜�o�^ID
	//int id = 0;
	//�O���t�B�b�N�ǂݍ���
	//Draw::LoadImageW(L"", id++, TEX_SIZE_???);
	
	// block�摜
	Draw::LoadImageW(L"block.png", 2, TEX_SIZE_128);

	//hero�摜
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_1024);

	//debug�pBoss�摜
	Draw::LoadImageW(L"image.png", 4, TEX_SIZE_1024);

	//Ladders�摜
	Draw::LoadImageW(L"Ladders.png", 5, TEX_SIZE_64);

	//Door & Padlock�摜
	Draw::LoadImageW(L"Door.png", 6, TEX_SIZE_128);

	//Wood�摜
	Draw::LoadImageW(L"Wood.png", 7, TEX_SIZE_128);
	
	//Enemy�摜
	Draw::LoadImageW(L"Snake.png", 8, TEX_SIZE_256);

	//Lever�摜
	Draw::LoadImageW(L"Lever.png", 9, TEX_SIZE_128);

	//rock�摜
	Draw::LoadImageW(L"rock.png", 10, TEX_SIZE_256);

	//Water�摜
	Draw::LoadImageW(L"Water.png", 11, TEX_SIZE_256);

	//Water�g�Ȃ��摜  �������Ⴞ�߁B����܂��I
	Draw::LoadImageW(L"WaterBlock.png", 12, TEX_SIZE_256);
	
	//RopeSwitch�摜
	Draw::LoadImageW(L"RopeSwitch.png", 13, TEX_SIZE_64);

	//��C
	Draw::LoadImageW(L"image4.png", 14, TEX_SIZE_64);
	
	//�w�i�摜
	Draw::LoadImageW(L"background.png" ,15, TEX_SIZE_1536);

	//�؉摜
	Draw::LoadImageW(L"woodtst.png", 16, TEX_SIZE_128);

	//�Ŕ̘g��
	Draw::LoadImageW(L"Sign.png", 17, TEX_SIZE_256);
	
	//�{�^��
	Draw::LoadImageW(L"button.png", 20, TEX_SIZE_128);

	//lastwall(��)
	Draw::LoadImageW(L"Lastwall.png", 21, TEX_SIZE_256);//��
	Draw::LoadImageW(L"Openwall.png", 22, TEX_SIZE_512);//��

	//zanki(��)
	Draw::LoadImageW(L"zanki.png", 23, TEX_SIZE_64);
	
	//���t�g
	Draw::LoadImageW(L"Lift.png", 24, TEX_SIZE_128);

	//�Ŕ�
	//Draw::LoadImageW(L"", 25, TEX_SIZE_256);�C���X�g���܂��Ă���ǂݍ���ł�������


}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
	//���y�o�^ID
	int id = 0;
	//Audio::LoadAudio(id++, L"", ? ? ? ? );
}