#pragma once

#include "RenderCommand.h"

#include "OverEngine/Renderer/Shader.h"
#include "OverEngine/Renderer/Camera.h"
#include "OverEngine/Renderer/Texture.h"

namespace OverEngine
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void DrawQuad(const Vector2& position, float rotation, const Vector2& size, const Color& color);
		static void DrawQuad(const Vector3& position, float rotation, const Vector2& size, const Color& color);
		static void DrawQuad(const Mat4x4& transform, float rotation, const Vector2& size, const Color& color);

		static void DrawQuad(const Vector2& position, float rotation, const Vector2& size, Ref<Texture2D> texture, float tilingFactor = 1.0f, const Color& tint = Color(1.0f));
		static void DrawQuad(const Vector3& position, float rotation, const Vector2& size, Ref<Texture2D> texture, float tilingFactor = 1.0f, const Color& tint = Color(1.0f));
		static void DrawQuad(const Mat4x4& transform, float rotation, const Vector2& size, Ref<Texture2D> texture, float tilingFactor = 1.0f, const Color& tint = Color(1.0f));

		struct Statistics
		{
			void Reset()
			{
				QuadCount = 0;
				DrawCalls = 0;
			}

			uint32_t GetIndexCount() { return 6 * QuadCount; }
			uint32_t GetVertexCount() { return 4 * QuadCount; }

			uint32_t QuadCount;
			uint32_t DrawCalls;
		};

		static Statistics& GetStatistics() { return s_Statistics; }
	private:
		static Statistics s_Statistics;
	};
}