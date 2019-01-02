// this classs rely on threejs lib 
// threejs must be loaded before this object is loaded

var ps_02 = function(){
    this.SQRT_NUM_PARTICLES = 64;

    this.timer = 0.;

    this.is_init = false;

    this.w = document.documentElement.clientWidth;
    this.h = document.documentElement.clientHeight;

    this.tex_sprite = new THREE.TextureLoader().load( "assets/sprite_additive.png" );
    this.tex_sprite.magFilter = THREE.LinearFilter;
    this.tex_sprite.minFilter = THREE.LinearFilter;

    this.matrix = new THREE.OrthographicCamera( -.5, .5, .5, -.5, 1, 10 );
    this.matrix.position.z = 1;

    this.fbo_master = this.init_fbo(this.w, this.h);
    this.fbo_pp_src = this.init_fbo(this.w, this.h);
    this.fbo_pp_dst = this.init_fbo(this.w, this.h);
    this.fbo_pos_src = this.init_fbo(this.SQRT_NUM_PARTICLES, this.SQRT_NUM_PARTICLES);
    this.fbo_pos_dst = this.init_fbo(this.SQRT_NUM_PARTICLES, this.SQRT_NUM_PARTICLES);
    this.fbo_vel_src = this.init_fbo(this.SQRT_NUM_PARTICLES, this.SQRT_NUM_PARTICLES);
    this.fbo_vel_dst = this.init_fbo(this.SQRT_NUM_PARTICLES, this.SQRT_NUM_PARTICLES);

    this.shdr_master = this.init_shdr("shdr_master_vert", "shdr_master_frag");
    this.shdr_master.uniforms = {
        tex_sprite: {value: this.tex_sprite},
        tex_pos: {value: this.fbo_pos_src.texture},
        tex_vel: {value: this.fbo_vel_src.texture},
        mouse: {valuse: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        is_init: {value: false},
        t: {value: 0}
    };
    this.shdr_master.defines.screen_res = 'vec2( ' + this.w.toFixed( 1 ) +', ' + this.h.toFixed( 1 ) + ')';
    this.shdr_master.blending = THREE.AdditiveBlending;
    this.shdr_master.transparent = true;
    this.shdr_master.alphaTest = 1.;
    this.shdr_master.depthTest = false;

    this.shdr_standard = this.init_shdr("shdr_master_vert", "shdr_standard_frag");
    this.shdr_standard.uniforms = {
        tex_pos: {value: this.fbo_pos_src.texture},
        tex_vel: {value: this.fbo_vel_src.texture},
        mouse: {valuse: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        is_init: {value: false},
        t: {value: 0}
    };
    this.shdr_standard.defines.screen_res = 'vec2( ' + this.w.toFixed( 1 ) +', ' + this.h.toFixed( 1 ) + ')';
    this.shdr_standard.blending = THREE.AdditiveBlending;
    this.shdr_standard.transparent = true;
    this.shdr_standard.depthTest = false;


    this.shdr_pos = this.init_shdr("shdr_vert", "shdr_pos_frag");
    this.shdr_pos.uniforms = {
        resolution: {value: new THREE.Vector2(this.SQRT_NUM_PARTICLES, this.SQRT_NUM_PARTICLES)},
        tex_vel: {value: this.fbo_vel_src.texture},
        tex_p_pos: {value: this.fbo_pos_src.texture},
        mouse: {valuse: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        is_init: {value: false},
        t: {value: 0}
    };
    this.shdr_pos.transparent = false;
    this.shdr_pos.depthTest = false;

    this.shdr_vel = this.init_shdr("shdr_vert", "shdr_vel_frag");
    this.shdr_vel.uniforms = {
        tex_pos: {value:this.fbo_pos_src.texture},
        tex_p_vel: {value: this.fbo_vel_src.texture},
        tex_noise: {value: this.tex_noise },
        mouse: {valuse: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        is_init: {value: false},
        t: {value: 0}
    };
    // this.shdr_vel.extensions.drawBuffers = true;
    this.shdr_vel.defines.res = 'vec2( ' + this.SQRT_NUM_PARTICLES.toFixed( 1 ) +', ' + this.SQRT_NUM_PARTICLES.toFixed( 1 ) + ')';
    this.shdr_vel.defines.screen_res = 'vec2( ' + this.w.toFixed( 1 ) +', ' + this.h.toFixed( 1 ) + ')';
    this.shdr_vel.transparent = false;
    this.shdr_vel.depthTest = false;

    var geom = new THREE.BufferGeometry();
    var _pos = new Float32Array( this.SQRT_NUM_PARTICLES * this.SQRT_NUM_PARTICLES * 3);
    var _uv = new Float32Array( this.SQRT_NUM_PARTICLES * this.SQRT_NUM_PARTICLES * 2);
    var _pi = 0, _ui = 0;
    var _size = this.SQRT_NUM_PARTICLES;
    for(var i = 0; i < _size; i++){
        for(var j = 0; j < _size; j++){
            _pos[_pi++] = 0;
            _pos[_pi++] = 0;
            _pos[_pi++] = 0;

            _uv[_ui++] = i / (_size - 1);
            _uv[_ui++] = j / (_size - 1);
        }
    }
    geom.addAttribute("position", new THREE.BufferAttribute( _pos, 3 ) );
    geom.addAttribute("uv", new THREE.BufferAttribute( _uv, 2 ) );

    this.scene = new THREE.Scene();
    var particles = new THREE.Points(geom, this.shdr_master);
    particles.matrixAutoUpdate = false;
    particles.updateMatrix();

    this.scene.add(particles);

    var line = new THREE.Line(geom, this.shdr_standard);
    this.scene.add(line);

    var quad_geom = new THREE.PlaneGeometry(1., 1.); 
    this.fbo_scene_pos = new THREE.Scene();
    this.fbo_scene_pos.add( new THREE.Mesh( quad_geom, this.shdr_pos ));
    this.fbo_scene_vel = new THREE.Scene();
    this.fbo_scene_vel.add( new THREE.Mesh( quad_geom, this.shdr_vel ));

    this.renderer = new THREE.WebGLRenderer();
    this.renderer.antialias = false;
    this.renderer.depth = false;
    this.renderer.setPixelRatio( window.devicePixelRatio );
    this.renderer.setSize( this.w, this.h );
    
    console.log("ps_02::: renderer is set with", this.w, "by", this.h);

    document.body.addEventListener("mousemove", this.mouse_handler.bind(this), false);
    document.body.addEventListener("touchmove", this.mouse_handler.bind(this), false);
    console.log("ps_02::: mouse_handler() is registered to body mousemove event listener");

    document.addEventListener('touchstart', function(event){
        event.preventDefault();
    }, {passive: false});
    console.log("ps_01::: preventDefault is enabled");
};

ps_02.prototype.render = function(){
    requestAnimationFrame( this.render.bind(this) );

    this.update();
};

ps_02.prototype.update = function(){ 
    this.shdr_vel.uniforms.tex_pos.value = this.fbo_pos_src.texture;
    this.shdr_vel.uniforms.tex_p_vel.value = this.fbo_vel_src.texture;
    this.shdr_vel.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_vel.uniforms.t.value = this.timer;
    this.shdr_vel.uniforms.is_init.value = this.is_init;
    this.renderer.render(this.fbo_scene_vel, this.matrix, this.fbo_vel_dst);

    this.shdr_pos.uniforms.tex_vel.value = this.fbo_vel_dst.texture;
    this.shdr_pos.uniforms.tex_p_pos.value = this.fbo_pos_src.texture;
    this.shdr_pos.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_pos.uniforms.t.value = this.timer;
    this.shdr_pos.uniforms.is_init.value = this.is_init;
    this.renderer.render(this.fbo_scene_pos, this.matrix, this.fbo_pos_dst);

    var _temp;
    _temp = this.fbo_vel_src;   this.fbo_vel_src = this.fbo_vel_dst;   this.fbo_vel_dst = _temp;
    _temp = this.fbo_pos_src;   this.fbo_pos_src = this.fbo_pos_dst;   this.fbo_pos_dst = _temp;

    this.shdr_standard.uniforms.tex_pos.value = this.fbo_pos_src.texture;
    this.shdr_standard.uniforms.tex_vel.value = this.fbo_vel_src.texture;
    this.shdr_standard.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_standard.uniforms.is_init.value = this.is_init;
    this.shdr_standard.uniforms.t.value = this.timer;

    this.shdr_master.uniforms.tex_pos.value = this.fbo_pos_src.texture;
    this.shdr_master.uniforms.tex_vel.value = this.fbo_vel_src.texture;
    this.shdr_master.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_master.uniforms.is_init.value = this.is_init;
    this.shdr_master.uniforms.t.value = this.timer;
    this.renderer.render( this.scene, this.matrix,  );

    this.timer+= .001;
    if(this.timer > 999999.){
        this.timer = 0.;
    }

    // update doms
    if(this.is_dom_a){
        this.update_dom_a();
    }


    if(!this.is_init){ 
        this.is_init = true;
        console.log("ps_02::is initiated");
    }
};

ps_02.prototype.mouse_handler = function(_evt){
    if(_evt.targetTouches && _evt.targetTouches.length == 1){
        var touch = event.targetTouches[0];

        this.mouse_x = touch.pageX;
        this.mouse_y = touch.pageY;
    } else {
        this.mouse_x = _evt.clientX;
        this.mouse_y = _evt.clientY;
    }

    this.mouse_norm_x = this.mouse_x / this.w;
    this.mouse_norm_y = 1. - this.mouse_y / this.h;
};

// TODO
ps_02.prototype.register_dom_a = function(_dom){
    this.dom_a = _dom;

    this.is_dom_a = true;
};

ps_02.prototype.update_dom_a = function(){
    this.dom_a.style["left"] = (this.mouse_x - 100).toString() + "px";
    this.dom_a.style["top"] = (this.mouse_y - 100).toString() + "px";
};

ps_02.prototype.init_fbo = function(_w, _h){
    var _format = {
        type: THREE.FloatType,
        minFilter: THREE.NearestFilter,
        magFilter: THREE.NearestFilter,
        stencilBuffer:false,
        depthBuffer:false
    };
    return new THREE.WebGLRenderTarget( _w, _h, _format);
};

ps_02.prototype.init_shdr = function(_vert, _frag){
    return new THREE.ShaderMaterial( 
        { 
            vertexShader:   document.getElementById( _vert ).textContent,
            fragmentShader: document.getElementById( _frag ).textContent
        } 
    );
};

ps_02.prototype.append_renderer_to_dom = function(_target){
    _target.appendChild(this.renderer.domElement);

    console.log("ps_02::: renderer is appended to", _target.nodeName);
};

// TODO
ps_02.prototype.register_dom_a = function(_dom){
    this.dom_a = _dom;

    this.is_dom_a = true;
};

ps_02.prototype.update_dom_a = function(){
    this.dom_a.style["left"] = (this.mouse_x - 100).toString() + "px";
    this.dom_a.style["top"] = (this.mouse_y - 100).toString() + "px";
};