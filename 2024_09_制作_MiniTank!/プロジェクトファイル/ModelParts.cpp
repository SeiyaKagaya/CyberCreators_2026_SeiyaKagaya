//=========================================================
//
// ModelParts[ModelParts.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ModelParts.h"
#include "renderer.h"
#include "manager.h"
#include "object_motion.h"

//=============================
// コンストラクタ
//=============================
CModelParts::CModelParts(int nPriority) :CObjectX(nPriority), m_ChangeDatabool(false)
{
    m_ChangeDATA = {};

    m_CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//モーションでの移動量pos
     m_CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//モーションでの移動量move
     m_calculationExecution=false;//補正値計算したかbool

     for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
     {
         if (m_pTexture[nCnt] != nullptr)
         {
             m_pTexture[nCnt] = nullptr;
         }
     }
}

//=============================
//デストラクタ
//=============================
CModelParts::~CModelParts()
{
}

//=============================
//初期化
//=============================
HRESULT CModelParts::Init()
{
    CObjectX::Init();
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;//Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr;//マテリアルへのポインタ
    DWORD dwNumMat = 0;//マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //ファイルの読み込み
    D3DXLoadMeshFromX(m_PartfilePass,
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    //マテリアルデータへのポインタを取得
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    ////テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//テクスチャ登録

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//設定
        }
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat);//データ格納

    SetObjectType(CObject::OBJECT_MODELPARTS);

    return S_OK;
}

//=============================
//破棄
//=============================
void CModelParts::Uninit()
{
    CObjectX::Uninit();
}

//=============================
//更新
//=============================
void CModelParts::Update()
{
}

//=============================
//描画
//=============================
void CModelParts::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    if (m_ChangeDatabool==true)
    {//データ変更アリの時

        //これは親のマトリックスを考慮していない
        m_NowData = m_ChangeDATA;

        m_NowData.Pos = m_offSetData.Pos;

        //親のマトリックス
        D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

        // 親の向きを考慮して補正
        float parentAngle = atan2f(m_mtxWorldParent._31, m_mtxWorldParent._11);
        m_NowData.rot.y -= parentAngle;
    }

    DATA EscData = GetDATA();//再取得

    D3DXMATRIX EscMtxWorld;

    D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    //向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_NowData.rot.y, m_NowData.rot.x, m_NowData.rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    //位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_NowData.Pos.x, m_NowData.Pos.y, m_NowData.Pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    //親子関係
    if (m_pParentParts == nullptr)
    {
        //自分の主のマトリックスとかける(player/enemy)など
        EscDevice->GetTransform(D3DTS_WORLD, &EscMtxWorld);//とりあえず最新のマトリックス取得

        D3DXMATRIX EscMat = pMotion->GetMatrix();

        //始祖とかける
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &EscMat);
    }
    else
    {
        D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

        //自分の親のマトリックス欠けてる
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldParent);
    }

    ChangeModelPartsbool(true);//パーツ描画じマトリックス変更
    SetModelMtxWorld(m_mtxWorld);//マトリックス格納

    EscData.Pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);//マトリックスから取り出す

    // 回転行列を抽出し、floatにキャスト
    EscData.rot.x = static_cast<float>(atan2(m_mtxWorld._32, m_mtxWorld._33));
    EscData.rot.y = static_cast<float>(atan2(-m_mtxWorld._31, static_cast<double>(sqrt(static_cast<double>(m_mtxWorld._32) * static_cast<double>(m_mtxWorld._32) + static_cast<double>(m_mtxWorld._33) * static_cast<double>(m_mtxWorld._33)))));
    EscData.rot.z = static_cast<float>(atan2(m_mtxWorld._21, m_mtxWorld._11));

    SetDATA(EscData);//格納(描画時にこの計算後のposRotを使用するようになる)

    if (m_bDrawBool == true)
    {
        if (m_bChengeCol==true)
        {
            CObjectX::SetColorChangeBool(true);
            CObjectX::SetChangeColor(m_ChengeCol);
        }
        CObjectX::Draw();
    }
}

//=============================
//生成
//=============================
CModelParts* CModelParts::Create(const char* FilePass)
{
    CModelParts* pModelParts = new CModelParts;

    pModelParts->SetFilePass(FilePass);
    pModelParts->Init();
    return pModelParts;
}

