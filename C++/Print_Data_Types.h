#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int a = 3;
    long b = 12345678912345;
    char c = 'a';
    float d = 334.23;
    double e = 14049.30493;
    
    //%.02f/n  .02 decimal place stop - float - end line
    printf("%i\n%li\n%c\n%.02f\n%.01lf\n", a,b,c,d,e);
    
    return 0;
}
