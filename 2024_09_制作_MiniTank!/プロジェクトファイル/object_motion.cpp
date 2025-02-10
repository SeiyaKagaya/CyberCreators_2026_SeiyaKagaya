//=========================================================
//
// object_motion[object_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "object_motion.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CObjectMotion::CObjectMotion(int nPriority) :CObjectX(nPriority)
{
    m_FilePass = {};

    m_CrassData = {};//一個体としてのデータ
	m_CrassData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CrassData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CrassData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Model = {};
	m_oldMotionIndex_Parent = 0;
	m_NowMotionIndex_Parent = 1;
	m_NowKeyCnt_Parent=0;
	m_NowFrameCnt_Parent=0;
	m_EscapeMotion_Parent=0;
	m_BrendCnt_Parent=0;
	m_MotionLoopStop_Parent = false;
	m_MotionBrend_Parent = false;
	m_oldMotionIndex_Sub = 0;
	m_NowMotionIndex_Sub = 1;
	m_NowKeyCnt_Sub = 0;
	m_NowFrameCnt_Sub = 0;
	m_EscapeMotion_Sub = 0;
	m_BrendCnt_Sub = 0;
	m_MotionLoopStop_Sub = false;
	m_MotionBrend_Sub = false;

    for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
    {
        m_pMesh[nCnt] = {};//Meshポインタ
        m_pBuffMat[nCnt] = {};//マテリアルへのポインタ
        m_dwNumMat[nCnt] = {};//マテリアルの数
		m_FilePass = {};
		m_PartfilePass[nCnt] = {};

		for (int i = 0; i < MAX_TEXTURE; i++)
		{
			m_pTexture[nCnt][i] = {};
		}
	}
}

//=============================
// デストラクタ
//=============================
CObjectMotion::~CObjectMotion()
{
}

//=============================
// 初期化
//=============================
HRESULT CObjectMotion::Init()
{
    //txt読み込み
    DataLoad();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr; // マテリアルへのポインタ
    DWORD dwNumMat = 0; // マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	for (int nCntPart = 0; nCntPart < m_Model.nMaxLoadPartsCnt; nCntPart++)
	{
		// ファイルの読み込み
		D3DXLoadMeshFromX(m_PartfilePass[nCntPart],
			D3DXMESH_SYSTEMMEM,
			EscDevice,
			NULL,
			&m_pBuffMat[nCntPart],
			NULL,
			&m_dwNumMat[nCntPart],
			&m_pMesh[nCntPart]);

		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCntPart]->GetBufferPointer();

		////テクスチャ取得
		 CAllTexture* pTexture = pManager->GetTexture();

		for (int i = 0; i < (int)m_dwNumMat[nCntPart]; i++)
		{
			if (pMat[i].pTextureFilename != nullptr)
			{
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(EscDevice, pMat[i].pTextureFilename, &m_pTexture[nCntPart][i]);

				int texIndex = pTexture->Regist(pMat[i].pTextureFilename, EscDevice);//テクスチャ登録

				m_pTexture[nCntPart][i] = pTexture->GetAddress(texIndex);//Address参照で取得

			}
		}
	}

	SetObjectType(CObject::OBJECT_MOTIONMODEL);

    return S_OK; 
}

//=============================
// 破棄
//=============================
void CObjectMotion::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotion::Update()
{
	m_CrassData.OldPos = m_CrassData.Pos;
	m_CrassData.Pos += m_CrassData.move;

	bool bHit = false;

	//移動量を更新(疑似慣性で減衰)
	m_CrassData.move.x += (0.0f - m_CrassData.move.x) * (DAMPING_RATIO);
	m_CrassData.move.y += (0.0f - m_CrassData.move.y) * (DAMPING_RATIO);
	m_CrassData.move.z += (0.0f - m_CrassData.move.z) * (DAMPING_RATIO);
	//OBBまわり
	m_Obb.m_Pos = m_CrassData.Pos;

	D3DXMATRIX matRot;

	//方向ベクトル取得
	D3DXMatrixRotationYawPitchRoll(&matRot, m_CrassData.rot.y, m_CrassData.rot.x, m_CrassData.rot.z);
	m_Obb.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	m_Obb.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	m_Obb.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	//--------現在のいるGRIDを検索する
	for (int i = 0; i < CMathProc::GRIDROW; i++)
	{
		for (int M = 0; M < CMathProc::GRIDCOL; M++)
		{
			//ここで現在の位置を計算のち、所属GRIDを手に入れる
			if ((float)CMathProc::GRIDLEGTH * i < m_CrassData.Pos.z && (float)CMathProc::GRIDLEGTH * (i + 1) > m_CrassData.Pos.z)
			{
				if ((float)CMathProc::GRIDLEGTH * M < m_CrassData.Pos.x && (float)CMathProc::GRIDLEGTH * (M + 1) > m_CrassData.Pos.x)
				{
					CMathProc::Point EscPoint;
					EscPoint.x = M;
					EscPoint.y = i;

					//マスの範囲内＝GRID判別
					m_NowGridNum = CMathProc::GetObjectNumfromPoint(EscPoint);
					break;
				}
			}
		}
	}

	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
	{//ゲーム中
		if (m_NowMotionIndex_Sub == 1)
		{//移動

			if (m_RunCnt == 0)
			{
				CManager* pManager = CManager::GetInstance();
				CSound* pSound = pManager->GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SE_RUN);
				m_RunCnt = 15;
			}
			else
			{
				m_RunCnt--;
			}
		}
	}
	Motion_Parent();
	Motion_Sub();

	m_oldMotionIndex_Parent = m_NowMotionIndex_Parent;
	m_oldMotionIndex_Sub = m_NowMotionIndex_Sub;
}

