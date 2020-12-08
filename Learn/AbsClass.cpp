
#include <memory>
#include <iostream>

class AbsObject{
    public:
    virtual bool update() =0;
};

class Object : public AbsObject{
    public:
    virtual bool update(){
        std::cout << "Object update" << std::endl;
        return true;
    }
};

class Other{
    public:
    Other(std::shared_ptr<AbsObject> object){
        object->update();
    }
};

int main(int argc, char **argv){
    std::shared_ptr<AbsObject> obj(new Object());
    Other other(obj);
    return 0;
}