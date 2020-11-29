#include "HelloOpenGLApp.h"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

HelloOpenGLApp::HelloOpenGLApp()
{

}

HelloOpenGLApp::~HelloOpenGLApp()
{

}

void HelloOpenGLApp::Load()
{
    static const char* vertex_shader =
        "attribute vec3 vp;"
        "attribute vec4 vc;"
        "varying vec4 fc;"
        "void main ()"
        "{"
        "  fc = vc;"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    static const char* fragment_shader =
        "precision mediump float; "
        "varying vec4 fc;"
        "void main ()"
        "{"
        "  gl_FragColor = fc;"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    m_shader = glCreateProgram();

    glAttachShader(m_shader, fs);
    glAttachShader(m_shader, vs);

    glBindAttribLocation(m_shader, 0, "vp");
    glBindAttribLocation(m_shader, 1, "vc");

    glLinkProgram(m_shader);

    glDeleteShader(vs);
    glDeleteShader(fs);


    float verts[] =
    {
        //   x,     y,    z,    r,    g,    b,    a  
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };

    unsigned char indices[] =
    {
        0, 1, 2
    };


    // Generate our VAO and Bind bind it.
    // Our VBO and IBO will be "grouped" with this VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create our VBO and IBO
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    // Bind these buffers as well
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    // Fill the Buffers with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Here we are describing the format of our vertices to openGL
    // Our vertices has only one Attribute - position, so attribute 0
    // this will describe to openGL the size, location & offset in memory for each vertex.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute 0 (position)
        3,                  // size - how many floats make up the position (x, y, z)
        GL_FLOAT,           // type - our x,y,z are float values
        GL_FALSE,           // normalized? - not used
        sizeof(float) * 7,  // stride - size of the entire vertex object
        (void*)0            // offset in bytes for the position component
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                  // attribute 1 (color)
        4,                  // size - how many floats make up the color (r, g, b, a)
        GL_FLOAT,           // type - our r,g,b,a are float values
        GL_FALSE,           // normalized? - not used
        sizeof(float) * 7,   // stride - size of the vertex
        (void*)(sizeof(float) * 3) // there are 3 floats before the r component
    );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void HelloOpenGLApp::UnLoad()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_shader);
}

void HelloOpenGLApp::Update()
{

}

void HelloOpenGLApp::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // tell openGL to use our shader program
    glUseProgram(m_shader);

    // Bind our VAO, remember, its grouped our VBO and IBO
    glBindVertexArray(m_vao);

    // Draw our buffers. We've hard coded 3, referring to the number of verts. 
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

    // unbind our VAO so nothing else accidental changes it
    glBindVertexArray(0);
}
