//============================
//
//ビルボード処理(bilboard.h)
//Author:早川 友貴
//
//============================
#ifndef _BILBOARD_H_   //このマクロ定義がされていなかったら
#define _BILBOARD_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object3d.h"

#define MAX_TEX (3)		//最大テクスチャ数

class CBilboard : public CObject
{
public:
	CBilboard();
	~CBilboard();

	static HRESULT Load(void);
	static void Unload(void);
	static CBilboard *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture0;				//読みこむ用テクスチャ情報
	LPDIRECT3DTEXTURE9 m_pTexture1;						//割り当て用テクスチャ情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	D3DXMATRIX m_mtxWorld;								//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//位置
	D3DXVECTOR3 m_rot;		//傾き
	D3DXCOLOR m_col;		//色
};


#endif



