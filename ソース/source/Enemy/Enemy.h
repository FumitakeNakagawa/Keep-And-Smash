#pragma once
#include	<memory>
#include	<list>

class AI : public Base_Player
{
private:
	float speed;
	Vector3 posGoal;			//ƒS[ƒ‹À•W
	const float GoalRange = 25.0f;		//ƒS[ƒ‹‚ğç‚é‹——£‚Ì”ÍˆÍ
	static const int GatherTime = 120;
	static const int SmashTime = 60;
	void Smash() { }
	void Gathers(){}

public:
	void Initialize()override;
	float Update(iexMesh* mesh)override;
	void Update(iexMesh* mesh, Base_Player* player, PackManager* pack);
	void NearObject();
	void FarObject();
	void Move(iexMesh* mesh, Base_Player* player, PackManager* pack);
	void Render()override;
	bool ColCircle(const Vector3& pos_A, const float rad_A, const Vector3& pos_B, const float rad_B);
};