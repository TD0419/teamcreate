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
	bool GetKeyFlag() { return m_key_flag; }  //���[�v���ɐ؂藣���邩�ǂ�����Ԃ�
	bool GetLastRoll() { return m_lastroll; } //��]���Ō�܂ōs�������ǂ�����Ԃ�

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
	bool m_lastroll; //�Ō�܂ŉ�]�������ǂ����𒲂ׂ�ifalse:�Ō�܂ŉ�]���ĂȂ� true:�Ō�܂ŉ�]�����j
	bool m_key_flag; //���[�v���ɐ؂藣���邩�ǂ�����n���ϐ�
	bool m_once_flag; //��񂾂���������

};