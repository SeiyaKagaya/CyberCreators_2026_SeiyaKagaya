//=========================================================
//
//リザルト画面で使う変数、宣言、構造体[font.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _FONT_H_

#define _FONT_H_//二重インクルード防止

#include"main.h"
#include <d3d9.h>

class CFont
{
public:
	CFont();
	~CFont();

	// フォントの種類
		//--------------------フォントのラベル的な
		typedef enum
	{
		FONT_DOKIDOKI = 0,//どきどきファンタジア
		FONT_AKABARASINDELERA,//赤薔薇シンデレラ
		FONT_KEIFONT,//けいふぉんと
		FONT_SOUKOUMINCHO,//装甲明朝
		FONT_KIRARAJI04,//きらら字04
		FONT_ONRYOU,//怨霊フォント
		FONT_GENSIN,//げんしん
		FONT_DIGITAL,//DIGITAL
		FONT_MILITARY,
		FONT_GENKAI,
		FONT_MAX,
	}FONT;

		static const int MAXFONT = FONT_MAX;//---フォントの数


		//フォント構造体
		typedef struct
		{
			const char* pFilePass;	// ファイルパス
			const char* pFontName;	// フォントネーム
		} FONTINFO;


		//プロトタイプ宣言
		void InitText(void);
		void UninitText(void);
		//テキスト書き出し処理
		static void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);



		

private:

	static LPD3DXFONT m_pFont_Comment[MAXFONT];//フォントへのポインタ
	static LPD3DXFONT m_pFont_World[MAXFONT];//フォントへのポインタ

	// フォントの情報
//-------------------------------------------
//　　"ファイルパス","フォント名"
//-------------------------------------------
	static FONTINFO m_FontInfo[FONT_MAX];
};






#endif // !_TEXT_H_