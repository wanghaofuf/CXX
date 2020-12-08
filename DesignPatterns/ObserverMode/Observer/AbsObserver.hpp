#ifndef __ABS_Observer__H__
#define __ABS_Observer__H__
#include "../DesignPatternsLibrary.h"
#include "../Subject/AbsSubject.hpp"
class DP_EXPORT AbsObserver{
public:
    virtual ~AbsObserver() = default;
    virtual bool Visit(const std::string& msg)=0;
};
#endif //__ABS_Observer__H__
