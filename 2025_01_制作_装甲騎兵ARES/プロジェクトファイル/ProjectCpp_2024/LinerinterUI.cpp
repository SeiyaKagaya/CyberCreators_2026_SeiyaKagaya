//=======================================================
//
// linerinterUIに関する処理[linerinterUI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "linerinterUI.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// コンストラクタ
//=============================
CObjectLINEUI::CObjectLINEUI(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_LINEUI);

    ChengeAddDrawMode(true);

    // m_pVtxBuff = nullptr;
    // m_pTexture = nullptr;

}
//=============================
// デストラクタ
//=============================
CObjectLINEUI::~CObjectLINEUI()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObjectLINEUI::Init()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff;//頂点バッファ

    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//四角形のため4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &ESCpVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    BindVtxBuffer(ESCpVtxBuff);

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\bullet000.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定


 //   SetpVtx(pVtx);

  //  InputpVtx();

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObjectLINEUI::Uninit()
{
    CObjectBillBoard::Uninit();
}
//=============================
// 更新(頂点情報の更新)
//=============================
void CObjectLINEUI::Update()
{

    //CRenderer* pRenderer = nullptr;

    //CManager* pManager = CManager::GetInstance();

    //CInputKeyboard* keyboard = pManager->GetKeyboard();

    //CInputJoyPad* JoyPad = pManager->GetJoyPad();

    //XINPUT_STATE joykeystate;

    ////ショイパットの状態を取得
    //DWORD dwResult = XInputGetState(0, &joykeystate);

    ////Mouseで画面に指してる3D空間座標取得
    //D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());




    //// 配置物プライオリティの先頭を取得
    //CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

    //if (pObject != nullptr)
    //{ // 先頭がない==プライオリティまるっとない

    //    if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
    //    { // 対象のモデルのとき

    //        D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //        D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    //        // ここで使用分宣言
    //        CObjectMotionPlayer* pMotionPlayer;

    //        pMotionPlayer = (CObjectMotionPlayer*)pObject;


    //        m_Pos = pMotionPlayer->GetTARGETPOS();


    //    }
    //}

    ////取得
    //DATA EscData = GetDATA();

    //EscData.Pos = m_Pos;
    ////取得
    //SetDATA(EscData);



    m_nLife--;






    if (m_nLife <= 0)
    {
        SetDeath(true);
    }


    InputpVtx();

    //  m_nLife--;

    //m_nDelay++;

    //if (m_nDelay >= 0)
    //{
    //    m_nDelay = 0;
    //    m_nPatternAnim++;
    //}




    //if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
    //{
    //    SetDeath(true);
    //}



    CObjectBillBoard::Update();
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectLINEUI::Draw()
{
    //    ChengeAddDrawMode(true);
    SetZDrawDeth(true);
    for (int i = 0; i < 20; i++)
    {
        CObjectBillBoard::Draw();
    }
    SetZDrawDeth(false);
}
//=============================
// 座標設定
//=============================
void CObjectLINEUI::SetPos_Rot(D3DXVECTOR3 Pos)
{
    //取得
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    //取得
    SetDATA(EscData);

}
//=============================
// 頂点情報
//=============================
void CObjectLINEUI::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    //pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);
    //pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);

     //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);


    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    ////法線ベクトルの設定
    //pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //頂点カラーの設定
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    //テクスチャ座標を設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//
    //pVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//テクスチャ分割数分右側に座標がズレてる
    //pVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
    //pVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//テクスチャ分割数分右側に座標がズレてる
    //pVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);



    //   ESCpVtxBuff->Unlock();

   //    BindVtxBuffer(ESCpVtxBuff);

    SetpVtx(pVtx);

}
//=============================
// Object生成
//=============================
CObjectLINEUI* CObjectLINEUI::Create(D3DXVECTOR3 Pos)
{
    CObjectLINEUI* pObject3D = new CObjectLINEUI;

    pObject3D->Init();
    pObject3D->SetPos_Rot(Pos);
    return pObject3D;
}
