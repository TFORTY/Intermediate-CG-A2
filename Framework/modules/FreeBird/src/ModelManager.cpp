#include "ModelManager.h"
#include <iostream>

namespace freebird
{
	std::vector<std::string> ModelManager::m_filesLoaded;
	std::vector<Mesh*> ModelManager::m_meshes;

	ModelManager::~ModelManager()
	{
		//Loops through all the meshes loaded
		for (unsigned i = 0; i < m_meshes.size(); ++i)
		{
			//If the mesh isn't nullptr
			if (m_meshes[i] != nullptr)
			{
				//Delete mesh
				delete m_meshes[i];
				//Set it to nullptr
				m_meshes[i] = nullptr;
			}
		}
	}

	Mesh* ModelManager::LoadMesh(std::string& fileName, glm::vec3& inColor)
	{
		//Adds the filename to the loaded list and loads the mesh to the mesh list
		m_filesLoaded.push_back(fileName);
		//Push back a new mesh
		if (inColor == glm::vec3(0.2f))
			m_meshes.push_back(new Mesh(fileName));
		else
			m_meshes.push_back(new Mesh(fileName, inColor));
		//Loads new mesh

		return m_meshes[m_meshes.size() - 1];
	}

	Mesh* ModelManager::FindMesh(std::string& fileName, glm::vec3& inColor)
	{
		//Searches list of strings and stores result of iteration
		auto iteration = std::find(m_filesLoaded.begin(), m_filesLoaded.end(), fileName);
		int index = 0;

		//Checks if the file with the given name was already in the list of loaded files
		if (iteration != m_filesLoaded.end())
			index = int(std::distance(m_filesLoaded.begin(), iteration));
		else
			index = -1;

		//checks if index is -1 and if it is, return
		if (index != -1)
		{
			std::cout << "Mesh Found!" << std::endl;
			return m_meshes[index];
		}
		else
		{
			std::cout << "Making New Mesh" << std::endl;
			return LoadMesh(fileName, inColor);
		}
	}

	GLuint ModelManager::GetHandle(std::string& fileName)
	{
		Mesh* mesh = FindMesh(fileName);

		return mesh->GetVBO()->GetHandle();
	}

	std::vector<std::string> ModelManager::GetFilesLoaded()
	{
		return m_filesLoaded;
	}

}