//=========================================================
//
//�J�����֌W�g���錾�Ȃ�[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//���̃}�N������`����ĂȂ�������
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

	D3DXMATRIX GetViewMatrix() const { return m_mtxView; }				//�r���[�}�g���b�N�X���擾
	D3DXMATRIX GetProjectionMatrix() const { return m_mtxProjection; }	//�v���W�F�N�V�����}�g���b�N�X���擾
	static void SetScreenSize(float screenWidth, float screenHeight);	//�X�N���[���T�C�Y���Z�b�g

	static D3DXVECTOR2 GetScreenSize();									//�X�N���[���T�C�Y�擾

	D3DXVECTOR3 GetRot();												//�p�x�擾
private:
	static float m_Screen_Width;										//�X�N���[���T�C�Y
	static float m_Screen_Height;

	D3DXVECTOR3 m_posV = {};											//���_
	D3DXVECTOR3 m_posR = {};											//�����_
	D3DXVECTOR3 m_rot = {};												//�p�x
	D3DXVECTOR3 m_vecU = {};											//������x�N�g��
	D3DXMATRIX m_mtxProjection = {};									//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView = {};											//�r���[�}�g���b�N�X
	int m_nShakeFlame = 0;												//�V�F�C�N�t���[��
	float m_fMag = 0.0f;												//�T�C�Y
};
#endif