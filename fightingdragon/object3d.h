//============================
//
//3Dオブジェクト処理(object3d.h)
//Author:早川 友貴
//
//============================
#ifndef _OBJECT3D_H_   //このマクロ定義がされていなかったら
#define _OBJECT3D_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"

class CObject3d : public CObject
{
public:
	CObject3d();
	~CObject3d();

	static HRESULT Load(void);
	static void Unload(void);
	static CObject3d *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	float GetHeight(D3DXVECTOR3 pos);

	D3DXCOLOR GetColor(void);
	void SetColor(D3DXCOLOR col);

	bool GetShowEnemy(void);
	void SetShowEnemy(bool ShowEnemy);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ情報
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//位置
	D3DXVECTOR3 m_rot;		//傾き

	D3DXCOLOR m_objectcol;	//オブジェクトの色
	int m_TimeBlinking;		//点滅時間

	bool m_bShowEnemy;		//敵を移すかどうか

	static CObject3d *m_pObject[320];
};


#endif


