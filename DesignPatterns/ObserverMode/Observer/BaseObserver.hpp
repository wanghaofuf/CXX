#ifndef _BASEOBSERVER_H_PP__
#define _BASEOBSERVER_H_PP__
#include "AbsObserver.hpp"
#include <iostream>

class DP_EXPORT BaseObserver : public AbsObserver{
    public:
     virtual bool Visit(std::string msg){
         std::cout << msg << std::endl;
         return true;
     }
};


#endif // _BASEOBSERVER_H_PP__
