//============================================================================================
//
//���C����\�����鏈���̊֌W[line.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "object3D.h"

#include "main.h"


//#define MAX_LINE	(6000)

class Cline:public CObject3D
{
public:
	Cline(int nPriority = CObject::LAYERINDEX_LINE);
	~Cline() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static Cline* Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);//object����
	void SetLineData(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_endPos;

	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	int m_Life;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	D3DXMATRIX m_mtxWorld;  // ���[���h�}�g���b�N�X
//	bool g_bLineDisplay;                    // ���C����\�����邩
};


#endif // !_ENEMY_H_