//==================================================
//
//フェードに関する処理[fade.cpp]
// Author seiya kagaya
//
//==================================================
//#include "main.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
//#include "object3D.h"

//グローバル変数宣言

//=============================
// コンストラクタ
//=============================
CFade::CFade(int nPriority)
{
	m_ColorA = 0.0f;
	m_fade = FADE_IN;
	m_fadeCnt = 0;
	m_SetMode = false;

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//取得
	DATA EscData = GetDATA();

	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	//テクスチャ読み込み
//	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//テクスチャ取得
//	CAllTexture* pTexture = pManager->GetTexture();

//	int texIndex = pTexture->Regist("DATA\\TEXTURE\\FADE.jpg", EscDevice);//テクスチャ登録

//	m_ESCpTexture = pTexture->GetAddress(texIndex);



//	BindTexture(m_ESCpTexture);//設定

	//うまくいかなかったとき
//	m_pTexture2 = m_ESCpTexture;
	
	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_FADE);//設定

}
//=============================
// デストラクタ
//=============================
CFade::~CFade()
{
}
//=============================
// 初期化
//=============================
HRESULT CFade::Init(CScene::MODE ModeNext)
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//取得
	LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff = GetpVtxBuffer();

	if (FAILED(EscDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&ESCpVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	VERTEX_2D* pVtx;
	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新-----------------------------------
	pVtx[0].pos.x = 0.0f;//左上
	pVtx[0].pos.y = 0.0f;//左上
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = SCREEN_WIDTH;//右上
	pVtx[1].pos.y = 0.0f;//右上
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;//左下
	pVtx[2].pos.y = SCREEN_HEIGHT;//左下
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = SCREEN_WIDTH;//右下
	pVtx[3].pos.y = SCREEN_HEIGHT;//右下
	pVtx[3].pos.z = 0.0f;

	pVtx[0].rhw = 1.f;
	pVtx[1].rhw = 1.f;
	pVtx[2].rhw = 1.f;
	pVtx[3].rhw = 1.f;

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	ESCpVtxBuff->Unlock();

	InputpVtx();

	//設定
	BindVtxBuffer(ESCpVtxBuff);

	m_ModeNext = ModeNext;
	
	SetObjectType(CObject::OBJECT_FADE);

	return S_OK;
}
//=============================
// 終了
//=============================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}
//=============================
// 更新
//=============================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//フェードイン状態
			
			if (m_SetMode == false)
			{
			CObject::ReleaseAll();//全オブジェクト開放


				//モード設定(次の画面に移行)
				CManager::SetMode(m_ModeNext);

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				pManager->SetNewBulletAll(CNewBulletALL::Create());

				m_SetMode = true;
			}


			m_ColorA -= 0.05f;	//ポリゴンを透明にしていく

			if (m_ColorA <= 0.0f)
			{
				m_ColorA = 0.0f;

				m_fade = FADE_NONE;	//何もしていない状態
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態

			

			m_ColorA += 0.1f;	//ポリゴンを不透明にしていく

			if (m_ColorA >= 1.0f)
			{
				m_ColorA = 1.0f;

				m_fadeCnt++;//モード移行カウンター

				m_fade = FADE_IN;	//フェードイン状態
			}

			if (m_fadeCnt == 1)
			{//色が薄く残る問題を解決
				m_fadeCnt = 0;
			}

		}

		D3DXCOLOR EscColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_ColorA);
	
		ChangeRGBA(EscColor);
	
		CObject2D::Update();
	
		return;

	}
}
//=============================
// 描画
//=============================
void CFade::Draw(void)
{
#if _DEBUG

	if (m_fade != FADE_NONE)
	{

		if (m_fade == FADE_IN)
		{
			const char* aData = "フェードイン";


			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
		}
		else if (m_fade == FADE_OUT)
		{
			const char* aData = "フェードアウト";

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
		}

	}

#endif // _DEBUG

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// Zの比較方法
	EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Zバッファに書き込まない

	CObject2D::Draw();

	EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Zの比較方法変更
	EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Zバッファに書き込む


}
//=============================
// フェード設定
//=============================
void CFade::SetFade(CScene::MODE ModeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_SetMode = false;
		m_ColorA = 0.0f;
		m_fadeCnt = 0;
		m_ColorA = 0.0f;			//黒いポリゴン(透明)にしておく
		m_fade = FADE_OUT;											//フェードアウト状態に
		m_ModeNext = ModeNext;										//次の画面(モード)を設定

	}
}
//=============================
// 状態取得
//=============================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}
//=============================
// 頂点座標代入
//=============================
void CFade::InputpVtx()
{
	//取得
//	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = 0.0f;//左上
	EscVtx[0].pos.y = 0.0f;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = SCREEN_WIDTH;//右上
	EscVtx[1].pos.y = 0.0f;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = 0.0f;//左下
	EscVtx[2].pos.y = SCREEN_HEIGHT;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = SCREEN_WIDTH;//右下
	EscVtx[3].pos.y = SCREEN_HEIGHT;//右下
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].rhw = 1.f;
	EscVtx[1].rhw = 1.f;
	EscVtx[2].rhw = 1.f;
	EscVtx[3].rhw = 1.f;

	EscVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	EscVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EscVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EscVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetpVtx(EscVtx);

	
}
