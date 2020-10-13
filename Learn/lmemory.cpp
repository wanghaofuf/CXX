#include <iostream>
#include <memory>
struct B{
    std::string name;
    int num;
    B(std::string name):name(name){}
    ~B() {
        std::cout << "~B " << name <<std::endl;
    }
};
struct A{
    std::string name;
    B* pb=NULL;
    std::shared_ptr<B> spb;
    A(std::string name):name(name){
        pb = new B("pb");
    }
    ~A(){
        if(NULL!=pb){delete pb;}
        std::cout << "~A " << name << std::endl;
    }
};

void testoldpoint(){
    A* pa = new A("old pa");
    if(NULL==pa->pb) pa->pb = new B("old pb");
    delete pa;
    pa= NULL;
}

void testshare_ptr(){
    std::cout << "testshare_ptr start" << std::endl;
    std::shared_ptr<A> spA (new A("spA"));
    std::cout << spA->name << std::endl;
    if(!spA->spb){
        spA->spb.reset(new B("spA->spb"));
    }
    else{
        spA->spb.reset(new B("spb is not null"));
    }
    std::cout << spA->spb->name << std::endl;
    std::shared_ptr<A> spA2;
    std::cout << "spA.use_count:" << spA.use_count() << std::endl;
    spA2 = spA;
    std::cout << "spA.use_count:" << spA.use_count() << std::endl;
    std::cout << "spA2.use_count:" << spA2.use_count() << std::endl;
    std::shared_ptr<A> spA3;
    spA3 = std::move(spA);
    std::cout << "spA.use_count:" << spA.use_count() << std::endl;
    std::cout << "spA2.use_count:" << spA2.use_count() << std::endl;
    std::cout << "spA3.use_count:" << spA2.use_count() << std::endl;
    auto aptr = std::make_shared<A>("aptr A");
    std::cout << "aptr:" << aptr->name << std::endl;
    aptr->spb = std::make_shared<B>("aptr spB");
    if(NULL==aptr->pb) aptr->pb = aptr->spb.get();
    std::cout << "aptr->spb.use_count:" << aptr->spb.use_count() << std::endl;
    aptr->spb.reset(new B("reset spb"));
    aptr->pb = NULL;
    std::cout << "testshare_ptr end" << std::endl;
    std::cout << "aptr->spb is unique " << std::boolalpha << aptr->spb.unique() <<std::endl;
}

void testweak_ptr(){
    std::shared_ptr<A> spa = std::make_shared<A>("spa");
    std::cout << spa.use_count() << std::endl;
    std::weak_ptr<A> wpa(spa);
    std::cout << wpa.use_count() << std::endl;
    std::weak_ptr<A> wpa2=wpa;
    std::cout << wpa2.use_count() << std::endl;
    std::shared_ptr<A> spa2 = spa;
    std::cout << wpa2.use_count() << std::endl;
}

void testunique_ptr(){
    std::unique_ptr<A> upa (new A("upa"));
    std::shared_ptr<A> spa =std::make_shared<A>("spa");
    std::cout << spa.use_count() << std::endl;
    std::unique_ptr<A> upa2 = std::move(upa);
    std::cout << spa.use_count() << std::endl;
    std::cout << upa->name << std::endl;
}

int main(int argc, char **argv)
{
    //testshare_ptr();
    //testoldpoint();
    //testweak_ptr();
    testunique_ptr();
    return 0;
}