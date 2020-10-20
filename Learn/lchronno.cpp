#include <limits>
#include "DateTime.hpp"

void testduration(){
    milliseconds ms(2500);
    seconds s(61);
    minutes mi(61);
    hours h(25);
    days d(1);
    std::cout << (std::chrono::duration_cast<seconds>(ms)).count() << std::endl;
    std::cout << (std::chrono::duration_cast<seconds>(ms)).max().count() << std::endl;
    std::cout << (std::chrono::duration_cast<seconds>(ms)).min().count() << std::endl;
}

std::string time_point_tostr(const std::chrono::system_clock::time_point& pt,const std::string& fmt ) {
    std::stringstream os;
    struct tm *t;
    auto tt = std::chrono::system_clock::to_time_t(pt);
    //t = gmtime(&tt);
    t = localtime(&tt);
    if(fmt=="yyyy-MM-dd HH:mm:ss milli.micro.nano"){
        os << t->tm_year + 1900 <<"-"<< t->tm_mon+1 <<"-"<< t->tm_mday 
        << " " << t->tm_hour  << ":" << t->tm_min << ":" << t->tm_sec
        << " "<< (pt.time_since_epoch().count() - (pt.time_since_epoch().count()/1000000000)*1000000000) / 1000000 
        <<"."<< (pt.time_since_epoch().count()- (pt.time_since_epoch().count()/1000000)*1000000) / 1000 
        << "." << (pt.time_since_epoch().count()- (pt.time_since_epoch().count()/1000)*1000) ;        
    }
    return os.str();
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
    std::cout << "yesterday: " << ctime(&tt) << std::endl;
    tt = std::chrono::system_clock::to_time_t(tomorrow);
    std::cout << "tomorrow: " << ctime(&tt) << std::endl;
    std::cout << "1970年1月1日 00:00:00 :" << tt <<"  "<< now.time_since_epoch().count() <<std::endl;
    std::cout << "距离1970年1月1日 00:00:00 一共" << now.time_since_epoch().count()/1000000000 <<"秒"<<std::endl;
    //精确到纳秒
    std::cout<<  time_point_tostr(now,"yyyy-MM-dd HH:mm:ss milli.micro.nano") << std::endl;
    std::cout<<  time_point_tostr(std::chrono::system_clock::now(),"yyyy-MM-dd HH:mm:ss milli.micro.nano")<< std::endl;
    DateTime date_time(2020,10,19,16,56,18);
    //nanoseconds nanos(1603100741*1000000000L);
    TimePoint old ;
    old = date_time.toTimePoint();
    std::cout<< old.time_since_epoch().count() << std::endl;
    std::cout<<  time_point_tostr(old,"yyyy-MM-dd HH:mm:ss milli.micro.nano") << std::endl;
}

void testDateTime(){
    std::cout << DateTime(2020,1,1,1,1,1).AddDays(366).AddHours(24).AddMinutes(60).AddSeconds(60).AddMilliseconds(1000).AddMicroseconds(1000).AddNanoseconds(1001).AddDays(-366).toString()<< std::endl;
    std::cout << DateTime().AddDays(31).toString() << std::endl;
    const DateTime& date = DateTime();
    std::cout << date.TotalSeconds() << std::endl;
    std::cout << std::chrono::duration_cast<days>((DateTime(2021,10,21,3,0,1) - DateTime(2020,10,20,2,0,0))).count() << std::endl;
}

int main(int argc, char **argv)
{
    //std::cout << "int64_t:max:"<< std::numeric_limits<int64_t>::max() << std::endl;
    //testduration();
    //testsystemClock();
    testDateTime();
    return 0;
}