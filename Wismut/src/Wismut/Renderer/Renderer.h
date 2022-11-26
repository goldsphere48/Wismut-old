#pragma once
#include "Camera.h"
#include "RendererAPI.h"
#include "Shader.h"

namespace Wi
{
	class Renderer
	{
	public:
		static void BeginScene(Camera camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 transform);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData s_SceneData;
	};
}
