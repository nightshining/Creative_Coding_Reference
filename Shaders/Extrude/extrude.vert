#version 120

uniform sampler2DRect tex0;
uniform float scale;
varying vec2 texCoordVarying;

void main(void)
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;
    
   
    // get the position of the vertex relative to the modelViewProjectionMatrix
    vec4 position = gl_Vertex;
    vec2 sop;
    sop.x = texCoordVarying.y;
    sop.y = texCoordVarying.x ;
    
     vec4 col = texture2DRect( tex0, texCoordVarying );
    position.xyz += gl_Normal * col.r * scale;
   
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * position;

}
