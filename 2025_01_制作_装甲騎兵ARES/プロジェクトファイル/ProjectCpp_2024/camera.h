//=========================================================
//
//カメラ関係使う宣言など[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//このマクロが定義されてなかったら

//マクロ定義
#define _CAMERA_H_//二重インクルード防止のマクロ定義

#include"main.h"
#include "LockOnUI.h"
#include "LockOnUIMain.h"
class CCamera
{
public:

	const float CAMERA_MOVE_DAMPING_RATIO = 0.5f;//カメラ移動慣性
	const float  CAMERA_ROT_DAMPING_RATIO = 0.5f;//カメラ回転慣性
	const float  CAMERA_ROT_SPEED = 0.015f;//カメラ旋回速度
	const float JoyStickDiffCamera = 0.0000008f;			//スティック倍率
	const float LOCKMISSLEDDISTANCE = 7500.0f;
	//const float LOCKBULLETDISTANCE = 3000.0f;

	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();

	void ActionUpdate2D();//2DにおけるAction
	void ActionUpdate3D();//3DにおけるAction

	void Input3DCamera();//3Dのみのカメラ操作


	void SetCamera();//CAMERA設定
	void SetShake(int nShakeFlame, float fMagnitude);//カメラ揺れ

	D3DXMATRIX GetViewMatrix() const { return m_mtxView; }//ここでもかけるらしい
	D3DXMATRIX GetProjectionMatrix() const { return m_mtxProjection; }
	static void SetScreenSize(float screenWidth, float screenHeight);

	static D3DXVECTOR2 GetScreenSize();

	D3DXVECTOR3 GetRot();
	static D3DXVECTOR3 GetCameraPos() { return CameraPos; };


	void LockOnEnemy();//ロックオン敵処理
	void SetAllEnemyScreenPos();//スクリーン座標変換セット

	void LockOnEnemy2D();//2D用ロックオン

	// スクリーン座標が画面内にあるかどうかを判定
	bool IsInScreen(D3DXVECTOR3 screenPosition);

	// カメラが対象の方を向いているかどうかを判定
	bool IsFacingCamera(D3DXVECTOR3 enemyPosition);

	bool IntersectRayAABB(const D3DXVECTOR3& rayStart, const D3DXVECTOR3& rayDir, const D3DXVECTOR3& boxMin, const D3DXVECTOR3& boxMax, float& tMin, float& tMax);

	static void ResetCount() { m_nCntFrame = 0;};

private:
	D3DXVECTOR3 m_posV;//視点
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_vecU;//上方向ベクトル
	D3DXMATRIX m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	int m_nShakeFlame = 0;
	float m_fMag = 0.0f;

	bool m_bfast = false;
	static float m_Screen_Width;
	static float m_Screen_Height;
	static int m_nCntFrame;

	bool m_CameraType = false;

	static D3DXVECTOR3 CameraPos;

	////以下"基本は3D"のみ
	//CLockOnUI* m_LockOnUI[8] ={};	       //--ロックオン
	//CLockOnUIMain* m_LockOnUI_Main;//---バレットロックオン
	


	float DebuCameraLength = 300.0f;
};






#endif