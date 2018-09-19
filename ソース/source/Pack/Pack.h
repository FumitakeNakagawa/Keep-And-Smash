#pragma once

#include	"iextreme.h"
#include	"..\\Sphere.h"
#include	<memory>
#include	<list>
#include	<vector>
#include	"..\\Player\Player.h"


class Pack;
class UISceneMain;


//マネージャークラス
class PackManager
{
	std::list<std::unique_ptr<Pack>> padList;


	struct
	{
		Vector3 pos;
		Vector3 move;
	}offset[4];
	int nextAppend;

	int timer;

public:

	void Initialize();
	void Update(Vector3 move, Sphere sphere, Base_Player::State* state, iexMesh* mesh, UISceneMain& ui);
	void Render();
	void Append(std::list<std::unique_ptr<Pack>>::iterator* it, Vector3 p1, Vector3 p2, Vector3 m1, Vector3 m2);
	void Append();

	bool BreakUp(std::list<std::unique_ptr<Pack>>::iterator* it, Sphere s1, Base_Player::State state);

	void Collide(Vector3*pos1, Vector3*move1, float mass1, Vector3*pos2, Vector3*move2, float mass2, float repulsion, float time);
	bool ColCircle(Vector3 pos_A, const float rad_A, Vector3 pos_B, const float rad_B);
	bool ColCircle2(Vector3& pos_A, const float rad_A, Vector3& pos_B, const float rad_B);

	std::list<std::unique_ptr<Pack>>& GetList() { return padList; }

};



//パック(玉クラス)
class Pack
{
	static std::vector<std::unique_ptr<iexMesh>>	mesh;

	Vector3 pos, rot, scale;
	Vector3 move, velocity;
	int level;

	int step;
	Sphere sphere;

	void Collide(Vector3*pos, Vector3*move, float mass, float repulsion, float time, Vector3*normal);
	bool ColWall(iexMesh*mesh);
public:
	void Initialize();
	void Initialize(Vector3 p, Vector3 m);
	void Initialize(Vector3 p,Vector3 m,int l);
	bool Update(iexMesh* mesh);
	void Render();

	void SetPos(Vector3& pos) { this->pos = pos; }
	Vector3& GetPos() { return pos; }
	Vector3& GetScale() { return scale; }
	Vector3& GetMove() { return move; }
	Sphere& GetSphere() { return sphere; }
	void Gather(Sphere& s1,Pack& pack);

	int GetLevel() { return level; }

	static void ResizeModelContainer(int num) { mesh.resize(num); }
	static void LoadMesh(char* filename,int n) { mesh[n] = std::make_unique<iexMesh>(filename); }
	static void ReleaseMesh(int n) { mesh[n].reset(); }


};