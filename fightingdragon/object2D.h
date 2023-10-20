//============================
//
//オブジェクト2D処理(object2D.h)
//Author:早川 友貴
//
//============================
#ifndef _OBJECT2D_H_   //このマクロ定義がされていなかったら
#define _OBJECT2D_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"

class CObject2D : public CObject
{
public:
	CObject2D();
	~CObject2D();

	static HRESULT Load(int nTex);
	static void Unload(void);

	static CObject2D *Create(D3DXVECTOR3 pos,float fRot,int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);
	void SetLife(int nLife);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	int GetLife(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);


protected:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							//位置情報
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_rot;							//傾き
	D3DXCOLOR m_col;							//色
	int m_nLife;								//体力

private:
	static CObject2D *m_apObject[320];
};


#endif
