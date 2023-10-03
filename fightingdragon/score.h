//===============================
//
//スコア処理(score.h)
//Author:早川 友貴
//
//===============================
#ifndef _SCORE_H_   //このマクロ定義がされていなかったら
#define _SCORE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_PLACE (4)		//スコアの桁数
#define MAX_SCORE (128)		//スコアの最大数
#define POS_SCORE  (75.0f)  //スコアの幅を決める

//クラス定義
class CScore : public CNumber
{
public:

	CScore();
	~CScore();

	static HRESULT Load(void);
	static void Unload(void);

	static CScore *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Add(int nScore);
	int Get(void);
protected:
	
	void SetPos(D3DXVECTOR3 pos, float nWINDTH, float nHeight);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	int m_nScore;								//スコアの値
	float m_nWindth;							//幅の値
	float m_nHeight;							//高さの値
	CNumber *m_pNumber[NUM_PLACE];				//数字の情報
};

#endif

