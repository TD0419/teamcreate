#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FWater
class CObjWater :public CObj
{
public:
	CObjWater(int x, int y); 	//�R���X�g���N�^
	~CObjWater() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_px;	//X���W
	float m_py;	//Y���W
	float m_water_gauge; // ���ʊǗ�
};