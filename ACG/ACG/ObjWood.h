#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��(�M�~�b�N)
class CObjWood :public CObj
{
	public:
		CObjWood(int x, int y);				//�R���X�g���N�^
		~CObjWood() {};						//�f�X�g���N�^
		void Init();						//�C�j�V�����C�Y
		void Action();						//�A�N�V����
		void Draw();						//�h���[

	private:
		float m_px;			//X���W(��C�摜���܂�)
		float m_py;			//Y���W(��C�摜���܂�)
		float m_wood_image_x;//�؂̉摜(����)��X�ʒu
		float m_wood_image_y;//�؂̉摜(����)��Y�ʒu
		float m_r;			//��]�p�x
		bool m_audio_start_flag;//�؂̉���炷���߂̃t���O�ϐ�
};
