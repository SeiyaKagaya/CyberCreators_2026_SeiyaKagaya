//=========================================================
//
// enemy_motion_base.cppで使う関数[enemy_motion_base.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYBASE_H
#define _MOTIONENEMYBASE_H//二重インクルード防止

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"
#include <vector>
#include "object_motion.h"

//基底クラス
class CObjectMotionEnemyBase : public CObjectMotion
{
public:
	static const int ROUTE_TABLE_ROW = 11;//横列8まで
	static const int ROUTE_TABLE_SHIELDROW = 8;//縦列11まで
	static const int AABB_BOX = 58;

	typedef enum
	{
		ENEMYTYPE_NOMAL=0,
		ENEMYTYPE_MAX
	}ENEMYTYPE;


	CObjectMotionEnemyBase(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BASE);//コンストラクタ
	CObjectMotionEnemyBase(ENEMYTYPE Enemytype,int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BASE);//オーバーロード

	virtual ~CObjectMotionEnemyBase() override;//デストラクタ

	virtual HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;

	static CObjectMotionEnemyBase* Create(std::string pfilePass, DATA SetData);//オブジェクト生成

	static int GetEnemyAllNum();//総数取得

	//MainTargetか
	void SetPriorityAttackTarget(bool bSet) { m_bPriorityAttackTarget = bSet; };
	bool GetPriorityAttackTarget() { return m_bPriorityAttackTarget; };

	//画面内にいるか
	void SetInScreenTarget(bool bSet) { m_bIsInScreen = bSet; };
	bool GetInScreenTarget() { return m_bIsInScreen; };

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	int m_nLife=0;

	static int m_nNumENemyAll;//敵総数

	bool m_bPriorityAttackTarget = false;//mainTarget

	bool m_bIsInScreen = false;//画面内にうつっているか
};

#endif