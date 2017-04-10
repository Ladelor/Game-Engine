#include "ParticleRenderer.h"

namespace NumberOne {
	namespace Graphics {

		ParticleRenderer::ParticleRenderer(GLsizei maxParticles)
		{
			GLfloat vertexData[] =
			{
				0, 0, 0,
				1, 0, 0,
				0, 1, 0,
				1, 1, 0
			};

			glGenBuffers(1, &pr_vboBase);
			glBindBuffer(GL_ARRAY_BUFFER, pr_vboBase);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), NULL, GL_STATIC_DRAW);
			glEnableVertexAttribArray(SHADER_PARTICLE_OFFSET);
			glVertexAttribPointer(SHADER_PARTICLE_OFFSET, 3, GL_FLOAT, GL_FALSE, 0, (void*)NULL);
			
			glGenBuffers(1, &r_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
			glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(VertexData), NULL, GL_STREAM_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexData), vertexData);
			glEnableVertexAttribArray(SHADER_PARTICLE_POSITION);
		//	glEnableVertexAttribArray(SHADER_PARTICLE_UV);
		//	glEnableVertexAttribArray(SHADER_PARTICLE_TEXTUREID);
			glEnableVertexAttribArray(SHADER_PARTICLE_COLOR);
			glVertexAttribPointer(SHADER_PARTICLE_POSITION, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)NULL);
		//	glVertexAttribPointer(SHADER_PARTICLE_UV, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::v_uv));
		//	glVertexAttribPointer(SHADER_PARTICLE_TEXTUREID, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::v_tid));
			glVertexAttribPointer(SHADER_PARTICLE_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::v_color));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			pr_particleCount = 0;
		}

		ParticleRenderer::~ParticleRenderer()
		{

		}

		void ParticleRenderer::submit(const Renderable2D* renderable)
		{

		}

		void ParticleRenderer::submit(Particle* particle)
		{
		    //VertexData& vertexData = particle->p_vertexData;

			//float ts = 0.0f;

			pr_vertexData->v_color = particle->p_vertexData.v_color;
			pr_vertexData->v_position = particle->p_vertexData.v_position;
			pr_vertexData->v_tid = particle->p_vertexData.v_tid;
			pr_vertexData->v_uv = particle->p_vertexData.v_uv;
			pr_vertexData++;
			pr_particleCount++;
		}

		void ParticleRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, pr_particleCount * 4 * sizeof(VertexData), pr_vertexData);
			if (glGetError())
				std::cout << "Error" << std::endl;
			glVertexAttribDivisor(SHADER_PARTICLE_OFFSET, 0);
			glVertexAttribDivisor(SHADER_PARTICLE_POSITION, 1);
	//		glVertexAttribDivisor(SHADER_PARTICLE_UV, 1);
		//	glVertexAttribDivisor(SHADER_PARTICLE_TEXTUREID, 1);
			glVertexAttribDivisor(SHADER_PARTICLE_COLOR, 1);
			glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
			if (glGetError())
				std::cout << "Error" << std::endl;
			pr_vertexData = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void ParticleRenderer::flush()
		{
			if (glGetError())
				std::cout << "Error" << std::endl;
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			if (glGetError())
				std::cout << "Error" << std::endl;
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, pr_particleCount);
			if (glGetError())
				std::cout << "Error" << std::endl;
			pr_particleCount = 0;

		}


	}
}
