#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "Function.h"

#include "GameHead.h"
#include "ObjRope.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1	float x		:主人公の腕の位置X
//引数2	float y		:主人公の腕の位置Y
CObjRope::CObjRope(float x, float y)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公オブジェクト情報を取得
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//初期位置を決める
	m_px = x;
	m_py = y;

	//速さを決める
	m_speed = 6.5f;
	
	//マウスの位置情報をheroから持ってくるのでマージする時はこっちを残してください（変数もこっちに変えてください）
	m_moux = objhero->GetRopeMouX(); //Rを押した時のマウスの位置Xを持ってくる
	m_mouy = objhero->GetRopeMouY(); //Rを押した時のマウスの位置Yを持ってくる

	//主人公が本来いる位置に変更
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();
	
	//主人公の位置からマウスの位置のベクトル情報取得
	float vector_x = m_moux - x;
	float vector_y = m_mouy - y;

	//斜辺取得
	float hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//角度を求める
	m_r = acos(vector_x / hypotenuse);
	
	//角度方向に移動
	m_vx = cos(m_r) * m_speed;

	//マウスのY位置が主人公のY位置より下だったら
	if (m_mouy > y)
	{
		//180°～360°の値にする
		m_r = 360.0f - abs(m_r);
	}
	//マウスのY位置が初期Y位置より上
	if (m_mouy < y)
	{
		m_vy = -sin(m_r) * m_speed;
	}
	else
	{
		m_vy = sin(m_r) * m_speed;
	}
}

//イニシャライズ
void CObjRope::Init()
{
	m_caught_flag = false;//false = フラグOFF true = フラグON
	m_delete = false;     //false = フラグOFF true = フラグON
	
	//ブロックとの当たり判定フラグの初期化
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
						  
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, ROPE_SIZE, ROPE_SIZE, ELEMENT_PLAYER, OBJ_ROPE, 1);
}

//アクション
void CObjRope::Action()
{
	//主人公のオブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//画面外にいれば
	if(WindowCheck(m_px,m_py,ROPE_SIZE, ROPE_SIZE) == false)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		m_delete =true;  //ロープは消えていることを変数に入れる
		return;
	}
	else
		m_delete =false;//ロープは消えていないことを変数に入れる
	
	//ロープのHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	// ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, ROPE_SIZE, ROPE_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//ブロックとあたっていれば削除する
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		m_delete = true;  //ロープの削除フラグをオンにする
		return;
	}

	//ロープスイッチと衝突したとき、ロープが引っかかるようにする
	if(hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		//ロープスイッチと接触すると、ロープが引っかかる(動きが止まる)
		m_px -= m_vx ;
		m_py -= m_vy ;
		m_caught_flag = true;		//ロープ引っかかりフラグをONにする
	
		//今主人公が持っているm_vxを0にする。それだけではまだ動くので下の処理をする
		objhero->SetVecX(0.0f);
	}
	//ロープが消していいかどうかを調べる
	bool rope_delete_ani_con = objhero->GetRopeDeleteAniCon();

	//ロープ引っかかり判定がONの時、Rが押されたらロープを削除
	if (Input::GetMouButtonR() == true && m_caught_flag==true && rope_delete_ani_con ==true)
	{
		m_delete = true;			//ロープは消えていることを変数に入れる
		m_caught_flag = false;		//ロープ引っかかりフラグをOFFにする
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		return;
	}

	//引っ掛けたまま移動すると、ロープがズレて外れます。
	//ロープを引っ掛けているときは主人公は動かない(移動できない)仕様が実装で改善予定

	//移動
	m_px += m_vx ;
	m_py += m_vy ;

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjRope::Draw()
{
	float color[4] = {1.0f,0.6f,0.0f,1.0f};

	//主人公オブジェクト情報を取得
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//マップオブジェクト情報を取得
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公が向いている向きを持ってくる
	float hero_postrue = objhero->GetPosture();

	//主人公が存在していたら主人公とロープを結ぶ線を描画(仮)
	if (objhero != nullptr)
	{
		int thick = 2;	//太、厚さ
		
		//ロープの位置
		int own_x = m_px;
		int own_y = m_py;
		
		int nextX;	//点を描画するX位置

		//主人公が右を向いていたら
		if (hero_postrue == 0.0f)
			nextX = objhero->GetPosX() + 60.0f - objmap->GetScrollX();

		//左を向いていたら
		else			
			nextX = objhero->GetPosX() + 5.0f - objmap->GetScrollX();
		
		//点を描画するY位置
		int nextY = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
		
		//ロープから主人公の位置を引いた値(位置の差分)
		int deltaX = own_x - nextX;
		int deltaY = own_y - nextY;
		
		int stepX, stepY;	//どの方向に線を描画するか
		int step = 0;	//ステップ
		int fraction;	//線を引く方向（y成分/x成分)　または（y成分/x成分)
				
		if (deltaX < 0)	//Xの変量がマイナスなら	
			stepX = -1;	//X方向を-1にする
		
		else			//Xの変量がプラスなら	
			stepX = 1;	//X方向を＋1にする
		
		if (deltaY < 0)	//Yの変量がマイナスなら		
			stepY = -1;	//Y方向を-1にする
		
		else			//Yの変量がプラスなら	
			stepY = 1;	//Y方向を+1にする


		//位置の差分を*2する
		deltaX = deltaX * 2;
		deltaY = deltaY * 2;
		
		if (deltaX < 0)
			deltaX *= -1;	//符号を＋にする

		if (deltaY < 0)
			deltaY *= -1;	//符号を＋にする
		

		//主人公の位置に点を打つ
		Draw::DrawHitBox(nextX, nextY, thick, thick, color);
		
		step++;//ステップを進める
		
		//位置の差分の絶対値がXのほうが大きかったら
		if ( abs(deltaX) > abs(deltaY) )
		{
			//Yの変量 - Xの変量/2
			fraction = (deltaY - deltaX) / 2;

			//点を打とうとしているX位置がロープのX位置になるまで点を描く
			while (nextX != own_x)
			{
				//分数が＋値
				if (fraction >= 0)
				{
					//点を描画するY位置を進める
					nextY += stepY;
					//Xの変量を分数に引き算する
					fraction -= deltaX;
				}

				//点を描画するX位置を進める
				nextX += stepX;
				
				fraction += deltaY;	//Yの変量を分数に加算する
								
				//点を描画
				Draw::DrawHitBox(nextX, nextY, thick, thick, color);
				
				step++;	//ステップを進める
				
			}
		}
		//変量がYのほうが大きかったら
		else
		{
			//Xの変量ーYの変量/2
			fraction = deltaX - deltaY / 2;
			//点を打とうとしているY位置がロープのY位置になるまで点を描く
			while (nextY != own_y)
			{
				//分数が＋値
				if (fraction >= 0)
				{
					//点を描画するX位置を進める
					nextX += stepX;
					//Yの変量を分数に引き算する
					fraction -= deltaY;
				}
				//点を描画するY位置を進める
				nextY += stepY;
				//Xの変量を分数に加算する
				fraction += deltaX;
				//点を描画
				Draw::DrawHitBox(nextX, nextY, thick, thick, color);
				//ステップを進める
				step++;
			}
		}
	}
}