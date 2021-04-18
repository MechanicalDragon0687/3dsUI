#include <3ds.h>
#include <citro2d.h>
#include <string>
#include "gui/drawingHelper.hpp"
#include "gui/DataTypes.hpp"

void drawBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 color1, u32 color2) {
    //top
    C2D_DrawLine(topLeft.x-thickness/2,topLeft.y,color1,bottomRight.x+thickness/2,topLeft.y,color1,thickness,z);
    //left
    C2D_DrawLine(topLeft.x,topLeft.y,color1,topLeft.x,bottomRight.y+thickness/2,color1,thickness,z);
    //bottom
    C2D_DrawLine(bottomRight.x+thickness/2,bottomRight.y,color2,topLeft.x+thickness/2,bottomRight.y,color2,thickness,z);
    //right
    C2D_DrawLine(bottomRight.x,bottomRight.y,color2,bottomRight.x,topLeft.y+thickness/2,color2,thickness,z);
}
void drawBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 color1) {
    drawBox(topLeft,bottomRight,z,thickness,color1,color1);
}

void draw3dBox(Vector2f topLeft, Vector2f bottomRight, float z, float thickness, u32 bg, u32 border1, u32 border2) {
            //bg
            C2D_DrawRectSolid(topLeft.x,topLeft.y,z,bottomRight.x-topLeft.x,bottomRight.y-topLeft.y,bg);
            //borders
            drawBox(topLeft,bottomRight,z,thickness,border1,border2);
            //bottom-left-corner
            C2D_DrawTriangle(topLeft.x+thickness/2,bottomRight.y-thickness/2,border2,topLeft.x-thickness/2,bottomRight.y+thickness/2,border2,topLeft.x+thickness/2,bottomRight.y+thickness/2,border2,z);
            //top-right-corner
            C2D_DrawTriangle(bottomRight.x+thickness/2,topLeft.y-thickness/2,border2,bottomRight.x-thickness/2,topLeft.y+thickness/2,border2,bottomRight.x+thickness/2,topLeft.y+thickness/2,border2,z);
}
void drawText(Vector3f location, Vector2f size, float scale, u32 flags, u32 bgColor, u32 color, std::string label) {
            C2D_TextBuf buf=C2D_TextBufNew(4096);
            C2D_Text text;
            float w,h;
            float x=location.x;
            float y=location.y;
            C2D_TextParse(&text,buf,label.c_str());
            C2D_TextGetDimensions(&text,scale,scale,&w,&h);
            if (flags & VALIGN_CENTER) {
                y+=size.y/2;
                y-=h/2;
            }else if(flags & VALIGN_BOTTOM){
                flags|= C2D_AtBaseline;
            }
            C2D_TextOptimize(&text);
            if ((bgColor & 0xFF000000) > 0) {
                C2D_DrawRectSolid(x-w/2-3*scale,y-3*scale,location.z,w+6*scale,h+6*scale,bgColor);
            }
            C2D_DrawText(&text,(flags&0xFF) | C2D_WithColor,x,y,location.z,scale,scale,color);
            C2D_TextBufDelete(buf);
}