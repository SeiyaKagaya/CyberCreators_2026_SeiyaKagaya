//=======================================================
//
// Game_UIに関する処理[Game_UI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "LongPush.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"
#include "player_motion.h"



////あやしいcppのせんとうにこいつを
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//=============================
// コンストラクタ
//=============================
CLongPush::CLongPush(int nPriority) :CObject(nPriority)
{
    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;

        m_Pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_Size[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_fLength[nCnt] = 0.0f;
    }

    m_Pos[0] = D3DXVECTOR3(0.0f,0.0f, 0.0f);
    m_Pos[1] = D3DXVECTOR3(0.0f,0.0f, 0.0f);

    SetObjectType(OBJECT_LONGPUSH);
}
//=============================
// デストラクタ
//=============================
CLongPush::~CLongPush()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CLongPush::Init()
{
    // マウスカーソルを表示にする
 //   ShowCursor(TRUE);

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
    {
        if (FAILED(EscDevice->CreateVertexBuffer(
            sizeof(VERTEX_2D) * 4,
            D3DUSAGE_WRITEONLY,
            FVF_VERTEX_2D,
            D3DPOOL_MANAGED,
            &m_pVtxBuff[nCnt],
            nullptr)))
        {
            return E_FAIL;
        }
        // 初期設定
        VERTEX_2D* pVtx;

        m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

        pVtx[0].rhw = 1.0f;
        pVtx[1].rhw = 1.0f;
        pVtx[2].rhw = 1.0f;
        pVtx[3].rhw = 1.0f;

        pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
        pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
        pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
        pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
        pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
        pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

        m_fLength[nCnt] = 300;

        switch (nCnt)
        {
        case UI_BOOST_BACK:
            //マップ背景
            m_UiType[UI_BOOST_BACK] = UI_BOOST_BACK;

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 40.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt] + 5.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y + 13.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt] + 5.0f, m_Pos[nCnt].y + 13.0f, 0.0f);

            break;

        case UI_BOOST_MAIN:

            //操作UI
            m_UiType[UI_BOOST_MAIN] = UI_BOOST_MAIN;

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.75f + 2.5f, SCREEN_HEIGHT - 40.0f, 0.0f);

         

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y - 10.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 10.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y + 10.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 10.0f, 0.0f);

            break;
        }


        m_pVtxBuff[nCnt]->Unlock();

    }
    

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CLongPush::Uninit()
{
    // マウスカーソルを非表示にする
//    ShowCursor(FALSE);

    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
    {
        if (m_pVtxBuff[nCnt] != nullptr)
        {
            m_pVtxBuff[nCnt]->Release();
            m_pVtxBuff[nCnt] = nullptr;
        }
    }
}
//=============================
// 更新(頂点情報の更新)
//=============================
void CLongPush::Update()
{
    if (m_nCnt >= MAX_PUSHCNT)
    {
        m_bPushOk = true;
    }

    else
    {
        m_bPushOk = false;
    }

    for (int i = 0; i < UI_MAX; i++)
    {
        InputpVtx(i);//マップ描画Systemのみ
    } 
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CLongPush::Draw()
{
    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState != CScene::MODE_TITLE && NowState != CScene::MODE_RESULT)
    {//タイトル

        CRenderer* pRenderer = nullptr;

        CManager* pManager = CManager::GetInstance();

        pRenderer = pManager->GetRenderer();

        LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

        for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
        {
            EscDevice->SetStreamSource(0, m_pVtxBuff[nCnt], 0, sizeof(VERTEX_2D));
            EscDevice->SetFVF(FVF_VERTEX_2D);

            EscDevice->SetTexture(0, nullptr);

            HRESULT hr = {};

            XINPUT_STATE joykeystate;
            //ショイパットの状態を取得
            DWORD dwResult = XInputGetState(0, &joykeystate);

            hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        }
    
        const char* aData = "A長押しでスキップ";
        
        if (m_nCnt <= 0)
        {
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.75f + 2.5f, SCREEN_HEIGHT - 80.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.2f), aData);

        }
        else
        {
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.75f + 2.5f, SCREEN_HEIGHT - 80.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), aData);

        }
    }

}
//=============================
// Object生成
//=============================
CLongPush* CLongPush::Create()
{
    CLongPush* pObject = new CLongPush;
    pObject->Init();

    return pObject;
}
//=============================
// 頂点情報
//=============================
void CLongPush::InputpVtx(int nCnt)
{
    int nEscRGBA[4] = { 0,0,0,0 };
    float EscLength = 0.0f;//ゲージのみ使用

    // 初期設定
    VERTEX_2D* pVtx;

 //   m_nCnt++;

    m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

    if (nCnt == UI_BOOST_BACK)
    {
        if (m_nCnt <= 0)
        {
            nEscRGBA[0] = 255;
            nEscRGBA[1] = 255;
            nEscRGBA[2] = 255;
            nEscRGBA[3] = 45;
        }
        else
        {
            nEscRGBA[0] = 255;
            nEscRGBA[1] = 255;
            nEscRGBA[2] = 255;
            nEscRGBA[3] = 255;
        }

    }
    else  if (nCnt == UI_BOOST_MAIN)
    {
        if (m_nCnt <= 0)
        {
            nEscRGBA[0] = 255;
            nEscRGBA[1] = 0;
            nEscRGBA[2] = 0;
            nEscRGBA[3] = 45;
        }
        else
        {
            nEscRGBA[0] = 255;
            nEscRGBA[1] = 0;
            nEscRGBA[2] = 0;
            nEscRGBA[3] = 255;
        }

        EscLength = (m_fLength[nCnt] * m_nCnt / MAX_PUSHCNT);


        //   pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
        pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength);
        //  pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
        pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength);
    }

    pVtx[0].col = D3DCOLOR_RGBA(nEscRGBA[0], nEscRGBA[1], nEscRGBA[2], nEscRGBA[3]);
    pVtx[1].col = D3DCOLOR_RGBA(nEscRGBA[0], nEscRGBA[1], nEscRGBA[2], nEscRGBA[3]);
    pVtx[2].col = D3DCOLOR_RGBA(nEscRGBA[0], nEscRGBA[1], nEscRGBA[2], nEscRGBA[3]);
    pVtx[3].col = D3DCOLOR_RGBA(nEscRGBA[0], nEscRGBA[1], nEscRGBA[2], nEscRGBA[3]);

    m_pVtxBuff[nCnt]->Unlock();
}
//=============================
// 加算処理
//=============================
void CLongPush::AddCnt()
{
    m_nCnt++;

    if (m_nCnt > MAX_PUSHCNT)
    {
        m_nCnt = MAX_PUSHCNT;
    }
}
//=============================
// 減算処理
//=============================
void CLongPush::SubCnt()
{
    m_nCnt--;

    if (m_nCnt < 0)
    {
        m_nCnt = 0;
    }
}