//=============================
// 描画
//=============================
void CObjectMotion::Draw()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

	//キャラ全体の基準(親の親)
		//---------------------------------------------------------------------------------------------------プレイヤーの位置のみ
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_CrassData.rot.y, m_CrassData.rot.x, m_CrassData.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_CrassData.Pos.x, m_CrassData.Pos.y, m_CrassData.Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//=============================
// 生成
//=============================
CObjectMotion* CObjectMotion::Create(const char* pfilePass, DATA SetData)
{
    CObjectMotion* pObstacle = new CObjectMotion;
   
    pObstacle->SetFilePass(pfilePass);//パス格納
    
    pObstacle->Init();

    // 取得
    DATA EscData = pObstacle->GetClassData();
	pObstacle->SetClassData(SetData);
    
    return pObstacle;
}

//=============================
// データロード
//=============================
void CObjectMotion::DataLoad()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	FILE* pFile;//ファイルポインタを宣言

	char aString[MAX_WORD] = {};	//読み込む最大文字数
	int nEscapeCntModel=0;//モデル数
	int nfirstEscapePartsCnt=0;//はじめに使うパーツカウント
	int nMotionCnt=0;//モーションカウント
	int KeyCnt=0;//キーカウント
	int nKeyPartsCnt=0;//各キーの中でのパーツカウント
	int EscapeIndex = 0;//仮
	int EscapeParentIndex = 0;//親番号
	DATA EscOffSetData;//
	DATA EscNowData;//
	int SetMotionCheck = 1;

	pFile = fopen(m_FilePass, "r");
	
	if (pFile != NULL)
	{//ファイルが開いたら
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//最後にきたら
				fclose(pFile);
				break;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%d", &m_Model.nMaxLoadPartsCnt);//モデル数格納

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//各モデルのパーツのパスが来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);//ファイルパス


				char* filePass = new char[strlen(aString) + 1];//長さ分確保
				strcpy(filePass, aString);//コピー

				m_PartfilePass[nEscapeCntModel] = filePass;

				nEscapeCntModel++;//モデル格納後インクリ

			}
			else if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{//キャラセットがきたら
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
					{
						//nCnt++;
						break;
					}
					else if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{//Parts数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.nMaxPartsCnt);
					}
					else if (strcmp(&aString[0], "PARTSSET") == 0)
					{//Parts設定が来たら
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_PARTSSET") == 0)
							{//Parts数エンドが来たら
								//クリエイト
								m_pModelParts[nfirstEscapePartsCnt] = CModelParts::Create(m_PartfilePass[nfirstEscapePartsCnt]);
								//親設定
								m_pModelParts[nfirstEscapePartsCnt]->SetParent(m_pModelParts[EscapeParentIndex]);
								//オフセット格納
								m_pModelParts[nfirstEscapePartsCnt]->SetOffSetData(EscOffSetData);
								//現行データ格納 
								m_pModelParts[nfirstEscapePartsCnt]->SetNowData(EscNowData);
								m_pModelParts[nfirstEscapePartsCnt]->SetMotionPoint(this);
								m_pModelParts[nfirstEscapePartsCnt]->SetMotion_Parent(SetMotionCheck);
								nfirstEscapePartsCnt++;
								break;
							}
							else if (strcmp(&aString[0], "INDEX") == 0)
							{//インデックスが来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &EscapeIndex);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//親が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &EscapeParentIndex);
								
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POSが来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f %f %f", &EscNowData.Pos.x, &EscNowData.Pos.y, &EscNowData.Pos.z);
								//保存
								EscOffSetData.Pos = EscNowData.Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROTが来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f %f %f", &EscNowData.rot.x, &EscNowData.rot.y, &EscNowData.rot.z);

								//保存
								EscOffSetData.rot = EscNowData.rot;
							}
							else if (strcmp(&aString[0], "MOTIONPARENT") == 0)
							{//ROTが来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &SetMotionCheck);

								//保存
								EscOffSetData.rot = EscNowData.rot;
							}
						}
					}
				}
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{//MOTIONセットが来たら
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{//エンドMOTIONセット

						m_Model.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//モーションインクリメント

						if (m_Model.nMaxMotionCnt <= nMotionCnt)
						{
							m_Model.nMaxMotionCnt = nMotionCnt;//モーション数は最大のみ
						}

						KeyCnt = 0;//キー番号リセット

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//ループ数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------最大キー数に応用
					{//キーの数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].nNumKey);
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{//KEYセットが来たら
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_KEYSET") == 0)
							{//エンドKEYセット

								KeyCnt++;//キーインクリメント
								nKeyPartsCnt = 0;//パーツ番号もリセット
								break;

							}
							else if (strcmp(&aString[0], "FRAME") == 0)
							{//フレームの数が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------下記と同じ//わけないと、飛ばされたときに認識できない

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEYが来たら

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//フレームの数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------上記と同じ

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//エンドKEY

										nKeyPartsCnt++;//パーツインクリメント
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Keyごとかつパーツごとで変動

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Keyごとかつパーツごとで変動
									}
								}
							}
						}
					}
				}
			}
			else if(strcmp(&aString[0], "CHANGE_MODEL_INDEX") == 0)
			{//モデルデータ変更のあるモデルのインデックス
			int nChangeIndex = 0;
			fscanf(pFile, "%s", &aString[0]);

			fscanf(pFile, "%d", &nChangeIndex);

			//Changeboolをtrueに
			m_pModelParts[nChangeIndex]->m_DataChangeModel(true);
			m_ChangeDataModelIndex = nChangeIndex;
			}
		}
	}
}

