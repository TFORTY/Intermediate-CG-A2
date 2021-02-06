#pragma once

#include <memory>
#include <Entity.h>
#include <Mesh.h>
#include "MeshRenderer.h"

namespace freebird
{
	class MorphRenderer : public MeshRenderer
	{
	public: 

		/*enum class Attributes
		{
			POS0 = 0,
			POS1 = 1,
			NORM0 = 2,
			NORM1 = 3,
			UV = 4
		};*/

		MorphRenderer(Entity& ent, Mesh& base, Shader::sptr& shader/*Material& mat*/);

		MorphRenderer() = default;

		VertexArrayObject::sptr MakeVAO(Mesh& mesh);

		void UpdateData(Mesh& frame0, Mesh& frame1, float t);
		virtual void Render(Camera& camera, glm::mat4 transform);

	protected:

		Mesh* frame0, frame1;

		float t;
	};
}