#ifndef _BASEOBSERVER_H_PP__
#define _BASEOBSERVER_H_PP__
#include "AbsObserver.hpp"
#include <iostream>

class DP_EXPORT BaseObserver : public AbsObserver{
    public:
     virtual bool Visit(const std::string& msg){
         std::cout << msg << std::endl;
     }
};


#endif // _BASEOBSERVER_H_PP__
