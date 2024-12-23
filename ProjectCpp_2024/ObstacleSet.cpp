//=========================================================
//
// ObstacleSet[ObstacleSet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ObstacleSet.h"
#include "manager.h"

// 静的メンバ変数の初期化
std::vector<CObstacleSet::OBSTACLEINFO> CObstacleSet::m_ObstacleInfo = {}; // xfileとインデックスの格納
int CObstacleSet::m_ObstacleCount = 10; // 上の構造体のサイズ

bool CObstacleSet::m_bRelease = false;//開放したか

int CObstacleSet::m_NowSetModelIndex = 0;//現在のモデルタイプ
int CObstacleSet::m_MAXModelIndex = 0;//最大モデル数
D3DXVECTOR3 CObstacleSet::m_SetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//現在のモデルタイプ


//=============================
// コンストラクタ
//=============================
CObstacleSet::CObstacleSet(int nPriority) :CObjectX(nPriority)
{
    m_bBreak = false;
    m_bPreview = false;
    m_nType = 0;
    m_StageBlock = false;
}

//=============================
// デストラクタ
//=============================
CObstacleSet::~CObstacleSet()
{
}

//=============================
// 初期化
//=============================
HRESULT CObstacleSet::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr; // マテリアルへのポインタ
    DWORD dwNumMat = 0; // マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // ファイルの読み込み
    D3DXLoadMeshFromX(m_ObstacleInfo[m_nType].pFilePass,
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);
    





    //// バウンディングボックスを格納するための変数
    //D3DXVECTOR3 vMin, vMax;

    //// 頂点バッファを取得
    //LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
    //pMesh->GetVertexBuffer(&pVertexBuffer);
    //
    //// 頂点データをメモリにロックする
    //void* pVertices = NULL;
    //pVertexBuffer->Lock(0, 0, &pVertices, 0);
    //
    //// 頂点フォーマットを取得し、頂点の位置情報が格納されているオフセットを求める
    //DWORD vertexSize = pMesh->GetNumVertices();
    //DWORD fvf = pMesh->GetFVF();
    //DWORD vertexPosOffset = (fvf & D3DFVF_XYZRHW) ? sizeof(D3DXVECTOR3) : 0;

    //// バウンディングボックスを計算
    //D3DXComputeBoundingBox(
    //    (const D3DXVECTOR3*)pVertices,  // 頂点データ（位置情報）
    //    vertexSize,                     // 頂点の数
    //    vertexPosOffset,                // 頂点フォーマットに基づくオフセット（位置情報のオフセット）
    //    &vMin,                          // 最小点
    //    &vMax                           // 最大点
    //);

   // // 頂点バッファのロックを解除
   // pVertexBuffer->Unlock();


    // 取得
    DATA EscData = GetDATA();

    EscData.MinLength = D3DXVECTOR3(100000.0f, 1000000.0f, 100000.0f); //モデルの最小位置
    EscData.MaxLength = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //モデルの最大位置

    int nNumVtx; //頂点数
    DWORD sizeFVF; //頂点フォーマットのサイズ
    BYTE* pVtxBuff; //頂点バッファのポインタ

    //頂点数の取得
    nNumVtx = pMesh->GetNumVertices();
    //頂点フォーマットのサイズを取得
    sizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

    //頂点バッファのロック
    pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
    for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
    {
        //頂点座標の代入
        D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

        // 座標変換行列を作成
        D3DXMATRIXA16 matRotation;
        D3DXMatrixRotationYawPitchRoll(&matRotation, EscData.rot.y, EscData.rot.x, EscData.rot.z);

        // 頂点座標を回転
        D3DXVec3TransformCoord(&vtx, &vtx, &matRotation);


        if (vtx.x > EscData.MaxLength.x)
        {
            EscData.MaxLength.x = vtx.x;
        }
        if (vtx.x < EscData.MinLength.x)
        {
            EscData.MinLength.x = vtx.x;
        }

        if (vtx.y > EscData.MaxLength.y)
        {
            EscData.MaxLength.y = vtx.y;
        }
        if (vtx.y < EscData.MinLength.y)
        {
            EscData.MinLength.y = vtx.y;
        }

        if (vtx.z > EscData.MaxLength.z)
        {
            EscData.MaxLength.z = vtx.z;
        }
        if (vtx.z < EscData.MinLength.z)
        {
            EscData.MinLength.z = vtx.z;
        }

        // 次の頂点に進む
        pVtxBuff += sizeFVF;
    }


    if (m_nType == 5)
    {//stagemodel
        EscData.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        EscData.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }


    SetDATA(EscData); // 格納



   





    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
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


    SetXfireData(pMesh, pBuffMat, dwNumMat); // データ格納

    SetObjectType(CObject::OBJECT_OBSTACLE);

    SetSizeMag(D3DXVECTOR3(1.0f,1.0f,1.0f)); // 大きさ倍率

 

    return S_OK;
}