//=============================
// pass格納
//=============================
void CObjectMotion::SetFilePass(const char* FilePass)
{
	char* filePass = new char[strlen(FilePass) + 1];//長さ分確保
	strcpy(filePass, FilePass);//コピー

	m_FilePass = filePass;
}

//=============================
// MOTION！！！！
//=============================
void CObjectMotion::Motion_Parent()
{
	if (m_NowMotionIndex_Parent==2)
	{
		int test = 0;
	}


	if (m_NowMotionIndex_Parent != m_oldMotionIndex_Parent)
	{//前回のモーションと違う時
	//-------------------------------リセット動作
		m_NowKeyCnt_Parent = 0;
		m_NowFrameCnt_Parent= 0;
		m_EscapeMotion_Parent = m_NowMotionIndex_Parent;
		m_BrendCnt_Parent = 0;
		for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
		{//リセット

			if (m_pModelParts[i]->GetMotion_Parent() == 1)
			{//parent属の時
				m_pModelParts[i]->SetcalculationExecution(false);
				m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_MotionLoopStop_Parent = false;
			}
		}
		m_MotionBrend_Parent = true;
	}

#if 0
#else // 1
	if (m_MotionBrend_Parent == true)
	{//モーションブレンド

		if (m_BrendCnt_Parent < BRENDFLAME)
		{
			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//パーツ分回る
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
				{//parent属の時

					DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//オフセット取得
					DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//現行取得

						//ROT系
					if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
					{
						//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
						D3DXVECTOR3 TargetRot;
						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


						TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[1].PartsData[nCnt].CorrectionRot;

						m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot) / BRENDFLAME);

						m_pModelParts[nCnt]->SetcalculationExecution(true);
					}
					m_pModelParts[nCnt]->UpdateRotMotion();


					//POS系
					//--------------------------------------------------------------------------------
					if (m_pModelParts[nCnt]->GetParent() == nullptr)
					{//自分がすべての親の時
						D3DXVECTOR3 TargetPos;
						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						//初期位置から見た地点を補正した、目標地点の算出
						TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[1].PartsData[nCnt].CorrectionPos;

						//現在の位置から、上で算出した目標地点までの差分計算
						m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / BRENDFLAME);

						//POSの更新
						m_pModelParts[nCnt]->UpdatePosMotion();
						//------------------------------------------------------------------------------------
					}
				}
			}
		}
		m_BrendCnt_Parent++;

		if (m_BrendCnt_Parent >= BRENDFLAME)
		{
			m_BrendCnt_Parent = 0;

			m_MotionBrend_Parent = false;

			m_NowKeyCnt_Parent++;//キーを進める

			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//パーツ分回る
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
				{//parent属の時
					m_pModelParts[nCnt]->SetcalculationExecution(false);
					m_pModelParts[nCnt]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}
		}

	}
	else
	{
		if (m_NowMotionIndex_Parent == 2)
		{
			int test = 0;
		}

		// 本動作------------------------------------------------------------------------------------------------------------------
		if (m_MotionLoopStop_Parent == false)
		{
			if (m_NowFrameCnt_Parent < m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent /*- 1*/].nSplitFrame)
			{//分割フレームの分回る
				if (m_NowKeyCnt_Parent < m_Model.Motion[m_NowMotionIndex_Parent].nNumKey)
				{//キーの分回る
					for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
					{//パーツ分回る
						if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
						{//parent属の時
							DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//オフセット取得
							DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//現行取得

								//ROT系
							if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
							{
								//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
								D3DXVECTOR3 TargetRot;
								TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

								if (m_NowKeyCnt_Parent != m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//最後キーじゃない
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent + 1].PartsData[nCnt].CorrectionRot;
								}
								else if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//最後キーのとき
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[0].PartsData[nCnt].CorrectionRot;
								}
								m_pModelParts[nCnt]->SetCorrectCorrectionRotMove((CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot)) / (float)m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent].nSplitFrame);

								m_pModelParts[nCnt]->SetcalculationExecution(true);
							}
							m_pModelParts[nCnt]->UpdateRotMotion();

							//POS系
							//--------------------------------------------------------------------------------
							if (m_pModelParts[nCnt]->GetParent() == nullptr)
							{//自分がすべての親の時
								D3DXVECTOR3 TargetPos;
								TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
								if (m_NowKeyCnt_Parent != m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//最後キーじゃない
								//初期位置から見た地点を補正した、目標地点の算出
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent + 1].PartsData[nCnt].CorrectionPos;
								}
								else if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//最後キーのとき
								//初期位置から見た地点を補正した、目標地点の算出
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[0].PartsData[nCnt].CorrectionPos;
								}
								//現在の位置から、上で算出した目標地点までの差分計算
								m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / (float)m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent].nSplitFrame);

								//POSの更新
								m_pModelParts[nCnt]->UpdatePosMotion();
								//------------------------------------------------------------------------------------
							}
						}
					}
				}
				m_NowFrameCnt_Parent++;//フレーム進める
			}
			else
			{//フレーム数超えた
				m_NowFrameCnt_Parent = 0;//フレームリセット

				m_NowKeyCnt_Parent++;//キーを進める

				for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
				{//リセット
					if (m_pModelParts[i]->GetMotion_Parent() == 1)
					{//parent属の時
						m_pModelParts[i]->SetcalculationExecution(false);
					}
				}

				if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey)
				{//キーが、最大キーを超えた時

					m_NowFrameCnt_Parent = 0;//フレームリセット
					m_NowKeyCnt_Parent = 0;//キーリセット

					if (m_Model.Motion[m_NowMotionIndex_Parent].nLoop == 0)
					{//ループしない
						if (m_NowMotionIndex_Parent == 3)
						{
							m_MotionLoopStop_Parent = true;
						}
						else
						{//飛翔以外
							//待機にする
							m_NowMotionIndex_Parent = 0;//待機状態に戻す
							//ブレンド挟む
							if (m_MotionBrend_Parent == false)
							{
								m_NowKeyCnt_Parent = 0;
								m_NowFrameCnt_Parent = 0;
								m_EscapeMotion_Parent = m_NowMotionIndex_Parent;
								m_BrendCnt_Parent = 0;
								for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
								{//リセット
									if (m_pModelParts[i]->GetMotion_Parent() == 1)
									{//parent属の時
										m_pModelParts[i]->SetcalculationExecution(false);
										m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_MotionLoopStop_Parent = false;

										m_MotionBrend_Parent = true;
									}
								}
							}
						}
					}
					else
					{//ループ

					}
				}
			}
		}
	}
