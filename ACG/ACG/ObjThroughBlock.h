#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X���[�u���b�N
class CObjThroughBlock :public CObj
{
public:
	CObjThroughBlock(int x, int y); 	//�R���X�g���N�^
	~CObjThroughBlock() {};				//�f�X�g���N�^
	void Init() {};						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
	
private:
	float m_px;	//X���W
	float m_py;	//Y���W
	int m_map_x;//�}�b�v�̗v�f��
	int m_map_y;
};
