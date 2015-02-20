#include <iostream>

class FloatVectorFriend{
    float x;

// public:
//     void stealX(FloatVector fv){
//         x = fv.x;
//     }
};

class FloatVector{
    float x;
    float y;
    float z;

  friend void printVector(FloatVector);
  friend class FloatVectorFriend;

public:
  void stealX(FloatVectorFriend fvf){
    x = fvf.x;
  }
};

void printVector(FloatVector fv){
    std::cout << "[" << fv.x << "," << fv.y << "," << fv.z << "]";    
}

int main(){
    FloatVector fv;
    FloatVectorFriend f;

    //f.stealX(fv);
    printVector(fv);

    fv.stealX(f);

    return 0;
}
