#ifndef __BASESUBJECT_H__PP__
#define __BASESUBJECT_H__PP__
#include <mutex>
#include <algorithm>
#include "AbsSubject.hpp"
#include "../TaskQueue.hpp"

class DP_EXPORT BaseSubject : public AbsSubject{
    private:
    std::mutex _observersmutex;
    std::unique_ptr<TaskQueue> task_queue;
public:
    BaseSubject():task_queue(new  ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT)){

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
    virtual std::string Getmsg(){
        return "BaseSubject";
    };

};



#endif// __BASESUBJECT_H__PP__
