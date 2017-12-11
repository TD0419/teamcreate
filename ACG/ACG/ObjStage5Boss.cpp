#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;
//コンストラクタ
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //第5ボスのＨＰ(仮にＨＰを[100]と設定)

	//初期化する(何もしていない)
	m_attack_mode = 0;

	//音楽
	//Audio::Start(BOSS);
	//Audio::Stop(STAGE);

	//右腕オブジェクト作成
	m_boos_arm_right = new CObjStage5BossArms(m_px - 370.0f, m_py - 166.0f, 1);
	Objs::InsertObj(m_boos_arm_right, OBJ_STAGE5_BOSS_ARMS, 10);

	//左腕オブジェクト作成
	m_boos_arm_left = new CObjStage5BossArms(m_px + 126.0f, m_py - 166.0f, 2);
	Objs::InsertObj(m_boos_arm_left, OBJ_STAGE5_BOSS_ARMS, 10);

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//アクション
void CObjStage5Boss::Action()
{
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	switch (m_attack_mode)
	{
		//何もしていない状態
	case 0:
		//何もしていないので攻撃モードをランダムで決める
		m_attack_mode = GetRandom(1, 4);
		break;
		//主人公のいる位置を取って上から地面までに当たると死ぬ攻撃を落とす攻撃
	case 1:

		break;
		//打ち出してからランダムな時間経過で拡散弾(15度ほど)になる弾を出す攻撃
	case 2:

		break;
		//ボス自身が動きながら主人公の位置に弾を撃つ(レーザー)攻撃
	case 3:

		break;
		//3地点に縄を引っ掛けるオブジェクトを出現させ、その後地面が落ちる攻撃をする。
	case 4:

		break;
	default:
		break;
	}
	//当たり判定更新
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	//主人公の弾丸とぶつかったらＨＰを-1にする
	//弾丸とあたったらＨＰを1減らす
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	//(仮)ＨＰが0になったらクリア画面に移動
	//クリア画面移動条件が確定したら、変更してください。
	if (m_hp == 0)
	{
		//クリア画面に移動
		Scene::SetScene(new CSceneGameClear());
		return;
	}

}

//ドロー
void CObjStage5Boss::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//胴腕接続電気-------------------------------
	//左腕部分
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()  + ELECTRIC_L_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() - ELECTRIC_L_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//右腕部分
	//切り取り位置
	src.m_top = STAGE5_BOSS_ELECTRIC_HEIGHT;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//描画位置
	dst.m_top =  m_py - objmap->GetScrollY() + ELECTRIC_R_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + ELECTRIC_R_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//胴体--------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;
	
	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);


	//眼球---------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_EYE_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_EYE_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()  + EYE_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + EYE_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_EYE_SIZE;	
	dst.m_bottom = dst.m_top + STAGE5_BOSS_EYE_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_EYE, &src, &dst, color, 0.0f);
	

}
//ランダムで値を決める関数
//引数1 int min	:最小値
//引数2 int max	:最大値
//戻り値 int	:最小値～最大値の間の数値をランダムで渡す(最大値、最小値を含む)
int CObjStage5Boss::GetRandom(int min, int max)
{
	//一回だけ初期化をする用
	static bool initialization = true;
	if (initialization == true)
	{
		srand((unsigned)time(NULL));  //乱数系列の変更
		initialization = false;
	}
	return min + (int)(rand()*(max - min + 1.0f) / (1.0f + RAND_MAX));
}