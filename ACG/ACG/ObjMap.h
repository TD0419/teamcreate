#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�}�b�v
class CObjMap :public CObj
{
public:
	CObjMap(); 	//�R���X�g���N�^
	~CObjMap() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	//�X�N���[���֘A
	float GetScrollX() { return m_scroll_x; }		//X�����̃X�N���[���l��Ԃ��֐�
	float GetScrollY() { return m_scroll_y; }		//Y�����̃X�N���[���l��Ԃ��֐�
	void SetScrollX(float x) { m_scroll_x += x; }	//X�����̃X�N���[���l���Z�b�g����֐�
	void SetScrollY(float y) { m_scroll_y += y; }	//X�����̃X�N���[���l���Z�b�g����֐�
	
private:
	float m_scroll_x;//X���̃X�N���[���l
	float m_scroll_y;//Y���̃X�N���[���l
};