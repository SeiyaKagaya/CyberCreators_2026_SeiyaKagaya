#ifndef _TEXTWINDOW_H_
#define _TEXTWINDOW_H_

#include "main.h"
#include "object.h"
#include "font.h" // テキスト描画用
#include <cstring> // strlen関数を使用するために必要

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

    void SetText(D3DXVECTOR3 pos, int DrawStartDelay,int DelayFrame,  const char* text,D3DCOLOR col,int nlife); // 表示するテキストを設定
 //   bool IsComplete() const;       // セリフ送りが完了したか
    bool GetCloseWindowNow() { return m_CloseWindowNow; };

private:
    const char* m_pText;      // 表示する全体のテキスト
    char m_DisplayText[256];  // 現在表示中のテキスト
    int m_CurrentIndex;       // 現在表示中の位置
    int m_FrameCount;         // フレームカウント
    int m_FrameDelay;         // 1文字表示ごとのフレーム遅延
    D3DXVECTOR3 m_DrawPos;    // 描画位置
    D3DCOLOR m_col;           //色
    int m_nlife;              //描画後ライフ
    bool m_DrawNow = false;     //描画状態
    int m_nlife_ColseWimdow;              //描画後ライフ(ウィンドウ閉じろフレーム)
    bool m_CloseWindowNow = false;     //描画状態
    int m_DrawStartDelay = 0;
    bool m_DelayStart = false;
};

#endif // _TEXTWINDOW_H_
