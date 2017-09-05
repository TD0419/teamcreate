#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�^��
class CObjButton : public CObj
{
	public:
		CObjButton(int x, int y);
		~CObjButton() {};
		void Init();	//�C�j�V�����C�Y
		void Action();  //�A�N�V����
		void Draw();	//�h���[

		/*-----------------------�A�N�Z�T-------------------------*/
		bool GetTrickFlag() { return m_trick_flag; } //�e�Ƃ������Ă��邩�ǂ�����Ԃ�

	private:
		float m_px; //�{�^��X�ʒu
		float m_py; //�{�^��Y�ʒu

		bool m_trick_flag; //��Ɠ������Ă��邩�ǂ����𒲂ׂ�

};