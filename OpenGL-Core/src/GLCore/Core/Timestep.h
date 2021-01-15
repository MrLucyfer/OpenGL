#pragma once

namespace GLCore {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		void SetTotalTime(float time) { m_TotalTime = time; }

		float GetTotalTime() const { return m_TotalTime; }
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
		float m_TotalTime;
	};

}