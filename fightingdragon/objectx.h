//============================
//
//Xファイル処理(objectx.h)
//Author:早川 友貴
//
//============================
#ifndef _OBJECTX_H_   //このマクロ定義がされていなかったら
#define _OBJECTX_H_   //2重インクルード防止のマクロを定義する
#include "manager.h"
#include "main.h"
#include "object.h"

//マクロ定義
#define MAX_OBJECTX  (5)		//オブジェクトXの最大数

class CObjectx : public CObject
{
public:

	typedef struct
	{
		LPD3DXMESH m_pMesh;										//メッシュ
		LPD3DXBUFFER m_pBuffMat;						//頂点情報のマテリアル
		DWORD m_dwNumMat;								//マテリアル
		D3DXMATRIX m_mtxWorld;									//ワールドマトリックス
		LPDIRECT3DTEXTURE9 m_apTexture[10] = {};		//テクスチャへのポインタ
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	}SET_OBJECTX;

	CObjectx();
	~CObjectx();

	static CObjectx *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	/*void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);*/
	void SetLife(int nLife);
	void SetVtxMax(D3DXVECTOR3 VtxMax);
	void SetVtxMin(D3DXVECTOR3 VtxMin);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);
	/*LPDIRECT3DVERTEXBUFFER9 GetBuff(void);*/
	int GetLife(void);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);

private:

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//位置
	D3DXVECTOR3 m_rot;		//傾き
	D3DXCOLOR m_col;							//色
	int m_nLife;								//体力

	SET_OBJECTX m_Objectx;		//モデルの情報

	static SET_OBJECTX Objectx[MAX_OBJECTX];		//モデルの情報

	int m_nTexCnt;		//テクスチャ情報の番号
	
};


#endif


