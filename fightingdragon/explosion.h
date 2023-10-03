//============================
//
//爆発処理(explosion.h)
//Author:早川 友貴
//
//============================
#ifndef _EXPLOSION_H_   //このマクロ定義がされていなかったら
#define _EXPLOSION_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "bilboard.h"

class CExplosion : public CBilboard
{
public:
	CExplosion();
	CExplosion(D3DXVECTOR3 pos);
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DrawAnim(void);

private:
	int m_nCounterAnim;							//アニメーションカウンターを加算
	int m_nPatternAnim;							//アニメーションパターン
	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ
	int m_nLife;								//体力
};


#endif



