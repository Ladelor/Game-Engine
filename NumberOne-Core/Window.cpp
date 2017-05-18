#include "Window.h"

namespace NumberOne { namespace Graphics {

	//constructor for Window
	//calls init() which does most of the work
	Window::Window(const char* name, int width, int height)
	{
		//setting Window properties
		w_name = name;
		w_width = width;
		w_height = height;

		if (!init())		//initialize and check if init fails
			glfwTerminate();
		
		//set every key and button to false
		memset(w_keys, false, MAX_KEYS);
		memset(w_keysClicked, false, MAX_KEYS);
		memset(w_keysPressed, false, MAX_KEYS);

		memset(w_buttons, false, MAX_BUTTONS);
		memset(w_buttonsClicked, false, MAX_BUTTONS);
		memset(w_buttonsPressed, false, MAX_BUTTONS);
	}

	//Window destructor
	Window::~Window()
	{
		glfwTerminate();
	}

	//Initializes Window, called by Window constructor
	bool Window::init()
	{
		if (!glfwInit())			//check to see if glfw initialized
		{
			std::cout << "Failed to initialize GLFW in Window" << std::endl;
			return false;
		}
		
		//create glfw Window
		w_Window = glfwCreateWindow(w_height, w_width, w_name, NULL, NULL);
		if (!w_Window)		//check to see if Window opened
		{
			glfwTerminate();
			std::cout << "Failed to create Window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(w_Window);
		glfwSetWindowUserPointer(w_Window, this);

		//method to adjust size 
		//TODO: Change class properties
		glfwSetFramebufferSizeCallback(w_Window, Window_Resize);
		glfwSetKeyCallback(w_Window, keyCallback);
		glfwSetMouseButtonCallback(w_Window, mouseButtonCallback);
		glfwSetCursorPosCallback(w_Window, cursorPositionCallback);
		glfwSwapInterval(0.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Initialize GLEW
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initialize GLEW" << std::endl;
			return false;
		}
		return true;
	}

	void Window::clear()
	{
		//GL Code 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//Method for app run loop
	void Window::update()
	{
		for (int i = 0; i < MAX_BUTTONS; i++)
			w_buttonsClicked[i] = w_buttons[i] && !w_buttonsPressed[i];
		for (int i = 0; i < MAX_KEYS; i++)
			w_keysClicked[i] = w_keys[i] && !w_keysPressed[i];
		memcpy(w_buttonsPressed, w_buttons, MAX_BUTTONS);
		memcpy(w_keysPressed, w_keys, MAX_KEYS);

	//	GLenum err = glGetError();
		if (GLenum err = glGetError())
			std::cout << "OpenGL error: " << err;
		glfwPollEvents();	//Event Handler
		glfwSwapBuffers(w_Window);
	}

	//Method to modify elements in Window if size changes
	void Window_Resize(GLFWwindow *window, int width, int height) 
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->w_width = width;
		win->w_height = height;
	}

	//Method to deal with key events
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);

		//if the key action is press or hold, key is being pressed
		//otherwise, action is release so key is set back to false
		if (action != GLFW_RELEASE)	
			win->w_keys[key] = true;
		else 
			win->w_keys[key] = false;
	}
	
	//Method to deal with mouse button events
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		//set the button equal to true if pressed, false if released
		win->w_buttons[button] = action != 0;
	}

	void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		//set cursor positions
		win->w_posX = xpos;
		win->w_posY = ypos;
	}

	bool Window::isKeyPressed(unsigned int keyCode) const
	{
		if (keyCode >= MAX_KEYS)
		{
			return false;
			//**TODO: log something
		}
		return w_keysPressed[keyCode];
	}

	bool Window::isKeyClicked(unsigned int keyCode) const
	{
		if (keyCode >= MAX_KEYS)
		{
			return false;
			//**TODO: log something
		}
		return w_keysClicked[keyCode];
	}

	bool Window::isButtonPressed(unsigned int buttonCode) const
	{
		if (buttonCode >= MAX_BUTTONS)
		{
			return false;
			//**TODO: log something
		}
		return w_buttonsPressed[buttonCode];
	}

	bool Window::isButtonClicked(unsigned int buttonCode) const
	{
		if (buttonCode >= MAX_BUTTONS)
		{
			return false;
			//**TODO: log something
		}
		return w_buttonsClicked[buttonCode];
	}
	
	bool Window::close() const
	{

		return (glfwWindowShouldClose(w_Window) != 0);
	}

	void Window::getMousePos(double& x, double& y)
	{
		x = w_posX;
		y = w_posY;
	}

} }