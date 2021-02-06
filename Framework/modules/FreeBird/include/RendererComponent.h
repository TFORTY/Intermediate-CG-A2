#pragma once
#include "VertexArrayObject.h"
#include "Material.h"

namespace freebird
{
	class RendererComponent {
	public:
		VertexArrayObject::sptr Mesh;
		Material::sptr    Material;

		RendererComponent& SetMesh(const VertexArrayObject::sptr& mesh) { Mesh = mesh; return *this; }
		RendererComponent& SetMaterial(const Material::sptr& material) { Material = material; return *this; }
	};
}
