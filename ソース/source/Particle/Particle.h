#pragma once

class Particle
{
public:
	/* mass:�d�� repulsion: ���C�W�� */
	static void Collide(Vector3*pos1, Vector3*move1, float mass1, Vector3*pos2, Vector3*move2, float mass2, float repulsion, float time);
	static void Collide(Vector3*pos, Vector3*move, float mass, float repulsion, float time, Vector3*normal);
	static void Collide(Vector3*pos, Vector3*move1, Vector3*move2, float mass, float repulsion, float time, Vector3*normal);

	//�ǔ���
	static float WallDistJudg(iexMesh* mesh, Vector3&pos, Vector3&v, float r);
	//�ړ��ǔ���
	static Vector3 MoveWallJudg(iexMesh* mesh, const Vector3&pos, const Vector3&move, float r);
};