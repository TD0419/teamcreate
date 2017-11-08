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
//引数1	float x		:初期位置X
//引数2	float y		:初期位置Y
CObjRope::CObjRope(int x, int y)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公オブジェクト情報を取得
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公が本来いる位置に変更
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();

	//初期位置を決める
	m_px = x;
	m_py = y;
	
	//速さを決める
	m_speed = 6.5f;
	
	//マウスの位置情報をheroから持ってくるのでマージする時はこっちを残してください（変数もこっちに変えてください）
	m_moux = objhero->GetRopeMouX(); //Rを押した時のマウスの位置Xを持ってくる
	m_mouy = objhero->GetRopeMouY(); //Rを押した時のマウスの位置Yを持ってくる

	//主人公の位置からマウスの位置のベクトル情報取得
	double vector_x = m_moux - x;
	double vector_y = m_mouy - y;

	//斜辺取得
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//角度を求める
	m_r = acos(vector_x / hypotenuse);
	//角度方向に移動
	m_vx = cos(m_r) * m_speed;
	m_r = m_r * 180.0 / 3.14;

	//マウスのY位置が主人公のY位置より下だったら
	if (m_mouy > y)
	{
		//180°～360°の値にする
		m_r = 360 - abs(m_r);
	}
	//マウスのY位置が初期Y位置より上
	if (m_mouy < y)
	{
		m_vy = -sin(acos(vector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(vector_x / hypotenuse)) * m_speed;
	}
}

//イニシャライズ
void CObjRope::Init()
{
	m_moux = 0.0f;
	m_mouy = 0.0f;
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

	//画面外へいったら消去
	if (m_px < -(BULLET_SIZE + BULLET_SIZE / 2) || //左　回転してるかもなので少し余裕を持たせる
		m_px > WINDOW_SIZE_W ||   //右
		m_py < -(BULLET_SIZE + BULLET_SIZE / 2) || //上　回転してるかもなので少し余裕を持たせる
		m_py > WINDOW_SIZE_H     //下
		)
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
	HitBoxUpData(hit, m_px+objmap->GetScrollX(), m_py+objmap->GetScrollY());
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

	//主人公が存在していたら主人公と自身を結ぶ線を描画(仮)
	if (objhero != nullptr)
	{
		//太、厚さ
		int thick = 2;
		//自身の位置
		int own_x = m_px;
		int own_y = m_py;
		//点を描画するX位置
		int nextX;
		//主人公が右を向いていたら
		if(hero_postrue == 0.0f)
			nextX = objhero->GetPosX() + 60.0f - objmap->GetScrollX();
		else//左を向いていたら
			nextX = objhero->GetPosX() + 5.0f - objmap->GetScrollX();
		//点を描画するY位置
		int nextY = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
		//自身から主人公の位置を引いた値X(変量)
		int deltaX = own_x - nextX;
		//自身から主人公の位置を引いた値Y(変量)
		int deltaY = own_y - nextY;
		//どの方向に線を描画するか
		int stepX, stepY;
		//ステップ
		int step = 0;
		//分数
		int fraction;

		//Xの変量がマイナスなら
		if (deltaX < 0)
		{
			//X方向を-1にする
			stepX = -1;
		}
		//Xの変量がプラスなら
		else
		{
			//X方向を＋1にする
			stepX = 1;
		}
		//Yの変量がマイナスなら
		if (deltaY < 0)
		{
			//Y方向を-1にする
			stepY = -1;
		}
		//Yの変量がプラスなら
		else
		{
			//Y方向を+1にする
			stepY = 1;
		}
		//Xの変量を*2する
		deltaX = deltaX * 2;
		//符号を＋にする
		if (deltaX < 0)
			deltaX *= -1;
		//Yの変量を*2する
		deltaY = deltaY * 2;
		//符号を＋にする
		if (deltaY < 0)
			deltaY *= -1;
		//主人公の位置に点を打つ
		Draw::DrawHitBox(nextX, nextY, thick, thick, color);
		//ステップを進める
		step++;

		//変量がXのほうが大きかったら
		if (deltaX > deltaY)
		{
			//Yの変量ーXの変量/2
			fraction = deltaY - deltaX / 2;
			//点を打とうとしているX位置が自身のX位置になるまで点を描く
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
				//Yの変量を分数に加算する
				fraction += deltaY;
				//点を描画
				Draw::DrawHitBox(nextX, nextY, thick, thick, color);
				//ステップを進める
				step++;
			}
		}
		//変量がYのほうが大きかったら｜｜同じ
		else
		{
			//Xの変量ーYの変量/2
			fraction = deltaX - deltaY / 2;
			//点を打とうとしているY位置が自身のY位置になるまで点を描く
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