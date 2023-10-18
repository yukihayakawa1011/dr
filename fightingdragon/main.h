//============================
//
//ポリゴン描画(main.h)
//Author:早川 友貴
//
//============================

#ifndef _MAIN_H_   //このマクロ定義がされていなかったら
#define _MAIN_H_   //2重インクルード防止のマクロを定義する

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION  (0x0800)    //ビルド時の警告対処用マクロ
#include "dinput.h"
#include <assert.h>		//アサート処理

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")     //描画処理に必要
#pragma comment(lib,"d3dx9.lib")    //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")   //DirectXコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")    //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")  //入力処理に必要


//マクロ定義
#define SCREEN_WIDTH  (1280)              //ウインドウの幅
#define SCREEN_HEIGHT  (720)               //ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)  //頂点フォーマット[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //頂点フォーマット[3D]

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;   //頂点座標
	float rhw;         //座標変換用係数(1.0fで固定)
	D3DCOLOR col;      //頂点カラー
	D3DXVECTOR2 tex;   //テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体
typedef struct
{
	D3DXVECTOR3 pos; //頂点情報
	D3DXVECTOR3 nor; //法線ベクトル(向きと方向)
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_3D;

//void DrawFPS(void);

//メモリリーク出力用マクロ
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>  //メモリリーク検出に必要

#ifdef _DEBUG
#define NEW_DBG new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define NEW_DBG new
#endif

#endif // 



