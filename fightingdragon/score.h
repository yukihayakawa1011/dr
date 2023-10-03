//===============================
//
//�X�R�A����(score.h)
//Author:���� �F�M
//
//===============================
#ifndef _SCORE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_PLACE (4)		//�X�R�A�̌���
#define MAX_SCORE (128)		//�X�R�A�̍ő吔
#define POS_SCORE  (75.0f)  //�X�R�A�̕������߂�

//�N���X��`
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
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	int m_nScore;								//�X�R�A�̒l
	float m_nWindth;							//���̒l
	float m_nHeight;							//�����̒l
	CNumber *m_pNumber[NUM_PLACE];				//�����̏��
};

#endif

