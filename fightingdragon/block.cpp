//============================
//
//ブロック処理(block.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "bg.h"
//#include "bullet.h"
//#include "explosion.h"
#include "block.h"
#include "renderer.h"
#include "player.h"
#include "mode.h"

//マクロ
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_HEIGHT (20.0f)

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9  CBlock::m_pTexture = {};

//CObject2D *CBlock::m_apBlock = NULL;
//============================
//コンストラクタ
//============================
CBlock::CBlock()
{
	
}

CBlock::CBlock(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//デストラクタ
//============================
CBlock::~CBlock()
{

}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CBlock::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\images.jpg",
		&m_pTexture);

	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CBlock::Unload(void)
{
		//テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}


//============================
//生成処理
//============================
CBlock *CBlock::Create(D3DXVECTOR3 pos, float fRot, int nTex,float fWidth, float fHeight)
{
	CBlock *pBlock;

	//オブジェクト2Dの生成
	pBlock = NEW_DBG CBlock(pos);

	//初期化処理
	pBlock->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////テクスチャの割り当て
	//pBlock->BindTexture(m_pTexture);

	return pBlock;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CBlock::Init(D3DXVECTOR3 pos, float fRot, int nTex,float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObjectx::Init(pos, fRot, nTex,fWidth,fHeight);

	if (nTex == 0)
	{
		//種類を設定
		SetType(CObject::TYPE_BLOCK);
	}
	if (nTex == 1)
	{
		//種類を設定
		SetType(CObject::TYPE_FLOOR);
	}

	if (nTex == 2)
	{
		//種類を設定
		SetType(CObject::TYPE_LONGFLOOR);
	}

	//m_nLife = 100;


	SetPosition(pos);

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CBlock::Uninit(void)
{
	CObjectx::Uninit();
}
//============================
//ポリゴンの更新
//============================
void CBlock::Update(void)
{

}
//============================
//ポリゴンの描画
//============================
void CBlock::Draw(void)
{
	CObjectx::Draw();
}


//===============================
//ブロックの当たり判定
//===============================
bool CBlock::colision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, bool bJump)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	/*int nCntBlock;*/
	bool bLand = false; //着地したかどうか

	/*for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{*/
     	D3DXVECTOR3 pos = GetPosition();

	bJump = pPlayer->GetJump();

	if (bJump == true)
	{//ジャンプが使用されていたら
		if (pPos->y >= pos.y - BLOCK_Y
			&& pPos->y - fHeight <= pos.y + BLOCK_Y)
		{//ブロックのYの範囲内の時,横の当たり判定
			if (pPosOld->x + fWidth <= pos.x - BLOCK_X
				&&pPos->x + fWidth >= pos.x - BLOCK_X)
			{
				pPos->x = pos.x - BLOCK_X - fWidth;
				pMove->x = 0.0f; //移動量を0にする
			}

			if (pPosOld->x - fWidth >= pos.x + BLOCK_X
				&& pPos->x - fWidth < pos.x + BLOCK_X)
			{
				pPos->x = pos.x + BLOCK_X + fWidth;
				pMove->x = 0.0f; //移動量を0にする
			}
		}

		if (pPos->x - fWidth <= pos.x + BLOCK_X
			&& pPos->x + fWidth >= pos.x - BLOCK_X)
		{//ブロックの範囲内の時,縦の当たり判定
			if (pPosOld->y <= pos.y - BLOCK_Y
				&& pPos->y > pos.y - BLOCK_Y )
			{
				bJump = false;
				pPlayer->SetJump(bJump);
				bLand = true;
				pPos->y = pos.y - BLOCK_Y; //ブロックの上に立たせる
				pMove->y = 0.0f; //移動量を0にする
			}

			if (pPosOld->y - fHeight >= pos.y + BLOCK_Y + 30
				&& pPos->y - fHeight <= pos.y + BLOCK_Y + 30)
			{//ブロックより下で範囲内の時
				pPos->y = +pos.y + BLOCK_Y + fHeight + 30;
				pMove->y = 0.0f; //移動量を0にする
			}
		}
	}

	else
	{//ジャンプが使用されていなかったら
		if (pPos->x - fWidth <= pos.x + BLOCK_X
			&& pPos->x + fWidth >= pos.x - BLOCK_X)
		{//ブロックの範囲内の時,縦の当たり判定
			if (pPosOld->y <= pos.y - BLOCK_Y
				&& pPos->y >= pos.y - BLOCK_Y)
			{
				bJump = false;
				pPlayer->SetJump(bJump);
				bLand = true;
				pPos->y = pos.y - BLOCK_Y; //ブロックの上に立たせる
				pMove->y = 0.0f; //移動量を0にする
			}

			if (pPosOld->y - fHeight >= pos.y + BLOCK_Y + 30
				&& pPos->y - fHeight <= pos.y + BLOCK_Y + 30)
			{//ブロックより下で範囲内の時
				pPos->y = pos.y + BLOCK_Y + fHeight + 30;
				pMove->y = 0.0f; //移動量を0にする
			}
		}

		if (pPos->y >= pos.y - BLOCK_Y
			&& pPos->y - fHeight <= pos.y + BLOCK_Y)
		{//ブロックのYの範囲内の時,横の当たり判定
			if (pPosOld->x + fWidth <= pos.x - BLOCK_X
				&&pPos->x + fWidth > pos.x - BLOCK_X)
			{
				pPos->x = pos.x - BLOCK_X - fWidth;
				pMove->x = 0.0f; //移動量を0にする
			}

			if (pPosOld->x - fWidth > pos.x + BLOCK_X
				&& pPos->x - fWidth <= pos.x + BLOCK_X)
			{
				pPos->x = pos.x + BLOCK_X + fWidth;
				pMove->x = 0.0f; //移動量を0にする
			}
		}
	}

	/*SetPosition(pos);*/
//}
	/*}*/
	return bLand;
}
