#include "Cube.h"
Cube::Cube()
{

	vertices.push_back(Vector3(-1, 1, 1));
	vertices.push_back(Vector3(1, 1, 1));
	vertices.push_back(Vector3(1, 1, -1));	
	vertices.push_back(Vector3(-1, 1, -1));

	vertices.push_back(Vector3(-1, -1, 1));
	vertices.push_back(Vector3(1, -1, 1));
	vertices.push_back(Vector3(1, -1, -1));
	vertices.push_back(Vector3(-1, -1, -1));

	indices.push_back(Index(0, 1, 2)); 
	indices.push_back(Index(0, 2, 3));
	indices.push_back(Index(0, 3, 7)); 
	indices.push_back(Index(0, 7, 4));
	indices.push_back(Index(3, 2, 6)); 
	indices.push_back(Index(3, 6, 7));
	indices.push_back(Index(2, 1, 5)); 
	indices.push_back(Index(2, 5, 6));
	indices.push_back(Index(1, 0, 4)); 
	indices.push_back(Index(1, 4, 5));
	indices.push_back(Index(7, 6, 5)); 
	indices.push_back(Index(7, 5, 4));
}
