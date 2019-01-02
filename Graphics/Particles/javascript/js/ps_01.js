// this classs rely on threejs lib 
// threejs must be loaded before this object is loaded

var ps_01 = function(){
    this.SQRT_NUM_PARTICLES = 256;

    this.timer = 0.;

    this.dom_a;
    this.is_dom_a = false;

    this.mouse_norm_x = 0;
    this.mouse_norm_y = 0;
    this.p_mouse_norm_x = 0;
    this.p_mouse_norm_y = 0;
    this.mouse_delta_x = 0;
    this.mouse_delta_y = 0;
    this.mouse_x = 0;
    this.mouse_y = 0;

    this.w = document.documentElement.clientWidth;
    this.h = document.documentElement.clientHeight;

    this.tex_noise = new THREE.TextureLoader().load( "assets/noise.jpg" );
    this.tex_noise.wrapS = THREE.ClampToEdgeWrapping;
    this.tex_noise.wrapT = THREE.ClampToEdgeWrapping;
    this.tex_noise.magFilter = THREE.LinearFilter;
    this.tex_noise.minFilter = THREE.LinearFilter;

    this.tex_sprite = new THREE.TextureLoader().load( "assets/sprite.png" );
    this.tex_sprite.wrapS = THREE.ClampToEdgeWrapping;
    this.tex_sprite.wrapT = THREE.ClampToEdgeWrapping;
    this.tex_sprite.magFilter = THREE.LinearFilter;
    this.tex_sprite.minFilter = THREE.LinearFilter;

    this.matrix = new THREE.OrthographicCamera( 
        this.w / - 2, 
        this.w / 2, 
        this.h / 2, 
        this.h / - 2, 
        1, 1000 );
    this.matrix.position.z = 10;

    this.fbo_vel_src = this.init_fbo(this.w, this.h);
    this.fbo_vel_dst = this.init_fbo(this.w, this.h);
    this.fbo_feedback_src = this.init_fbo(this.w, this.h);
    this.fbo_feedback_dst = this.init_fbo(this.w, this.h);

    this.shdr_master = this.init_shdr("shdr_master_vert", "shdr_master_frag");
    this.shdr_master.uniforms = {
        resolution: {value: new THREE.Vector2(this.w, this.h)},
        mouse: {value: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        mouse_delta: {value: new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y)},
        tex_sprite: {value: this.tex_sprite},
        tex_vel: {value: this.fbo_vel_src.texture.image},
        t: {value: 0}
    };
    this.shdr_master.blending = THREE.AdditiveBlending;
    this.shdr_master.transparent = true;

    this.shdr_vel = this.init_shdr("shdr_master_vert", "shdr_vel_frag");
    this.shdr_vel.uniforms = {
        resolution: {value: new THREE.Vector2(this.w, this.h)},
        mouse: {value: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        mouse_delta: {value: new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y)},
        tex_p_vel: {value: this.fbo_vel_src.texture},
        tex_noise: {value: this.tex_noise },
        t: {value: 0}
    };

    this.shdr_feedback = this.init_shdr("shdr_master_vert", "shdr_feedback_frag");
    this.shdr_feedback.uniforms = {
        resolution: {value: new THREE.Vector2(this.w, this.h)},
        mouse: {value: new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y)},
        mouse_delta: {value: new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y)},
        tex_vel: {value: this.fbo_vel_dst.texture},
        tex_p_feedback: {value: this.fbo_feedback_src.texture},
        tex_noise: {value: this.tex_noise },
        t: {value: 0}
    };

    this.geom = new THREE.BufferGeometry();
    var _pos = new Float32Array( this.SQRT_NUM_PARTICLES * this.SQRT_NUM_PARTICLES * 3);
    var _uv = new Float32Array( this.SQRT_NUM_PARTICLES * this.SQRT_NUM_PARTICLES * 2);
    var _pi = 0, _ui = 0;
    var _size = this.SQRT_NUM_PARTICLES;
    for(var i = 0; i < _size; i++){
        for(var j = 0; j < _size; j++){
            var _x = i * this.w/_size - this.w/2;
            var _y = j * this.h/_size - this.h/2;
            
            _pos[_pi++] = _x;
            _pos[_pi++] = _y;
            _pos[_pi++] = 0;

            _uv[_ui++] = i / (_size - 1);
            _uv[_ui++] = j / (_size - 1);
        }
    }
    this.geom.addAttribute("position", new THREE.BufferAttribute( _pos, 3 ) );
    this.geom.addAttribute("uv", new THREE.BufferAttribute( _uv, 2 ) );

    this.scene = new THREE.Scene();
    this.particles = new THREE.Points(this.geom, this.shdr_master);
    this.scene.add(this.particles);

    var quad_geom = new THREE.PlaneGeometry(this.w, this.h); 
    this.fbo_scene_vel = new THREE.Scene();
    this.fbo_scene_vel.add( new THREE.Mesh( quad_geom, this.shdr_vel ));
    this.fbo_scene_feedback = new THREE.Scene();
    this.fbo_scene_feedback.add( new THREE.Mesh( quad_geom, this.shdr_feedback ));

    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setPixelRatio( window.devicePixelRatio );
    this.renderer.setSize( this.w, this.h );
    console.log("ps_01::: renderer is set with", this.w, "by", this.h);

    window.addEventListener( 'resize', this.resize.bind(this), false );
    console.log("ps_01::: resize() is registered to window resize event listener");

    document.body.addEventListener("mousemove", this.mouse_handler.bind(this), false);
    document.body.addEventListener("touchmove", this.mouse_handler.bind(this), false);
    console.log("ps_01::: mouse_handler() is registered to body mousemove event listener");

    document.addEventListener('touchstart', function(event){
        event.preventDefault();
    }, {passive: false});
    console.log("ps_01::: preventDefault is enabled");
};

