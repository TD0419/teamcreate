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
		void Rotation(bool flag) { m_rota_flag = flag; } // �؂���]�����邩�ǂ����̊Ǘ�������֐�
	private:
		float m_px;			//X���W(��C�摜���܂�)
		float m_py;			//Y���W(��C�摜���܂�)
		float m_wood_image_x;//�؂̉摜(����)��X�ʒu
		float m_wood_image_y;//�؂̉摜(����)��Y�ʒu
		float m_r;			//��]�p�x
		bool  m_rota_flag;  //��]�t���O false:��]���Ȃ� true:��]����
		bool a;
};
