//=========================================================
//
// newbullet.cppで使う関数[newbullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _NEWBULLET_H

#define _NEWBULLET_H//二重インクルード防止

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"
//

class CNewBullet : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;//反射回数

	CNewBullet(int nPriority = CObject::LAYERINDEX_NEWBULLET);//コンストラクタ
	~CNewBullet() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
    void Update()override;
	void Draw()override;


	void HitCollision();

	void SetReflect(int nCnt);
	void SetCaller(void* pCaller);
	void SetCOL(D3DXCOLOR col);

	//バグ回避のため凍結
	static CNewBullet* Create();//オブジェクト生成

	void SetbUse(bool bUse);

	bool GetbUse();

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);


	//射撃手への当たり判定抑制取得
	int GetHitEscapeTime();

	COBB GetOBB();
	void* GetCaller();


	//相殺あるとバグ率上がるため避難方式。寿命で死んでもらう
	void SetGoodby();

	int GetID();
	void SetID(int nID);

private:
	
	bool m_bUse = false;

	int m_nReflect = 0;
	void* m_pCaller = nullptr;//発射した本人のみ当たり判定緩和するため必要
	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	CMathProc::CollisionData m_HitData;//当たり判定データ

	COBB m_OBB = {};

	int m_nLife = 0;

	int m_Reflection = 0;

	int m_ShotByHitEscapeTime = 0;

	//バグの回避策
	int m_bGoodbyNow = false;

	int m_nID = 0;

};







class CNewBulletALL : public CObjectX
{
public:
	static const int MAXBULLETALL = 120;
	
	CNewBulletALL(int nPriority = CObject::LAYERINDEX_NEWBULLET_MNG);//コンストラクタ
	~CNewBulletALL() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CNewBulletALL* Create();//オブジェクト生成

	void ReleaseAllBullet();

	//バグ回避のため凍結
	//static CNewBulletALL* Create();//オブジェクト生成

	//規定数を初期化する
	void AllClean();

	CNewBullet* GetBulletData(int nNum);

	//すでに生成されているもののbUseをtrueにして稼働させる
	void SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);


private:

	//先に確保し、回す
	CNewBullet* m_NewBullet[MAXBULLETALL];
};

#endif