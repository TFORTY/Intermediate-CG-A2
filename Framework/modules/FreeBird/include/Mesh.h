//Mesh class to load our objects
/*
	Tyler Wong
	2020-10-24
*/

#pragma once
#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "VertexArrayObject.h"

namespace freebird
{
	class Mesh
	{
	public:
		Mesh(const std::string& fileName, const glm::vec3& inColor = glm::vec3(1.0f));
		Mesh() = default;
		VertexArrayObject::sptr vao;

		VertexBuffer::sptr GetVBO();
		std::string GetName();
		void SetName(std::string name);
		
	protected:
		std::vector<float> interleaved;
		std::vector<unsigned int> vertIndices, uvIndices, normIndices; 

		std::string name;
		VertexBuffer::sptr vbo;
	};
}