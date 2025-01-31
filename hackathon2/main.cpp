#include <iostream>
#include <vector>
#include <valarray>

class Goo {
private:
    float x;
    float y;
    float vx;
    float vy;
    std::vector<Goo> liens;
    std::vector<float> l0;
public:
    int distance(Goo A) {
        return (std::pow((x-A.x),2)+std::pow((y-A.y),2));
    }
    void update() {
        float m=0.4;
        float g=9.81/20;
        float k=100;
        x=x+vx;
        y=y+vy;
        float force_x=0;
        float force_y=-g;
        for (int i=0;i<liens.size();i++) {
            Goo A=liens[i];
            float theta=std::atan((A.y-y)/(A.x-x));
            float l_0=l0[i];
            if (A.x>x) {theta=theta+std::numbers::pi;}
            force_x=force_x+k/m*(distance(A)-l_0)*std::cos(theta);
            force_y=force_y+k/m*(distance(A)-l_0)*std::sin(theta);
        }
        vx=vx+force_x;
        vy=vy+force_y;
    }
};

int main() {

}