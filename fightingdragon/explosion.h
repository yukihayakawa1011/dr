//============================
//
//��������(explosion.h)
//Author:���� �F�M
//
//============================
#ifndef _EXPLOSION_H_   //���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSION_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "bilboard.h"

class CExplosion : public CBilboard
{
public:
	CExplosion();
	CExplosion(D3DXVECTOR3 pos);
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DrawAnim(void);

private:
	int m_nCounterAnim;							//�A�j���[�V�����J�E���^�[�����Z
	int m_nPatternAnim;							//�A�j���[�V�����p�^�[��
	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��
	int m_nLife;								//�̗�
};


#endif