ps_01.prototype.render = function(){
    requestAnimationFrame( this.render.bind(this) );

    this.update();
};

ps_01.prototype.update = function(){ 

    this.shdr_vel.uniforms.resolution.value = new THREE.Vector2(this.w, this.h);
    this.shdr_vel.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_vel.uniforms.mouse_delta.value = new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y);
    this.shdr_vel.uniforms.tex_p_vel.value = this.fbo_vel_src.texture;
    this.shdr_vel.uniforms.t.value = this.timer;
    this.renderer.render(this.fbo_scene_vel, this.matrix, this.fbo_vel_dst);

    this.shdr_feedback.uniforms.resolution.value = new THREE.Vector2(this.w, this.h);
    this.shdr_feedback.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_feedback.uniforms.mouse_delta.value = new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y);
    this.shdr_feedback.uniforms.tex_vel.value = this.fbo_vel_dst.texture;
    this.shdr_feedback.uniforms.tex_p_feedback.value = this.fbo_feedback_src.texture;
    this.shdr_feedback.uniforms.t.value = this.timer;
    this.renderer.render(this.fbo_scene_feedback, this.matrix, this.fbo_feedback_dst);

    var _temp = this.fbo_vel_src;
    this.fbo_vel_src = this.fbo_vel_dst;
    this.fbo_vel_dst = _temp;

    _temp = this.fbo_feedback_src;
    this.fbo_feedback_src = this.fbo_feedback_dst;
    this.fbo_feedback_dst = _temp;

    this.shdr_master.uniforms.resolution.value = new THREE.Vector2(this.w, this.h);
    this.shdr_master.uniforms.mouse.value = new THREE.Vector2(this.mouse_norm_x, this.mouse_norm_y);
    this.shdr_master.uniforms.mouse_delta.value = new THREE.Vector2(this.mouse_delta_x, this.mouse_delta_y);
    this.shdr_master.uniforms.tex_vel.value = this.fbo_feedback_src.texture; 
    this.shdr_master.uniforms.t.value = this.timer;
    this.renderer.render( this.scene, this.matrix );

    this.timer+= .001;
    if(this.timer > 999999.)
        this.timer = 0.;

    // update doms
    if(this.is_dom_a)
        this.update_dom_a();
};

ps_01.prototype.mouse_handler = function(_evt){
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

    this.mouse_delta_x = this.mouse_norm_x - this.p_mouse_norm_x;
    this.mouse_delta_y = this.mouse_norm_y - this.p_mouse_norm_y;

    this.p_mouse_norm_x = this.mouse_norm_x;
    this.p_mouse_norm_y = this.mouse_norm_y;
};

ps_01.prototype.init_fbo = function(_w, _h){
    var _format = {
      wrapS: THREE.ClampToEdgeWrapping,
      wrapT: THREE.ClampToEdgeWrapping,
      minFilter:THREE.LinearFilter,
      magFilter: THREE.LinearFilter,
      // type: THREE.FloatType,
      format: THREE.RGBFormat,
      stencilBuffer:false,
      depthBuffer:false
    };
    return new THREE.WebGLRenderTarget( _w, _h, _format);
};

ps_01.prototype.init_shdr = function(_vert, _frag){
    console.log(document.getElementById( _vert ));
    return new THREE.ShaderMaterial( 
        { 
            vertexShader:   document.getElementById( _vert ).textContent,
            fragmentShader: document.getElementById( _frag ).textContent
        } 
    );
};

ps_01.prototype.append_renderer_to_dom = function(_target){
    _target.appendChild(this.renderer.domElement);

    console.log("ps_01::: renderer is appended to", _target.nodeName);
};

// TODO
ps_01.prototype.register_dom_a = function(_dom){
    this.dom_a = _dom;

    this.is_dom_a = true;
};

ps_01.prototype.update_dom_a = function(){
    // this.dom_a.style["left"] = (this.mouse_x - 100).toString() + "px";
    // this.dom_a.style["top"] = (this.mouse_y - 100).toString() + "px";
};

ps_01.prototype.resize = function(){
    this.w = window.innerWidth;
    this.h = window.innerHeight;

    this.aspect = this.w / this.h;

    this.matrix.left   = this.w / - 2;
    this.matrix.right  =   this.w / 2;
    this.matrix.top    =   this.h / 2;
    this.matrix.bottom = this.h / - 2;
    this.matrix.updateProjectionMatrix();

    this.renderer.setSize( this.w, this.h );

    console.log("ps_01::: renderer is resized with", this.w, "by", this.h);
};