#pragma once
#include "IndexBuffer.h"
#include "OrthographicCamera.h"
#include "ShaderLibrary.h"
#include "Texture.h"
#include "UniformBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Wi
{
	class Renderer2D
	{
	public:
		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::mat4 transform);

	private:
		struct Renderer2DData
		{
			Ref<Shader> FlatColorShader;
			Ref<Shader> BlobShader;
			Ref<Texture2D> WhiteTexture;
			Ref<VertexBuffer> QuadVertexBuffer;
			Ref<IndexBuffer> QuadIndexBuffer;
			Ref<VertexArray> VertexArray;
		};

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			Ref<ShaderLibrary> ShaderLibrary;
		};

		static SceneData s_SceneData;
		static Renderer2DData s_Data;
	};
}

