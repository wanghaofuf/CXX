#include  <iostream>
#include <memory>
class Test{
    public:
    explicit Test(int num):i(num){}
    ~Test(){
        std::cout << "~Test" << std::endl;
    }
    int i;
};

void testAuto(){
    auto pt = new Test(1);
    std::cout << pt->i << std::endl;
    delete pt;
    std::auto_ptr<Test> p(new Test(2));
    std::cout << p->i++ << std::endl;
    std::auto_ptr<Test> p2=p;
    //  (p is now null-pointer auto_ptr)
    std::cout << p2->i << std::endl;
    p2.get()->i++;
    Test* pt2 = p2.release();
    //  (p2 is now null-pointer auto_ptr)
    std::cout << pt2->i << std::endl;
    delete pt2;
    std::auto_ptr<Test> p5(new Test(5));
    std::cout << p5->i << std::endl;
}

int main(int argc, char **argv){

    auto i = 0;
    auto s ="str";
    testAuto();    
    return 0;
}
