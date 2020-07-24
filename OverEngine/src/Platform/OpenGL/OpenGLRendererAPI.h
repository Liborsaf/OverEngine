#pragma once

#include "OverEngine/Renderer/RendererAPI.h"

namespace OverEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const Math::Color& color) override;
		virtual void SetClearDepth(float depth) override;
		virtual void Clear(bool clearColorBuffer, bool clearDepthBuffer) override;

		virtual void DrawIndexed(const VertexArray& vertexArray) override;

		virtual uint32_t GetMaxTextureSize() override;
		virtual uint32_t GetMaxTextureSlotCount() override;
	};
}