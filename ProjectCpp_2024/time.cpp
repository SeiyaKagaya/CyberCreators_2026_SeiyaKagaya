//=======================================================
//
// time�Ɋւ��鏈��[tine.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "time.h"
#include "font.h"



int CTime::m_LimitTime = 0;//��������
int CTime::m_flame = 0;//�t���[��

//=============================
//�R���X�g
//=============================
CTime::CTime(int nPriority) :CObject(nPriority)
{
	SetObjectType(CObject::OBJECT_TIME);
}
//=============================
//�f�X�g���N�^
//=============================
CTime::~CTime()
{
}
//=============================
//������
//=============================
HRESULT CTime::Init()
{
	m_LimitTime = 120;
	m_Data.Pos = D3DXVECTOR3(SCREEN_WIDTH-470.0f, 10.0f, 0.0f);

	snprintf(m_cData, sizeof(m_cData), ""); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[


	return S_OK;
}
//=============================
//�I��
//=============================
void CTime::Uninit()
{

}
//=============================
//�X�V
//=============================
void CTime::Update()
{
	AddTime();

	snprintf(m_cData, sizeof(m_cData), "��������%d", m_LimitTime); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

}
//=============================
//�`��
//=============================
void CTime::Draw()
{
	CFont::DrawTextSet(m_Data.Pos, 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), m_cData);
}
//=============================
//score�ǉ�
//=============================
void CTime::AddTime()
{
	m_flame++;//�C���N�������g

	if (m_flame % 60 == 0)
	{

		m_LimitTime--;//�\�����鐔�l�����炷
	}
}
//=============================
//����
//=============================
CTime* CTime::Create()
{
	CTime* pTime = new CTime;
	pTime->Init();


	return pTime;
}
//=============================
//���Ԏ擾
//=============================
int CTime::GetTime()
{
	return m_LimitTime;
}
