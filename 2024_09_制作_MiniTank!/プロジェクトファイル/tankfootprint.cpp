//=======================================================
//
// tankfootprintに関する処理[tankfootprint.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "tankfootprint.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CObjectFootPrint::CObjectFootPrint(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_FOOTPRINT);
}

//=============================
// デストラクタ
//=============================
CObjectFootPrint::~CObjectFootPrint()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObjectFootPrint::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\TankMove.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定

    m_nLife = STANPLIFE;

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObjectFootPrint::Uninit()
{
	CObject3D::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CObjectFootPrint::Update()
{
    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
    {//ゲーム中

    }
    else if (NowState == CScene::MODE_TITLE)
    {//タイトル

      //取得
        DATA EscData = GetDATA();

        EscData.Pos.x += 13.0f;
        //取得
        SetDATA(EscData);
    }
    else if (NowState == CScene::MODE_RESULT)
    {//タイトル
      //取得
        DATA EscData = GetDATA();

        EscData.Pos.x -= 13.0f;
        //取得
        SetDATA(EscData);
    }

    InputpVtx();

    CObject3D::Update();

    m_nLife--;

    if (m_nLife <= 0)
    {
        SetDeath(true);
    }
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectFootPrint::Draw()
{
	CObject3D::Draw();
}

//=============================
// 座標設定
//=============================
void CObjectFootPrint::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    //取得
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;
    //取得
    SetDATA(EscData);
}

//=============================
// 頂点情報
//=============================
void CObjectFootPrint::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];
    
    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE_X, (float)PRINTSIZE_Y, (float)PRINTSIZE_Z);
    pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE_X, (float)PRINTSIZE_Y, (float)PRINTSIZE_Z);
    pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE_X, (float)PRINTSIZE_Y, (float)-PRINTSIZE_Z);
    pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE_X, (float)PRINTSIZE_Y, (float)-PRINTSIZE_Z);

    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);

    //テクスチャ座標を設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

    SetpVtx(pVtx);
}

//=============================
// Object生成
//=============================
CObjectFootPrint* CObjectFootPrint::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    CObjectFootPrint* pObject3D = new CObjectFootPrint;
	pObject3D->SetPos_Rot(Pos,rot);
    pObject3D->Init();
    return pObject3D;
}