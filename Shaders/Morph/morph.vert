#version 120

uniform sampler2DRect tex0;
uniform float scale;
uniform float time;
uniform float width;
uniform float height;
varying vec2 texCoordVarying;

void main(void)
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;
    
    
    // get the position of the vertex relative to the modelViewProjectionMatrix
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;
    
    float u = position.x / width  * 2 * 3.1415926;
    float v = position.y / height * 2 * 3.1415926;
    
  
    
    
    vec4 positionA  = gl_Vertex / width;
    vec4 positionB = gl_Vertex / width;
//
//    
    positionA.x = cos(2*u)/2.0;
    positionA.y = sin(u+v);
    positionA.z = cos(v);
    
    
    positionB.x = sin(v)*cos(u);
    positionB.y = sin(v)*sin(u);
    positionB.z = cos(v);
    
    positionA *= width;
    positionB *= width;

//    position /= width;
//    
//    position.x = cos(u);
//    position.y = sin(u);
//    position.z = v;
//    
//    position *= width;
//


    
    float morph = sin(time) * 0.5 + 0.5;
    
    vec4 morphedPosition = positionA * morph + positionB * (1.0 - morph);
    
    vec4 finalPosition = gl_Vertex * (1.0 - scale) + morphedPosition * scale;


	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * finalPosition;

}
