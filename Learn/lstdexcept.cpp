#include <iostream>
#include <stdexcept>


void testlogci_error(){
    try {
        throw std::logic_error("logic_error");
    }
    catch(const std::logic_error& e){
        std::cerr << "std::logic_error:" << e.what()  << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "std::exception:" << e.what()  << std::endl;
    }
    catch(...) {
        std::cerr << "..." << std::endl;
    }
}

void testruntime_error(){
    try {
        char* p;
        delete p; //这种错误C++ 还是没办法捕获，尽量用智能指针.
        throw std::runtime_error("runtime_error");
    }
    catch(const std::logic_error& e){
        std::cerr << "std::logic_error:" << e.what()  << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "std::exception:" << e.what()  << std::endl;
    }
    catch(...) {
        std::cerr << "..." << std::endl;    
    }
}

int main(int argc, char **argv){
    //testlogci_error();
    testruntime_error();
    return 0;
}