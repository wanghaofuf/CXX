#include "ObserverMode.h"
#include "Observer/BaseObserver.hpp"
#include "Subject/BaseSubject.hpp"

class TestSubject : public BaseSubject{
    public:
    std::string Getmsg(){
        return "TestSubject";
    };
};


int main(int argc, char **argv){

    std::shared_ptr<BaseObserver> observer(new BaseObserver());
    std::shared_ptr<BaseSubject> tsubject(new TestSubject);
    tsubject->Attach(observer);
    tsubject->Notify();
    tsubject->Detach(observer);
    std::cout <<"main:" << tsubject->Getmsg() << std::endl;
    return 0;
}
