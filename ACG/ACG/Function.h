#pragma once
#include "GameL\HitBoxManager.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

bool DeleteCheckObjNameHit(CHitBox* hit,CObj* cobj,OBJ_NAME objname);//オブジェクトの消失する関数

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBoxの位置を更新する関数

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBoxの位置と大きさを更新する関数

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//画面の外に出ているか判定する関数


void WindowOutDelete(CObj* obj_p);//画面外にあるオブジェクトの削除関数(画面内に入っても復活しない)
void WindowOutDelete(CObj* obj_p, int map_x, int map_y);//画面外にあるオブジェクトの削除関数(画面内に入ったときに再度復活)

//ブロックAとブロックBの当たり判定
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy);

//2直線の交点を求める関数
bool CrossLineVSLine(float L1_x, float L1_y, float L2_x, float L2_y, float L3_x, float L3_y, float L4_x, float L4_y, float &p_cross_x, float &p_cross_y);

