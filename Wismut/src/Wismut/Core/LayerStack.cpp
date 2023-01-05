#include "wipch.h"
#include "LayerStack.h"

namespace Wi
{
	LayerStack::LayerStack()
	{
		m_LayerInsertIndex = 0;
	}

	LayerStack::~LayerStack()
	{
		for (const Layer* layer : m_LayerStack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerStack.emplace(m_LayerStack.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_LayerStack.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto it = std::ranges::find(m_LayerStack, layer);
		if (it != m_LayerStack.end())
		{
			m_LayerStack.erase(it);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		const auto it = std::ranges::find(m_LayerStack, layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			layer->OnDetach();
		}
	}
}
