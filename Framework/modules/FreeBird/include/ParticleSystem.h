#pragma once

#include "Entity.h"
#include "Material.h"
#include "GLM/glm.hpp"

#include <vector>
#include <deque>
#include <memory>
#include <VertexArrayObject.h>
#include "../../../projects/Project Poultry/src/Scene.h"

namespace freebird
{

	struct ParticleParam
	{
		size_t maxParticles;

		float lifetime;

		float startSize;
		float endSize;

		float startSpeed;
		float endSpeed;

		glm::vec4 startColor;
		glm::vec4 endColor;

		float emissionRate;
		float tanTheta;


		ParticleParam()
		{
			maxParticles = 50;
			lifetime = 1.5f;
			startSize = 0.5f;
			//endSize = 0.05f;
			startSpeed = 1.0f;
			startColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
			endColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
			emissionRate = 100.0f;
			tanTheta = glm::tan(glm::radians(30.0f));
		}
	};


	class ParticleSystem
	{
	public:

		static const size_t MAX_PARTICLES;

		enum class Attributes
		{
			POS = 0,
			SIZE = 1,
			COLOR = 2
		};

		ParticleSystem(Entity& ent/*, Material& mat*/, const ParticleParam& startParam);
		ParticleSystem() = default;

		void Update(float dt, Camera& camera);
		void Draw(Camera& camera, Shader::sptr&);

		void SetMax(int n);
		void SetLifetime(float n);
		void SetStartSize(float n);
		void SetEndSize(float n);
		void SetStartSpeed(float n);
		void SetEndSpeed(float n);
		void SetStartColor(glm::vec4 n);
		void SetEndColor(glm::vec4 n);
		void SetEmissionRate(float n);
		void SetTan(float n);

		void VerticalConeEmit(float tanTheta, float speed, glm::vec3& pos, glm::vec3& vel);

	private:

		struct Sorter
		{
			GLuint ind;
			const bool* alive;
			const glm::vec3* viewPos;

			bool operator<(const Sorter& sort) const
			{
				if (!(*sort.alive) && *alive)
					return true;
				if (!(*alive) && *sort.alive)
					return false;

				if (viewPos->z < sort.viewPos->z)
					return true;
				if (sort.viewPos->z < viewPos->z)
					return false;

				return ind < sort.ind;
			}
		};

		struct Data
		{
			VertexArrayObject::sptr vao;

			std::vector<VertexBuffer::sptr> vbos;

			std::vector<Sorter> sorter;

			std::vector<glm::vec3> positions;
			std::vector<glm::vec3> viewPositions;
			std::vector<glm::float32> sizes;
			std::vector<glm::vec4> colors;

			std::vector<glm::vec3> velocities;

			std::vector<float> lifetime;
			
			bool* alive;

			std::vector<GLuint> indices;

			ParticleParam param;

			size_t count;

			size_t numAlive;

			size_t lastAlive;

			std::deque<size_t> insertIndices;

			float emissionTimer;

			Data(size_t numParticles, const ParticleParam& startParam);

		};

		Entity* thisEnt;
		Material* thisMat;
		std::unique_ptr<Data> data;

		void Emit();
		void Sort();
	};

}