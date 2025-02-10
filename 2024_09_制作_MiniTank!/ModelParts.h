//=========================================================
//
// ModelParts.cppで使う関数[ModelParts.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MODELPARTS_H
#define _MODELPARTS_H//二重インクルード防止

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CObjectMotion;//前方宣言

class CModelParts : public CObjectX
{
public:
	CModelParts(int nPriority = CObject::LAYERINDEX_MODELPARTS);//コンストラクタ
	~CModelParts() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CModelParts* Create(const char* FilePass);		//オブジェクト生成

	void SetFilePass(const char* FilePass);					//ファイルパス格納
	void SetParent(CModelParts* pParentParts);				//親格納

	void SetOffSetData(DATA offSetData);					//Offset位置格納
	DATA GetOffSetData();									//Offset位置取得

	D3DXMATRIX GetMtxWorld();								//マトリックス取得
	CModelParts* GetParent();								//親取得

	void SetNowData(DATA data);								//現行データ格納
	DATA GetNowData();										//データ取得

	//計算周り取得
	D3DXVECTOR3 GetCorrectCorrectionPosMove();				//POS補正値取得
	D3DXVECTOR3 GetCorrectCorrectionRotMove();				//ROT補正値取得

	bool GetcalculationExecution();							//計算済みか

	void SetCorrectCorrectionPosMove(D3DXVECTOR3 pos);		//POS補正値格納
	void SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot);		//ROT補正値格納

	void SetcalculationExecution(bool calculationExecution);//計算済みか

	//動作
	void UpdatePosMotion();
	void UpdateRotMotion();

	void SetMotionPoint(CObjectMotion* Motion);				//モーション格納

	D3DXMATRIX GetPartsMtx();								//マトリックス取得
	void SetPartsMtx(D3DXMATRIX mtxWorld);					//マトリックス格納

	void m_DataChangeModel(bool changebool);				//データ変更モデルbool
	
	void ChangeDataSet(DATA data);							//変更データ格納
	
	//モーション属をセット
	void SetMotion_Parent(int Check);						//1でParent　0でSub

	//モーション属を取得
	int GetMotion_Parent();									//1でParent　0でSub

	void DrawOkBool(bool Draw);								//描画して良いか

	void ChengeRGBAbool(bool chenge, D3DXCOLOR col );		//色変更があるか

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE] = {};	//テクスチャ
	
	//ここではDATAを最終的な描画などに使用。
	//下地用(親マトリックスとの融合など)は別の変数に入れる
	D3DXMATRIX m_mtxWorld = {};

	DATA m_offSetData = CObject::DataInit();	//Offset位置
	DATA m_NowData = CObject::DataInit();		//現在の位置
	DATA m_ChangeDATA = CObject::DataInit();	//変更量

	CModelParts* m_pParentParts = nullptr;		//親モデルへのポインタ
	const char* m_PartfilePass = nullptr;		//各modelごとのpass
	D3DXVECTOR3 m_CorrectCorrectionPosMove = {};//モーションでの移動量pos
	D3DXVECTOR3 m_CorrectCorrectionRotMove = {};//モーションでの移動量move
	CObjectMotion* pMotion = nullptr;			//すべての親のポインタ
	bool m_calculationExecution = false;		//補正値計算したかbool
	bool m_ChangeDatabool = false;				//データ変更があるモデルか
	bool m_bChengeCol = false;					//カラーチェンジかどうか
	bool m_bDrawBool = true;					//描画状態か
	int m_MotionParent = 0;						//motionがparent属か、1でそうなる
	D3DXCOLOR m_ChengeCol = {};					//チェンジ時のカラー
};

#endif