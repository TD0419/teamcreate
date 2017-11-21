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
		
	private:
		float m_px;	//X���W
		float m_py;	//Y���W

					//�}�b�v��̈ʒu�i�v�f���j
		int m_map_x;//X
		int m_map_y;//Y
		int m_wall_gauge;//�ǂ̍����Ǘ�
		int m_wall_gauge2;
		bool m_wall_unlock_flag;//�{�^���������ꂽ���̃t���O
		bool m_hero_hit_flag;   //�ǂ̍�����hero�����������Ƃ��̃t���O
		bool m_wall_down_flag;  //�ǂ����ɉ�����t���O

		//�ǂ̃X�e�[�W���Ƃ̎�ށB
		//1,2�������Ȃ��@3���X�C�b�`�ł�����@5=��l��������������J��
		int m_wall_type;


};