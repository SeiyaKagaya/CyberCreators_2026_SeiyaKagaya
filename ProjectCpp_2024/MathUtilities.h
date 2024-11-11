//=========================================================
//
// ���܂��̐��l�v�Z���s���֐�[MathUtilities.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MATH_H

#define _MATH_H//��d�C���N���[�h�h�~
#include <Windows.h>
#include <d3dx9.h>
#include "object.h"

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <queue>

class  COBB//OBB�p
{
public:
	 COBB();
	~ COBB();
protected:
	
public:
	D3DXVECTOR3 m_Direct[3];   // �����x�N�g��
	D3DXVECTOR3 m_Pos;              // �ʒu
	float m_fLength[3];             // �e�������̒���

	D3DXVECTOR3 GetDirect(int elem);   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen(int elem);          // �w�莲�����̒������擾
	D3DXVECTOR3 GetPos();             // �ʒu���擾
	void SetPos(const D3DXVECTOR3& pos);

};

class CMathProc//�v�Z�N���X
{
public:
	CMathProc();
	~CMathProc();

	//�����蔻��f�[�^
	typedef struct
	{
		bool bHit;//����������
		int targetIndex;//����̃C���f�b�N�X(�v���C�I���e�B����̔ԍ�)
	//	bool SpecialHit;


		//�C��
		D3DXVECTOR3 ResultDistance;//�����蔻��ɓǂ݈ړ����������Ƃ��ɒl������
		D3DXVECTOR3 HitAngle;//X.Y.z��1.-1�Ŕ���
		D3DXVECTOR3 ContactPoint; // �ڐG�_�̍��W
		D3DXVECTOR3 ReflectionVector;//���˃x�N�g���i�[
	}CollisionData;


	//�v�Z�����΂���Ȃ̂ŃN���X�������Ďg��Ȃ�

	//�~�`�����蔻��
	static	CollisionData CheckCircleCollision(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller,int nID);//�����蔻�茋�ʂƃC���f�b�N�X��Ԃ�

		//���^�����蔻��3D
	static	CollisionData CheckBoxCollision_3D(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType,CObject::LAYERINDEX TargetLayer,D3DXVECTOR3 Mymove,void* pCaller);//�����蔻�茋�ʂƃC���f�b�N�X��Ԃ�

		//���^�����蔻��2D
	static	CollisionData CheckBoxCollision_2D(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType);//�����蔻�茋�ʂƃC���f�b�N�X��Ԃ�

	//��]
	static D3DXVECTOR3 ConversionXfireRot3(D3DXVECTOR3 fRot);

	static float ConversionRot2(float NowRot, float fTargetRot);
	

	// OBB��OBB�̓����蔻��
	static bool ColOBBs(COBB& obb1, COBB& obb2, D3DXVECTOR3* contactPoint);

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	static FLOAT LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3 = 0);

	// �ŏ��������ƍŏ��H�����ݐ[�����g�p���ĐڐG�_���v�Z
	static D3DXVECTOR3 CalculateContactPoint(COBB& obb1, COBB& obb2, D3DXVECTOR3& minSepAxis, float minPenetration);

	// �Փˌ�̔���������ǉ�
	static void ResolveCollision(COBB& obb1, COBB& obb2, const D3DXVECTOR3& minSepAxis, float minPenetration);

	static CollisionData CheckCircleCollision_Cancel(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller);

	static bool AvoidInternalSpawn_3D_BoxCollision(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);
	

	//�����m�����蔻��(player/enemy�ϓ�����)
//	static CollisionData CheckCircleCollision_Cancel(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);

	//3Dobject�������h�~����//true�œ����ɂ��锻��
	//static bool AvoidInternalSpawn_3D_BoxCollision(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength,CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller);



