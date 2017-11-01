#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FWater(�M�~�b�N)
class CObjLastWall :public CObj
{
	public:
		CObjLastWall(int x, int y); 	//�R���X�g���N�^
		~CObjLastWall() {};			//�f�X�g���N�^
		void Init();				//�C�j�V�����C�Y
		void Action();				//�A�N�V����
		void Draw();				//�h���[

		bool GateOpenflag;
	private:
		float m_px;	//X���W
		float m_py;	//Y���W

					//�}�b�v��̈ʒu�i�v�f���j
		int m_map_x;//X
		int m_map_y;//Y
		float m_wall_gauge;//�ǂ̍����Ǘ�
		bool m_look_unlock_flag;//�{�^���������ꂽ���̃t���O
};