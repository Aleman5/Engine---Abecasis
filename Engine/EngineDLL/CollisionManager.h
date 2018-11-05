#pragma once

/*
Collision Manager Objectives:
	+ Make this class a Singletone (search in internet how to do it).
	+ Make a list for each layer.
	- Check the collision btw each ENTITY of each list with the possible objectives of each of the other lists.
	- If collision = true resolve all the math problems.
	- Tell to both of victims who was the other guy.
*/

#include <list>
#include <vector>
#include "Entity.h"
#include "Tags.h"

using namespace std;

class CollisionManager
{
	static vector<list<Entity>*> listsOfEntities[Count];

	static bool tagsRelation[Count][Count];

	static void MakeTheRealDetection(int index1, int index2);
public:
	static void AddEntity(Entity* entity);
	static void SetRelation(int tag1, int tag2);
	static void DetectCollisions();

	static CollisionManager& getInstance()
	{
		static CollisionManager instance;
		return instance;
	}
	CollisionManager(CollisionManager const&) = delete;
	void operator = (CollisionManager const&) = delete;
private:
	CollisionManager();
	CollisionManager(CollisionManager const&); // Don't implement
	void operator = (CollisionManager const&); // Don't implement
};

