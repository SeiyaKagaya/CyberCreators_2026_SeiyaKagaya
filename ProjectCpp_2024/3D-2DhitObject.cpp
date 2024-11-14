//=========================================================
//
// 2D-3DhitColision[2D-3DhitColision.cpp]
// Author seiya kagaya
//
//=========================================================
#include"3D-2DhitObject.h"
#include "manager.h"
#include "player_motion.h"
#include "enemy_motion_Nomal.h"





//=============================
// コンストラクタ
//=============================
CStageCollisionBox3D2D::CStageCollisionBox3D2D(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
CStageCollisionBox3D2D::~CStageCollisionBox3D2D()
{
}

//=============================
// 初期化
//=============================
HRESULT CStageCollisionBox3D2D::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

   // LPD3DXMESH pMesh = nullptr;
    LPD3DXBUFFER pBuffMat = nullptr;
    DWORD dwNumMat = 0;

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    
    const char* aData = {};

    switch (m_hitbox)
    {
    case TYPE_RIGHTSLOPE:
        aData = "DATA\\MODEL\\iwaR.x";
        break;
    
    case TYPE_LEFTSLOPE:
        aData = "DATA\\MODEL\\iwaL.x";
        break;

    case TYPE_NOMALBLOCK:
    
        aData = "DATA\\MODEL\\iwa.x";
        break;
    }

    // メッシュの読み込み
        D3DXLoadMeshFromX(aData,
            D3DXMESH_SYSTEMMEM,
            EscDevice,
            NULL,
            &pBuffMat,
            NULL,
            &dwNumMat,
            &m_pMesh);

    












    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    // テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();
    LPDIRECT3DTEXTURE9 m_ESCpTexture = nullptr;

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
    //        const char* TexName = "DATA\\TEXTURE\\iwa.jpg";
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);

            // UVスケールを調整（UVを2倍にすることで600サイズに合わせる例）
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        }
    }


    float USize = m_TexSize.x / 150.0f;
    float VSize = m_TexSize.y / 150.0f;;

    m_pMesh = ScaleMeshUVs(m_pMesh, USize,VSize);

    SetXfireData(m_pMesh, pBuffMat, dwNumMat);
    SetObjectType(CObject::OBJECT_HITBOX_2D3D);

    return S_OK;
}

//=============================
// 破棄
//=============================
void CStageCollisionBox3D2D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void CStageCollisionBox3D2D::Update()
{


}

//=============================
// 描画
//=============================
void CStageCollisionBox3D2D::Draw()
{

#if _DEBUG

    ChengeStageTex(true);
    SizeMagChangebool(true);
 //   SetColorChangeBool(true);
    CObjectX::Draw();
    ChengeStageTex(false);

#else

#endif // _D
}

//=============================
// 生成
//=============================
CStageCollisionBox3D2D* CStageCollisionBox3D2D::Create(DATA SetData, HITBOX hitman)
{
    CStageCollisionBox3D2D* pObstacle = new CStageCollisionBox3D2D;

    pObstacle->SetSIzeTexture(SetData.MaxLength);

    pObstacle->SetType(hitman);
    pObstacle->Init();


    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    D3DXVECTOR3 SizeMag;

    //サイズ変動
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 10.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

    pObstacle->SetSizeMag(SizeMag);//倍率変動

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // 格納

     

    return pObstacle;
}