#endif
}

//=============================
// MOTION！！！！Sub
//=============================
void CObjectMotion::Motion_Sub()
{
	if (m_NowMotionIndex_Sub != m_oldMotionIndex_Sub)
	{//前回のモーションと違う時
	//-------------------------------リセット動作
		m_NowKeyCnt_Sub = 0;
		m_NowFrameCnt_Sub = 0;
		m_EscapeMotion_Sub = m_NowMotionIndex_Sub;
		m_BrendCnt_Sub = 0;
		for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
		{//リセット
			if (m_pModelParts[i]->GetMotion_Parent() == 0)
			{//Sub属の時
				m_pModelParts[i]->SetcalculationExecution(false);
				m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_MotionLoopStop_Sub = false;
			}
		}
		m_MotionBrend_Sub = true;
	}
#if 0
#else // 1
	if (m_MotionBrend_Sub == true)
	{//モーションブレンド
		if (m_BrendCnt_Sub < BRENDFLAME)
		{
			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//パーツ分回る
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
				{//Sub属の時
					DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//オフセット取得
					DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//現行取得

						//ROT系
					if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
					{
						//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
						D3DXVECTOR3 TargetRot;
						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[1].PartsData[nCnt].CorrectionRot;

						m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot) / BRENDFLAME);

						m_pModelParts[nCnt]->SetcalculationExecution(true);
					}
					m_pModelParts[nCnt]->UpdateRotMotion();

					//POS系
					//--------------------------------------------------------------------------------
					if (m_pModelParts[nCnt]->GetParent() == nullptr)
					{//自分がすべての親の時
						D3DXVECTOR3 TargetPos;
						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						//初期位置から見た地点を補正した、目標地点の算出
						TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[1].PartsData[nCnt].CorrectionPos;

						//現在の位置から、上で算出した目標地点までの差分計算
						m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / BRENDFLAME);

						//POSの更新
						m_pModelParts[nCnt]->UpdatePosMotion();
						//------------------------------------------------------------------------------------
					}
				}
			}
		}
		m_BrendCnt_Sub++;

		if (m_BrendCnt_Sub >= BRENDFLAME)
		{
			m_BrendCnt_Sub = 0;

			m_MotionBrend_Sub = false;

			m_NowKeyCnt_Sub++;//キーを進める

			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//パーツ分回る
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
				{//Sub属の時
					m_pModelParts[nCnt]->SetcalculationExecution(false);
					m_pModelParts[nCnt]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}
		}
	}
	else
	{
		if (m_NowMotionIndex_Sub == 2)
		{
			int test = 0;
		}

		// 本動作------------------------------------------------------------------------------------------------------------------
		if (m_MotionLoopStop_Sub == false)
		{
			if (m_NowFrameCnt_Sub < m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub /*- 1*/].nSplitFrame)
			{//分割フレームの分回る
				if (m_NowKeyCnt_Sub < m_Model.Motion[m_NowMotionIndex_Sub].nNumKey)
				{//キーの分回る
					for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
					{//パーツ分回る
						if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
						{//Sub属の時
							DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//オフセット取得
							DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//現行取得

								//ROT系
							if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
							{
								//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
								D3DXVECTOR3 TargetRot;
								TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

								if (m_NowKeyCnt_Sub != m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//最後キーじゃない
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub + 1].PartsData[nCnt].CorrectionRot;
								}
								else if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//最後キーのとき
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[0].PartsData[nCnt].CorrectionRot;
								}
								m_pModelParts[nCnt]->SetCorrectCorrectionRotMove((CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot)) / (float)m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub].nSplitFrame);

								m_pModelParts[nCnt]->SetcalculationExecution(true);
							}
							m_pModelParts[nCnt]->UpdateRotMotion();

							//POS系
							//--------------------------------------------------------------------------------
							if (m_pModelParts[nCnt]->GetParent() == nullptr)
							{//自分がすべての親の時
								D3DXVECTOR3 TargetPos;
								TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
								if (m_NowKeyCnt_Sub != m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//最後キーじゃない
								//初期位置から見た地点を補正した、目標地点の算出
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub + 1].PartsData[nCnt].CorrectionPos;
								}
								else if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//最後キーのとき
								//初期位置から見た地点を補正した、目標地点の算出
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[0].PartsData[nCnt].CorrectionPos;
								}
								//現在の位置から、上で算出した目標地点までの差分計算
								m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / (float)m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub].nSplitFrame);

								//POSの更新
								m_pModelParts[nCnt]->UpdatePosMotion();
								//------------------------------------------------------------------------------------
							}
						}
					}
				}
				m_NowFrameCnt_Sub++;//フレーム進める
			}
			else
			{//フレーム数超えた
				m_NowFrameCnt_Sub = 0;//フレームリセット

				m_NowKeyCnt_Sub++;//キーを進める

				for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
				{//リセット
					if (m_pModelParts[i]->GetMotion_Parent() == 0)
					{//Sub属の時
						m_pModelParts[i]->SetcalculationExecution(false);
					}
				}

				if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey)
				{//キーが、最大キーを超えた時

					m_NowFrameCnt_Sub = 0;//フレームリセット
					m_NowKeyCnt_Sub = 0;//キーリセット

					if (m_Model.Motion[m_NowMotionIndex_Sub].nLoop == 0)
					{//ループしない
						if (m_NowMotionIndex_Sub == 3)
						{
							m_MotionLoopStop_Sub = true;
						}
						else
						{//飛翔以外
							//待機にする
							m_NowMotionIndex_Sub = 0;//待機状態に戻す
							//ブレンド挟む
							if (m_MotionBrend_Sub == false)
							{
								m_NowKeyCnt_Sub = 0;
								m_NowFrameCnt_Sub = 0;
								m_EscapeMotion_Sub = m_NowMotionIndex_Sub;
								m_BrendCnt_Sub = 0;
								for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
								{//リセット
									if (m_pModelParts[i]->GetMotion_Parent() == 0)
									{//Sub属の時
										m_pModelParts[i]->SetcalculationExecution(false);
										m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_MotionLoopStop_Sub = false;

										m_MotionBrend_Sub = true;
									}
								}
							}
						}
					}
					else
					{//ループ

					}
				}
			}
		}
	}
