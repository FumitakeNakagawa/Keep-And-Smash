#pragma once
#include <memory>

class UISceneMain
{
private:
	std::unique_ptr<iex2DObj> frame;		//スコアの枠
	std::unique_ptr<iex2DObj> fontScore;
	std::unique_ptr<iex2DObj> fontTime;
	std::unique_ptr<iex2DObj> subject;		//素材

	int scorePlayer;
	int scoreEnemy;
	int time;
	int timePlayer, timeEnemy;
	int gageTimePlayer, gageTimeEnemy;

public:
	void Initialize();
	void Update(int scorePlayer, int scoreEnemy, int time, int t_player, int t_enemy);
	void Render(iexView* view, const Vector3& posPlayer, const Vector3& posEnemy);

	int GetTime() { return time; }

	int GetPlayerScore() { return scorePlayer; }
	void SetPlayerScore(int s) { scorePlayer = s; }

	int GetEnemyScore() { return scoreEnemy; }
	void SetEnemyScore(int s) { scoreEnemy = s; }

};

class UISceneTitle
{
private:
	std::unique_ptr<iex2DObj> subject1;			//素材1
	std::unique_ptr<iex2DObj> subject2;			//素材2

	bool pushBotton;
	POINT mousePoint;
public:
	void Initialize();
	void Update(bool botton, POINT mousePoint);
	void Render();
};

class UISceneResult
{
public:
	enum
	{
		NON,		//何もボタンとカーソルがあっていない
		RETRY,		//RETRYボタン
		TITLE,		//TITLEボタン
	};
private:
	std::unique_ptr<iex2DObj> subject1;
	std::unique_ptr<iex2DObj> subject2;
	std::unique_ptr<iex2DObj> subject3;
	std::unique_ptr<iex2DObj> fontScore;
	std::unique_ptr<iex2DObj> character;

	int botton;
	int scorePlayer;
	int scoreEnemy;
	POINT mousePoint;
public:
	void Initialize(int ps,int es);
	void Update(int b, POINT mousePoint);
	void Render();
};