#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�n�V�S
class CObjLadders :public CObj
{
public:
	CObjLadders(float x, float y);
	~CObjLadders() {};	//�f�X�g���N�^
	void Init();	    //�C�j�V�����C�Y
	void Action();	    //�A�N�V����
	void Draw();	    //�h���[

private:
	float m_ladders_x; //�n�V�SX���W
	float m_ladders_y; //�n�V�SY���W
};
