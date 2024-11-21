//=========================================================
//
//�J�����֌W�g���錾�Ȃ�[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//���̃}�N������`����ĂȂ�������

//�}�N����`
#define _CAMERA_H_//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();//CAMERA�ݒ�
	void SetShake(int nShakeFlame, float fMagnitude);//�J�����h��

	D3DXMATRIX GetViewMatrix() const { return m_mtxView; }//�����ł�������炵��
	D3DXMATRIX GetProjectionMatrix() const { return m_mtxProjection; }
	static void SetScreenSize(float screenWidth, float screenHeight);

	static D3DXVECTOR2 GetScreenSize();

	D3DXVECTOR3 GetRot();
	static D3DXVECTOR3 GetCameraPos() { return CameraPos; };

private:
	D3DXVECTOR3 m_posV;//���_
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	int m_nShakeFlame;
	float m_fMag;


	static float m_Screen_Width;
	static float m_Screen_Height;
	bool m_CameraType = false;

	static D3DXVECTOR3 CameraPos;
};






#endif