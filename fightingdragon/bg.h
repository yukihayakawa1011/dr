//============================
//
//背景処理(bg.h)
//Author:早川 友貴
//
//============================
#ifndef _BG_H_   //このマクロ定義がされていなかったら
#define _BG_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "object2D.h"

class CBg : public CObject2D
{
public:
	CBg();
	~CBg();

	static CBg *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	
	float m_fAngle;								//対角線の角度
	float m_fLength;							//対角線の長さ

	float m_fTex;								//テクスチャの移動分
										
};


#endif

