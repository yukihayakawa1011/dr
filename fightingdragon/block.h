//============================
//
//�u���b�N����(block.h)
//Author:���� �F�M
//
//============================
#ifndef _BLOCK_H_   //���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "objectx.h"

#define MAX_BLOCK (3)				//�G�̍ő吔

class CBlock : public CObjectx
{
public:
	CBlock();
	CBlock(D3DXVECTOR3 pos);
	~CBlock();

	static HRESULT Load(void);
	static void Unload(void);
	static CBlock *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	/*CBlock GetPos(void);
	void SetPos(D3DXVECTOR3 pos);*/

	bool colision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, bool bJump);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	static CObject2D *m_apBlock;			//�u���b�N

};


#endif





