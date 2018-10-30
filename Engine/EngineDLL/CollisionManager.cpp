#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	listsOfEntities = new vector<list<Entity>>[Tags::Count];

	for (int i = 0; i < Count; i++)
		for (int j = 0; j < Count; j++)
			tagsRelation[i][j] = false;
}

void CollisionManager::SetRelation(int tag1, int tag2)
{
	if(tag1 >= tag2)
		tagsRelation[tag1][tag2] = true;
	else
		tagsRelation[tag2][tag1] = true;
}

void CollisionManager::DetectCollisions()
{
	for (int i = 0; i < Count; i++)
		for (int j = 0; j < Count - i; j++)
			if (tagsRelation[i][j])
				MakeTheRealDetection(i, j);
}

void CollisionManager::MakeTheRealDetection(int index1, int index2)
{
	// If any of the lists has no Entity just return.
	if ((listsOfEntities + index1)->size == 0
	 || (listsOfEntities + index2)->size == 0)
		return;

	for (int i = 0; i < (listsOfEntities + index1)->size; i++)
	{
		for (int j = 0; j < (listsOfEntities + index2)->size; j++)
		{
			// Here implement the teacher's explanation on the images.
		}
	}
}