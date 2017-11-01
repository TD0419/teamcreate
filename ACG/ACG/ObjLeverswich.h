#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���o�[�X�C�b�`
class CObjLeverSwich :public CObj
{
public:
	CObjLeverSwich(float x, float y);	// �R���X�g���N�^
	~CObjLeverSwich() {};				// �f�X�g���N�^
	void Init();						// �C�j�V�����C�Y
	void Action();						// �A�N�V����
	void Draw();						// �h���[
	bool GetWater() { return m_water_con; } //���o�[�ƃX�C�b�`���������Ă��邩�ǂ���������ϐ��iWater�p�j

private:
	float m_px;				// ���o�[�X�C�b�`X���W
	float m_py;				// ���o�[�X�C�b�`Y���W
	bool  m_water_con;          //�@���̔��������ϐ�

	//�A�j���[�V�����֌W
	int m_ani_time;         //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;        //�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
};
