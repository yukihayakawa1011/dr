//============================
//
//ライト処理(light.h)
//Author:早川 友貴
//
//============================
#ifndef _LIGHT_H_   //このマクロ定義がされていなかったら
#define _LIGHT_H_   //2重インクルード防止のマクロを定義する
#include "main.h"

#define MAX_LIGHT (3)		//ライトの最大数

class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	D3DLIGHT9 m_aLight[3];		//ライト情報

	D3DXVECTOR3 m_VecDir[3];		//設定用方向ベクトル
};


#endif


