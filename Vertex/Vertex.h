#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

#endif // VERTEX_H