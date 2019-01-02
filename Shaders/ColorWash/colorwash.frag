#version 120

uniform float radius;
uniform vec3 color;
uniform vec2 origin;
uniform vec2 offset;

void main(){
	vec2 pos = gl_FragCoord.xy + offset;
    
    float dist = distance(pos, origin);
    float alpha;
    
    if (dist < radius) {
         alpha = 1.0 - (dist / radius);
    }
    else {
        alpha = 0.0;
    }
    
    gl_FragColor = vec4(color, alpha);
}


//void main(){
//    vec3 twitBlue = vec3(0.3333333, 0.674, 0.9333);
//    vec3 twitFadedGray = vec3(0.886, 0.913, 0.929);
//    vec3 combined;
//    
//    vec2 pos = gl_FragCoord.xy;
//    vec2 origin = vec2(512.0, 384.0);
//    
//    float dist = distance(pos, origin);
//    
//    if (dist < radius) {
//        float ratio = dist / radius;
//        combined = twitBlue * ratio + twitFadedGray * (1.0 - ratio);
//    }
//    else {
//        combined = twitBlue;
//    }
//    
//    gl_FragColor = vec4(combined, 1.0);
//}