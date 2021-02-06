#include "MorphAnimation.h"
#include "Mesh.h"
#include <MorphRenderer.h>

namespace freebird
{
	MorphAnimation::MorphData::MorphData()
	{
		frameTime = 1.0f;
	}

	MorphAnimation::MorphAnimation(Entity& ent)
	{
		data = std::make_unique<MorphData>();
		timer = 0.0f;
		frame = 0;
		thisEnt = &ent;
	}

	void MorphAnimation::Update(float dt)
	{
		if (data->frames.empty())
			return;

		if (data->frames.size() == 1)
		{
			thisEnt->Get<MorphRenderer>().UpdateData(*data->frames[0], *data->frames[0], 0.0f);
			return;
		}

		float t = 0.0f;

		if (data->frameTime > 0.0f)
		{
			timer += dt;

			size_t frameSkip = timer / data->frameTime;

			frame = (frame + frameSkip) % data->frames.size();

			timer = fmod(timer, data->frameTime);

			t = timer / data->frameTime;
		}

		size_t nextFrame = (frame + 1) % data->frames.size();
		if (!looping && frame >= data->frames.size() - 1)
		{
			data->frameTime = 0.0f;
		}
		else
			thisEnt->Get<MorphRenderer>().UpdateData(*data->frames[frame], *data->frames[nextFrame], t);
	}

	void MorphAnimation::SetFrames(const std::vector<std::unique_ptr<Mesh>>& frames)
	{
		data->frames.clear();
		data->frames.reserve(frames.size());

		for (size_t i = 0; i < frames.size(); ++i)
		{
			data->frames.push_back(frames[i].get());
		}
	}

	void MorphAnimation::SetTime(float time)
	{
		data->frameTime = time;
	}

	void MorphAnimation::SetLoop(bool loop)
	{
		looping = loop;
	}

}