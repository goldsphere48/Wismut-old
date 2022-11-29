#pragma once
#include "wipch.h"

namespace Wi
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
			
		}

		float GetSeconds() const
		{
			return m_Time;
		}

		operator float() const
		{
			return m_Time;
		}

	private:
		float m_Time;
	};
}
