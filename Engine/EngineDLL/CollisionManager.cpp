#include "CollisionManager.h"

CollisionManager * CollisionManager::instance = NULL;

CollisionManager::CollisionManager()
{
	for (int i = 0; i < Count; i++)
	{
		list<Entity*> list;
		listsOfEntities.push_back(list);
	}

	for (int i = 0; i < Count; i++)
		for (int j = 0; j < Count; j++)
			tagsRelation[i][j] = false;
}

void CollisionManager::AddEntity(Entity* entity)
{
	listsOfEntities[entity->GetTag()].push_back(entity);
}

void CollisionManager::SetRelation(int layer1, int layer2)
{
	if (layer1 <= layer2)
	{
		tagsRelation[layer1][layer2] = true;
		cout << "Colision: " << layer1 << " - " << layer2 << " = " << tagsRelation[layer1][layer2] << endl;
	}
	else
	{
		cout << "holi" << endl;
		tagsRelation[layer2][layer1] = true;
		cout << "Colision: " << layer2 << " - " << layer1 << " = " << tagsRelation[layer2][layer1] << endl;
	}

	
}

void CollisionManager::DetectCollisions()
{
	/*for (int i = 0; i < Count; i++)
	{
		for (int j = i; j < Count; j++)
			cout << tagsRelation[i][j] << " ";
		cout << endl;
	}*/
	for (int i = 0; i < Count; i++)
		for (int j = i; j < Count; j++)
			if (tagsRelation[i][j] == 1)
				MakeTheRealDetection(i, j);
}

void CollisionManager::MakeTheRealDetection(int index1, int index2)
{
	
	// If any of this lists has no Entity just return.
	if (listsOfEntities[index1].size() == 0
	 || listsOfEntities[index2].size() == 0)
		return;
	
	for(list<Entity*>::iterator it1 = listsOfEntities[index1].begin(); it1 != listsOfEntities[index1].end(); it1++)
	{
		glm::vec2 col1 = (*it1)->GetColProps();

		for (list<Entity*>::iterator it2 = listsOfEntities[index2].begin(); it2 != listsOfEntities[index2].end(); it2++)
		{
			if (!(*it1)->IsStatic() && !(*it2)->IsStatic()) // If both are static don't check collision.
			{
				glm::vec3 diff = (*it2)->GetPosition() - (*it1)->GetPosition();

				int dX = abs(diff.x);
				int dY = abs(diff.y);

				glm::vec2 col2 = (*it2)->GetColProps();
				
				if (dX < col1.x / 2 + col2.x / 2
				&&  dY < col1.y / 2 + col2.y / 2)
				{
					int pX = (int)(col1.x / 2 + col2.x / 2 - diff.x);
					int pY = (int)(col1.y / 2 + col2.y / 2 - diff.y);

					if (pX > pY)
					{
						cout << "Vertical collision detected." << endl;
						// Vertical Collision
						if (!(*it1)->IsStatic())
						{
							if (!(*it2)->IsStatic()) // Any of them are static.
							{
								// Acá haría los cálculos teniendo en cuenta las masas.
								float m1 = (*it1)->GetMass();
								float m2 = (*it2)->GetMass();

								float mPercentage = (m1 + m2) / m1;
								float move = diff.y / mPercentage;

								(*it2)->Translate(glm::vec3(0.0f, move, 0.0f));
								(*it1)->Translate(glm::vec3(0.0f, diff.y - move, 0.0f));
							}
							else // Entity 1 is pushed back
							{
								(*it1)->Translate(glm::vec3(0.0f, diff.y, 0.0f));
							}
						}
						else // Entity 2 is pushed back
						{
							(*it2)->Translate(glm::vec3(0.0f, diff.y, 0.0f));
						}
					}
					else
					{
						cout << "Horizontal collision detected." << endl;
						// Horizontal Collision
						if (!(*it1)->IsStatic())
						{
							if (!(*it2)->IsStatic()) // Any of them are static.
							{
								// Acá haría los cálculos teniendo en cuenta las masas.
								float m1 = (*it1)->GetMass();
								float m2 = (*it2)->GetMass();

								float mPercentage = (m1 + m2) / m1;
								float move = diff.x / mPercentage;

								(*it2)->Translate(glm::vec3(move, 0.0f, 0.0f));
								(*it1)->Translate(glm::vec3(diff.x - move, 0.0f, 0.0f));
							}
							else // Entity 1 is pushed back
							{
								(*it1)->Translate(glm::vec3(diff.x, 0.0f, 0.0f));
							}
						}
						else // Entity 2 is pushed back
						{
							(*it2)->Translate(glm::vec3(diff.x, 0.0f, 0.0f));
						}
					}
				}
			}
		}
	}
}