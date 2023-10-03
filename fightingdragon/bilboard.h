//============================
//
//�r���{�[�h����(bilboard.h)
//Author:���� �F�M
//
//============================
#ifndef _BILBOARD_H_   //���̃}�N����`������Ă��Ȃ�������
#define _BILBOARD_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object3d.h"

#define MAX_TEX (3)		//�ő�e�N�X�`����

class CBilboard : public CObject
{
public:
	CBilboard();
	~CBilboard();

	static HRESULT Load(void);
	static void Unload(void);
	static CBilboard *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture0;				//�ǂ݂��ޗp�e�N�X�`�����
	LPDIRECT3DTEXTURE9 m_pTexture1;						//���蓖�ėp�e�N�X�`�����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;								//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ʒu
	D3DXVECTOR3 m_rot;		//�X��
	D3DXCOLOR m_col;		//�F
};


#endif



