//From Shawn's Week 5 Intro to Computer Graphics tutorial

#pragma once
#include "IBuffer.h"
#include <memory>

namespace freebird
{
	/// <summary>
	/// The vertex buffer will store all of our vertex data for rendering
	/// </summary>
	class VertexBuffer : public IBuffer
	{
	public:
		typedef std::shared_ptr<VertexBuffer> sptr;
		static inline sptr Create(GLenum usage = GL_STATIC_DRAW) {
			return std::make_shared<VertexBuffer>(usage);
		}
	
	public:
		/// <summary>
		/// Creates a new vertex buffer, with the given usage. Data will still need to be uploaded before it can be used
		/// </summary>
		/// <param name="usage">The usage hint for the buffer, default is GL_STATIC_DRAW</param>
		VertexBuffer(GLenum usage = GL_STATIC_DRAW) : IBuffer(GL_ARRAY_BUFFER, usage) { 
			if (usage == GL_DYNAMIC_DRAW || usage == GL_STREAM_DRAW)
				dynamic = true;
		}

		template <typename T>
		explicit VertexBuffer(const T* data, size_t count, GLenum usage = GL_STATIC_DRAW) : IBuffer(GL_ARRAY_BUFFER, usage)
		{
			LoadData(data, count);

			if (usage == GL_DYNAMIC_DRAW || usage == GL_STREAM_DRAW)
				dynamic = true;
		}
	
		/// <summary>
		/// Unbinds the current vertex buffer
		/// </summary>
		static void UnBind() { IBuffer::UnBind(GL_ARRAY_BUFFER); }
	};
}