#pragma once
#include "GameL\HitBoxManager.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

bool DeleteCheckObjNameHit(CHitBox* hit,CObj* cobj,OBJ_NAME objname);//�I�u�W�F�N�g�̏�������֐�

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBox�̈ʒu���X�V����֐�

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBox�̈ʒu�Ƒ傫�����X�V����֐�

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//��ʂ̊O�ɏo�Ă��邩���肷��֐�


void WindowOutDelete(CObj* obj_p);//��ʊO�ɂ���I�u�W�F�N�g�̍폜�֐�(��ʓ��ɓ����Ă��������Ȃ�)
void WindowOutDelete(CObj* obj_p, int map_x, int map_y);//��ʊO�ɂ���I�u�W�F�N�g�̍폜�֐�(��ʓ��ɓ������Ƃ��ɍēx����)

//�u���b�NA�ƃu���b�NB�̓����蔻��
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy);

//2�����̌�_�����߂�֐�
bool CrossLineVSLine(float L1_x, float L1_y, float L2_x, float L2_y, float L3_x, float L3_y, float L4_x, float L4_y, float &p_cross_x, float &p_cross_y);