#endif
}

//=============================
// モーション番号セット
//=============================
void CObjectMotion::SetNowMotion_Parent(int nMotionNum)
{
	m_NowMotionIndex_Parent = nMotionNum;
}

//=============================
// モーション番号セットサブ
//=============================
void CObjectMotion::SetNowMotion_Sub(int nMotionNum)
{
	m_NowMotionIndex_Sub = nMotionNum;
}

//=============================
// 全体としてのデータ設定
//=============================
void CObjectMotion::SetClassData(DATA data)
{
	m_CrassData = data;
}

//=============================
// 全体としてのデータ取得
//=============================
CObjectMotion::DATA CObjectMotion::GetClassData()
{
	return m_CrassData;
}

//=============================
//マトリックス取得
//=============================
D3DXMATRIX CObjectMotion::GetMatrix()
{
	return m_mtxWorld;
}

//=============================
// マトリックス設定
//=============================
void CObjectMotion::SetMatrix(D3DXMATRIX mtx)
{
	m_mtxWorld = mtx;
}

//=============================
// データ変更ありモデルへの変更データ格納
//=============================
void CObjectMotion::SetChangeDataInObjectMotion(DATA ChangeData)
{
	m_pModelParts[m_ChangeDataModelIndex]->ChangeDataSet(ChangeData);
}

