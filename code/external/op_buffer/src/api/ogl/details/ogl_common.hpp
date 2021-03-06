#ifdef OP_BUFFER_API_OGL
#ifndef COMMON_INCLUDED_9D778023_6B77_4216_86C6_B1FBB1505C74
#define COMMON_INCLUDED_9D778023_6B77_4216_86C6_B1FBB1505C74


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <GLES2/gl2.h>
#elif __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#elif __linux__
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#elif _WIN32
#include <GL/gl.h>
#include <GL/glext.h>
// Glew or somesuch needs to go here
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#ifdef OP_BUFFER_API_OGL_ES2
#define OGL_GLES2
#endif

#ifdef OGL_GLES2
#define OGL_GLES2_SAMPLERS
// #define OGL_HAS_CONTEXT_LOST_ERROR
#else
#define OGL_GL
#define OGL_HAS_VAO
#define OGL_HAS_GL_QUADS
#define OGL_HAS_GEOMETRY_SHADER
#define OGL_HAS_TEXTURE_1D
#define OGL_HAS_TEXTURE_3D

#ifdef __APPLE__
#define OGL_HAS_DEBUG_MARKER // temporary.
#endif

#define OGL_HAS_GL_RED
#endif


// -- List of GL Related Defines In Code -- //

// -- GL VERSIONS -- //
// OGL_GLES2
// OGL_GL4

// -- GL Features -- //
// OGL_GLES2_SAMPLERS
// OGL_HAS_VAO
// OGL_HAS_GL_QUADS
// OGL_HAS_GEOMETRY_SHADER
// OGL_HAS_CONTEXT_LOST_ERROR
// OGL_HAS_TEXTURE_1D
// OGL_HAS_TEXTURE_3D



#endif // inc guard
#endif // ogl guard
