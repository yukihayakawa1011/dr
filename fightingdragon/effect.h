//============================
//
//�G�t�F�N�g����(effect.h)
//Author:���� �F�M
//
//============================
#ifndef _EFFECT_H_   //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "object2D.h"

#define MAX_EFFECT (128)	//�G�t�F�N�g�̍ő吔

class CEffect : public CBilboard
{
public:
	CEffect();
	CEffect(D3DXVECTOR3 pos);
	~CEffect();

	/*static HRESULT Load(int nTex);*/
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move,D3DXCOLOR col,int nLife);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col,int nLife);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��
	int m_nLife;								//�̗�
	float m_fRadius;							//���a
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXCOLOR m_col;							//�F
};


#endif



