#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��
class CObjFallingWalls :public CObj
{
public:
	CObjFallingWalls(int x, int y); 	//�R���X�g���N�^
	~CObjFallingWalls() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_px;	//��X���W
	float m_py;	//��Y���W
};