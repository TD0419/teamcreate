#pragma once
//�g�p�w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���t�g
class CObjButton : public CObj
{
	public:
		CObjButton(float x, float y);
		~CObjButton() {};
		void Init();	//�C�j�V�����C�Y
		void Action();  //�A�N�V����
		void Draw();	//�h���[

		bool GetFlag() { return m_door_flag; } //�e�Ƃ������Ă��邩�ǂ�����Ԃ�

	private:
		float m_x;		//�ʒu
		float m_y;

		bool m_door_flag; //�e�Ƃ����Ă��邩�ǂ���������ϐ�

						  //bool�Ƃ̏Փˏ�Ԋm�F�p
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;	//�`��t���[��
		int m_ani_max_time;	//�A�j���[�V�����t���[������Ԋu�̍ő�l
		int m_ani_max_frame;//�`��t���[���̍ő�l

};