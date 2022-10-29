#include "wipch.h"

#include "LayerStack.h"

namespace Wi
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_LayerStack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (const Layer* layer : m_LayerStack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_LayerStack.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_LayerStack.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end())
		{
			m_LayerStack.erase(it);
			--m_LayerInsert;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		const auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			layer->OnDetach();
		}
	}
}
