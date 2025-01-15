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

//
class CModelParts : public CObjectX
{
public:



	CModelParts(int nPriority = CObject::LAYERINDEX_MODELPARTS);//コンストラクタ
	~CModelParts() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CModelParts* Create(std::string FilePass,int PartsNum);//オブジェクト生成

	void SetPartsNum(int nNum) { m_nPartNum = nNum ;};
	void SetFilePass(std::string FilePass);//ファイルパス格納
	void SetParent(CModelParts* pParentParts);

	void SetOffSetData(DATA offSetData);//Offset位置格納
	DATA GetOffSetData();//Offset位置取得

	D3DXMATRIX GetMtxWorld();//マトリックス取得

	CModelParts* GetParent();//親取得
	//void SetPartsNum(int nNum) {}

	void SetNowData(DATA data);//現行データ
	DATA GetNowData();

	//計算周り取得
	D3DXVECTOR3 GetCorrectCorrectionPosMove();//補正値
	D3DXVECTOR3 GetCorrectCorrectionRotMove();
	bool GetcalculationExecution();			  //計算済みか

	void SetCorrectCorrectionPosMove(D3DXVECTOR3 pos);		//補正値
	void SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot);
	void SetcalculationExecution(bool calculationExecution);//計算済みか

	//動作
	void UpdatePosMotion();
	void UpdateRotMotion();

	void SetMotionPoint(CObjectMotion* Motion);

	D3DXMATRIX GetPartsMtx();
	void SetPartsMtx(D3DXMATRIX mtxWorld);


	//データ変更モデルbool
	void m_DataChangeModel(bool changebool);
	
	//変更データ格納
	void ChangeDataSet(DATA data);
	
	//モーション属をセット
	void SetMotion_Parent(int Check);//1でParent　0でSub

	//モーション属を取得
	int GetMotion_Parent();//1でParent　0でSub

	void DrawOkBool(bool Draw);

	void ChengeRGBAbool(bool chenge, D3DXCOLOR col );

	bool IsValid() const;

private:
//	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//テクスチャ

	//ここではDATAを最終的な描画などに使用。
	//下地用(親マトリックスとの融合など)は別の変数に入れる
	D3DXMATRIX m_mtxWorld;

	DATA m_offSetData;//Offset位置
	DATA m_NowData;

	DATA m_ChangeDATA;

//	int INDEX;//自分の番号
// 
//		int PEARENT;		//自分の親番号
	CModelParts* m_pParentParts;//親モデルへのポインタ

	std::string m_PartfilePass;					//各modelごとのpass

	D3DXVECTOR3 m_CorrectCorrectionPosMove;//モーションでの移動量pos
	D3DXVECTOR3 m_CorrectCorrectionRotMove;//モーションでの移動量move
	bool m_calculationExecution=false;//補正値計算したかbool

	CObjectMotion* pMotion;//すべての親のポインタ

	bool m_ChangeDatabool=false;//データ変更があるモデルか
	int m_MotionParent=0;//motionがparent属か、1でそうなる

	bool m_bDrawBool = true;

	D3DXCOLOR m_ChengeCol=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	bool m_bChengeCol = false;

	int m_nPartNum = 0;

};

#endif