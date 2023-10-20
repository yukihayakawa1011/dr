//============================
//
//�I�u�W�F�N�g2D����(object2D.h)
//Author:���� �F�M
//
//============================
#ifndef _OBJECT2D_H_   //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2D_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"

class CObject2D : public CObject
{
public:
	CObject2D();
	~CObject2D();

	static HRESULT Load(int nTex);
	static void Unload(void);

	static CObject2D *Create(D3DXVECTOR3 pos,float fRot,int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);
	void SetLife(int nLife);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	int GetLife(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);


protected:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�ʒu���
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_rot;							//�X��
	D3DXCOLOR m_col;							//�F
	int m_nLife;								//�̗�

private:
	static CObject2D *m_apObject[320];
};


#endif
