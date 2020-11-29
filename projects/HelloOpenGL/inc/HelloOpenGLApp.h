
#pragma once

#include "Application.h"

class HelloOpenGLApp : public Application
{
public:

	HelloOpenGLApp();
	virtual ~HelloOpenGLApp();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update();
	virtual void Render();

protected:
private:

	unsigned int m_vao; // handle for a vertex array object (wrapper for our vbo and ibo)
	unsigned int m_vbo; // handle for vertex buffer object
	unsigned int m_ibo; // handle for index buffer object

	unsigned int m_shader; // handle for our shader program
};