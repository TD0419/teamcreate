#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define MAP_X 100
#define MAP_Y 10

//�V�[���F�Q�[�����C��
class CSceneMain:public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//�Q�[�����C�����������\�b�h
	void Scene();   //�Q�[�����C���̎��s�����\�b�h
	
private:
	void MapDataLoading(int map[MAP_Y][MAP_X]);//�}�b�v�f�[�^�ǂݍ��݊֐��@�����͉�
	void ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	void AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�

};