#pragma once
#include "GameL\HitBoxManager.h"
using namespace GameL;

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBox�̈ʒu���X�V����֐�

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBox�̈ʒu�Ƒ傫�����X�V����֐�

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//��ʂ̊O�ɏo�Ă��邩���肷��֐