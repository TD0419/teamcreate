#pragma once
#include "GameL\HitBoxManager.h"
using namespace GameL;

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBox�̈ʒu���X�V����֐�

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBox�̈ʒu�Ƒ傫�����X�V����֐�

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//��ʂ̊O�ɏo�Ă��邩���肷��֐�

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
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy);