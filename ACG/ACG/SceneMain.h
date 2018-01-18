#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�Q�[�����C��
class CSceneMain:public CScene
{
public:
	CSceneMain() ;		//�R���X�g���N�^
	CSceneMain::CSceneMain(int n);//�R���X�g���N�^(���X�^�[�g�p)
	~CSceneMain() {};	//�f�X�g���N�^
	void InitScene();	//�Q�[�����C�����������\�b�h
	void Scene() {};		//�Q�[�����C���̎��s�����\�b�h
private:
	int m_map[MAP_Y_MAX][MAP_X_MAX];//�}�b�v�i�[�p�ϐ�
	void MapDataLoading(int map[MAP_Y_MAX][MAP_X_MAX]);//�}�b�v�f�[�^�ǂݍ��݊֐��@�����͉�
	void ImageDataLoading();	//�摜�f�[�^�ǂݍ��݊֐�
	void AudioDataLoading();	//���y�f�[�^�ǂݍ��݊֐�
};

