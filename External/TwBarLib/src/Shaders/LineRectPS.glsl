//  ---------------------------------------------------------------------------
//
//  @file       LineRectPS.glsl
//  @author     Egor Yusov
//	@brief		Source code of the LineRectPS OpenGL pixel shader
//
//  ---------------------------------------------------------------------------

 
layout(location = 1) in vec4 Color;

layout(location = 0) out vec4 out_Color;

void main()
{ 
    out_Color = Color; 
}
