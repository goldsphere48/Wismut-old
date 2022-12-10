#pragma once
#include "Layer.h"

namespace Wi
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::reverse_iterator rbegin() { return m_LayerStack.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_LayerStack.rend(); }
		std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerStack.end(); }

	private:
		std::vector<Layer*> m_LayerStack;
		int m_LayerInsertIndex;
	};
}
