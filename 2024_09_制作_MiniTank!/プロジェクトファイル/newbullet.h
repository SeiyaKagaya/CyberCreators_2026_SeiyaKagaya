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


//バレット
class CNewBullet : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;				//反射回数
	static const int HIT_COL_ESCAPE_TIME = 30;			//当たり判定無効化時間
	static const int LIFE = 200;						//寿命
	const float ObbLength[3] = { 15.0f,15.0f,30.0f };	//Obbの長さ
	const float SIZE = 30.0f;							//サイズ
	const float SIZEMAG = 5.5f;							//サイズ倍率

	CNewBullet(int nPriority = CObject::LAYERINDEX_NEWBULLET);//コンストラクタ
	~CNewBullet() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
    void Update()override;
	void Draw()override;

	void HitCollision();			//当たり判定

	void SetCaller(void* pCaller);	//親格納

	void SetCOL(D3DXCOLOR col);		//色格納

	static CNewBullet* Create();	//オブジェクト生成

	void SetbUse(bool bUse);		//使用状態か格納

	bool GetbUse();					//使用状態か取得

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);//バレットをセット
	
	int GetHitEscapeTime();			//射撃手への当たり判定抑制取得

	COBB GetOBB();					//obb取得

	void* GetCaller();				//親取得

	void SetGoodby();				//相殺あるとバグ率上がるため避難方式。寿命で死んでもらう

	//配列番号格納
	int GetID();
	void SetID(int nID);

private:
	
	bool m_bUse = false;									//使用状態か
	void* m_pCaller = nullptr;								//親	(発射した本人のみ当たり判定緩和するため必要)
	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//カラー
	CMathProc::CollisionData m_HitData;						//当たり判定データ
	COBB m_OBB = {};

	int m_nLife = 0;				//寿命
	int m_Reflection = 0;			//反射回数
	int m_ShotByHitEscapeTime = 0;	//当たり判定無効化期間
	int m_bGoodbyNow = false;		//bUseと同じ役割/試験的バグ防止
	int m_nID = 0;					//配列番号
};






//バレット管理
class CNewBulletALL
{
public:
	static const int MAXBULLETALL = 120;//最大数
	
	CNewBulletALL();//コンストラクタ
	~CNewBulletALL();//デストラクタ
	HRESULT Init();
	void Uninit();

	void ReleaseAllBullet();///自身のRelease

	static CNewBulletALL* Create();//オブジェクト生成


	void AllClean();//すべてのbUseをfalseに

	static CNewBullet* GetBulletData(int nNum);//特定の配列番号の弾情報を取得

	//すでに生成されている物のbUseをtrueにして稼働させる
	static void SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);

private:

	//静的メンバ変数
	static CNewBullet* m_NewBullet[MAXBULLETALL];
};

#endif