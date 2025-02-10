//============================================================================================
//
//テキスト表示する処理[font.cpp]
// Author seiya kagaya
//
//============================================================================================
#include <stdarg.h>  // 可変長引数関連のヘッダ
#include "font.h"
#include <stdio.h>
#include "renderer.h"
#include "manager.h"

LPD3DXFONT CFont::m_pFont_Comment[MAXFONT] = {};//フォントへのポインタ
LPD3DXFONT CFont::m_pFont_World[MAXFONT] = {};//フォントへのポインタ

// フォントの情報
//-------------------------------------------
//　　"ファイルパス","フォント名"
//-------------------------------------------
// フォントの情報
CFont::FONTINFO CFont::m_FontInfo[CFont::FONT_MAX] = 
{
	{"DATA\\FONT\\DokiDokiFantasia.otf", "どきどきファンタジア"},
	{"DATA\\FONT\\akabara-cinderella.ttf", "赤薔薇シンデレラ"},
	{"DATA\\FONT\\keifont.ttf", "けいふぉんと"},
	{"DATA\\FONT\\SoukouMincho.ttf", "装甲明朝"},
	{"DATA\\FONT\\kiraraji04.ttf", "きらら字04"},
	{"DATA\\FONT\\onryou.TTF", "怨霊"},
	{"DATA\\FONT\\ZH-CN.TTF", "SDK_SC_Web Heavy"},
	{"DATA\\FONT\\DS-DIGI.TTF", "DS-Digital"},
	{"DATA\\FONT\\rycsminStencily.ttf", "略字超少明朝ステンシル風"},
	{"DATA\\FONT\\genkai-mincho.ttf", "源界明朝"},
	
	
};

//=============================
//コンストラクタ
//=============================
CFont::CFont()
{
}
//=============================
//デストラクタ
//=============================
CFont::~CFont()
{
}

//=============================
//初期化処理
//=============================
void CFont::InitText(void)
{
	UninitText();

	//フォントの読み込みテスト//
	for (int i = 0; i < FONT_MAX; i++)
	{
		LPCSTR font_path = m_FontInfo[i].pFilePass; // ここで各フォントを使用可能に

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
		{
		}
		else
		{
			// フォント読込エラー処理
			MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		}
	}
}
//=============================
//終了処理
//=============================
void CFont::UninitText(void)
{
	for (int i = 0; i < MAXFONT; i++)
	{
		//UIComment表示用フォントの破棄
		if (m_pFont_Comment[i] != nullptr)
		{
			m_pFont_Comment[i]->Release();
			m_pFont_Comment[i] = nullptr;
		}
		//UIComment表示用フォントの破棄
		if (m_pFont_World[i] != nullptr)
		{
			m_pFont_World[i]->Release();
			m_pFont_World[i] = nullptr;
		}
	}
}
//=============================
//UIコメント表示処理
//=============================
void CFont::DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...)
{//...は可変長引数（Variable Arguments）
	
	 //初期化大事
	if (m_pFont_Comment[Font] != nullptr)
	{
		m_pFont_Comment[Font]->Release();
		m_pFont_Comment[Font] = nullptr;
	}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	// RECTの座標をLONGにキャスト
	RECT rect = { static_cast<LONG>(DrawPos.x), static_cast<LONG>(DrawPos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024];

	D3DXCreateFont(EscDevice, FontSize, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT(m_FontInfo[Font].pFontName),//--読み込んだフォントの名前(プロパティのタイトルで分かる)
		&m_pFont_Comment[Font]);

	//D3DXCreateFontの引数の意味

	//D3DXCreateFont(EscDevice,                /* デバイス */
	//	16,                            /* 文字の高さ */
	//	0,                            /* 文字幅 */
	//	FW_NORMAL,                    /* フォントの太さ */
	//	1,                            /* MIPMAPのレベル */
	//	FALSE,                        /* イタリックか？ */
	//	DEFAULT_CHARSET,            /* 文字セット */
	//	OUT_DEFAULT_PRECIS,            /* 出力精度 */
	//	DEFAULT_QUALITY,            /* 出力品質 */
	//	DEFAULT_PITCH | FF_SWISS,    /* フォントピッチとファミリ */
	//	L"ＭＳ Ｐゴシック",                    /* フォント名 */
	//	&lpFont)         /* Direct3Dフォントへのポインタへのアドレス */




	// 可変長引数の処理-------
	va_list args;				 //可変長引数の引数リストを指定する
	va_start(args, Text);		 //va_list を初期化--＞//可変長引数の一つ前の引数を指定
	vsprintf_s(aStr, Text, args);//書式指定文字列を使用して可変長引数から文字列を生成するための安全な関数
	va_end(args);				 //va_start マクロによって開始された可変長引数リストを終了するために使用

	// テキストの描画
	m_pFont_Comment[Font]->DrawText(NULL, aStr, -1, &rect, DT_LEFT/* | DT_WORDBREAK*/, RGBA);



	//使用例！！

	//	DrawTextSet(　座標　, フォントサイズ　, フォント名（ｈ.で作ったラベル的な）, カラー, "打ちたい文字(任意で%d.%f,%s)",(任意で変数));
}
