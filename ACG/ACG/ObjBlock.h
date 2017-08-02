#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public :
	CObjBlock(int map[MAP_X][MAP_Y]);
	~CObjBlock(){};

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetScroll(float s)	{m_scroll = s;}
	float GetScroll()		{return m_scroll;}

	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,int *bt,bool *needle
	);

	//��l���ƕǂ̌�������
	bool HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	);

	//�}�b�v�ύX�p�֐�
	void MapChange(int map[MAP_Y][MAP_X]);

private:
	void BlockDraw(float x, float y, RECT_F* dst, float c[]);
	
	int m_map[MAP_Y][MAP_X]; //�}�b�v���

	float m_scroll;		//���E�X�N���[���p

	float m_magma;		//�}�O�}�̐؂���n�ύX�p

	float Dot(float ax, float ay, float bx, float by);	//����
	float Cross(float ax, float ay, float bx, float by);//�O��

	//���Ɛ��Ƃ̌�������
	bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
		);

};