var vel_frag = 
`
uniform sampler2D tex_p_vel;
uniform sampler2D tex_noise;
uniform vec2 mouse;
uniform vec2 mouse_delta;
uniform float t;

uniform bool is_attract;
uniform float attract_transition_frame;

vec4 advect(sampler2D _tex, vec2 _uv, vec2 _dir, float _texel){
    //https://www.shadertoy.com/view/MsyXRW
    const float _G0 = .25;
    const float _G1 = .125;
    const float _G2 = .0625;
    const float ADVECT_DIST = 2.;

    vec2 uv = _uv - _dir * ADVECT_DIST * _texel;

    vec2 n  = vec2( 0., 1.);
    vec2 ne = vec2( 1., 1.);
    vec2 e  = vec2( 1., 0.);
    vec2 se = vec2( 1.,-1.);
    vec2 s  = vec2( 0.,-1.);
    vec2 sw = vec2(-1.,-1.);
    vec2 w  = vec2(-1., 0.);
    vec2 nw = vec2(-1., 1.);

    vec4 c =    texture2D(_tex, fract(uv));
    vec4 c_n =  texture2D(_tex, fract(uv+_texel*n));
    vec4 c_e =  texture2D(_tex, fract(uv+_texel*e));
    vec4 c_s =  texture2D(_tex, fract(uv+_texel*s));
    vec4 c_w =  texture2D(_tex, fract(uv+_texel*w));
    vec4 c_nw = texture2D(_tex, fract(uv+_texel*nw));
    vec4 c_sw = texture2D(_tex, fract(uv+_texel*sw));
    vec4 c_ne = texture2D(_tex, fract(uv+_texel*ne));
    vec4 c_se = texture2D(_tex, fract(uv+_texel*se));

    return _G0*c+_G1*(c_n+c_e+c_w+c_s)+_G2*(c_nw+c_sw+c_ne+c_se);
}
float circle(vec2 _st, vec2 _center, float _radius){
    vec2 dist = _st-_center;
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
    vec2 uv = gl_FragCoord.xy / buffer_res;
    vec2 t_mouse = mouse;
    t_mouse.y -= t*.99; // need to match with pos offset 
    t_mouse = fract(t_mouse);

    vec2 dir = mouse_delta * 5.;
    float dist = pow( distance(uv, t_mouse), 2.)*10.;
    float c = circle(uv, t_mouse, .01);

    vec2 swir_dir = normalize(uv - t_mouse);
    float swir_dist = .3 - distance(uv, t_mouse);
    swir_dist = swir_dist < 0. ? 0. : swir_dist;
    vec2 swir_f = swir_dir * swir_dist * 10.;
     
    float noise_intensity = 1.;
    vec3 noise = (texture2D(tex_noise, fract(uv + vec2(t ,  t * 1.)) ).rgb - .5) * 2. *  noise_intensity; 
    vec3 p_vel = advect(tex_p_vel, uv, noise.rg + swir_f, 1./1024.).rgb + c * vec3(dir, 0) * dist;

    vec3 vel = p_vel;
    vel *= .96;

    if(length(vel) < .01 && is_attract)
        vel = noise * attract_transition_frame * .005;

    gl_FragColor = vec4(vel,1);
}`;