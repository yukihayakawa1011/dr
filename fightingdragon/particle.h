//============================
//
//パーティクル処理(particle.h)
//Author:早川 友貴
//
//============================
#ifndef _PARTICLE_H_   //このマクロ定義がされていなかったら
#define _PARTICLE_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "bilboard.h"

//マクロ定義
#define MAX_PARTICLE (128)		//パーティクル最大数
#define USE_PARTICLE (20)		//使用しているパーティクル数
#define USE_RADIUS	 (10.0f)		//使う半径

class CParticle : public CBilboard
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_DAMAGE,		//ダメージ
		TYPE_WINDOW,		//ガラス
		TYPE_MAX
	}TYPE;

	CParticle();
	CParticle(D3DXVECTOR3 pos);
	~CParticle();

	static void *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nLife;																								//体力
	static void ParticleRed(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife);		//赤いパーティクル
	static void ParticleWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife);		//ガラスパーティクル

	static CEffect *pEffect;

};


#endif




