#include "ParticleSystem.h"
#include "Camera.h"

namespace freebird
{

	const size_t ParticleSystem::MAX_PARTICLES = 10000;

	ParticleSystem::ParticleSystem(Entity& ent,/*, Material& mat*/ const ParticleParam& startParam)
	{
		thisEnt = &ent;

		size_t particleNum = (startParam.maxParticles < MAX_PARTICLES) ? startParam.maxParticles : MAX_PARTICLES;
		
		data = std::make_unique<Data>(particleNum, startParam);

	}

	void ParticleSystem::Update(float dt, Camera& camera)
	{
		data->emissionTimer += dt;

		float emissionTime = 1.0f / data->param.emissionRate;

		while (data->emissionTimer > emissionTime)
		{
			data->emissionTimer -= emissionTime;
			Emit();
		}

		auto& trans = thisEnt->Get<Transform>();

		glm::mat4 modelView = camera.GetView() * trans.GetModelMatrix();

		for (int index = static_cast<int>(data->lastAlive); index >= 0; --index)
		{
			size_t i = static_cast<size_t>(index);

			if (!data->alive[i])
				continue;

			data->lifetime[i] -= dt;

			if (data->lifetime[i] <= 0.0f)
			{
				data->alive[i] = false;
				--(data->numAlive);

				if (i == data->lastAlive && i != 0)
					--data->lastAlive;

				data->insertIndices.push_front(i);
				continue;
			}

			float lifeT = 1.0f - (data->lifetime[i] / data->param.lifetime);
			data->colors[i] = glm::mix(data->param.startColor,
				data->param.endColor,
				lifeT);

			data->positions[i] += dt * data->velocities[i];

			data->viewPositions[i] = modelView * glm::vec4(data->positions[i], 1.0f);

			//float lifeT = 1.0f - (data->lifetime[i] / data->param.lifetime);

			/*float lifeS = 1.0f - (data->lifetime[i] / data->param.lifetime);
			data->sizes[i] = glm::mix(data->param.startSize,
				data->param.endSize,
				lifeS);*/

		
			/*data->colors[i] = glm::mix(data->param.startColor,
				data->param.endColor,
				lifeT);*/
		}

		Sort();
	}
	void ParticleSystem::Draw(Camera& camera, Shader::sptr& shader)
	{

		data->vbos[0]->UpdateData(data->viewPositions);
		data->vbos[1]->UpdateData(data->sizes);
		data->vbos[2]->UpdateData(data->colors);

		shader->SetUniformMatrix("u_Projection", camera.GetProjection());

		if (data->numAlive == 0)
			return;

		glBindVertexArray(data->vao->GetHandle());
		glDrawElements((int)GL_POINTS,
			static_cast<GLsizei>(data->numAlive),
			GL_UNSIGNED_INT,
			&(data->indices[0]));
	}
	void ParticleSystem::SetMax(int n)
	{
		data->param.maxParticles = n;
	}
	void ParticleSystem::SetLifetime(float n)
	{
		data->param.lifetime = n;
	}
	void ParticleSystem::SetStartSize(float n)
	{
		data->param.startSize = n;
	}
	void ParticleSystem::SetEndSize(float n)
	{
		data->param.endSize = n;
	}
	void ParticleSystem::SetStartSpeed(float n)
	{
		data->param.startSpeed = n;
	}
	void ParticleSystem::SetEndSpeed(float n)
	{
		data->param.endSpeed = n;
	}
	void ParticleSystem::SetStartColor(glm::vec4 n)
	{
		data->param.startColor = n;
	}
	void ParticleSystem::SetEndColor(glm::vec4 n)
	{
		data->param.endColor = n;
	}
	void ParticleSystem::SetEmissionRate(float n)
	{
		data->param.emissionRate = n;
	}
	void ParticleSystem::SetTan(float n)
	{
		data->param.tanTheta = n;
	}

	void ParticleSystem::VerticalConeEmit(float tanTheta, float speed, glm::vec3& pos, glm::vec3& vel)
	{
		pos = glm::vec3(0.0f);
		float x;
		float z;

		do
		{
			x = 2.0f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0f;
			z = 2.0f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0f;
		}
		while ((x * x + z * z) > 1.0f);

		vel = speed * glm::normalize(glm::vec3(tanTheta * x, 1.0f, tanTheta * z));
	}

	void ParticleSystem::Emit()
	{
		if (data->numAlive < data->count)
		{
			size_t i = data->insertIndices.front();
			data->insertIndices.pop_front();

			VerticalConeEmit(
				data->param.tanTheta,
				data->param.startSpeed,
				data->positions[i],
				data->velocities[i]
			);

			data->colors[i] = data->param.startColor;
			data->sizes[i] = data->param.startSize;
			data->lifetime[i] = data->param.lifetime;

			data->alive[i] = true;

			++(data->numAlive);

			if (i > data->lastAlive)
				data->lastAlive = i;
		}
	}

	void ParticleSystem::Sort()
	{

		std::sort(data->sorter.begin(), data->sorter.end());

		for (size_t i = 0; i < data->numAlive; ++i)
		{
			data->indices[i] = data->sorter[i].ind;
		}

	}

	ParticleSystem::Data::Data(size_t numParticles, const ParticleParam& startParam)
	{
		count = numParticles;
		param = startParam;

		vao = VertexArrayObject::Create();

		//TODO: Finish VBO Stuff
		positions.resize(count);

		viewPositions.resize(count);
		VertexBuffer::sptr viewBuffer = VertexBuffer::Create(GL_STREAM_DRAW);
		viewBuffer->LoadData(viewPositions.data(), viewPositions.size());

		sizes.resize(count);
		VertexBuffer::sptr sizeBuffer = VertexBuffer::Create(GL_STREAM_DRAW);
		sizeBuffer->LoadData(sizes.data(), sizes.size());

		colors.resize(count);
		VertexBuffer::sptr colorBuffer = VertexBuffer::Create(GL_STREAM_DRAW);
		colorBuffer->LoadData(colors.data(), colors.size());

		vbos.push_back(viewBuffer);
		vbos.push_back(sizeBuffer);
		vbos.push_back(colorBuffer);


		vao->AddVertexBuffer(viewBuffer, {
			BufferAttribute(0, 3, GL_FLOAT, false, 0, NULL, AttribUsage::Position)
			});

		vao->AddVertexBuffer(sizeBuffer, {
			BufferAttribute(1, 1, GL_FLOAT, false, 0, NULL)
			});

		vao->AddVertexBuffer(colorBuffer, {
			BufferAttribute(2, 4, GL_FLOAT, false, 0, NULL, AttribUsage::Color)
			});

		velocities.resize(count);
		lifetime.resize(count);

		alive = static_cast<bool*>(calloc(count, sizeof(bool)));

		indices.resize(count);
		std::fill(indices.begin(), indices.end(), 0);

		sorter.resize(count);

		for (size_t i = 0; i < count; ++i)
		{
			sorter[i].ind = static_cast<GLuint>(i);
			sorter[i].alive = &(alive[i]);
			sorter[i].viewPos = &(viewPositions[i]);
		}

		insertIndices.resize(count);

		for (size_t i = 0; i < count; ++i)
		{
			insertIndices[i] = i;
		}

		numAlive = 0;
		lastAlive = 0;
		emissionTimer = 0.0f;
	}
}