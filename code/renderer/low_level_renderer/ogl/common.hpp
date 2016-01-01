#ifndef COMMON_INCLUDED_
#define COMMON_INCLUDED_


#include <ostream>
#include <OpenGL/gl3.h>


namespace Ogl {


inline void
error_check(std::ostream *stream = nullptr, const char* msg = nullptr)
{
  if(stream) // Check stream first, if none given we don't want to clear the error.
  {
    const auto err_id = glGetError();

    if(err_id != GL_NO_ERROR)
    {
      (*stream) << err_id << " " << msg << "\n";
    }
  }
}


inline void
error_clear()
{
  glGetError();
}


} // ns


#endif // inc guard