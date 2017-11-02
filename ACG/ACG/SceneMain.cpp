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
	MapDataLoading(m_map);//�}�b�v����ǂݍ���
	ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�

    //Map�I�u�W�F�N�g���쐬����
	CObjMap* objmap = new CObjMap(m_map);
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

	//�ǃe�X�g�̂���boss
	CObjBoss*objboss = new CObjBoss(10, 5);
	Objs::InsertObj(objboss, OBJ_BOSS, 10);

	//�e�X�g�^�C��
	CObjTime* objtime = new CObjTime();
	Objs::InsertObj(objtime, OBJ_TIME, 100);
	//�f�o�b�O--------------------------------------------

	//�e�X�g�{�^��
	CObjButton* objbuttn = new CObjButton(5,5);
	Objs::InsertObj(objbuttn, OBJ_BUTTON, 10);
	

	//BGM�Đ�
	Audio::Start(STAGE1);

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
		MessageBox(0, L"�}�b�v�f�[�^��������܂���ł����B", NULL, MB_OK);
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
	
	//�w�i�摜
	Draw::LoadImageW(L"background.png", GRA_BACKGROUND, TEX_SIZE_1536);

	//hero�摜
	Draw::LoadImageW(L"Hero.png", GRA_HERO, TEX_SIZE_1024);

	// block�摜
	Draw::LoadImageW(L"block.png", GRA_BLOCK, TEX_SIZE_128);

	//Boss�摜
	Draw::LoadImageW(L"image.png", GRA_BOSS, TEX_SIZE_1024);

	//Ladders�摜
	Draw::LoadImageW(L"Ladders.png", GRA_LADDERS, TEX_SIZE_64);

	//Door & Padlock�摜
	Draw::LoadImageW(L"Door.png", GRA_DOOR, TEX_SIZE_128);

	//Wood�摜
	Draw::LoadImageW(L"Wood.png", GRA_WOOD, TEX_SIZE_128);
	
	//Enemy�摜
	Draw::LoadImageW(L"Snake.png", GRA_ENEMY, TEX_SIZE_256);

	//Leverswich�摜
	Draw::LoadImageW(L"Lever.png", GRA_LEVER_SWICH, TEX_SIZE_128);

	//rock�摜
	Draw::LoadImageW(L"rock.png", GRA_ROCK, TEX_SIZE_256);

	//Water(����)�摜
	Draw::LoadImageW(L"Water.png", GRA_AQUATIC, TEX_SIZE_256);

	//Water�g�Ȃ�(����)�摜  �������Ⴞ�߁B����܂��I
	Draw::LoadImageW(L"WaterBlock.png", GRA_UNDER_WATER, TEX_SIZE_256);
	
	//RopeSwitch�摜
	Draw::LoadImageW(L"RopeSwitch.png", GRA_ROPE_SWITCH, TEX_SIZE_64);

	//��C
	Draw::LoadImageW(L"image4.png", GRA_CANNON, TEX_SIZE_64);
	

	//�Ŕ̘g��
	Draw::LoadImageW(L"Sign.png", GRA_SIGN_FRAME, TEX_SIZE_256);
	
	//�{�^��
	Draw::LoadImageW(L"button.png", GRA_BUTTON, TEX_SIZE_128);

	//lastwall(��)
	Draw::LoadImageW(L"Lastwall.png", GRA_LAST_WALL, TEX_SIZE_256);//��
	Draw::LoadImageW(L"Openwall.png", GRA_OPEN_WALL, TEX_SIZE_512);//��

	//zanki(��)
	Draw::LoadImageW(L"zanki.png", GRA_LIFE, TEX_SIZE_64);
	
	//���t�g
	Draw::LoadImageW(L"Lift.png", GRA_LIFT, TEX_SIZE_128);

	//�Ŕ�(�{��)
	//Draw::LoadImageW(L"", GRA_SIGN_MAIN, TEX_SIZE_256);�C���X�g���܂��Ă���ǂݍ���ł�������
	
}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
	//���y�o�^ID
	//int id = 0;
	//Audio::LoadAudio(id++, L"", ? ? ? ? );

//BGM--------------------------------------------------------

	//�X�e�[�W1
	Audio::LoadAudio(STAGE1, L"Grassland1.wav",SOUND_TYPE::BACK_MUSIC);

//------------------------------------------------------------

//SE--------------------------------------------------------
	
	//�e�̔���
	Audio::LoadAudio(FIRING, L"Firing1.wav", SOUND_TYPE::EFFECT);

	//��̑ł��o��
	Audio::LoadAudio(ROPE, L"Rope1.wav", SOUND_TYPE::EFFECT);

	//��̔���
	Audio::LoadAudio(ROCK, L"Rock1.wav", SOUND_TYPE::EFFECT);

	//���̊J��
	Audio::LoadAudio(DOOR, L"Door1.wav", SOUND_TYPE::EFFECT);

	//�؂̓]�|
	Audio::LoadAudio(TREE, L"Tree1.wav", SOUND_TYPE::EFFECT);

//------------------------------------------------------------


}