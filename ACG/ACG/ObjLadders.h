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
	CObjLadders(int x,int y,bool look);	//�R���X�g���N�^
	~CObjLadders() {};					//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
	void HeroHit(float px, float py);//�v���C���[�����������Ƃ��̏���

private:
	float m_px;					//�n�V�SX���W
	float m_py;					//�n�V�SY���W
	bool  m_obj_look_f;			//�n�V�S�������邩�ǂ��� false:�����Ȃ� true:������
};
