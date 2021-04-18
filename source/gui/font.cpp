
#include <3ds.h>
#include <citro2d.h>
#include <string>
#include "gui/DataTypes.hpp"
#include "gui/font.hpp"

Vector2f getTextDimensions(std::string text, float scale) {
  float w,h;
  C2D_TextBuf buf = C2D_TextBufNew(4096);
  C2D_Text t;
  C2D_TextParse(&t,buf,text.c_str());
  C2D_TextGetDimensions(&t,scale,scale,&w,&h);
  C2D_TextBufDelete(buf);
  return {w,h};
}

