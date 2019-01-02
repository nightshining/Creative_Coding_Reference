PVector[] p = new PVector[10];
float t;
int curr;

void setup() {
  size(600, 600);
  noFill();
  for (int i = 0; i < p.length; i++) p[i] = new PVector();
  reset();
}

void draw() {
  background(255);
  for (int i = 0; i < p.length-1; i++) {
    line(p[i].x, p[i].y, p[i+1].x, p[i+1].y);
  }

  float tx = p[curr].x+t*(p[curr+1].x-p[curr].x);
  float ty = p[curr].y+t*(p[curr+1].y-p[curr].y);
  ellipse(tx, ty, 20, 20);

  if (t < 1.0) {
    t += 0.025;
    if (t > 1.0) {
      t = 0.0;
      if (curr < p.length-2) curr++;
      else t = 1.0;
    }
  }
}

void mousePressed() {
  reset();
}

void reset() {
  for (int i = 0; i < p.length; i++) {
    p[i].x = random(width);
    p[i].y = random(height);
  }
  t = 0.0;
  curr = 0;
}