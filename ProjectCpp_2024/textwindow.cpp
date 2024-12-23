#include "textwindow.h"
#include "font.h"
#include <chrono>
#include <thread>

////���₵��cpp�̂���Ƃ��ɂ�����
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//=============================
// �R���X�g���N�^
//=============================
CTextWindow::CTextWindow(int nPriority) : CObject(nPriority), m_pText(nullptr), m_CurrentIndex(0), m_FrameCount(0), m_FrameDelay(10)
{
    SetObjectType(CObject::OBJECT_TEXTWINDOW);
    std::memset(m_DisplayText, 0, sizeof(m_DisplayText));
}

//=============================
// �f�X�g���N�^
//=============================
CTextWindow::~CTextWindow() 
{
}

//=============================
// ������
//=============================
HRESULT CTextWindow::Init() 
{
    return S_OK;
}

//=============================
// �I������
//=============================
void CTextWindow::Uninit() 
{
}

//=============================
// �X�V����
//=============================
void CTextWindow::Update() 
{
    m_DrawStartDelay--;
    if (m_DrawStartDelay <= 0)
    {
        m_DrawStartDelay = 0;
        m_DelayStart = false;
    }

    if (m_DelayStart == false)
    {
        if (m_CloseWindowNow == false)
        {
            if (m_pText && m_pText[m_CurrentIndex] != '\0')
            {
                // ���t���[�����ƂɎ��̕�����ǉ�
                if (m_FrameCount >= m_FrameDelay)
                {
                    m_DisplayText[m_CurrentIndex] = m_pText[m_CurrentIndex];
                    m_CurrentIndex++;
                    m_FrameCount = 0; // �t���[���J�E���g�����Z�b�g
                }
                m_FrameCount++;
            }
            else
            {
                m_nlife--;

                if (m_nlife <= 0)
                {

                    m_pText = "";
                    snprintf(m_DisplayText, sizeof(m_DisplayText), "");

                    m_CloseWindowNow = true;
                }

            }
        }
        else
        {
         //   m_CloseWindowNow = true;

            m_nlife_ColseWimdow--;
            if (m_nlife_ColseWimdow <= 0)
            {
                m_DrawNow = false;

                m_CloseWindowNow = false;
            }
        }
    }
}

//=============================
// �`�揈��
//=============================
void CTextWindow::Draw() 
{
    if (m_DisplayText[0] != '\0') 
    {
   //     snprintf(m_pText, sizeof(m_pText), "SCORE:%d", m_score); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

        CFont::DrawTextSet(m_DrawPos, m_TextSize, CFont::FONT_DIGITAL, m_col, m_DisplayText);


        // �`�揈�� (�t�H���g�`��N���X���g�p)
 //       DrawFont(m_DisplayText, 100, 100, D3DCOLOR_XRGB(255, 255, 255)); // ��: ����(100, 100)�ɕ\��
    }
}

//=============================
// ��������
//=============================
CTextWindow* CTextWindow::Create() 
{
	CTextWindow* pScore = new CTextWindow;
	pScore->Init();

	return pScore;
}

//=============================
// �e�L�X�g�ݒ�
//=============================
void CTextWindow::SetText(D3DXVECTOR3 pos, int TextSize, int DrawStartDelay, int DelayFrame, const char* text,D3DCOLOR col, int nlife)
{
    m_CloseWindowNow = false;
    m_DrawStartDelay = DrawStartDelay;
    m_DrawPos = pos;
    m_pText = text;
    m_FrameCount = 0;
    m_CurrentIndex = 0;
    m_FrameDelay = DelayFrame;
    m_col = col;
    std::memset(m_DisplayText, 0, sizeof(m_DisplayText)); // �\���e�L�X�g��������
    m_nlife = nlife;
    m_DrawNow = true;
    m_nlife_ColseWimdow = 30;
    m_DelayStart = true;
    m_TextSize = TextSize;
}

////=============================
//// �Z���t���芮������
////=============================
//bool CTextWindow::IsComplete() const 
//{
//    return m_pText && m_pText[m_CurrentIndex] == '\0';
//}
