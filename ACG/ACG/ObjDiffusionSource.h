#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�g�U�e�̌�
class CObjDiffusionSource :public CObj
{
public:
	CObjDiffusionSource(float x, float y,int limit); 	//�R���X�g���N�^
	~CObjDiffusionSource() {};				//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[

	//�A�N�Z�T
	float GetPosX() { return m_px; }
	float GetPosY() { return m_py; }

private:
	float m_px;			//X���W
	float m_py;			//Y���W
	float m_vy;			//�ړ��x�N�g��
	float m_vx;			//�ړ��x�N�g��
	int m_limit;		//�����܂ł̎���
};