//	static void 


	//-----------------------------------------------------------------------------------------------------------------
	static const int GRIDROW = 8;//����
	static const int GRIDCOL = 11;//�悱
	static const int  GRIDLEGTH = 300;//GRID�̕ӂ̒���
	static const int SHOTPOINUM = 8;

	typedef struct
	{
		int x, y;
	} Point;

	typedef struct
	{
		bool bBlock; // ��Q���̗L��
		int Num;     // �X�^�[�g����̋���
		int ObjectNum;//���ݔԍ�
		Point ParemtPoint;//�e�̈ʒu
	} Cell;

	
	static int dx[4]; // �㉺���E�̈ړ�
	static int dy[4];
	
	// �L���ȍ��W���ǂ������m�F����֐�
	static bool isValid(int x, int y);

	// ���D��T���iBFS�j�����s����֐�
	static void bfs(Point start, Point goal);

	// CSV�t�@�C���ɏ����o���֐�
	static void writeToCSV(const char* filename);

	//�Z����Ԋi�[
	static void SetCell(Cell pCell[GRIDROW][GRIDCOL]);


	//--------------------------------------------------
	//Point���W���畨�̔ԍ��擾
	static int GetObjectNumfromPoint(Point point);
	//���̔ԍ�����point���W�擾
	static Point GetPointfromObjectNum(int ObjectNum);
	//--------------------------------------------------

	//�Z���̏��
	static Cell GRID[GRIDROW][GRIDCOL];

	static int RouteTable[GRIDROW* GRIDCOL][GRIDROW * GRIDCOL];

	static D3DXVECTOR3 m_ShotPos[SHOTPOINUM];//���E�s�ǎ��ˌ��ʒu�A�ő�4�ӏ�



	//------------------------------------------------
	//
	//++���������c�W��11�̃}�X�̎��_��
	//88�n�_����88�n�_�܂ł̌o�H
	//�@�@7744���[�g���Z�o����
	//���[�g�����̂܂܎g�p�͖���(�d��)�̂Ōo�H�e�[�u��������
	//
	//++�[�x�����ɃS�[������X�^�[�g�܂ł��ǂ�A���̊Ԃ̒n�_���o�H�e�[�u���ɑł�����ł䂭

	//�ŒZ���[�g�Z�o
	static void RouteTableSet(Point StartPoint, Point GoalPoint);
	

	//CSV��������
	static void DRAWCSV( const char* filename);

	//CSV��������
	static void LoadRouteCSV(const char* filename);


	//����̈ʒu�ԍ��Ǝ����̈ʒu�ԍ��𑗂�A���ɐi�ވʒu�ԍ���Ԃ������B(-100�̂Ƃ��̓S�[���ɂ������B���Ă��邱�ƂɂȂ�)
	static int GetNextMoveGridNum(int PartnerGridNum, int MyGridNum);

	//object�Ɍ��݂̈ʒu�ԍ�����ɕێ������A������Q�Ƃ��ړ��̗L����Gcpp�ɔ��f������

	//���E�s�ǎ��ˌ��ʒu
	static void LoadShotPoint(const char* filename);

	////���E�s�ǎ��ˌ��擾--���������ԋ߂��n�_�̃����_���ɃY�����ʒu��n��
	static D3DXVECTOR3 GetShotPos(D3DXVECTOR3 MyPos);


	// �\�������_���v�Z����v�Z
	//static D3DXVECTOR3 PredictIntersection(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMove, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove);

	
	//�e���\���Ə�
	static CObject::DATA FCS_TrajectoryPredictionAiming(D3DXVECTOR3 MyPos, float BulletSpeed, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove);
	
	//�����Ƒ���̊Ԃ̏�Q������
	static CollisionData AdjustMyPosToCollision_Partner(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMin, D3DXVECTOR3 MyMax,D3DXVECTOR3 TargetPos,float MaxLength,CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);


private:  
	

};

#endif



//�����蔻�胁��
// 
//    ballet-->player/enemy                   OBB���m�Փˁ@��

//    ballet-->StageWall/StageBlock          AABB���m�Փ�  ��
 
//�@�@player<-->enemy                        �@�����m�Փ�  ��

//�@  player/enemy-->StageWall/StageBlock    AABB���m�Փ�  ��    �X�ɘA���Œu�����������p�ɓ����蔻����蔠��ݒu
