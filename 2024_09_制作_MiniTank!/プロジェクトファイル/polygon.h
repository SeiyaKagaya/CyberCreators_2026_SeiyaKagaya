//=========================================================
//
// polygon.cpp�Ŏg���֐�[polygon.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _POLYGON_H
#define _POLYGON_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CPolygon : public CObject2D
{
public:
	static const int POLYGON_SIZE = 100;//�T�C�Y

	CPolygon(int nPriority=CObject::LAYERINDEX_POLYGON);//�R���X�g���N�^
	~CPolygon() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPolygon* Create();//�I�u�W�F�N�g����
private:

	int m_nCounterAnim = 0;		//�A�j��Counter
	int m_nDirectionMove = 0;	//����//0���E����1����
	int m_nPatternAnim = 0;		//�p�^�[���ԍ�
};

#endif