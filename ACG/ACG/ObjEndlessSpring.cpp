#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEndlessSpring.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjEndlessSpring::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_timelag = 180.0f;//敵生成間隔(180フレーム)
}

//アクション
void CObjEndlessSpring::Action()
{
	//敵生成処理(仮)
	m_timelag +=TIME;

	if (m_timelag>=180.0f)
	{
		m_timelag = 0.0f;
	}
}

//ドロー
void CObjEndlessSpring::Draw()
{

}