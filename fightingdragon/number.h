//============================
//
//ナンバー処理(number.h)
//Author:早川 友貴
//
//============================
#ifndef _NUMBER_H_   //このマクロ定義がされていなかったら
#define _NUMBER_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "object2D.h"

//マクロ定義
#define NUMBER_PUTURN	(0.1f)	//数字のテクスチャのパターン数

//数字のクラス定義
class CNumber : public CObject2D
{
public:
	CNumber();
	~CNumber();

	static CNumber *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DrawAnim(void);

private:
	int m_nNumber;								//頂点バッファで表示する番号

};


#endif

