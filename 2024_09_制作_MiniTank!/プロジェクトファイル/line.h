//============================================================================================
//
//ラインを表示する処理の関係[line.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "object3D.h"
#include "main.h"

class Cline:public CObject3D
{
public:
	static const int LIFE = 2;//寿命

	Cline(int nPriority = CObject::LAYERINDEX_LINE);
	~Cline() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static Cline* Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);//object生成
	void SetLineData(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);

private:
	D3DXVECTOR3 m_pos = {};
	D3DXVECTOR3 m_startPos = {};
	D3DXVECTOR3 m_endPos = {};
	D3DXVECTOR3 m_rot = {};
	D3DXCOLOR m_col = {};
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;
	D3DXMATRIX m_mtxWorld = {};  // ワールドマトリックス
	int m_Life = 0;
};
#endif