////=============================
//// 当たり判定まとめ
////=============================
//void CStageCollisionBox3D2D::HitCollision()
//{
//
//}
//=============================
// メッシュのUV座標をスケーリングする関数
//=============================
LPD3DXMESH CStageCollisionBox3D2D::ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale)
{
    
    struct Vertex
    {
        D3DXVECTOR3 position;
        D3DXVECTOR3 normal;
        float u, v;
    };

    Vertex* pVertices = nullptr;
    pMesh->LockVertexBuffer(0, (void**)&pVertices);

    // メッシュの頂点数を取得
    DWORD numVertices = pMesh->GetNumVertices();

    // 各頂点のUV座標をスケーリング
    for (DWORD i = 0; i < numVertices; ++i)
    {
        pVertices[i].u *= uScale;  // 横方向のスケール
        pVertices[i].v *= vScale;  // 縦方向のスケール
    }

    // バッファをアンロック
    pMesh->UnlockVertexBuffer();

    return pMesh;
}
//=============================
// テクスチャサイズ
//=============================
void CStageCollisionBox3D2D::SetSIzeTexture(D3DXVECTOR3 TexSize)
{
    m_TexSize = TexSize;
}
//=============================
// タイプ格納
//=============================
void CStageCollisionBox3D2D::SetType(HITBOX type)
{
    m_hitbox = type;
}
//=============================
// タイプ取得
//=============================
CStageCollisionBox3D2D::HITBOX CStageCollisionBox3D2D::GetHitBoxType()
{
    return m_hitbox;
}
CMathProc::CollisionData CStageCollisionBox3D2D::bHitColision(D3DXVECTOR3 pos, D3DXVECTOR3 rayDirection, CObject::OBJECTTYPE MyType, void* pCaller)
{
    return CMathProc::CollisionData();

  //  一度でも接触があればtrueに
	bool EscHit = false;

	// 必要に応じて改良、下記は試験運用段階
	CMathProc::CollisionData HitData;

	HitData.bHit = false;
	HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.targetIndex = -1;

	// 自分
	// あたり判定用のHitBox
	D3DXVECTOR3 My_Collision_Min_Pos;
	//My_Collision_Min_Pos.x = MyPos.x + MyMinLength.x;
	//My_Collision_Min_Pos.y = MyPos.y + MyMinLength.y;
	//My_Collision_Min_Pos.z = MyPos.z + MyMinLength.z;

	//D3DXVECTOR3 My_Collision_Max_Pos = MyPos + MyMaxLength;

	bool bLandingHit = false;


	
	


	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(LAYERINDEX_HITBOX_2D3D);

	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		int nIndex = 0;

		while (pObject != nullptr)
		{
			bool bSkip = false;


			HitData.bHit = false;
			HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.targetIndex = -1;

			if (pObject->GetObjectType() == LAYERINDEX_HITBOX_2D3D)
			{ // 対象のモデルのとき

				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CObject::DATA EscData;

				// ここで使用分宣言
				CNewBullet* pNewBullet = {};

				CStageCollisionBox3D2D* pStageHitBox_2D3D;

				pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;

				EscData = pStageHitBox_2D3D->GetDATA();
				

				if (pStageHitBox_2D3D->GetHitBoxType() != CStageCollisionBox3D2D::TYPE_LEFTSLOPE)
				{
					bSkip = true;
				}
	
				if (bSkip == false)
				{

					
					//ここで接触判定














					if (HitData.bHit == true)
					{ // 衝突時
						EscHit = true;


						HitData.targetIndex = nIndex;

						D3DXVECTOR3 moveVector;//ベクトル格納
						D3DXVECTOR3 reflectionVector;//反射ベクトル格納
						float dotProduct;//内積格納
						float moveVectorLength;//ベクトルの長さ
						bool bBreak = false;

						//data格納
						CObject::DATA EscData2 = CObject::DataInit();


						EscData2.Pos = pos;

						if (HitData.HitAngle.x == 1)
						{//+x
							EscData2.Pos.x += HitData.ResultDistance.x;

							EscData2.move.x = 0.0f;
						}
						else if (HitData.HitAngle.x == -1)
						{//-x

							EscData2.Pos.x -= HitData.ResultDistance.x;
							EscData2.move.x = 0.0f;
						}
						else if (HitData.HitAngle.y == 1)
						{//+y
							EscData2.Pos.y += (HitData.ResultDistance.y);
							//				EscData2.Pos.y = TarGet_Collision_Max_Pos.y + (My_Collision_Min_Pos.y - MyPos.y + 15.1f);
							EscData2.move.y = 0.0f;
						}
						else if (HitData.HitAngle.y == -1)
						{//-y
							EscData2.Pos.y -= HitData.ResultDistance.y;
							EscData2.move.y = 0.0f;
						}
						else if (HitData.HitAngle.z == 1)
						{//+z
							EscData2.Pos.z += HitData.ResultDistance.z;

							EscData2.move.z = 0.0f;
						}
						else if (HitData.HitAngle.z == -1)
						{//-z
							EscData2.Pos.z -= HitData.ResultDistance.z;
							EscData2.move.z = 0.0f;
						}


						//-------------------------------------------ここをなんとか自身のポインタにする

						//ここでこの関数を呼んだ元のクラスの値にデータを代入する

						CObject::DATA SETDATA = CObject::DataInit();

						switch (MyType)
						{
						case CObject::OBJECT_MOTIONPLAYER:

							SETDATA = ((CObjectMotionPlayer*)pCaller)->GetClassData();

							SETDATA.Pos = EscData2.Pos;

							//SETDATA.move

							if (HitData.HitAngle.x == 1)
							{//+x
								SETDATA.move.x = 0.0f;
							}
							else if (HitData.HitAngle.x == -1)
							{//-x

								SETDATA.move.x = 0.0f;
							}
							else if (HitData.HitAngle.y == 1)
							{//+y
								SETDATA.move.y = 0.0f;
							}
							else if (HitData.HitAngle.y == -1)
							{//-y
								SETDATA.move.y = 0.0f;
							}
							else if (HitData.HitAngle.z == 1)
							{//+z

								SETDATA.move.z = 0.0f;
							}
							else if (HitData.HitAngle.z == -1)
							{//-z
								SETDATA.move.z = 0.0f;
							}

							//	SETDATA.move = EscData2.move;

							((CObjectMotionPlayer*)pCaller)->SetClassData(SETDATA);

							if (HitData.HitAngle.y == 1)
							{//ヒットアングルが上(着地)の時
								bLandingHit = true;
							}



							break;
						case CObject::OBJECT_MOTIONENEMY_NOMAL:

							SETDATA = ((CObjectMotionEnemyNomal*)pCaller)->GetClassData();

							SETDATA.Pos = EscData2.Pos;
							SETDATA.move = EscData2.move;

							((CObjectMotionEnemyNomal*)pCaller)->SetClassData(SETDATA);
							break;
							// 他の呼び出し元のケース
						}


					}

					CObject* pNext = pObject->GetNext();
					pObject = pNext;
					nIndex++;

					//		break;


				}
				else
				{
					CObject* pNext = pObject->GetNext();
					pObject = pNext;
					nIndex++;
				}


			}
		}
	}


	if (EscHit == true)
	{
		HitData.bHit = true;
	}
	else
	{
		switch (MyType)
		{
		case CObject::OBJECT_MOTIONPLAYER:

			int test = 0;
			break;
		}
	}

	if (bLandingHit == true)
	{
		HitData.HitAngle.y = 1;
	}
	else
	{
		switch (MyType)
		{
		case CObject::OBJECT_MOTIONPLAYER:

			int test = 0;
			break;
		}
	}

	return HitData;





}