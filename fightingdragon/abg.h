//============================
//
//オブジェクト2D多重背景(abg.h)
//Author:早川 友貴
//
//============================
#ifndef _ABG_H_   //このマクロ定義がされていなかったら
#define _ABG_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object2D.h"

//前方クラス宣言
class CObject;


//マクロ定義
#define MAX_TEX (3)	//背景の最大数

class CAbg : public CObject
{
public:

	//テクスチャの構造体定義
	typedef struct
	{
		D3DXVECTOR2 m_fTex;		//テクスチャ
		D3DXVECTOR2 m_fMove;	//移動量
		CObject2D	*pObject2d;  //オブジェクトの作成
	}SBG;

	CAbg();
	~CAbg();

	static HRESULT Load(void);
	static void Unload(void);
	
	static CAbg *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX];				//テクスチャのポインタ

private:
	SBG m_apObject[MAX_TEX];						//オブジェクト2Dの変数
};


#endif

