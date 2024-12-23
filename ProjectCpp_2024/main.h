//=========================================================
//
// main.cppで使う関数[main.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MAIN_H

#define _MAIN_H//二重インクルード防止


#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include <cmath>
#include <vector>
#define DIRECTINPUT_VERSION (0x0800)//警告対策

#include "dinput.h"//入力

#include "xinput.h"
#include <iostream>



#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要


//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")	//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//コンポーネット（部品）使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要




//マクロ定義
#define CLASS_NAME		("WindowsClass")
#define WINDOW_NAME		("Mini-Tank!")
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//頂点情報を設定
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//3D用頂点座標(頂点座標{3D},法線、頂点フォーマット２つ)

#define GAME_FPS		(60)

//基本4頂点
#define BASE_INDEX	(4)




//頂点座標構造体の定義
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	//テクスチャ座標
};

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;			//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;



//ウィンドウプロシー
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int GetFPS(void);

// ウィンドウの幅と高さを取得する関数

void GetWindowSize(HWND hWnd, int& width, int& height);

#endif