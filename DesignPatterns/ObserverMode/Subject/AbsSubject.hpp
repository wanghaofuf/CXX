#ifndef ABSSUBJECT_H_PP
#define ABSSUBJECT_H_PP

#include "../DesignPatternsLibrary.h"
#include <vector>
#include <memory>
#include "../Observer/AbsObserver.hpp"
class AbsObserver;
class DP_EXPORT AbsSubject{
public:
    std::vector<std::shared_ptr<AbsObserver>> observers;
    virtual ~AbsSubject()=default;
    virtual bool Notify()=0;
    virtual bool Attach(std::shared_ptr<AbsObserver> observer)=0;
    virtual bool Detach(std::shared_ptr<AbsObserver> observer)=0;
};


#endif // ABSSUBJECT_H_PP