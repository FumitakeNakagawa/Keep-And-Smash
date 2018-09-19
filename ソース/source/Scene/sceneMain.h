//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
#include	"../Pack/Pack.h"
#include	"../Player/Player.h"
#include	"../Enemy/Enemy.h"
#include	"../UI/UI.h"
#include	"../Effect/Effect.h"
#include	<memory>
#include	"sceneResult.h"

class	sceneMain : public Scene
{
private:
	std::unique_ptr<iexView>	view;
	std::unique_ptr<PackManager> pad;
	std::unique_ptr<Base_Player> pl;
	std::unique_ptr<iexMesh> mesh;
	std::unique_ptr <iexMesh>mesh2;
	std::unique_ptr<AI> ai;
	std::unique_ptr<UISceneMain> ui;
	std::unique_ptr<Effect> effect;

	std::unique_ptr<iex2DObj>	manual;
	std::vector<std::unique_ptr<iex2DObj>>	chappy;

	int frame;
	int num;

	int step;
	std::unique_ptr<sceneResult> result;
public:
	~sceneMain();
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画
};


