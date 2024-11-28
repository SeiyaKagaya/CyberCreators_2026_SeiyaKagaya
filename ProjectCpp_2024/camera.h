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

class CCamera
{
public:

	const float CAMERA_MOVE_DAMPING_RATIO = 0.5f;//カメラ移動慣性
	const float  CAMERA_ROT_DAMPING_RATIO = 0.5f;//カメラ回転慣性
	const float  CAMERA_ROT_SPEED = 0.015f;//カメラ旋回速度
	const float JoyStickDiffCamera = 0.0000008f;			//スティック倍率



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

private:
	D3DXVECTOR3 m_posV;//視点
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_vecU;//上方向ベクトル
	D3DXMATRIX m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	int m_nShakeFlame;
	float m_fMag;


	static float m_Screen_Width;
	static float m_Screen_Height;
	bool m_CameraType = false;

	static D3DXVECTOR3 CameraPos;
};






#endif