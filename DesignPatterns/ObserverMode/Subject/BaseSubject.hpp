#ifndef __BASESUBJECT_H__PP__
#define __BASESUBJECT_H__PP__
#include <mutex>
#include <algorithm>
#include "AbsSubject.hpp"
#include "../TaskQueue.hpp"

namespace Global {
    static std::shared_ptr<TaskQueue> task_queue (new  ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT));
}

class DP_EXPORT BaseSubject : public AbsSubject{
    private:
    std::mutex _observersmutex;
    std::shared_ptr<TaskQueue> task_queue;
public:
    BaseSubject():task_queue(Global::task_queue){

    }
    virtual ~BaseSubject(){
        task_queue->shutdown();
    };
    bool Notify(){
        std::unique_lock<std::mutex> lock(_observersmutex);
        for(auto ob : observers){
            #if __cplusplus > 201703L
            task_queue->enqueue([=,this](){ ob->Visit(Getmsg());});
            #else
            task_queue->enqueue([=](){ ob->Visit(Getmsg());});
            #endif
        }
        return true;
    };
    bool Attach(std::shared_ptr<AbsObserver> observer){
        std::unique_lock<std::mutex> lock(_observersmutex);
        auto it = std::find(observers.begin(), observers.end(), observer);
        if( it == observers.end()) observers.push_back(observer);
        return std::find(observers.begin(), observers.end(), observer) != observers.end();
    }
    bool Detach(std::shared_ptr<AbsObserver> observer){
        std::unique_lock<std::mutex> lock(_observersmutex);
        auto it = std::find(observers.begin(), observers.end(), observer);
        if( it != observers.end()) observers.erase(it);
        return std::find(observers.begin(), observers.end(), observer) == observers.end();
    }
    /* 必须为纯虚函数 因为在父类调用了该函数，为防止调用了父类的虚函数则该虚函数必须写成纯虚的函数 */
    virtual std::string Getmsg()=0;

};



#endif// __BASESUBJECT_H__PP__
