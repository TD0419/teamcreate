#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�}�b�v
class CObjMap :public CObj
{
public:
	CObjMap(int map[MAP_Y_MAX][MAP_X_MAX],int remaining); 	//�R���X�g���N�^
	~CObjMap() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	//�X�N���[���֘A--------------------------------------------------
	float GetScrollX() { return m_scroll_x; }		//X�����̃X�N���[���l��Ԃ��֐�
	float GetScrollY() { return m_scroll_y; }		//Y�����̃X�N���[���l��Ԃ��֐�
	void SetScrollX(float x) { m_scroll_x += x; }	//X�����̃X�N���[���l���Z�b�g����֐�
	void SetScrollY(float y) { m_scroll_y += y; }	//Y�����̃X�N���[���l���Z�b�g����֐�
	
	//�}�b�v����Ԃ�
	int  GetMap(int x, int y);

	//�}�b�v�̃t���O���X�V����
	void SetMapCreate(int x, int y, bool f) { m_map[y][x].create = f; }

	//�}�b�v�����Ƃɂ����I�u�W�F�N�g�̐����֘A----------------------------------
	void CreateObj(int x, int y);//�I�u�W�F�N�g�̐������s��
	void ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y);//�X�N���[���ʂ����ƂɃI�u�W�F�N�g�̐������s��
	void CreateFallingBloack();//������u���b�N�����𐶐�����i�{�X��p�j

	//�[�[�[�[�[�[�[�[�[�[�[�[�A�N�Z�T�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//m_map[y][x]�@�̂Ƃ����id������
	void SetMap(int x, int y, int id) { m_map[y][x].num = id; }	
	//------------------------------------------------------------------
	
private:
	float m_scroll_x;	//X���̃X�N���[���l
	float m_scroll_y;	//Y���̃X�N���[���l

	//�}�b�v�̍\����
	struct Map
	{
		int num;		//�}�b�v�̐��l
		bool create;	//�������邩�̃t���O
	};

	Map m_map[MAP_Y_MAX][MAP_X_MAX];	//�}�b�v�p�z��	���}�b�v���ł����炱�̔z��ɓ����
	int m_remaining;					// �v���C���[�̎c�@��
};