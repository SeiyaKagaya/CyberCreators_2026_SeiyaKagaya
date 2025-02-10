//=========================================================
//
//カメラ関係使う宣言など[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//このマクロが定義されてなかったら
#define _CAMERA_H_//二重インクルード防止のマクロ定義

#include"main.h"

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();//CAMERA設定
	void SetShake(int nShakeFlame, float fMagnitude);//カメラ揺れ

	D3DXMATRIX GetViewMatrix() const { return m_mtxView; }				//ビューマトリックスを取得
	D3DXMATRIX GetProjectionMatrix() const { return m_mtxProjection; }	//プロジェクションマトリックスを取得
	static void SetScreenSize(float screenWidth, float screenHeight);	//スクリーンサイズをセット

	static D3DXVECTOR2 GetScreenSize();									//スクリーンサイズ取得

	D3DXVECTOR3 GetRot();												//角度取得
private:
	static float m_Screen_Width;										//スクリーンサイズ
	static float m_Screen_Height;

	D3DXVECTOR3 m_posV = {};											//視点
	D3DXVECTOR3 m_posR = {};											//注視点
	D3DXVECTOR3 m_rot = {};												//角度
	D3DXVECTOR3 m_vecU = {};											//上方向ベクトル
	D3DXMATRIX m_mtxProjection = {};									//プロジェクションマトリックス
	D3DXMATRIX m_mtxView = {};											//ビューマトリックス
	int m_nShakeFlame = 0;												//シェイクフレーム
	float m_fMag = 0.0f;												//サイズ
};
#endif