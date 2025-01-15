//=======================================================
//
// scoreに関する処理[score.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "score.h"
#include "font.h"
#include "enemy_motion_base.h"



int CScore::m_score = 0;

//=============================
//コンスト
//=============================
CScore::CScore(int nPriority) :CObject(nPriority)
{
	SetObjectType(CObject::OBJECT_SCORE);
}
//=============================
//デスト
//=============================
CScore::~CScore()
{
}
//=============================
//初期化
//=============================
HRESULT CScore::Init()
{

	m_Data[0].Pos = D3DXVECTOR3(SCREEN_WIDTH - 230.0f, 10.0f, 0.0f);
	m_Data[1].Pos = D3DXVECTOR3(SCREEN_WIDTH/2.0f - 80.0f, 670.0f, 0.0f);

	snprintf(m_cData, sizeof(m_cData), ""); // 数値を文字列に変換してCDataにコピー



	return S_OK;
}
//=============================
//終了
//=============================
void CScore::Uninit()
{
}
//=============================
//更新
//=============================
void CScore::Update()
{
	//snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // 数値を文字列に変換してCDataにコピー

//	snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // 数値を文字列に変換してCDataにコピー
}
//=============================
//描画
//=============================
void CScore::Draw()
{
	snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // 数値を文字列に変換してCDataにコピー

	CFont::DrawTextSet(m_Data[0].Pos, 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), m_cData);

//	int TestEnemy=CObjectMotionEnemyBase::GetEnemyAllNum();

	//snprintf(m_cData, sizeof(m_cData), "残り敵機:%d", TestEnemy); // 数値を文字列に変換してCDataにコピー
//	CFont::DrawTextSet(m_Data[1].Pos, 50, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), m_cData);
}
//=============================
//score追加
//=============================
void CScore::AddScore(int AddCScore)
{
	m_score += AddCScore;
}
void CScore::ResetScore()
{
	m_score = 0;
}
//=============================
//生成
//=============================
CScore* CScore::Create()
{
	CScore* pScore = new CScore;
	pScore->Init();


	return pScore;
}
//=============================
//スコア取得
//=============================
int CScore::GetScore()
{
	return m_score;
}
