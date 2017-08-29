#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEndlessSpring.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEndlessSpring::CObjEndlessSpring()
{

}

//イニシャライズ
void CObjEndlessSpring::Init()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_timelag = 180.0f;//敵生成間隔(180フレーム)
	

}

//アクション
void CObjEndlessSpring::Action()
{
	//敵生成処理(仮)
	m_timelag +=TIME ;

	if (m_timelag>=180.0f)
	{
		m_timelag = 0;

	}

	

}

//ドロー
void CObjEndlessSpring::Draw()
{

}