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
#include "LockOnUI.h"
#include "LockOnUIMain.h"
class CCamera
{
public:

	const float CAMERA_MOVE_DAMPING_RATIO = 0.5f;//�J�����ړ�����
	const float  CAMERA_ROT_DAMPING_RATIO = 0.5f;//�J������]����
	const float  CAMERA_ROT_SPEED = 0.015f;//�J�������񑬓x
	const float JoyStickDiffCamera = 0.0000008f;			//�X�e�B�b�N�{��
	const float LOCKMISSLEDDISTANCE = 7500.0f;
	//const float LOCKBULLETDISTANCE = 3000.0f;

	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();

	void ActionUpdate2D();//2D�ɂ�����Action
	void ActionUpdate3D();//3D�ɂ�����Action

	void Input3DCamera();//3D�݂̂̃J��������


	void SetCamera();//CAMERA�ݒ�
	void SetShake(int nShakeFlame, float fMagnitude);//�J�����h��

	D3DXMATRIX GetViewMatrix() const { return m_mtxView; }//�����ł�������炵��
	D3DXMATRIX GetProjectionMatrix() const { return m_mtxProjection; }
	static void SetScreenSize(float screenWidth, float screenHeight);

	static D3DXVECTOR2 GetScreenSize();

	D3DXVECTOR3 GetRot();
	static D3DXVECTOR3 GetCameraPos() { return CameraPos; };


	void LockOnEnemy();//���b�N�I���G����
	void SetAllEnemyScreenPos();//�X�N���[�����W�ϊ��Z�b�g


	// �X�N���[�����W����ʓ��ɂ��邩�ǂ����𔻒�
	bool IsInScreen(D3DXVECTOR3 screenPosition);

	// �J�������Ώۂ̕��������Ă��邩�ǂ����𔻒�
	bool IsFacingCamera(D3DXVECTOR3 enemyPosition);

	bool IntersectRayAABB(const D3DXVECTOR3& rayStart, const D3DXVECTOR3& rayDir, const D3DXVECTOR3& boxMin, const D3DXVECTOR3& boxMax, float& tMin, float& tMax);

	//��Q���̖W�Q����
//	bool IsBlockedByObstacle(const D3DXVECTOR3& rayStart, const D3DXVECTOR3& rayDir, float rayLength, CObject* pObstacleTop);

	//�����̕����l�v�Z
//	float CalculateDistanceSquared(const D3DXVECTOR3& screenPos, float screenWidth, float screenHeight);



private:
	D3DXVECTOR3 m_posV;//���_
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	int m_nShakeFlame;
	float m_fMag;


	static float m_Screen_Width;
	static float m_Screen_Height;
	bool m_CameraType = false;

	static D3DXVECTOR3 CameraPos;

	////�ȉ�"��{��3D"�̂�
	//CLockOnUI* m_LockOnUI[8] ={};	       //--���b�N�I��
	//CLockOnUIMain* m_LockOnUI_Main;//---�o���b�g���b�N�I��
	

	int m_nCntFrane = 0;
	float DebuCameraLength = 300.0f;
};






#endif