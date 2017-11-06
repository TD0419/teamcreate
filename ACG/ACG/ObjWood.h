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
		//�u���b�NA�ƃu���b�NB�̓����蔻��
		//�u���b�NA���ړ����Ȃ��u���b�N
		//�u���b�NB�����������ꍇ�ړ�����u���b�N
		//����1  float  ax		:�u���b�NA��X�ʒu
		//����2  float  ay		:�u���b�NA��Y�ʒu
		//����3  float  aw		:�u���b�NA�̕�
		//����4  float  ah		:�u���b�NA�̍���
		//����5  float* bx		:�u���b�NB��X�ʒu �|�C���^
		//����6  float* by		:�u���b�NB��Y�ʒu �|�C���^
		//����7  float  bw		:�u���b�NB�̕�
		//����8  float  bh		:�u���b�NB�̍���
		//����9  float* bvx		:�u���b�NB��X�ړ��� �|�C���^
		//����10 float* bvy		:�u���b�NB��Y�ړ��� �|�C���^
		//�߂�l	int			:�����������ǂ���||�ǂ��ɓ����������@0=�����薳���F1=B���猩�ď�F2=B���猩�ĉ��F3=B���猩�ĉE:4=B���猩�č�
		int HeroHit(float ax, float ay, float aw, float ah,
			float* bx, float* by, float bw, float bh,
			float* bvx, float* bvy);
		void Rotation(bool flag) { m_rota_flag = flag; } // �؂���]�����邩�ǂ����̊Ǘ�������֐�
	private:
		float m_px;			//X���W(��C�摜���܂�)
		float m_py;			//Y���W(��C�摜���܂�)
		float m_wood_x;	//�؂̉摜(����)��X�ʒu
		float m_wood_y;	//�؂̉摜(����)��Y�ʒu
		float m_r;			//��]�p�x
		bool  m_rota_flag;  //��]�t���O false:��]���Ȃ� true:��]����
};
