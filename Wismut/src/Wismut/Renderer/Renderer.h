#pragma once
#include "ShaderLibrary.h"
#include "Wismut/Renderer/Camera/PerspectiveCamera.h"
#include "Wismut/Renderer/Camera/OrthographicCamera.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexArray.h"
#include "Wismut/Renderer/RendererAPI.h"

namespace Wi
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(int width, int height);
		static void BeginFrame(const glm::mat4& camera);
		static void EndFrame();
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform);
		static void Clear(glm::vec4 clearColor);

		static ShaderLibrary& GetShaderLibrary() { return s_ShaderLibrary; }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData s_SceneData;
		static ShaderLibrary s_ShaderLibrary;
		static Scope<RendererAPI> s_RendererAPI;
	};
}
