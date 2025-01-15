//============================================================================================
//
//フェードに関する宣言や構造体[fade.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _FADE_H_

#define _FADE_H_

#include "main.h"
#include "object2D.h"
#include "scene.h"

class CFade:public CObject2D
{
public:
	CFade(int nPriority = CObject::LAYERINDEX_FADE);
	~CFade();

	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,//何もしていない状態
		FADE_IN,	//フェードイン状態
		FADE_OUT,	//フェードアウト状態
		FADE_MAX

	}FADE;


	//プロトタイプ宣言
	HRESULT Init(CScene::MODE ModeNext);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetFade(CScene::MODE ModeNext);

	FADE GetFade(void);

	//頂点格納
	void InputpVtx()override;

private:
	int m_nTime;//おいおい必要
	FADE m_fade;
	CScene::MODE m_ModeNext;//次のモード
	float m_ColorA;
	int m_fadeCnt;//とりあえず

	bool m_SetMode;//モード設定したか

	//うまくいかなかったとき用
	LPDIRECT3DTEXTURE9 m_pTexture2;//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff2;//頂点バッファ
	//テクスチャや頂点座標などの保持
	VERTEX_2D m_pVtx2[BASE_INDEX];


	bool bBulletSet = false;
};




#endif