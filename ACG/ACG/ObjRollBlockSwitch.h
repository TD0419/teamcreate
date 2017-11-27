#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�@��]�u���b�N
class CObjRollBlockSwitch : public CObj
{
public:
	CObjRollBlockSwitch(float x, float y, CObjRollBlock* p);		//�R���X�g���N�^
	~CObjRollBlockSwitch() {};	//�f�X�g���N�^

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	float GetRad() { return m_r; }//�p�x��Ԃ�

	//�u���b�N�̈ʒu��Ԃ�
	float GetX() { return m_px; }
	float GetY() { return m_py; }
private:
	//�ʒu
	float m_px;
	float m_py;
	float m_r;

	//�u���b�N�̃|�W�V����
	float m_base_block_px;
	float m_base_block_py;


	//�X�C�b�`����p�������]�u���b�N�̃|�C���^
	CObjRollBlock* mp_base_block;

	bool m_pull_flag;//���[�v�ň�����Ă��邩�ǂ����̃t���O
	
};