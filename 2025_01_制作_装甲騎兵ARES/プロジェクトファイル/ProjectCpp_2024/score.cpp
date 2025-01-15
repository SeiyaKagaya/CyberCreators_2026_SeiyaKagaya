//=======================================================
//
// score�Ɋւ��鏈��[score.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "score.h"
#include "font.h"
#include "enemy_motion_base.h"



int CScore::m_score = 0;

//=============================
//�R���X�g
//=============================
CScore::CScore(int nPriority) :CObject(nPriority)
{
	SetObjectType(CObject::OBJECT_SCORE);
}
//=============================
//�f�X�g
//=============================
CScore::~CScore()
{
}
//=============================
//������
//=============================
HRESULT CScore::Init()
{

	m_Data[0].Pos = D3DXVECTOR3(SCREEN_WIDTH - 230.0f, 10.0f, 0.0f);
	m_Data[1].Pos = D3DXVECTOR3(SCREEN_WIDTH/2.0f - 80.0f, 670.0f, 0.0f);

	snprintf(m_cData, sizeof(m_cData), ""); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[



	return S_OK;
}
//=============================
//�I��
//=============================
void CScore::Uninit()
{
}
//=============================
//�X�V
//=============================
void CScore::Update()
{
	//snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

//	snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
}
//=============================
//�`��
//=============================
void CScore::Draw()
{
	snprintf(m_cData, sizeof(m_cData), "SCORE:%d", m_score); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

	CFont::DrawTextSet(m_Data[0].Pos, 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), m_cData);

//	int TestEnemy=CObjectMotionEnemyBase::GetEnemyAllNum();

	//snprintf(m_cData, sizeof(m_cData), "�c��G�@:%d", TestEnemy); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
//	CFont::DrawTextSet(m_Data[1].Pos, 50, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), m_cData);
}
//=============================
//score�ǉ�
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
//����
//=============================
CScore* CScore::Create()
{
	CScore* pScore = new CScore;
	pScore->Init();


	return pScore;
}
//=============================
//�X�R�A�擾
//=============================
int CScore::GetScore()
{
	return m_score;
}
