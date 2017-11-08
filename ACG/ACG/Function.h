#pragma once
#include "GameL\HitBoxManager.h"
using namespace GameL;

void HitBoxUpData(CHitBox* hit,float m_px,float m_py);//HitBoxの位置を更新する関数

void HitBoxUpData(CHitBox* hit, float m_px, float m_py,float w,float h);//HitBoxの位置と大きさを更新する関数

bool WindowCheck(float m_px, float m_py,float obj_size_x,float obj_size_y);//画面の外に出ているか判定する関数

//ブロックAとブロックBの当たり判定
//ブロックA＝移動しないブロック
//ブロックB＝あたった場合移動するブロック
//引数1  float  ax		:ブロックAのX位置
//引数2  float  ay		:ブロックAのY位置
//引数3  float  aw		:ブロックAの幅
//引数4  float  ah		:ブロックAの高さ
//引数5  float* bx		:ブロックBのX位置 ポインタ
//引数6  float* by		:ブロックBのY位置 ポインタ
//引数7  float  bw		:ブロックBの幅
//引数8  float  bh		:ブロックBの高さ
//引数9  float* bvx		:ブロックBのX移動量 ポインタ
//引数10 float* bvy		:ブロックBのY移動量 ポインタ
//戻り値	int			:当たったかどうか||どこに当たったか　0=当たり無し：1=Bから見て上：2=Bから見て下：3=Bから見て右:4=Bから見て左
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy);