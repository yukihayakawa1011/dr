//============================
//
//モデル処理(model.h)
//Author:早川 友貴
//
//============================
#ifndef _MODEL_H_   //このマクロ定義がされていなかったら
#define _MODEL_H_   //2重インクルード防止のマクロを定義する
#include "manager.h"
#include "main.h"
#include "object.h"

#define MAX_PART		  (17)		//パーツ最大数

class CModel 
{
public:

	typedef enum
	{
		MODELTYPE_PLAYER = 0,		//プレイヤーのモデル
		MODELTYPE_ENEMY0,			//ザコ敵のモデル
		MODELTYPE_ENEMY1,			//中ボスのモデル
		MODELTYPE_ENEMY2,			//ボスのモデル
		MODELTYPE_MAX
	}MODELTYPE;

	typedef struct 
	{
		LPD3DXMESH m_pMesh;										//メッシュ
		LPD3DXBUFFER m_pBuffMat;						//頂点情報のマテリアル
		DWORD m_dwNumMat;								//マテリアル
		D3DXMATRIX m_mtxWorld;									//ワールドマトリックス
		D3DXMATRIX m_mtxParent;									//親のマトリックス
		LPDIRECT3DTEXTURE9 m_apTexture[10] = {};		//テクスチャへのポインタ
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	}SET_MODEL;

	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight,int nType);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawCol(D3DXCOLOR col);

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetVtxMax(D3DXVECTOR3 VtxMax);
	void SetVtxMin(D3DXVECTOR3 VtxMin);
	void SetBuffMat(LPD3DXBUFFER Mat);
	void SetModelType(MODELTYPE type);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);
	LPD3DXBUFFER GetBuffMat();
	SET_MODEL *GetModel(void);

private:
	
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//傾き

	CModel *m_pParent;		//親モデルへのポインタ

	int nModel;		//何個目のモデルか知る処理

	SET_MODEL Model;		//モデルの情報

	static SET_MODEL pModels[MAX_PART];		//モデルの情報

	int m_nIdx;								//何番目のパーツ

	MODELTYPE m_Type;
};


#endif



