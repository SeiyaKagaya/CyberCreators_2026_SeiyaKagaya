//=======================================================
//
// Tutorialに関する処理[Tutorial.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Tutorial.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"

// 静的メンバー変数の定義
//int CTutorialUI::m_SelectNum = 0; // 初期値をMODE_TITLEに設定



//=============================
// コンストラクタ
//=============================
CTutorialUI::CTutorialUI(/*int nPriority*/)/* :CObject(nPriority)*/
{
  
    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
    }


    m_Pos[0] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[1] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[2] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
}
//=============================
// デストラクタ
//=============================
CTutorialUI::~CTutorialUI()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CTutorialUI::Init()
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
            //テクスチャの読み込み
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\yuka.jpg", &m_pTexture[nCnt]);//通常時


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - (float)(SCREEN_WIDTH *0.5f), m_Pos[nCnt].y - (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (float)(SCREEN_HEIGHT * 0.5f), 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 1:
            //テクスチャの読み込み
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial1.png", &m_pTexture[nCnt]);//通常時

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 000.0f, SCREEN_HEIGHT * 0.5f - 90.0f , 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y + 130.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y + 130.0f, 0.0f);

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

        case 2:
            //テクスチャの読み込み
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial2.png", &m_pTexture[nCnt]);//通常時

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 280.0f, SCREEN_HEIGHT * 0.5f +180.0f, 0.0f);
            
            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 300.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 300.0f, m_Pos[nCnt].y + 130.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y + 130.0f, 0.0f);

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
void CTutorialUI::Uninit()
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
void CTutorialUI::Update()
{

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    CInputJoyPad* JoyPad = pManager->GetJoyPad();

    XINPUT_STATE joykeystate;

    //ショイパットの状態を取得
    DWORD dwResult = XInputGetState(0, &joykeystate);


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
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN))
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
            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


                CFade* pFade = {};

                switch (GetSelectNum())
                {
                case 0://タイトルに戻る

                    pFade = pManager->GetFade();
                 //   pFade->SetFade(CScene::MODE_GAME);
                    pFade->SetFade(CScene::MODE_OP);

                    break;

                case 1:

                    pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);

                    break;

                case 2:

                 //   m_bStopNow = false;

                    /*pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);*/


                    break;
                }

            }

        }
        else
        {//キーボード入力反映(移動)
//
//            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
//            {
//                CSound* pSound = pManager->GetSound();
//           
//
//                CFade* pFade;
//
//                switch (GetSelectNum())
//                {
//                case 0://タイトルに戻る
//
//                    pFade = pManager->GetFade();
////                    pFade->SetFade(CScene::MODE_GAME);
//                    pFade->SetFade(CScene::MODE_OP);
//
//                    break;
//
//                case 1://操作方式変更
//
//             
//
//                    break;
//
//                case 2://次に進む
//
//                 //   m_bStopNow = false;
//
//                    pFade = pManager->GetFade();
//                    pFade->SetFade(CScene::MODE_TITLE);
//
//
//                    break;
//                }
//            }
        }
    






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
void CTutorialUI::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        EscDevice->SetStreamSource(0, m_pVtxBuff[nCnt], 0, sizeof(VERTEX_2D));
        EscDevice->SetFVF(FVF_VERTEX_2D);

        if (m_pTexture != nullptr)
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

        EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

        //switch (nCnt)
        //{
        //case 0://背景
        //    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    break;

        //case 1://キーマウ

        //    if (pManager->bGetInputState() == false)
        //    {//操作方法--trueでコントローラー
        //        hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    }
        //    else
        //    {//マウス

        //    }

        //    break;

        //case 2://コントローラー

        //    if (pManager->bGetInputState() == true)
        //    {//操作方法--trueでコントローラー
        //        hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    }

        //    break;
        //}





        EscDevice->SetTexture(0, nullptr);

    }




    const char* aData = "-TUTORIAL-";
   // CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 600.0f, SCREEN_HEIGHT / 2.0f - 340.0f, 0.0f), 80, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);



    aData = "今回の任務は、-新型揚陸艦-の捕縛作戦の陽動である。単独潜入後、制限時間以内に\n地上部隊を撃破しつつ敵基地入口にて待機。揚陸艦の捕縛が完遂したら作戦成功である。\n捕縛自体は海軍のみで行うので簡単な任務になるだろう。";
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 28.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);

    aData = "陽動作戦 図解";
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 150.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);


    aData = "操作方法      Aで選択";
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, SCREEN_HEIGHT - 45.0f, 0.0f), 40, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);


    XINPUT_STATE joykeystate;
    //ショイパットの状態を取得
    DWORD dwResult = XInputGetState(0, &joykeystate);

    switch (m_SelectNum)
    {
    case 0:
        aData = "ゲームに進む";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);



     


        aData = "タイトルに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);


        break;

    case 1:

        aData = "ゲームに進む";

        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);



 

        aData = "タイトルに戻る";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);


        break;

   
    }



}
//=============================
// Object生成
//=============================
CTutorialUI* CTutorialUI::Create()
{
    CTutorialUI* pObject2D = new CTutorialUI;
    pObject2D->Init();
    return pObject2D;
}


void CTutorialUI::AddSelectNum(int addnum)
{
    m_SelectNum += addnum;

    if (m_SelectNum < 0)
    {
        m_SelectNum = 1;
    }
    else if (m_SelectNum > 1)
    {
        m_SelectNum = 0;
    }
}

void CTutorialUI::DirectSetNum(int Num)
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

int CTutorialUI::GetSelectNum()
{
    return m_SelectNum;
}
