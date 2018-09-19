#pragma once
#include	"iextreme.h"
#include	"..\\Sphere.h"
#include	<memory>

class Base_Player
{
public:
	enum class State
	{
		MOVE,	//通常
		SMASH,	//スマッシュ
		SMASH_WAIT,//スマッシュ解除待ち
		GATHER,	//くっつき
		GATHER_WAIT
	};

protected:

	State	state;
	std::unique_ptr<iexMesh> obj;
	Vector3 pos, rot, scale;
	Vector3 move, velocity;
	float pow;
	Sphere sphere;

	int smashTimer;
	int gatherTimer;
	bool smash;
	bool gather;
	int smashStep;

	virtual void Smash() = 0;
	virtual void Gathers() = 0;
public:
	virtual void Initialize()=0;
	virtual float Update(iexMesh* mesh)=0;
	virtual void Render()=0;

	State GetState() { return state; }
	State* GetStateB() { return &state; }
	Vector3& GetPos() { return pos; }
	Vector3& GetMove() { return move; }
	Sphere& GetSphere() { return sphere; }
	float GetPow() { return pow; }
	int GetGatherTimer() { return gatherTimer; }

};


class Player :public Base_Player
{
	
	POINT	oldMousePoint;
	POINT	mousePoint;
	BOOL mouseReverse;
	D3DXMATRIX viewport;
	void Smash();
	void Gathers();
public:
	void Initialize()override;
	float Update(iexMesh* mesh)override;
	void Render()override;
};