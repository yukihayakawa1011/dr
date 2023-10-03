//============================
//
//�i���o�[����(number.h)
//Author:���� �F�M
//
//============================
#ifndef _NUMBER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "object2D.h"

//�}�N����`
#define NUMBER_PUTURN	(0.1f)	//�����̃e�N�X�`���̃p�^�[����

//�����̃N���X��`
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
	int m_nNumber;								//���_�o�b�t�@�ŕ\������ԍ�

};


#endif

