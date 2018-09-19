#pragma once
#include <memory>

class sceneResult : public Scene
{
public:
	enum
	{
		NON,		//何もボタンとカーソルがあっていない
		RETRY,		//RETRYボタン
		TITLE,		//TITLEボタン
	};

private:
	std::unique_ptr<iexView>	view;
	std::unique_ptr<UISceneResult> ui;

	POINT	mousePoint;
	BOOL mouseReverse;

	int botton;

	int scorePlayer;
	int scoreEnemy;
public:
	~sceneResult();
	//初期化
	bool Initialize(int playerScore, int enemyScore);
	//更新
	void Update();
	//描画
	void Render();
};