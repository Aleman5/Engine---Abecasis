#pragma once

/*
Collision Manager Objectives:
	- Make this class a Singletone (search in internet how to do it).
	- Make a list for each layer.
	- Check the collision btw each ENTITY of each list with the possible objectives of each of the other lists.
	- If collision = true resolve all the math problems.
	- Tell to both of victims who was the other guy.
*/

class CollisionManager
{


public:


	CollisionManager();
	~CollisionManager();
};

