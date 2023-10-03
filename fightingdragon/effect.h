//============================
//
//エフェクト処理(effect.h)
//Author:早川 友貴
//
//============================
#ifndef _EFFECT_H_   //このマクロ定義がされていなかったら
#define _EFFECT_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "object2D.h"

#define MAX_EFFECT (128)	//エフェクトの最大数

class CEffect : public CBilboard
{
public:
	CEffect();
	CEffect(D3DXVECTOR3 pos);
	~CEffect();

	/*static HRESULT Load(int nTex);*/
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move,D3DXCOLOR col,int nLife);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col,int nLife);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ
	int m_nLife;								//体力
	float m_fRadius;							//半径
	D3DXVECTOR3 m_move;							//移動量
	D3DXCOLOR m_col;							//色
};


#endif



