//=======================================================
//
// timeに関する処理[tine.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "time.h"
#include "font.h"



int CTime::m_LimitTime = 0;//制限時間
int CTime::m_flame = 0;//フレーム

//=============================
//コンスト
//=============================
CTime::CTime(int nPriority) :CObject(nPriority)
{
	SetObjectType(CObject::OBJECT_TIME);
}
//=============================
//デストラクタ
//=============================
CTime::~CTime()
{
}
//=============================
//初期化
//=============================
HRESULT CTime::Init()
{
	m_LimitTime = 120;
	m_Data.Pos = D3DXVECTOR3(SCREEN_WIDTH-470.0f, 10.0f, 0.0f);

	snprintf(m_cData, sizeof(m_cData), ""); // 数値を文字列に変換してCDataにコピー


	return S_OK;
}
//=============================
//終了
//=============================
void CTime::Uninit()
{

}
//=============================
//更新
//=============================
void CTime::Update()
{
	AddTime();

	snprintf(m_cData, sizeof(m_cData), "制限時間%d", m_LimitTime); // 数値を文字列に変換してCDataにコピー

}
//=============================
//描画
//=============================
void CTime::Draw()
{
	CFont::DrawTextSet(m_Data.Pos, 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), m_cData);
}
//=============================
//score追加
//=============================
void CTime::AddTime()
{
	m_flame++;//インクリメント

	if (m_flame % 60 == 0)
	{

		m_LimitTime--;//表示する数値を減らす
	}
}
//=============================
//生成
//=============================
CTime* CTime::Create()
{
	CTime* pTime = new CTime;
	pTime->Init();


	return pTime;
}
//=============================
//時間取得
//=============================
int CTime::GetTime()
{
	return m_LimitTime;
}
