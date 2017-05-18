#pragma once

#include <glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace NumberOne {	namespace Graphics {

	#define MAX_KEYS 512
	#define MAX_BUTTONS 32
	
	class Window
	{
	private:
		//private member data
		//given w_ precursor ofr belonging to Window
		int w_width, w_height;
		const char *w_name;
		GLFWwindow *w_Window;
		bool w_closed;
		bool w_keys[MAX_KEYS];
		bool w_keysPressed[MAX_KEYS];
		bool w_keysClicked[MAX_KEYS];
		bool w_buttons[MAX_BUTTONS];
		bool w_buttonsPressed[MAX_BUTTONS];
		bool w_buttonsClicked[MAX_BUTTONS];
		double w_posX, w_posY;

		//private member methods
		bool init();
		friend static void keyCallback(GLFWwindow* Window, int key, int scancode, int action, int mods);
		friend static void mouseButtonCallback(GLFWwindow* Window, int button, int action, int mods);
		friend static void cursorPositionCallback(GLFWwindow* Window, double xpos, double ypos);
		friend static void Window_Resize(GLFWwindow *Window, int width, int height);


	public:
		//public member data

		//public member methods
		Window(const char* name, int width, int height);
		~Window();
		void clear();
		void update();
		bool close() const;
		bool isKeyPressed(unsigned int keyCode) const;
		bool isKeyClicked(unsigned int keyCode) const;
		bool isButtonPressed(unsigned int buttonCode) const;
		bool isButtonClicked(unsigned int buttonCode) const;

		void getMousePos(double& x, double& y);
		
	};
} }
 // !Window_H
