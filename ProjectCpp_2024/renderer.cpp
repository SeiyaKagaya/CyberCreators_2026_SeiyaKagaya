//=======================================================
//
//rendererに関する処理[renderer.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "renderer.h"
//#include "object2D.h"
//#include "polygon.h"
#include "main.h"
#include "manager.h"
//#include "input.h"
#include <stdio.h>

//=============================
//コンストラクタ
//=============================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pCObject = nullptr;
	m_pFont = nullptr;
	m_mesh = false;
}
//=============================
//デストラクタ
//=============================
CRenderer::~CRenderer()
{
}
//=============================
//初期設定
//=============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ
	
	//direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定[決まった形]
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//ゲーム画面サイズ横
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//ゲーム画面サイズ縦
	d3dpp.BackBufferFormat = d3ddm.Format;								//バックバッファの形式
	d3dpp.BackBufferCount = 1;											//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;								//デプスバッファとステンシルバッファを作成

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8/*D3DFMT_D16*/;	//24ビットに変更(Zfight防止)--		//デパスバッファとして１６ビットを使う
	d3dpp.Windowed = bWindow;											//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

		//direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//direct３Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//direct３Dデバイスの生成（描画処理と頂点処理はCPUで行う）
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定//-----------------------------------------------------------------
#if 1
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定


	//アルファブランドの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//D3DXMATRIX matProj;
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 4.0f / 3.0f, 1.0f, 1000.0f); // z-nearを1.0f、z-farを1000.0fに設定
	//m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // 反時計回りの面をカリング

		//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);


	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


#endif

	//デバッグ表示用のフォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont);



	//各種オブジェクトの初期化処理
	return S_OK;
}
//=============================
//終了処理
//=============================
void CRenderer::Uninit()
{

	//direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}
//=============================
//更新処理(全オブジェクト)
//=============================
void CRenderer::Update()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{

			m_pCObject->UpdateAll();//---------------------------------------------------------すべてのオブジェクト更新

			if (keyboard->GetTrigger(DIK_F4) == true)//-----------------メッシュ表示系
			{
				m_mesh = !m_mesh;
				if (m_mesh == false)
				{
					//元の状態
					m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				}
				else if (m_mesh == true)
				{
					//ワイヤーフレームモードの状態
					m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				}
			}
		}
	}
}
//=============================
//描画処理(全オブジェクト)
//=============================
void CRenderer::Draw()
{
	
	CManager* pManager = CManager::GetInstance();


	//画面クリア(バックバッファ＆Zバッファのクリア)
	m_pD3DDevice->Clear(
		0,
		nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(100, 100, 100, 100),
		1.0f,
		0);


	//描画段階
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		


		 pManager->GetCamera()->SetCamera();



		 m_pCObject->DrawAll();

		//シーンの描画
		if (pManager->GetScene() != nullptr)
		{
			pManager->GetScene()->Draw();
		}
	
		//フェード描画
		if (pManager->GetFade() != nullptr)
		{
			pManager->GetFade()->Draw();
		}

//#if _DEBUG

		DrawFPS();
//#else
//#endif // _DEBUG

		//----------------------------------------------------------------------------------------------------------------------------------


		m_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
//=============================
//3Dデバイスの取得
//=============================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}
//=============================
//FPS表示処理
//=============================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];
	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d", GetFPS());

	//テキストの描画
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 15, 15, 255));

}
