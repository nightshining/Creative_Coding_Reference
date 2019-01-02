var master_vert = 
`
uniform sampler2D tex_feedback;
uniform vec2 mouse;
uniform bool is_init;
uniform float t;

uniform vec2 aperture_locs[4];
uniform float aperture_sizes[4];
uniform float aperture_size_magnifiers[4];

uniform bool is_attract;
uniform float attract_transition_frame;

uniform bool is_unidirection;

varying float v_size;
varying float v_fbm;
varying float v_line_render_factor;

float hash( float n ){return fract(sin(n)*43758.5453);}
float cal_noise( vec2 x ){
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0;
    return mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);
}

void main() {
    float aspect = screen_res.x / screen_res.y;

    vec3 pos = position;

    pos += .5;
    pos.y += t*.99 + .5*attract_transition_frame;
    pos = fract(pos) - .5;

    const float bound = .48;
    if(pos.y < -bound || pos.y > bound || pos.x < -bound || pos.x > bound)
        v_line_render_factor = 0.;
    else 
        v_line_render_factor = 1.;

    vec2 feedback = texture2D(tex_feedback, uv).rg;
    pos.xy += feedback*3.;

    float noise_a = cal_noise(vec2(uv.x, uv.y + t * .4) * 10.);
    float noise_b = cal_noise(vec2(uv.x, uv.y - t * 1.) * 2.);
    float noise_c = cal_noise(vec2(uv.x + t * .1, uv.y) * 50.);
    float fbm = (noise_a + noise_b + noise_c)/3.;

    if(is_unidirection){
        pos.xy *= 1.2; 
        pos.y += (fbm * .2 - .1) * aspect;
        pos.x += fbm * .2 - .1;
    } else {
        const float complexity = 13.;
        vec2 rand_dir = vec2(cal_noise(uv*complexity), cal_noise(uv.yx*complexity))-.5;
        pos.xy += rand_dir * fbm * .4;
    }

    // apertures 
    for(int i = 0; i < 4; i++){
        float _dist = distance(aperture_locs[i], pos.xy);
        vec2 _dir = normalize(pos.xy - aperture_locs[i]);
        vec2 _f = _dir * .00001/(_dist * _dist) * aperture_sizes[i] * pow(aperture_size_magnifiers[i], 2.);
        
        pos.xy += _f;
    }

    pos.y *= aspect;

    float size = pow(fbm, 1.) * 2. + length(feedback)*10.;

    float size_mag = 20. + 20. * attract_transition_frame; 
    gl_PointSize = size * size_mag;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(pos, 1.);

    v_size = size * .1;
    v_fbm = 1. - pow(fbm, 4.) + length(feedback)*10.;
}
`;