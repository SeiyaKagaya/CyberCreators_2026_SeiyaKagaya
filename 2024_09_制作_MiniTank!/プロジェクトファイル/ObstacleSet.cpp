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

    // 取得
    DATA EscData = GetDATA();
    EscData = GetDATA(); // 再取得


    SetDATA(EscData); // 格納

    return S_OK;
}

//=============================
// 破棄
//=============================
void CObstacleSet::Uninit()
{
    CObjectX::Uninit();
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
       

//以下はMAPPING用
#if 0
    if (m_bPreview == true)
    {
        DATA EscData = GetDATA();//取得

        //Mouseで画面に指してる3D空間座標取得
        EscData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());
        
        EscData.rot = m_SetRot;

        SetDATA(EscData); // 格納
   
    }
    else
    {
        //消されるか判別
        if (keyboard->GetTrigger(DIK_F1) == true)
        {//削除
               //Mouseで画面に指してる3D空間座標取得
            DATA EscData2;
            EscData2.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

            //範囲制定
            D3DXVECTOR3 HitMin = D3DXVECTOR3(EscData2.Pos.x - 200.0f, 0.0f, EscData2.Pos.z - 200.0f);
            D3DXVECTOR3 HitMax = D3DXVECTOR3(EscData2.Pos.x + 200.0f, 0.0f, EscData2.Pos.z + 200.0f);

            if (HitMin.x <= EscData.Pos.x && HitMax.x >= EscData.Pos.x)
            {
                if (HitMin.z <= EscData.Pos.z && HitMax.z >= EscData.Pos.z)
                {//判定内
                    SetDeath(true);
                }
            }
        }
    }
#else
#endif // 0
}

//=============================
// 描画
//=============================
void CObstacleSet::Draw()
{
    SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
// 生成
//=============================
CObstacleSet* CObstacleSet::Create(DATA SetData, int SetType, bool bBreak, bool bPreview)
{
    CObstacleSet* pObstacle = new CObstacleSet;

    pObstacle->m_nType = SetType;
    pObstacle->Init();

    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    pObstacle->m_bBreak = bBreak;
    pObstacle->m_bPreview = bPreview;

    if (pObstacle->m_nType == (m_ObstacleCount - 1))
    {//最大値のモデルタイプのとき
        pObstacle->m_StageBlock = true;//ステージblock扱い

        EscData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
        EscData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 150.0f);
    }
    else
    {
        EscData.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        EscData.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }

    pObstacle->SetDATA(EscData); // 格納

    return pObstacle;
}

//=============================
// 配列サイズ変更
//=============================
void CObstacleSet::Resize(int count)
{
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
                        pObstacleSet->SetDeath(true);
                        
                        break;
                    }
                }
                pObj = pNext;
            }
        }
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
    snprintf(cData2, sizeof(cData2), "[F1]でマウス座標のモデル削除！\n[F3]でmodel書き出し！現在のIndex[%d]角度[y=%.2f]", m_NowSetModelIndex, m_SetRot.y); // 数値を文字列に変換してCDataにコピー
    // mousePos.x と mousePos.y がマウスの位置
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), cData2);

}

//=============================
//障害物の検知とそれを踏まえたマッピング
//=============================
void CObstacleSet::ObstacleScanMapping()
{
    //マCObstacleSetス目用データ
    CMathProc::Cell GridData[CMathProc::GRIDROW][CMathProc::GRIDCOL] = {};

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
                                break;
                            }
                        }
                    }
                    CObject* pNext = pObj->GetNext();
                    pObj = pNext;
                }
            }
        }
    }

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

                    //セル格納
                    CMathProc::SetCell(GridData);

                    // 幅優先探索を実行
                    CMathProc::bfs(start, goal);

                    //最短距離と経路テーブルの作成
                    CMathProc::RouteTableSet(start, goal);
                }
            }
        }
    }

    //CSVに書き出し
    CMathProc::DRAWCSV("DATA\\ForDevelopment\\RouteResult.csv");
}

//=============================
// 当たり判定まとめ
//=============================
void CObstacleSet::HitCollision()
{
}

//=============================
// ステージ配置物か取得
//=============================
bool CObstacleSet::GetStageBlockbool()
{
    return m_StageBlock;
}