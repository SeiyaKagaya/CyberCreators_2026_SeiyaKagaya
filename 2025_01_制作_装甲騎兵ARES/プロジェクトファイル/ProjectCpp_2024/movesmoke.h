////=========================================================
////
//// movesmoke�Ŏg���֐�[movesmoke.h]
//// Author seiya kagaya
////
////=========================================================
//#ifndef _MOVESMOKE_H
//#define _MOVESMOKE_H//��d�C���N���[�h�h�~
//
//#include "Object_billboard.h"
//#include "d3dx9.h"//�`�ʏ����Ɏg��
//#include "main.h"
//
//class CMoveSmoke : public CObjectBillBoard
//{
//public:
//
//	static const int EX_WIDE = 150;
//	static const int EX_HEIGHT = 150;
//
//	const int START_LIFE = 120;
//	const int DIVISION_NUMBER = 8;	//�e�N�X�`��������
//
//	static const int  PRINTSIZE_X = 120;
//	static const int  PRINTSIZE_Z = 120;
//
//
//	CMoveSmoke(int nPriority = CObject::LAYERINDEX_ReflectEffect);//�R���X�g���N�^
//	~CMoveSmoke() override;//�f�X�g���N�^
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//
//	static CMoveSmoke* Create(D3DXVECTOR3 Pos);//object����
//
//	void SetPos_Rot(D3DXVECTOR3 Pos);
//
//	//���_�i�[
//	void InputpVtx()override;
//
//
//private:
//
//	int m_nLife;//�����ŏ���
//
//	int m_nPatternAnim;//����
//
//	int m_nDelay;
//
//	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	int m_nACnt = 100;
//};
//
//#endif