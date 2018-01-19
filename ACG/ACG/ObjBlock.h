#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock(int x, int y);
	~CObjBlock() {};

	void Init() {};			//�C�j�V�����C�Y
	void Action();			//�A�N�V����
	void Draw();			//�h���[
	
	//�ʏ�u���b�N�Ƃ̓����蔻��
	void BlockHit(
		float* x, float* y, float width, float height,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy
	);

	// �S�Ẵu���b�N�Ƃ̓����蔻��
	void AllBlockHit(
		float* x, float* y, float width, float height,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy
	);
		
private:
	//�}�b�v��̈ʒu�i�v�f���j
	int m_map_x;	
	int m_map_y;
	//�u���b�N�̈ʒu
	float m_px;		
	float m_py;		
};
