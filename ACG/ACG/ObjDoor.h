#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�h�A�Ƃ�������
class CObjDoor :public CObj
{
public:
	CObjDoor(int x, int y); // �R���X�g���N�^
	~CObjDoor() {};	// �f�X�g���N�^
	void Init();	// �C�j�V�����C�Y
	void Action();	// �A�N�V����
	void Draw();	// �h���[

private:
	float m_px;	// �h�AX���W
	float m_py; // �h�AY���W
};
