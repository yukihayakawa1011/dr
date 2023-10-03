//============================
//
//レンダラー処理(renderer.h)
//Author:早川 友貴
//
//============================
#ifndef _RENDERER_H_   //このマクロ定義がされていなかったら
#define _RENDERER_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	LPDIRECT3D9				m_pD3D;				//Direct3Dのオブジェクトへのポインタ
	LPDIRECT3DDEVICE9		m_pD3DDevice;		//Direct3Dデバイスのポインタ
};

#endif




