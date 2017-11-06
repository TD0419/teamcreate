#pragma once
#include "GameL\HitBoxManager.h"
using namespace GameL;

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBoxの位置を更新する関数

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBoxの位置と大きさを更新する関数

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//画面の外に出ているか判定する関数