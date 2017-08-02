#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public :
	CObjBlock(int map[MAP_X][MAP_Y]);
	~CObjBlock(){};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScroll(float s)	{m_scroll = s;}
	float GetScroll()		{return m_scroll;}

	//ブロックとの当たり判定
	void BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,int *bt,bool *needle
	);

	//主人公と壁の交差判定
	bool HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	);

	//マップ変更用関数
	void MapChange(int map[MAP_Y][MAP_X]);

private:
	void BlockDraw(float x, float y, RECT_F* dst, float c[]);
	
	int m_map[MAP_Y][MAP_X]; //マップ情報

	float m_scroll;		//左右スクリーン用

	float m_magma;		//マグマの切り取り地変更用

	float Dot(float ax, float ay, float bx, float by);	//内積
	float Cross(float ax, float ay, float bx, float by);//外積

	//線と線との交差判定
	bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
		);

};