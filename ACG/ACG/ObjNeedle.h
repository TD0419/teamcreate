#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�Q
class CObjNeedle:public CObj
{
public:
	CObjNeedle(float x, float y);	// �R���X�g���N�^
	~CObjNeedle() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[

private:
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY
	
};
