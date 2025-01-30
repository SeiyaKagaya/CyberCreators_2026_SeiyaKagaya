//=======================================================
//
// pauseに関する処理[pause.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "pause.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"

// 静的メンバー変数の定義
//int CPause::m_SelectNum = 0; // 初期値をMODE_TITLEに設定



//=============================
// コンストラクタ
//=============================
CPause::CPause(/*int nPriority*/)/* :CObject(nPriority)*/
{
    m_SelectNum = 0;

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
        m_Pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }

  
}
//=============================
// デストラクタ
//=============================
CPause::~CPause()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CPause::Init()
{
  



    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
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


        switch (nCnt)
        {
        case 0:
            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y - 340.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y - 340.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y + 340.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y + 340.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[1].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[2].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[3].col = D3DCOLOR_RGBA(25, 25, 25, 225);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 1:
            //テクスチャの読み込み
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial2.png", &m_pTexture[nCnt]);//通常時

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 200.0f, SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

    
        case 2:

            //テクスチャの読み込み
              D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\pngwing.png", &m_pTexture[nCnt]);//通常時


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f-50.0f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 25.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 25.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 25.0f, m_Pos[nCnt].y + 25.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 25.0f, m_Pos[nCnt].y + 25.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;
    
        
        case 3:

            //テクスチャの読み込み
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\A.png", &m_pTexture[nCnt]);//通常時


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5 + 250.0f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 22.0f, m_Pos[nCnt].y - 22.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 22.0f, m_Pos[nCnt].y - 22.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 22.0f, m_Pos[nCnt].y + 22.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 22.0f, m_Pos[nCnt].y + 22.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;
        }
        


       

    }
    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CPause::Uninit()
{
    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        if (m_pVtxBuff[nCnt] != nullptr)
        {
            m_pVtxBuff[nCnt]->Release();
            m_pVtxBuff[nCnt] = nullptr;
        }
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();//-----テクスチャcppでやること
            m_pTexture[nCnt] = nullptr;
        }
    }
}
//=============================
// 更新(頂点情報の更新)
//=============================
void CPause::Update()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    CInputJoyPad* JoyPad = pManager->GetJoyPad();

    XINPUT_STATE joykeystate;

    //ショイパットの状態を取得
    DWORD dwResult = XInputGetState(0, &joykeystate);






    // マウスカーソルを表示にする
    int nDrawCnt = ShowCursor(TRUE);

    while (true)
    {
        if (nDrawCnt > 0)
        {//表示状態のとき
            if (nDrawCnt > 1)
            {//2超える
                nDrawCnt = ShowCursor(FALSE);
            }

            break;
        }
        else
        {//非表示状態のとき
            nDrawCnt = ShowCursor(TRUE);
        }
    }





     if (dwResult == ERROR_SUCCESS)
      {//キーボード/コントローラー入力反映(移動)

         //   if (m_bSetStick==false)
          //  {
            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_UP))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

                AddSelectNum(-1);
                //        m_bSetStick = true;
            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN) )
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);


                AddSelectNum(+1);
                //        m_bSetStick = true;
            }
            // }
        }
        //else
        //{//キーボード入力反映(移動)

        //    if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_UP))
        //    {
        //        AddSelectNum(-1);
        //    }
        //    else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN))
        //    {
        //        AddSelectNum(+1);
        //    }


        //}

        // ここで、マウスの位置を取得して表示する処理を行う
        POINT mousePos = keyboard->GetMousePosition();

        D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置
     //   POINT point= keyboard->GetMousePosition();

        POS.x = (float)mousePos.x;
        POS.y = (float)mousePos.y;


        float MinX[3];
        MinX[0] = 115.0f;
        MinX[1] = 115.0f;
        MinX[2] = 115.0f;

        float MaxX[3];
        MaxX[0] = 385.0f;
        MaxX[1] = 385.0f;
        MaxX[2] = 425.0f;

        float MinY[3];
        MinY[0] = 260.0f;
        MinY[1] = 400.0f;
        MinY[2] = 560.0f;

        float MaxY[3];
        MaxY[0] = 300.0f;
        MaxY[1] = 475.0f;
        MaxY[2] = 640.0f;

        bool bHit = false;

        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            if ((POS.y) >= MinY[nCnt] &&
                (POS.y) <= MaxY[nCnt])
            {//上下
                if ((POS.x) >= MinX[nCnt] &&
                    (POS.x) <= MaxX[nCnt])
                {//左右
                    bHit = true;
                }
            }

            if ((POS.x) >= MinX[nCnt] &&
                (POS.x) <= MaxX[nCnt])
            {//左右
                if ((POS.y) >= MinY[nCnt] &&
                    (POS.y) <= MaxY[nCnt])
                {//上下
                    bHit = true;
                }
            }

            if (bHit == true)
            {
                DirectSetNum(nCnt);
                break;
            }
        }


        //-----------------------------------------------------


















        //-------------------------------------------------------------------

        if (dwResult == ERROR_SUCCESS)
        {//キーボード/コントローラー入力反映(移動)

         //   if (m_bSetStick==false)
          //  {
            JoyPad = pManager->GetJoyPad();

            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left)|| keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                StopCnt++;

                switch (GetSelectNum())
                {
                case 0://ゲームに戻る

                    pManager->SetPauseState(false);


                    break;

                case 1://タイトルに戻る

                    pManager->SetPauseState(false);

                    m_SelectNum = 0; //値リセット

                    CFade* pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);
                    break;
                }

            }

        }
        else
        {//キーボード入力反映(移動)

            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                StopCnt++;

                switch (GetSelectNum())
                {
                case 0://ゲームに戻る

                    pManager->SetPauseState(false);

                    break;

                case 1://タイトルに戻る

                    pManager->SetPauseState(false);

                    m_SelectNum = 0;//値リセット

                    CFade* pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);

                    break;
                }
            }
        }
        
  //      return;

    if (dwResult == ERROR_SUCCESS)
    {//パッド接続あり
    }
    else
    {
        pManager->bSetInputState(false);
    }
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CPause::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        EscDevice->SetStreamSource(0, m_pVtxBuff[nCnt], 0, sizeof(VERTEX_2D));
        EscDevice->SetFVF(FVF_VERTEX_2D);

        if (m_pTexture[nCnt] != nullptr)
        {
            EscDevice->SetTexture(0, m_pTexture[nCnt]);
        }
        else
        {
            EscDevice->SetTexture(0, nullptr);
        }

        HRESULT hr = {};


        XINPUT_STATE joykeystate;
        //ショイパットの状態を取得
        DWORD dwResult = XInputGetState(0, &joykeystate);

        hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        
        EscDevice->SetTexture(0, nullptr);

    }




    const char* aData = "-PAUSE-";                                                                                                                       
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 180.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 103, CFont::FONT_GENKAI, D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f), aData);

    switch (m_SelectNum)
    {
    case 0:
        aData = "ゲームに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f - 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);


        aData = "タイトルに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);

        break;

    case 1:
        aData = "ゲームに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f - 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);

        aData = "タイトルに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);
      
        
        break;

    }
    aData = "+操作方法+";
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 90.0f, SCREEN_HEIGHT / 2.0f - 150.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);


    aData = "選択";
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

    aData = "決定";
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 330.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
}

//=============================
// Object生成
//=============================
CPause* CPause::Create()
{
    CPause* pObject2D = new CPause;
    pObject2D->Init();
    return pObject2D;
}



void CPause::AddSelectNum(int addnum)
{
    m_SelectNum += addnum;

    if (m_SelectNum<0)
    {
        m_SelectNum = 1;
    }
    else if(m_SelectNum > 1)
    {
        m_SelectNum = 0;
    }
}

void CPause::DirectSetNum(int Num)
{
    m_SelectNum = Num;

    if (m_SelectNum < 0)
    {
        m_SelectNum = 1;
    }
    else if (m_SelectNum > 1)
    {
        m_SelectNum = 0;
    }
}

int CPause::GetSelectNum()
{
    return m_SelectNum;
}
