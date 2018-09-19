#include "iextreme.h"
#include "..\\system\Framework.h"
#include "..\\UI\UI.h"
#include "sceneResult.h"
#include "sceneTitle.h"
#include "sceneMain.h"

#include	"../Sound/Sound.h"

//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************
bool sceneResult::Initialize(int ps,int es)
{
	//	環境設定
	iexLight::SetFog(800, 1000, 0);

	//	カメラ設定
	view = std::make_unique<iexView>();
	//view->Set(Vector3(0.0f, 40.0f, 50.0f), Vector3(0.0f, -10.0f, -30.0f));

	ui = std::make_unique<UISceneResult>();
	ui->Initialize(ps,es);

	botton = NON;

	//マウス設定
	ShowCursor(FALSE);
	GetCursorPos(&mousePoint);
	mouseReverse = GetSystemMetrics(SM_SWAPBUTTON);

	//勝敗
	if (ps > es)		//勝利
	{
		sound->PlayWAV(SE_WIN);
	}
	else if (ps < es)	//敗北
	{
		sound->PlayWAV(SE_LOSE);
	}
	else if (ps == es)	//引き分け
	{
		sound->PlayWAV(SE_DRAW);
	}

	return true;
}



//*****************************************************************************************************************************
//
//	解放
//
//*****************************************************************************************************************************
sceneResult::~sceneResult()
{

}



//*****************************************************************************************************************************
//
//	更新
//
//*****************************************************************************************************************************
void sceneResult::Update()
{
	//マウス設定
	GetCursorPos(&mousePoint);
	mouseReverse = GetSystemMetrics(SM_SWAPBUTTON);

	if      (mousePoint.x <= 587  && mousePoint.x >= 190  && mousePoint.y <= 955 && mousePoint.y >= 739) botton = RETRY;
	else if (mousePoint.x <= 1333 && mousePoint.x >= 930 && mousePoint.y <= 955 && mousePoint.y >= 739) botton = TITLE;
	else botton = NON;

	//UI更新
	ui->Update(botton, mousePoint);

	//シーン切り替え
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && botton == TITLE)
	{
		sound->PlayWAV(SE_SELECT);

		MainFrame->ChangeScene(new sceneTitle());
	}
	else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && botton == RETRY)
	{
		sound->PlayWAV(SE_SELECT);

		MainFrame->ChangeScene(new sceneMain());
	}
}



//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************
void sceneResult::Render()
{

	//UI描画
	ui->Render();

#ifdef _DEBUG
	char	str[64];
	wsprintf(str, "Mouse pos : %d %d", mousePoint.x, mousePoint.y);
	IEX_DrawText(str, 10, 30, 400, 20, 0xFF000000);
#endif // _DEBUG

}