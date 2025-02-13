//=======================================================
//
//objectに関する処理[object.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object.h"

int CObject::m_nNumAll = 0;

CObject* CObject::m_pTop[CObject::LAYERINDEX_MAX] = {};//最初
CObject* CObject::m_pCur[CObject::LAYERINDEX_MAX] = {};//最後
CObject* CObject::m_pLastCreatedObject[CObject::LAYERINDEX_MAX] = {};//最後に作ったもの

//=============================
//コンストラクタ(自分自身の登録)
//=============================
CObject::CObject(int nPriority): m_nPriority(nPriority), m_pPrev(nullptr), m_pNext(nullptr),m_bDeath(false)
{
	m_bDeath = false;

	if (m_pTop[m_nPriority]==nullptr)
	{//いまのプライオリティの先頭がいないとき
		m_pTop[m_nPriority] = this;//先頭をこれに
		m_pPrev = nullptr;//前は存在しない
	}
	else
	{//前は存在する
		m_pPrev = m_pLastCreatedObject[m_nPriority];//前回最後に生成したONJECTに設定
		m_pPrev->m_pNext = this;//最後に生成したOBJECTのNEXTを自身に設定
	}
	//最後列のため次はいない
	m_pNext = nullptr;

	m_nID = m_nNumAll;

	m_nNumAll++; // 総数インクリメント

	//最後に生成したOBJECTを更新
	m_pLastCreatedObject[m_nPriority] = this;
}

//=============================
//	デストラクタ
//=============================
CObject::~CObject()
{
}

//=============================
//	全オブジェクト開放
//=============================
void CObject::ReleaseAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];//先頭取得
		
		if (m_pTop[nCnt2] != nullptr)
		{//先頭がない==プライオリティまるっとない
		
		 //最大数不明のためwhile
			while (pObj != nullptr)
			{
				CObject* pNext = pObj->m_pNext;
				if (pObj->m_ObjectType != OBJECT_FADE)
				{
					pObj->m_bDeath = true;//フラグ建てる
					pObj->Release();//開放
				}
				pObj = pNext;
			}
		}
	}
}

//=============================
//	全オブジェクト更新
//=============================
void CObject::UpdateAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];//先頭取得
		//最大数不明のためwhile
	
		if (m_pTop[nCnt2] != nullptr)
		{//先頭がない==プライオリティまるっとない
			while (pObj != nullptr)
			{
				CObject* pNext = pObj->m_pNext;

				if (pObj->GetDeathNow() == false)
				{//死亡判定じゃない時

					pObj->Update();
				}
				pObj = pNext;
			}
		}
	}

	DelayDeath();//遅らせたリリースをここで
}

//=============================
//	全オブジェクト描画
//=============================
void CObject::DrawAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		if (m_pTop[nCnt2] != nullptr)
		{
			CObject* pObj = m_pTop[nCnt2];//先頭取得
			
			if (m_pTop[nCnt2] != nullptr)
			{//先頭がない==プライオリティまるっとない

				//最大数不明のためwhile
				while (pObj != nullptr)
				{
					CObject* pNext = pObj->m_pNext;
					pObj->Draw();
					pObj = pNext;
				}
			}
		}
	}
}

//=============================
//	遅延開放
//=============================
void CObject::DelayDeath()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{
				pObj->Release();
			}

			pObj = pNext;
		}
	}
}

//=============================
//	敵総数取得
//=============================
int CObject::GetnNumAll()
{
	return m_nNumAll;
}

//=============================
//	objectのポインタを取得
//=============================
CObject* CObject::GetObjectPoint(int nPriority, OBJECTTYPE ObjectType)
{
	CObject* pObj = m_pTop[nPriority];//先頭取得

	//最大数不明のためwhile
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->m_pNext;

		if (ObjectType== pObj->m_ObjectType)
		{
			return pObj;
		}
	
		pObj = pNext;
	}

	return nullptr;
}

//=============================
// 先頭取得
//=============================
CObject* CObject::GetpTop(int nPriority)
{
	return m_pTop[nPriority];
}

//=============================
//	次のポインタ取得
//=============================
CObject* CObject::GetNext()
{
	return m_pNext;
}

//=============================
//	データ初期化
//=============================
CObject::DATA CObject::DataInit()
{
	DATA data;
	data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.OldPos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.Radius = 0.0f;
	data.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return data;
}

//=============================
//	自分自身を開放
//=============================
void CObject::Release()
{
	// 前後をつなげる
	if (m_pPrev != nullptr)
	{//自分より前がいる時
		m_pPrev->m_pNext = m_pNext;//次を前に
	}
	else
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	if (m_pTop[m_nPriority] == this)
	{//自身が先頭のとき
		m_pTop[m_nPriority] = m_pNext;//先頭を前に
	}

	if (m_pNext != nullptr)
	{//次がある時
		m_pNext->m_pPrev = m_pPrev;//次の"前"を自身の前に
	}

	Uninit();

	m_nNumAll--;//総数をデクリメント

	delete this;

}

//=============================
// オブジェクトタイプ設定
//=============================
void CObject::SetObjectType(OBJECTTYPE ObjectType)
{
	m_ObjectType = ObjectType;
}

//=============================
// オブジェクトタイプ取得
//=============================
CObject::OBJECTTYPE CObject::GetObjectType()
{
	return m_ObjectType;
}