//=============================
// 破棄
//=============================
void CObstacleSet::Uninit()
{
    int test = 0;

    if (m_bRelease == false)
    {
        m_bRelease = true;
        for (int i = 0; i < m_ObstacleCount; i++)
        {
            delete m_ObstacleInfo[i].pFilePass;
        }
    }
 
    
    CObjectX::Uninit();

   // delete this;
}

//=============================
// 更新
//=============================
void CObstacleSet::Update()
{

    // 取得
   DATA EscData = GetDATA();

    SetDATA(EscData); // 格納

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();
    CInputKeyboard* keyboard = pManager->GetKeyboard();
       
    if (m_StageBlock == true)
    {

    }

}

//=============================
// 描画
//=============================
void CObstacleSet::Draw()
{
  //  SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
// 生成
//=============================
CObstacleSet* CObstacleSet::Create(DATA SetData, int SetType, bool bBreak, bool bPreview)
{
    CObstacleSet* pObstacle = new CObstacleSet;

    pObstacle->m_nType = SetType;


    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    pObstacle->m_bBreak = bBreak;
    pObstacle->m_bPreview = bPreview;

    pObstacle->SetDATA(EscData); // 格納

    pObstacle->Init();

    return pObstacle;
}

//=============================
// 配列サイズ変更
//=============================
void CObstacleSet::Resize(int count)
{

    //// 既存の動的メモリを解放
    //for (size_t i = 0; i < m_ObstacleInfo.size(); ++i)
    //{
    //    delete[] m_ObstacleInfo[i].pFilePass; // 動的に確保したメモリを解放
    //    m_ObstacleInfo[i].pFilePass = nullptr; // ポインタを無効化
    //}

    m_ObstacleInfo.resize(count);
}

//=============================
// データロード
//=============================
void CObstacleSet::DataLoad(const char* filename)
{
    int ModelPassCnt = 0; // passカウントアップ用
    DATA EscData = {}; // クリエイト用のデータ一時格納
    int SetTypeIndex = 0; // セットするタイプを一時格納

    FILE* pFile = nullptr; // ファイルポインタを宣言
    char aString[2000]; // 読み込む最大文字数
    
    pFile = fopen(filename, "r");

    if (pFile != nullptr)
    {
        while (1)
        {
            fscanf(pFile, "%s", aString);

            if (strcmp(aString, "END_SCRIPT") == 0)
            {
                fclose(pFile);//閉じる
                break;
            }
            else if (strcmp(aString, "NUM_MODEL") == 0)
            {
                fscanf(pFile, "%s", aString); // '='を吸う
                fscanf(pFile, "%d", &m_ObstacleCount); // 配列数も同一に

                CObstacleSet::Resize(m_ObstacleCount); // 配列のサイズを変更
            }
            else if (strcmp(aString, "MODEL_FILENAME") == 0)
            {
                fscanf(pFile, "%s", aString); // '='を吸う
                fscanf(pFile, "%s", aString); // 本体

                char* filePass = new char[strlen(aString) + 1];//長さ分確保
                strcpy(filePass, aString);//コピー

                m_ObstacleInfo[ModelPassCnt].ModelIndex = ModelPassCnt;
                m_ObstacleInfo[ModelPassCnt].pFilePass = filePass;

                ModelPassCnt++;

            }
            else if (strcmp(aString, "MODELSET") == 0)
            {
                while (1)
                {
                    fscanf(pFile, "%s", aString);

                    if (strcmp(aString, "END_MODELSET") == 0)
                    {
                        Create(EscData, SetTypeIndex, false, false);
                        break;
                    }
                    else if (strcmp(aString, "TYPE") == 0)
                    {
                        fscanf(pFile, "%s", aString); // '='を吸う
                        fscanf(pFile, "%d", &SetTypeIndex); // typeを格納
                    }
                    else if (strcmp(aString, "POS") == 0)
                    {
                        fscanf(pFile, "%s", aString);
                        fscanf(pFile, "%f %f %f", &EscData.Pos.x, &EscData.Pos.y, &EscData.Pos.z);
                    }
                    else if (strcmp(aString, "ROT") == 0)
                    {
                        fscanf(pFile, "%s", aString);
                        fscanf(pFile, "%f %f %f", &EscData.rot.x, &EscData.rot.y, &EscData.rot.z);
                    }
                }
            }
        }
    }
    //最大数を保存
    m_MAXModelIndex = ModelPassCnt-1;
}



//=============================
//モデルセット状態をセーブ
//=============================
void CObstacleSet::Model_DebugSave(void)
{
    FILE* pFile;//ファイルポインタを宣言

    //ファイルを開く
    pFile = fopen("DATA\\ForDevelopment\\Setinfo.txt", "w");

    if (pFile != NULL)
    {
        fprintf(pFile, "#------------------------------------------------------------------------------\n");
        fprintf(pFile, "  # モデル配置情報\n");
        fprintf(pFile, "#------------------------------------------------------------------------------\n");


      
     //   for (int nCnt = 0; nCnt < LAYERINDEX_MAX; nCnt++)
      //  {
        int nCnt = (int)LAYERINDEX_OBSTACLE;

            CObject* pObj = CObject::GetpTop(nCnt);//先頭取得

            if (pObj != nullptr)
            {//先頭がない==プライオリティまるっとない

             //最大数不明のためwhile
                while (pObj != nullptr)
                {
                    CObject* pNext = pObj->GetNext();
                    
                    //変換
                    CObstacleSet* pObstacleSet;

                    pObstacleSet = (CObstacleSet*)pObj;

                    if (pObstacleSet->GetPreviewBool() == true)
                    {//プレビューモデルだったとき
                    }
                    else
                    {
                        int EscType = pObstacleSet->GetModelType();
                        CObject::DATA EscData = pObstacleSet->GetDATA();

                        fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
                            , EscType
                            , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
                            , EscData.rot.x, EscData.rot.y, EscData.rot.z
                        );
                    }

                    pObj = pNext;

                }
            }
      //  }


        //
        // //プレビューモデル以外を検索
        //for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
        //{
    
        //    for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
        //    {//全object周回

        //        CObject* pObject = CObject::GetObjectData(nCnt, (CObject::LAYERINDEX)nPriority);//オブジェクトデータ取得

        //        if (pObject != nullptr)
        //        {
        //            CObject::OBJECTTYPE type = pObject->GetObjectType();//タイプ取得

        //            if (type == CObject::OBJECT_OBSTACLE)
        //            {//探しているタイプと一致

        //                //変換
        //                CObstacleSet* pObstacleSet;

        //                pObstacleSet = (CObstacleSet*)pObject;

        //                if (pObstacleSet->GetPreviewBool() == true)
        //                {//プレビューモデルだったとき
        //                }
        //                else
        //                {
        //                    int EscType = pObstacleSet->GetModelType();
        //                    CObject::DATA EscData = pObstacleSet->GetDATA();

        //                    fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
        //                        , EscType
        //                        , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
        //                        , EscData.rot.x, EscData.rot.y, EscData.rot.z
        //                        );
        //                }
        //            }
        //        }
        //    }

        //}
        
        fprintf(pFile, "\nEND_SCRIPT");

        //ファイル閉じる
        fclose(pFile);
    }
    else
    {
    }

}


