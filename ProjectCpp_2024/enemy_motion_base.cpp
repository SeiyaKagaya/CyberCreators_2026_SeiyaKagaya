//=========================================================
//
// enemy_motion_baseの動き[enemy_motion_base.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_base.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include <stdio.h>
#include <cstring>
#include <iostream> // デバッグ用
#include "line.h"
//#include "ballet3D.h"
#include "Explosion3D.h"

int CObjectMotionEnemyBase::m_nNumENemyAll = 0;


//=============================
// コンストラクタ
//=============================
CObjectMotionEnemyBase::CObjectMotionEnemyBase(int nPriority) :CObjectMotion(nPriority)
{
	m_nNumENemyAll++;
}
//=============================
//オーバーロードコンストラクタ
//=============================
CObjectMotionEnemyBase::CObjectMotionEnemyBase(ENEMYTYPE Enemytype, int nPriority) :CObjectMotion(nPriority)
{


	switch (Enemytype)
	{
	case ENEMYTYPE_NOMAL:
		
		break;

	case ENEMYTYPE_MAX:
		
		break;
	}
}

//=============================
// デストラクタ
//=============================
CObjectMotionEnemyBase::~CObjectMotionEnemyBase()
{
	m_nNumENemyAll--;

}

//=============================
// 初期化
//=============================
HRESULT CObjectMotionEnemyBase::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_BASE);

	float fLength[3];
	fLength[0] = 100.0f;
	fLength[1] = 100.0f;
	fLength[2] = 130.0f;

	m_nLife = 100;

	SetOBBLength(fLength);//OBB長さ格納

	return S_OK;
}

//=============================
// 破棄
//=============================
void CObjectMotionEnemyBase::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionEnemyBase::Update()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();


	CObjectMotion::Update();

	DATA classData = GetClassData();

	
	if (m_nLife <= 0)
	{
		SetDeath(true);
		//Explosion3D::Create(GetClassData().Pos);
		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
		{//パーツもDEATH
			GetModelParts(i)->SetDeath(true);
		}
	}

	SetClassData(classData);
}

//=============================
// 描画
//=============================
void CObjectMotionEnemyBase::Draw()
{
	CObjectMotion::Draw();
}
//=============================
// 生成
//=============================
CObjectMotionEnemyBase* CObjectMotionEnemyBase::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyBase* pObstacle = new CObjectMotionEnemyBase;

	pObstacle->SetFilePass(pfilePass);//パス格納

	pObstacle->Init();

	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX, (float)AABB_BOX*2, (float)AABB_BOX);
	SetData.MinLength = D3DXVECTOR3((float)-AABB_BOX, 0.0f, (float)-AABB_BOX);

	pObstacle->SetClassData(SetData);

	return pObstacle;
}
//=============================
// 敵総数取得
//=============================
int CObjectMotionEnemyBase::GetEnemyAllNum()
{
	return m_nNumENemyAll;
}
