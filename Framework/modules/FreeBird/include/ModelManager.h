#pragma once
#include <vector>
#include "GLM/glm.hpp"

#include "Mesh.h"


namespace freebird
{
	class ModelManager abstract
	{
	public:

		~ModelManager();

		//Loads the models
		static Mesh* LoadMesh(std::string& fileName, glm::vec3& inColor = glm::vec3(0.2f));

		//Finds the model
		static Mesh* FindMesh(std::string& fileName, glm::vec3& inColor = glm::vec3(0.2f));

		//Gets the handle
		static GLuint GetHandle(std::string& fileName);

		//Gets the list of all loaded meshes
		static std::vector<std::string> GetFilesLoaded();

	private:
		//List of loaded files
		static std::vector<std::string> m_filesLoaded;
		//List of loaded meshes
		static std::vector<Mesh*> m_meshes;
	};
}