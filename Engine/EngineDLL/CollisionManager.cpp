#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	//listsOfEntities = new vector<list<Entity>>[Tags::Count];

	/*for (int i = 0; i < listsOfEntities->size; i++)
	{
		listsOfEntities[i] = new list<Entity>();
	}*/

	for (int i = 0; i < Count; i++)
		for (int j = 0; j < Count; j++)
			tagsRelation[i][j] = false;
}

void CollisionManager::AddEntity(Entity* entity)
{
	(listsOfEntities + entity->GetTag()).push_back(entity); // Ask teacher why this is not working
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
	// If any of this lists has no Entity just return.
	if ((listsOfEntities + index1)->size == 0
	 || (listsOfEntities + index2)->size == 0)
		return;

	for (int i = 0; i < (listsOfEntities + index1)->size; i++)
	{
		glm::vec2 col1 = (listsOfEntities + index1)[i]->GetColProps();

		for (int j = 0; j < (listsOfEntities + index2)->size; j++)
		{
			if ((listsOfEntities + index1)[i]->IsStatic() && (listsOfEntities + index2)[j]->IsStatic()) // If both are static don't check collision.
			{
				// Here implement the teacher's explanation on the images.
				glm::vec3 diff = (listsOfEntities + index2)[j]->GetPosition() - (listsOfEntities + index1)[i]->GetPosition();

				int dX = abs(diff.x);
				int dY = abs(diff.y);

				glm::vec2 col2 = (listsOfEntities + index1)[i]->GetColProps();

				if (dX < col1.x / 2 + col2.x / 2
					&& dY < col1.y / 2 + col2.y / 2)
				{
					int pX = (int)(col1.x / 2 + col2.x / 2 - diff.x);
					int pY = (int)(col1.y / 2 + col2.y / 2 - diff.y);

					if (pX > pY) // Vertical Collision
					{
						if (!(listsOfEntities + index1)[i]->IsStatic())
						{
							if (!(listsOfEntities + index2)[j]->IsStatic()) // Any of them are static.
							{
								// Acá haría los cálculos teniendo en cuenta las masas.
								float mProps  = (listsOfEntities + index1)[i]->GetMass();
								float mProps2 = (listsOfEntities + index2)[j]->GetMass();

								if (mProps >= mProps2) // Entity 1 has more mass.
								{
									float mPercentage = mProps2 / mProps;

									float move = diff.y / mPercentage * 100; // Razonarlo mejor.

									(listsOfEntities + index1)[i]->Transtale(glm::vec3(0.0f, move, 0.0f));
									(listsOfEntities + index2)[j]->Transtale(glm::vec3(0.0f, diff.y - move, 0.0f));
								}
								else // Entity 2 has more mass.
								{
									float mPercentage = mProps / mProps2;
								}

							}
							else // Entity 1 is pushed back
							{
								(listsOfEntities + index1)[i]->Transtale(glm::vec3(0.0f, diff.y, 0.0f));
							}
						}
						else // Entity 2 is pushed back
						{
							(listsOfEntities + index2)[j]->Transtale(glm::vec3(0.0f, diff.y, 0.0f));
						}

					}
					else
					{
						// Horizontal Collision
					}
				}
			}

		}
	}
}