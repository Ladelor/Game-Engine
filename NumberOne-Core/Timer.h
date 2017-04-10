#pragma once

#include <Windows.h>
#include <iostream>
#include <GLFW\glfw3.h>

namespace NumberOne {

	double calcFPS()
	{
		// Static values which only get initialised the first time the function runs
		static double t0Value = glfwGetTime(); // Set the initial time to now
		static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
		static double fps = 0.0;           // Set the initial FPS value to 0.0

										   // Get the current time in seconds since the program started (non-static, so executed every time)
		double currentTime = glfwGetTime();

		// Calculate and display the FPS every specified time interval
		if ((currentTime - t0Value) > 1)
		{
			// Calculate the FPS as the number of frames divided by the interval in seconds
			fps = (double)fpsFrameCount / (currentTime - t0Value);

			std::cout << "FPS: " << fps << std::endl;

			// Reset the FPS frame counter and set the initial time to be now
			fpsFrameCount = 0;
			t0Value = glfwGetTime();
		}
		else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
		{
			fpsFrameCount++;
		}

		// Return the current FPS - doesn't have to be used if you don't want it!
		return fps;
	}
	
	//rewrite with a different library to work cross-platform
	
	class Timer
	{
	private:
		LARGE_INTEGER Start;
		double Frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			Frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			__int64 cycles = current.QuadPart - Start.QuadPart;
			return (float)(cycles * Frequency);
		}
	};
	
}


