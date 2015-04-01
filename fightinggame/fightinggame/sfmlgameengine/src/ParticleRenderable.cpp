#include "ParticleRenderable.h"

ParticleRenderable::ParticleRenderable()
{
	_generatedFlag	= false;

	std::cout << "Particle Renderer Start\n";
}

ParticleRenderable::~ParticleRenderable()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1,&_particlePositionBuffer);
	glDeleteBuffers(1,&_particleColourBuffer);
	glDeleteVertexArrays(1,&_vao);
	std::cout << "Particle Renderer End\n";
}
void ParticleRenderable::generate(SP_ParticleSystem s, size_t particlePool)
{
	//_particlePool = particlePool;
	if(_generatedFlag) 
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(1,&_particlePositionBuffer);
		glDeleteBuffers(1,&_particleColourBuffer);
		glDeleteVertexArrays(1,&_vao);
	}
	
	//_particleSystem.reset(new ParticleSystem(_particlePool));
	_generatedFlag=true;

	//_particleSystem->addEmitter(_emitter);
	//for(auto it : _updaters)
	//{
	//	_particleSystem->addUpdater(it);
	//}

	size_t count = particlePool;

	glGenVertexArrays(1,&_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1,&_particlePositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _particlePositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*count,nullptr,GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,(4)*sizeof(float),(void*)((0)*sizeof(float)));

	glGenBuffers(1,&_particleColourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,_particleColourBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*4*count,nullptr,GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,(4)*sizeof(float),(void*)((0)*sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
void ParticleRenderable::render(SP_ParticleSystem s)
{
	if(!_generatedFlag)return;
	
	//_shader->useProgram();

	glBindVertexArray(_vao);

	const size_t count = s->getAliveParticleCount();
	if(count > 0)
	{
		glDrawArrays(GL_POINTS , 0 , count); //Change to draw elements
	}

	glBindVertexArray(0);
}
 
void ParticleRenderable::updateBuffers(SP_ParticleSystem s)
{
	//if(!_generatedFlag)return;
	//if(_particleSystem->getParticleCount()<=0){return;}
	//if(_playFlag)
	//{
	//	s->update(t);
	
		const size_t count = s->getAliveParticleCount();
		if(count > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _particlePositionBuffer);
			float *ptr = (float *)(s->getFinalData()->_particlePositions.get());
			glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float)*4, ptr);

			glBindBuffer(GL_ARRAY_BUFFER, _particleColourBuffer);
			ptr = (float *)(s->getFinalData()->_particleColours.get());
			glBufferSubData(GL_ARRAY_BUFFER, 0, count*sizeof(float)*4,ptr);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	//}
}
//void ParticleRenderer::resetParticles()
//{
//	if(_particleSystem!=nullptr)
//		_particleSystem->reset();
//}
//void ParticleRenderer::addEmitter(SP_ParticleEmitter em)
//{
//	_emitter=em;
//	//_particleSystem->addEmitter(em);
//}
//void ParticleRenderer::addUpdater(SP_ParticleUpdater up)
//{
//	_updaters.push_back(up);
//	//_particleSystem->addUpdater(up);
//}
//
//void ParticleRenderable::clear()
//{
//	_updaters.clear();
//}
//void ParticleRenderable::setParticlePointSize(float size)
//{
//	_shader->setUniform("u_PointSize",size);
//}
//void ParticleRenderable::setAnimFlag(bool f)
//{
//	_playFlag = f;
//}
//void ParticleRenderable::setDispFlag(bool f)
//{
//	_renderFlag = f;
//}
//void ParticleRenderable::setEmitFlag(bool f)
//{
//	if(_particleSystem!=nullptr)
//		_particleSystem->_emitFlag=f;
//}
//bool ParticleRenderable::getEmitFlag()
//{
//	if(_particleSystem!=nullptr)
//	return _particleSystem->_emitFlag;
//	else
//	{
//		return false;
//	}
//}