//=============================
// パーツ取得
//=============================
CModelParts* CObjectMotion::GetModelParts(int index)
{
	return m_pModelParts[index];
}

//=============================
// パーツ数取得
//=============================
int CObjectMotion::GetMaxLoadPartsNum()
{
	return m_Model.nMaxLoadPartsCnt;
}

//=============================
// データ変更ありモデルのインデックス
//=============================
int CObjectMotion::GetChangeDataPartsIndex()
{
	return m_ChangeDataModelIndex;
}

//=============================
//OBBサイズかくのう
//=============================
void CObjectMotion::SetOBBLength(float fLength[3])
{
	m_Obb.m_fLength[0] = fLength[0];
	m_Obb.m_fLength[1] = fLength[1];
	m_Obb.m_fLength[2] = fLength[2];
}

//=============================
// OBB取得
//=============================
COBB CObjectMotion::GetOBB()
{
	return m_Obb;
}

//=============================
// GRID番号取得
//=============================
int CObjectMotion::GetNowGRIDNum()
{
	return m_NowGridNum;
}

//=============================
// 自機から障害物などへの当たり判定(player/enemy共通)
//=============================
void CObjectMotion::HitCollisionToStageBlock()
{
	//取得
	DATA EscData = GetClassData();
	SetClassData(EscData);//格納
}

//=============================
// 現在の移動量を返す
//=============================
D3DXVECTOR3 CObjectMotion::GetNowMove()
{
	return m_CrassData.move;
}