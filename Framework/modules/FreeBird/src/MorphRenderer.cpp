#include "MorphRenderer.h"
#include "Camera.h"

namespace freebird
{
	MorphRenderer::MorphRenderer(Entity& ent, Mesh& base, Shader::sptr& shader/*Material& mat*/)
		: MeshRenderer(ent, base, shader)
	{

		UpdateData(base, base, 0.0f);

	}
	VertexArrayObject::sptr MorphRenderer::MakeVAO(Mesh& mesh)
	{
		vao = VertexArrayObject::Create();

		size_t stride = sizeof(float) * 11;

		vao->AddVertexBuffer(mesh.GetVBO(), {
		BufferAttribute(0, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
		BufferAttribute(1, 3, GL_FLOAT, false, stride, sizeof(float) * 3, AttribUsage::Color),
		BufferAttribute(2, 2, GL_FLOAT, false, stride, sizeof(float) * 6, AttribUsage::Texture),
		BufferAttribute(3, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		return vao;
	}
	void MorphRenderer::UpdateData(Mesh& tempFrame0, Mesh& tempFrame1, float t)
	{
		size_t stride = sizeof(float) * 11;

		vao->ClearVertexBuffers();

		vao->AddVertexBuffer(tempFrame0.GetVBO(), {
			BufferAttribute(0, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
			BufferAttribute(1, 3, GL_FLOAT, false, stride, sizeof(float) * 3, AttribUsage::Color),
			BufferAttribute(2, 2, GL_FLOAT, false, stride, sizeof(float) * 6, AttribUsage::Texture),
			BufferAttribute(3, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		vao->AddVertexBuffer(tempFrame1.GetVBO(), {
			BufferAttribute(4, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
			BufferAttribute(5, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		this->t = t;
	}
	void MorphRenderer::Render(Camera& camera, glm::mat4 transform)
	{
		//thisMat->Apply();

		thisShader->SetUniformMatrix("u_Model", transform);
		thisShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		thisShader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
		thisShader->SetUniform("u_CamPos", camera.GetPosition());
		thisShader->SetUniform("u_MorphT", this->t);

		vao->Render();
	}
}