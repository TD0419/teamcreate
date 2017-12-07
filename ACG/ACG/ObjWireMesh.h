#pragma once
//使用するヘッダー

//使用するネームスペース
using namespace GameL;

//オブジェクト：金網
class CObjWireMesh :public CObj
{
public:
	CObjWireMesh(int x, int y);	// コンストラクタ
	~CObjWireMesh() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー

private:
	float m_px;		//位置X
	float m_py;		//位置Y
	//マップの要素数
	int m_map_x;
	int m_map_y;
};
