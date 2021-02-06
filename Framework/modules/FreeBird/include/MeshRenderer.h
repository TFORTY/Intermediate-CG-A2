#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Entity.h"
#include "../../../projects/Project Poultry/src/Scene.h"

#include <memory>

namespace freebird
{
	class MeshRenderer
	{
	public:
		MeshRenderer(Entity& ent, Mesh& mesh, Shader::sptr& shader /*Material& mat = Material()*/);
		MeshRenderer() = default;

		void SetMesh(Mesh& mesh);
		void SetMaterial(Material& mat);

		VertexArrayObject::sptr MakeVAO(Mesh& mesh);

		void SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos = glm::vec3(0.f, 0.f, 0.f),
			glm::vec3 lightDir = glm::vec3(0.f, 0.f, 0.f), glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f),
			float lightAmbientPow = 0.f, float lightSpecularPow = 0.f, float lightSpecularPow2 = 0.f,
			glm::vec3 ambientCol = glm::vec3(0.f, 0.f, 0.f), float ambientPow = 0.f, float shininess = 0.f);

		virtual void Render(Camera& camera, glm::mat4 transform);

	protected:
		Entity* thisEnt;
		Material* thisMat;
		Mesh* thisMesh;
		Shader::sptr thisShader;

		VertexArrayObject::sptr vao;
	};

}