//=============================
// パス格納//init前にやる
//=============================
void CModelParts::SetFilePass(const char* FilePass)
{
    char* filePass = new char[strlen(FilePass) + 1];//長さ分確保
    strcpy(filePass, FilePass);//コピー

    m_PartfilePass = filePass;
}

//=============================
// 親を格納
//=============================
void CModelParts::SetParent(CModelParts* pParentParts)
{
    m_pParentParts = pParentParts;
}

//=============================
// Offset格納
//=============================
void CModelParts::SetOffSetData(DATA offSetData)
{
    m_offSetData = offSetData;
}

//=============================
// Offset取得
//=============================
CModelParts::DATA CModelParts::GetOffSetData()
{
    return m_offSetData;
}

//=============================
// マトリックス取得
//=============================
D3DXMATRIX CModelParts::GetMtxWorld()
{
    return m_mtxWorld;
}

//=============================
// 親を取得
//=============================
CModelParts* CModelParts::GetParent()
{
    return m_pParentParts;
}

//=============================
// 通常データ格納
//=============================
void CModelParts::SetNowData(DATA data)
{
    m_NowData=data;
}

//=============================
// 通常データを取得
//=============================
CModelParts::DATA CModelParts::GetNowData()
{
    return m_NowData;
}

//=============================
// 補正値取得POS
//=============================
D3DXVECTOR3 CModelParts::GetCorrectCorrectionPosMove()
{
    return m_CorrectCorrectionPosMove;
}

//=============================
// 補正値取得ROT
//=============================
D3DXVECTOR3 CModelParts::GetCorrectCorrectionRotMove()
{
    return m_CorrectCorrectionRotMove;
}

//=============================
// 補正値計算済みか取得
//=============================
bool CModelParts::GetcalculationExecution()
{
    return m_calculationExecution;
}

//=============================
// 補正値格納POS
//=============================
void CModelParts::SetCorrectCorrectionPosMove(D3DXVECTOR3 pos)
{
    m_CorrectCorrectionPosMove = pos;
}

//=============================
// 補正値格納ROT
//=============================
void CModelParts::SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot)
{
    m_CorrectCorrectionRotMove = Rot;
}

//=============================
// 補正値計算済みかを格納
//=============================
void CModelParts::SetcalculationExecution(bool calculationExecution)
{
    m_calculationExecution = calculationExecution;
}

//=============================
// motionPos
//=============================
void CModelParts::UpdatePosMotion()
{
    //親のときしか動作しない
    m_NowData.Pos += m_CorrectCorrectionPosMove;
}

//=============================
//MotionRot
//=============================
void CModelParts::UpdateRotMotion()
{
    m_NowData.rot += m_CorrectCorrectionRotMove;
}

//=============================
// 親を格納
//=============================
void CModelParts::SetMotionPoint(CObjectMotion* Motion)
{
    pMotion = Motion;//すべての親のポインタ
}

//=============================
// マトリックスを返す
//=============================
D3DXMATRIX CModelParts::GetPartsMtx()
{
    return m_mtxWorld;
}

//=============================
// マトリックスを格納
//=============================
void CModelParts::SetPartsMtx(D3DXMATRIX mtxWorld)
{
    m_mtxWorld = mtxWorld;
}

//=============================
// データ変動パーツか
//=============================
void CModelParts::m_DataChangeModel(bool changebool)
{
    m_ChangeDatabool = changebool; 
}

//=============================
// 変更データ格納
//=============================
void CModelParts::ChangeDataSet(DATA data)
{
    m_ChangeDATA = data; 
}

//=============================
// モーション族値を格納
//=============================
void CModelParts::SetMotion_Parent(int Check)
{
    m_MotionParent = Check;
}

//=============================
// モーション族値を返す
//=============================
int CModelParts::GetMotion_Parent()
{
    return m_MotionParent;
}

//=============================
// 描画可能かを格納
//=============================
void CModelParts::DrawOkBool(bool Draw)
{
    m_bDrawBool = Draw;
}

//=============================
// 色を変えるかと変更色を格納
//=============================
void CModelParts::ChengeRGBAbool(bool chenge, D3DXCOLOR col)
{
    m_bChengeCol = chenge;
    m_ChengeCol = col;
}