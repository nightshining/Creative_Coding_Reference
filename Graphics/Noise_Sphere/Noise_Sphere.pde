

/**
* noisy sphere ring
*
* @author aa_debdeb
* @date 2016/06/18
*/
 
float radious = 200;
float noiseScale = 0.01;
float timeScale = 0.03;
 
void setup(){
  size(500, 500, P3D);
}
 
void draw(){
  background(255);
  stroke(60);
  noFill();
  translate(width / 2, height / 2, -100);
  rotateZ(map(mouseX, 0, width, -PI * 2.0 / 3, PI * 2.0 / 3));
  rotateX(map(mouseY, 0, height, -PI * 2.0 / 3, PI * 2.0 / 3));
  for(float y = -radious * 2.0 / 3; y <= radious * 2.0 / 3; y += 3){
    float r = radious * cos(asin(abs(y / radious)));
    beginShape();
    for(float radian = 0; radian < TWO_PI; radian += PI / 128){
      float x = r * cos(radian);
      float z = r * sin(radian);
      float yy = y + map(noise(x * noiseScale, frameCount * timeScale, z * noiseScale) , 0, 1, -radious / 3, radious / 3);
      if(yy > radious){
        yy = radious;
      }
      float rr = radious * cos(asin(abs(yy / radious)));
      float xx = rr * cos(radian);
      float zz = rr * sin(radian);
      vertex(xx, yy, zz);
    }
    endShape(CLOSE);
  }
}