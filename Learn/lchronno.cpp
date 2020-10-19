#include <iostream>
#include <chrono>
#include <limits>
using milliseconds = std::chrono::milliseconds; //std::chrono::duration<int64_t,std::ratio<1,1000>>;
using seconds = std::chrono::seconds;           //std::chrono::duration<int64_t>;
using min = std::chrono::minutes;               //std::chrono::duration<int64_t,std::ratio<60>>;
using hours = std::chrono::hours;               //std::chrono::duration<int64_t,std::ratio<3600>>;
using days = std::chrono::duration<int64_t,std::ratio<86400L>>;



void testduration(){
    milliseconds ms(2500);
    seconds s(61);
    min mi(61);
    hours h(25);
    days d(1);
    std::cout << (std::chrono::duration_cast<seconds>(ms)).count() << std::endl;
    std::cout << (std::chrono::duration_cast<seconds>(ms)).max().count() << std::endl;
    std::cout << (std::chrono::duration_cast<seconds>(ms)).min().count() << std::endl;
}


void testsystemClock(){
    using pt = std::chrono::system_clock::time_point;
    pt now = std::chrono::system_clock::now();
    days d1(1);
    pt yesterday = now - d1;
    pt tomorrow = now + d1;
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t(now);
    std::cout << "1970年1月1日 00:00:00 :" << tt <<"  "<< now.time_since_epoch().count() <<std::endl;
    std::cout << "now: " << ctime(&tt) <<  std::endl;
    tt = std::chrono::system_clock::to_time_t(yesterday);
    std::cout << "now: " << ctime(&tt) << std::endl;
    tt = std::chrono::system_clock::to_time_t(tomorrow);
    std::cout << "now: " << ctime(&tt) << std::endl;
    std::cout << "1970年1月1日 00:00:00 :" << tt <<"  "<< now.time_since_epoch().count() <<std::endl;
    std::cout << "距离1970年1月1日 00:00:00 一共" << now.time_since_epoch().count()/1000000000 <<"秒"<<std::endl;
    //精确到纳秒
    struct tm *t;
    tt = std::chrono::system_clock::to_time_t(now);
    t = gmtime(&tt);
    std::cout << t->tm_year + 1900 <<"-"<< t->tm_mon+1 <<"-"<< t->tm_mday 
    << " " << t->tm_hour + 8 << ":" << t->tm_min << ":" << t->tm_sec
    << " "<< (now.time_since_epoch().count() - (now.time_since_epoch().count()/1000000000)*1000000000) / 1000000 
    <<"."<< (now.time_since_epoch().count()- (now.time_since_epoch().count()/1000000)*1000000) / 1000 
    << "." << (now.time_since_epoch().count()- (now.time_since_epoch().count()/1000)*1000) << std::endl;
}

int main(int argc, char **argv)
{
    //std::cout << "int64_t:max:"<< std::numeric_limits<int64_t>::max() << std::endl;
    //testduration();
    testsystemClock();
    return 0;
}