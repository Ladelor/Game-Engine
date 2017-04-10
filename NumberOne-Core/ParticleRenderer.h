#pragma once

#include "Particle.h"
#include "Renderer2D.h"
#include "IndexBuffer.h"

namespace NumberOne {
	namespace Graphics {


		class ParticleRenderer : public Renderer2D
		{

#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define SHADER_PARTICLE_POSITION 0
//#define SHADER_PARTICLE_UV 1
//#define SHADER_PARTICLE_TEXTUREID 2
#define SHADER_PARTICLE_COLOR 1
#define SHADER_PARTICLE_OFFSET 2

#define MAX_PARTICLES 50000

		private:
			GLuint r_vao;
			IndexBuffer* r_ibo;
			GLsizei pr_particleCount;
			GLuint r_vbo, pr_vboBase;
			Particle* r_buffer;
			VertexData* pr_vertexData;
			//std::vector<GLuint> r_textures;

		public:
			GLsizei pr_indexCount;

			ParticleRenderer(GLsizei maxParticles);
			~ParticleRenderer();
			void submit(const Renderable2D* renderable) override;
			void submit(Particle* particle);
			void flush() override;
			void begin() override;
		};

} }