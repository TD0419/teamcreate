#pragma once
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�o�b�O�O���E���h(�w�i)
class CObjBackGround :public CObj
{
public:
	CObjBackGround() {};	// �R���X�g���N�^
	~CObjBackGround() {};			// �f�X�g���N�^
	void Init();					// �C�j�V�����C�Y
	void Action();					// �A�N�V����
	void Draw();					// �h���[

private:
	float m_px;	// �w�iX���W
	float m_py;	// �w�iY���W
	

};