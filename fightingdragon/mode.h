//============================
//
//モード処理(mode.h)
//Author:早川 友貴
//
//============================
#ifndef _MODE_H_   //このマクロ定義がされていなかったら
#define _MODE_H_   //2重インクルード防止のマクロを定義する
#include "manager.h"
#include "main.h"

class CParticle;
class CPlayer;
class CExplosion;
class CEffect;
class CAbg;
class CScore;
//class CTime;
class CEnemy;
class CBlock;
class CCamera;
class CLight;
class CObjectx;
class CModel;
class CInfection;
class CObject3d;
class CPause;

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	static CTitle *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ

private:
	

};

class CStory : public CScene
{
public:
	CStory();
	~CStory();

	static CStory *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ

private:


};

class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	static CTutorial *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ

private:


};

class CGame : public CScene
{
public:
	CGame();
	~CGame();

	static CGame *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
	static CPlayer *GetPlayer(void);
	static CPlayer *GetPlayerMirror(void);
	static CExplosion *GetExplosion(void);
	static CEnemy *GetEnemy(void);
	static CAbg *GetAbg(void);
	static CEffect *GetEffect(void);
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CBlock *GetBlock(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CObjectx *GetObjectx(void);
	static CModel *GetModel(void);
	static CInfection *GetInfection(void);
	static CObject3d *GetObject3d(void);

private:
	static CPlayer *m_pPlayer;					//プレイヤーの情報
	static CPlayer *m_pPlayerMirror;			//プレイヤーミラーの情報
	static CExplosion *m_pExplosion;			//爆発の情報
	static CEnemy *m_pEnemy;					//敵情報
	static CAbg *m_pAbg;						//多重背景情報
	static CEffect *m_pEffect;					//エフェクト情報
	static CScore *m_pScore;					//スコア情報
	static CTime *m_pTime;						//タイム情報
	static CBlock *m_pBlock;					//ブロック情報
	static CCamera *m_pCamera;					//カメラ情報
	static CLight *m_pLight;					//ライト情報
	static CObjectx *m_pObjectx[USE_OBJECTX];	//オブジェクト情報
	static CModel *m_pModel;					//モデル情報
	static CInfection *m_pInfection;			//感染情報
	static CObject3d *m_pObject3d;				//オブジェクト3d情報
	static CPause *m_pPause;					//ポーズの情報
	bool m_bPause;								//ポーズ状態のON/OFF
};

class CResult : public CScene
{
public:
	CResult();
	~CResult();

	static CResult *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
};

class CGameOver : public CScene
{
public:
	CGameOver();
	~CGameOver();

	static CGameOver *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
};



#endif