//=============================
// プレビューモデル周り
//=============================
void CObstacleSet::previewModelLoad()
{
    bool bSet = false;//セットされているか

    int nCnt = (int)LAYERINDEX_OBSTACLE;

   // for (int nCnt = 0; nCnt < LAYERINDEX_MAX; nCnt++)
   // {
        CObject* pObj = CObject::GetpTop(nCnt);//先頭取得

        if (pObj != nullptr)
        {//先頭がない==プライオリティまるっとない

         //最大数不明のためwhile
            while (pObj != nullptr)
            {
                CObject* pNext = pObj->GetNext();

                //変換
                CObstacleSet* pObstacleSet;

                pObstacleSet = (CObstacleSet*)pObj;

                if (pObstacleSet->GetPreviewBool() == true)
                {//プレビューモデルだったとき

                    if (pObstacleSet->GetModelType() == m_NowSetModelIndex)
                    {//現在のモデルタイプと同じとき
                        bSet = true;//セット済みにする。
                        break;
                    }
                    else
                    {//違うとき

//                        pObstacleSet->Release();//対象をリリース
                        pObstacleSet->SetDeath(true);
                        
                        break;

                    }
                }
                //if (pObstacleSet->GetPreviewBool() == true)
                //{//プレビューモデルだったとき
                //}
                //else
                //{
                //    int EscType = pObstacleSet->GetModelType();
                //    CObject::DATA EscData = pObstacleSet->GetDATA();

                //    fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
                //        , EscType
                //        , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
                //        , EscData.rot.x, EscData.rot.y, EscData.rot.z
                //    );
                //}

                pObj = pNext;

            }
        }
  //  }



    ////プレビューモデル検索
    //for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
    //{
    //    for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
    //    {//全object周回

    //        CObject* pObject = CObject::GetObjectData(nCnt, (CObject::LAYERINDEX)nPriority);//オブジェクトデータ取得

    //        if (pObject != nullptr)
    //        {
    //            CObject::OBJECTTYPE type = pObject->GetObjectType();//タイプ取得

    //            if (type == CObject::OBJECT_OBSTACLE)
    //            {//探しているタイプと一致
    //                
    //                //変換
    //                CObstacleSet* pObstacleSet;

    //                pObstacleSet = (CObstacleSet*)pObject;
    //                if (pObstacleSet->GetPreviewBool()==true)
    //                {//プレビューモデルだったとき
    //    
    //                    if (pObstacleSet->GetModelType()== m_NowSetModelIndex)
    //                    {//現在のモデルタイプと同じとき
    //                        bSet = true;//セット済みにする。
    //                        break;
    //                    }
    //                    else
    //                    {//違うとき
    //                        pObstacleSet->Release();//対象をリリース
    //                        break;
    //                      
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}













    if (bSet==false)
    {//セットしていない、もしくはタイプが違う
        CRenderer* pRenderer = nullptr;

        CManager* pManager = CManager::GetInstance();

        CInputKeyboard* keyboard = pManager->GetKeyboard();


        DATA SetData;
        //Mouseで画面に指してる3D空間座標取得
        SetData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

        // SetData.rot.y をターゲットの方向に合わせる
        SetData.rot = m_SetRot;
        //----------------------------------------------------------------------------------

        //現在のモデルタイプで再構成
        Create(SetData, m_NowSetModelIndex, false, true);
    }


}
//=============================
// プレビューモデルか取得
//=============================
bool CObstacleSet::GetPreviewBool()
{
    return m_bPreview;
}
//=============================
// モデルタイプ取得
//=============================
int CObstacleSet::GetModelType()
{
    return m_nType;
}
//=============================
// 設置用独立入力
//=============================
void CObstacleSet::Input()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    //---------------------------------------------------------移動系
    if (keyboard->GetTrigger(DIK_8) == true)
    {
        if (0 >= m_NowSetModelIndex)
        {
            m_NowSetModelIndex = m_MAXModelIndex;
        }
        else
        {
            m_NowSetModelIndex -= 1;
        }
    }
    if (keyboard->GetTrigger(DIK_9) == true)
    {
        if (m_NowSetModelIndex >= m_MAXModelIndex)
        {
            m_NowSetModelIndex = 0;
        }
        else
        {
            m_NowSetModelIndex += 1;
        }
    }



    if (keyboard->GetTrigger(DIK_UP) == true)
    {
      
        m_SetRot.y += (D3DX_PI / 6);

        if (D3DX_PI - 0.1f >= m_SetRot.y)
        {
            
        }
        else
        {
            m_SetRot.y = 0.0f;
        }
    }
    if (keyboard->GetTrigger(DIK_DOWN) == true)
    {
      
        m_SetRot.y -= (D3DX_PI / 6);

        if (0.0f + 0.1f <= m_SetRot.y)
        {
           
        }
        else
        {
            m_SetRot.y = D3DX_PI;
        }
    }


    //if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
    //{//左ボタンが押された

    //    //Mouseの方向にballetを飛ばす
    //    //----------------------------------------------------------------------------------
    //    DATA SetData;
    //    //Mouseで画面に指してる3D空間座標取得
    //    SetData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

    //    // SetData.rot.y をターゲットの方向に合わせる
    //    SetData.rot = m_SetRot;
    //    //----------------------------------------------------------------------------------

    //    Create(SetData, m_NowSetModelIndex, false, false);
    //}

    if (keyboard->GetTrigger(DIK_F3) == true)
    {//セーブ
        Model_DebugSave();
    }
    //if (keyboard->GetTrigger(DIK_F1) == true)
    //{//削除
    //    DestroyCircle();
    //}
   
    if (keyboard->GetTrigger(DIK_F6) == true)
    {
        ObstacleScanMapping();//マッピング
    }
}
//=============================
// 設置用テスト描画
//=============================
void CObstacleSet::DebugSetDataDraw()
{
    char cData2[100] = {};
    snprintf(cData2, sizeof(cData2), "[F1]でマウス座標のモデル削除！\n[F3]で書き出し！現在のIndex[%d]角度[y=%.2f]", m_NowSetModelIndex, m_SetRot.y); // 数値を文字列に変換してCDataにコピー
    // mousePos.x と mousePos.y がマウスの位置
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), cData2);

}




