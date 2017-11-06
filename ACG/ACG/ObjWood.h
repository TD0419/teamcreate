#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：木(ギミック)
class CObjWood :public CObj
{
	public:
		CObjWood(int x, int y);				//コンストラクタ
		~CObjWood() {};						//デストラクタ
		void Init();						//イニシャライズ
		void Action();						//アクション
		void Draw();						//ドロー
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
		int HeroHit(float ax, float ay, float aw, float ah,
			float* bx, float* by, float bw, float bh,
			float* bvx, float* bvy);
		void Rotation(bool flag) { m_rota_flag = flag; } // 木を回転させるかどうかの管理をする関数
	private:
		float m_px;			//X座標(空気画像を含む)
		float m_py;			//Y座標(空気画像を含む)
		float m_wood_x;	//木の画像(左上)のX位置
		float m_wood_y;	//木の画像(左上)のY位置
		float m_r;			//回転角度
		bool  m_rota_flag;  //回転フラグ false:回転しない true:回転する
};
