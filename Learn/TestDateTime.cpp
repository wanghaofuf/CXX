#include "DateTime.hpp"



void testDateTime(){
    auto dt{DateTime()};
    std::cout << "Testing:" << DateTime().toString() << " yyyy-MM-dd:" << DateTime().toString("yyyy-MM-dd")<<
    " yyyy-MM-dd HH:mm:ss:"<<  DateTime().toString("yyyy-MM-dd HH:mm:ss") <<
    " yyyy/MM/dd HH:mm:ss:" << DateTime().toString("yyyy/MM/dd HH:mm:ss") << std::endl;
    std::cout << " days:"<< std::chrono::duration_cast<days>(DateTime().AddHours(1)-DateTime()).count(); 
    std::cout << " hours:" << std::chrono::duration_cast<hours>(DateTime().AddHours(1)-DateTime()).count()   ;
    std::cout <<" minutes:" << std::chrono::duration_cast<minutes>(DateTime().AddHours(1)-DateTime()).count() ;  
    std::cout << " senconds:" << std::chrono::duration_cast<seconds>(DateTime().AddSeconds(61)-DateTime()).count() ;  
    std::cout <<" milliseconds:" << std::chrono::duration_cast<milliseconds>(DateTime().AddMilliseconds(1)-DateTime()).count() ;  
    std::cout << " microseconds:"  << std::chrono::duration_cast<microseconds>(DateTime()-DateTime()).count() ;  
    std::cout << " nanoseconds" << std::chrono::duration_cast<nanoseconds>(DateTime()-DateTime()).count() ;  
    std::cout << " >=:" << std::boolalpha << (DateTime()>=DateTime());
    std::cout << " ==:"<< std::boolalpha << (DateTime()==DateTime()) ;
    std::cout << " <=:"<< std::boolalpha << (DateTime()<=DateTime()) << std::endl;
        std::cout << "Testing:" << DateTime().toString() << " yyyy-MM-dd:" << DateTime().toString("yyyy-MM-dd")<<
    " yyyyMMddHHmmss:"<<  DateTime().toString("yyyyMMddHHmmss") <<
    " yyyy/MM/dd HH:mm:ss:" << DateTime().toString("yyyy/MM/dd HH:mm:ss") << std::endl;
    std::cout << " use Times:"<< std::chrono::duration_cast<nanoseconds>(DateTime()-dt).count() /1000000000.0 << " senconds"<<std::endl;
}

int main(int argc, char **argv){
    testDateTime();
    return 0;
}