//=============================
//障害物の検知とそれを踏まえたマッピング
//=============================
void CObstacleSet::ObstacleScanMapping()
{
    

  //  float fMapBlockLength = 300.0f;


    //マス目用データ
    CMathProc::Cell GridData[CMathProc::GRIDROW][CMathProc::GRIDCOL] = {};


    //typedef struct
    //{
    //    int GridDistance[CMathProc::GRIDROW][CMathProc::GRIDCOL];//グリッドに配置された距離
    //}ROUTEDATA;



    //初期化
    for (int i = 0; i < CMathProc::GRIDROW; i++)
    {
        for (int M = 0; M < CMathProc::GRIDCOL; M++)
        {
            GridData[i][M].bBlock = false;
            GridData[i][M].Num = 0;
        }
    }




    //まず障害物を検知・あるマスをtrueに
    //----------------------------------------------------------------------------------------------------
    for (int i = 0; i < CMathProc::GRIDROW; i++)
    {
        for (int M = 0; M < CMathProc::GRIDCOL; M++)
        {
            //配置物プライオリティの先頭を取得
            CObject* pObj = GetpTop(LAYERINDEX_OBSTACLE);

            if (pObj != nullptr)
            {//先頭がない==プライオリティまるっとない
                while (pObj != nullptr)
                {
                    if (pObj->GetObjectType() == OBJECT_OBSTACLE)
                    {//設置モデルのとき

                        CObstacleSet* pObstacleObject = static_cast<CObstacleSet*>(pObj);//キャスト

                        DATA ObjectData = pObstacleObject->GetDATA();//データ取得

                        if ((float)CMathProc::GRIDLEGTH * i < ObjectData.Pos.z && (float)CMathProc::GRIDLEGTH * (i + 1) > ObjectData.Pos.z)
                        {
                            if ((float)CMathProc::GRIDLEGTH * M < ObjectData.Pos.x && (float)CMathProc::GRIDLEGTH * (M + 1) > ObjectData.Pos.x)
                            {
                                //マスの範囲内＝障害物あり

                                GridData[i][M].bBlock = true;

                                //forまで戻って次のマスに進む
                                break;
                            }
                        }

                    }

                    CObject* pNext = pObj->GetNext();
                    pObj = pNext;
                }
            }
        }
    }//----------------------------------------------------------------------------------------------------

//    //障害物に気をつけながら"幅優先探索"をする
//    //--------------------------------------------------------------------------------------------------------------
    // スタート位置とゴール位置
     

#if 1
    for (int A = 0; A < CMathProc::GRIDROW; A++)
    {
        for (int B = 0; B < CMathProc::GRIDCOL; B++)
        {
            for (int C = 0; C < CMathProc::GRIDROW; C++)
            {
                for (int D = 0; D < CMathProc::GRIDCOL; D++)
                {

   //-------------------------X---Y
                    CMathProc::Point start = { B, A };
                    CMathProc::Point goal = { D,C };
#else
                    CMathProc::Point start = { 0, 0 };
                    CMathProc::Point goal = { 10,7 };
#endif



                 


                    //セル格納
                    CMathProc::SetCell(GridData);

                    // 幅優先探索を実行
                    CMathProc::bfs(start, goal);

                    // 結果をCSVに書き出す
           //         CMathProc::writeToCSV("DATA\\ForDevelopment\\DepthResult.csv");

                    //最短距離と経路テーブルの作成
                    CMathProc::RouteTableSet(start, goal);

#if 1


                }
            }
        }
    }
#else
#endif // 0
    CMathProc::DRAWCSV("DATA\\ForDevelopment\\RouteResult.csv");


    
}



//=============================
// 当たり判定まとめ
//=============================
void CObstacleSet::HitCollision()
{
    //// 取得
    //DATA EscData = GetDATA();

    //// 当たり判定計算
    //m_HitData = CMathProc::CheckBoxCollision_3D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_BLOCK3D,LAYERINDEX_BLOCK3D,EscData.move);

    //if (m_HitData.bHit == true)
    //{
    //    if (m_HitData.HitAngle.x == 1)
    //    {
    //        EscData.Pos.x += m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.x == -1)
    //    {
    //        EscData.Pos.x -= m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == 1)
    //    {
    //        EscData.Pos.y += m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == -1)
    //    {
    //        EscData.Pos.y -= m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == 1)
    //    {
    //        EscData.Pos.z += m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == -1)
    //    {
    //        EscData.Pos.z -= m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //}

    //SetDATA(EscData); // 格納
}
//=============================
// ステージ配置物か取得
//=============================
bool CObstacleSet::GetStageBlockbool()
{
    return m_StageBlock;
}
