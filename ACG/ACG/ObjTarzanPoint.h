#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���[�v�łԂ牺���邱�Ƃ��ł���M�~�b�N
class CObjTarzanPoint :public CObj
{
public:
	CObjTarzanPoint(int x,int y); 	//�R���X�g���N�^
	~CObjTarzanPoint() {};				//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
private:
	float m_px;							//X���W
	float m_py;							//Y���W
	
};