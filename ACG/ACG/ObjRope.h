#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���t�g
class CObjRope :public CObj
{
public:
	CObjRope(int x, int y); // �R���X�g���N�^
	~CObjRope() {};	// �f�X�g���N�^
	void Init();	// �C�j�V�����C�Y
	void Action();	// �A�N�V����
	void Draw();	// �h���[

private:
	float m_px;	// ���t�gX���W
	float m_py; // ���t�gY���W
};
