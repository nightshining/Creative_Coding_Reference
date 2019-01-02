#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;
uniform float time;



void main( void ){

    vec4 col0 = texture2DRect( tex0, texCoordVarying );
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}