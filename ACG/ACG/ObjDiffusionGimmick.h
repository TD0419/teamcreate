#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�U�e���ˑ��u
class CObjDiffusionGimmick :public CObj
{
public:
	CObjDiffusionGimmick(float x, float y);	// �R���X�g���N�^
	~CObjDiffusionGimmick() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[

private:
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY

};
