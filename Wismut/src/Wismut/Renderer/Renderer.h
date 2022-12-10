#pragma once
#include "Wismut/Renderer/PerspectiveCamera.h"
#include "Wismut/Renderer/OrthographicCamera.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexArray.h"
#include "Wismut/Renderer/RenderCommand.h"

namespace Wi
{
	class Renderer
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData s_SceneData;
	};
}
