//============================
//
//アニメーションオブジェクト処理(anim.h)
//Author:早川 友貴
//
//============================
#ifndef _ANIM_H_   //このマクロ定義がされていなかったら
#define _ANIM_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object2D.h"

class CAnim : public CObject2D
{
public:
	CAnim();
	~CAnim();

	static CAnim *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DrawAnim(void);

private:
	int m_nCounterAnim;							//アニメーションカウンターを加算
	int m_nPatternAnim;							//アニメーションパターン

	float m_fAngle;								//対角線の角度
	float m_fLength;							//対角線の長さ

	float m_pos;
	float m_move;

};


#endif
