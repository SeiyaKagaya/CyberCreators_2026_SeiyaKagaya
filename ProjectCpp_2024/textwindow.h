#ifndef _TEXTWINDOW_H_
#define _TEXTWINDOW_H_

#include "main.h"
#include "object.h"
#include "font.h" // �e�L�X�g�`��p
#include <cstring> // strlen�֐����g�p���邽�߂ɕK�v

class CTextWindow : public CObject
{
public:
    CTextWindow(int nPriority = CObject::LAYERINDEX_TEXTWINDOW);
    ~CTextWindow() override;

    HRESULT Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;
    static CTextWindow* Create();

    void SetText(D3DXVECTOR3 pos, int DrawStartDelay,int DelayFrame,  const char* text,D3DCOLOR col,int nlife); // �\������e�L�X�g��ݒ�
 //   bool IsComplete() const;       // �Z���t���肪����������
    bool GetCloseWindowNow() { return m_CloseWindowNow; };

private:
    const char* m_pText;      // �\������S�̂̃e�L�X�g
    char m_DisplayText[256];  // ���ݕ\�����̃e�L�X�g
    int m_CurrentIndex;       // ���ݕ\�����̈ʒu
    int m_FrameCount;         // �t���[���J�E���g
    int m_FrameDelay;         // 1�����\�����Ƃ̃t���[���x��
    D3DXVECTOR3 m_DrawPos;    // �`��ʒu
    D3DCOLOR m_col;           //�F
    int m_nlife;              //�`��ド�C�t
    bool m_DrawNow = false;     //�`����
    int m_nlife_ColseWimdow;              //�`��ド�C�t(�E�B���h�E����t���[��)
    bool m_CloseWindowNow = false;     //�`����
    int m_DrawStartDelay = 0;
    bool m_DelayStart = false;
};

#endif // _TEXTWINDOW_H_
