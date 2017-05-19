#include "Math.h"
#include "Graphics.h"
#include "SoundManager.h"

#if	1
int main()
{
	using namespace NumberOne;

	Sound::SoundManager* sm = new NumberOne::Sound::SoundManager(2);
	sm->addSound("C:\\Users\\Joshua McMorris\\Downloads\\temp.wav");
	sm->addSound("C:\\Users\\Joshua McMorris\\Downloads\\temp2.wav");

	Graphics::Window Window("Test", 540, 960);
	//glClearColor(.1f, .1f, .1f, 1.0f);

	Graphics::Shader shader("basic.vert", "basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", Math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Graphics::TileLayer layer(&shader);
	Graphics::Group* group = new Graphics::Group(Math::mat4::rotation(45.0f, Math::vec3(0, 0, 1)));
	
	Graphics::LabelManager2D* fm = new Graphics::LabelManager2D();
	Graphics::Label test("Hello World!", -10, -4, 60, 0xaa44ff00, FONT_TIMES_NEW);
	Graphics::Label test2("Test 2", 0, 0, 70, Math::vec4(1.0f, .0f, .0f, 1.0f), FONT_TIMES_NEW);
	group->add(fm);
	fm->add(&test);
	fm->add(&test2);

	Graphics::Texture* textures[] =
	{
		new Graphics::Texture("test.png"),
		new Graphics::Texture("tb.png"),
		new Graphics::Texture("tc.png")

	};

	for (float y = -9.0f; y < 9.0f; y += 1)
	{
		for (float x = -16.0f; x < 16.0f; x += 1)
		{
			//layer.add(new Graphics::Sprite(x, y, 0.15f, 0.2f, Math::vec4(.1f, rand() % 1000 / 1000.0f, .1f, 1.0f))); 
		//	if (rand() % 4 == 0)
				layer.add(new Graphics::Sprite(x, y, .5f, .5f, 0xffffff00));
		//	else
				layer.add(new Graphics::Sprite(x, y, .5f, .5f, textures[0]));
				layer.add(new Graphics::Sprite(x, y + .5f, .25f, .25f, textures[1]));
				layer.add(new Graphics::Sprite(x+ .5f, y + .5f, .25f, .25f, textures[2]));

		}
	}

	layer.add(new Graphics::Sprite(0, 0, 10.0f, 10.0f, 0x886666aa));
		
	layer.add(group);
		
/*	
	Graphics::Particle particles[10000];
	for (int i = 0; i < 10000; i++)
	{
		particles[i].p_vertexData.v_color = 0x88888888;
	}

	Graphics::ParticleRenderer pr(10000);
	*/
	
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.setUniform1iv("textures", texIDs, 10);

	
	Timer time;
	int frames = 0;
	double x, y;

	while (Window.close() == 0)
	{
		time.reset();
		calcFPS();

		Window.clear();

		if (Window.isKeyClicked(GLFW_KEY_A))
		{
			sm->playSound(1);
		}

		if (Window.isKeyClicked(GLFW_KEY_B))
		{
			sm->playSound(2);
		}

		if (Window.isKeyClicked(GLFW_KEY_C))
		{
			sm->pauseSound(1);
			sm->pauseSound(2);
		}

		if (Window.isKeyClicked(GLFW_KEY_D))
		{
			sm->removeSound(1);
		}
		
		Window.getMousePos(x, y);
		shader.setUniform2f("light_pos", Math::vec2((float)(-16 + x * 32.0f / 960.0f), (float)(9 - y * 18.0f / 540.0f)));
		
		layer.render();
		
		/*
		particles[frames].p_life = 1.0f;
		particles[frames].p_velocity = Math::vec2(rand() % 10, rand() % 10);
		particles[frames].p_vertexData.v_position = Math::vec3(rand() % 8, rand() % 8, 0);
		for (int i = 0; i < frames; i++)
		{
			particles[i].p_life -= time.elapsed();
			particles[i].p_vertexData.v_position.x += (particles[i].p_velocity.x / 10000);
			particles[i].p_vertexData.v_position.y += (particles[i].p_velocity.y / 10000);
		}
a

		for (int i = 0; i < frames; i++)
		{
			pr.submit(&particles[i]);
		}
		pr.begin();
		pr.flush();
		*/
		

		Window.update();
		frames++;
	}

//	delete textures[0];
//	delete textures[1];
//	delete textures[2];

	return 0;
}
#endif
