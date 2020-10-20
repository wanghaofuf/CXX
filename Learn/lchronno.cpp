#include <iostream>
#include <chrono>
#include <limits>
#include <sstream>
#include <iomanip>

using nanoseconds = std::chrono::nanoseconds;   //std::chrono::duration<int64_t,std::ratio<std::nano>>;
using microseconds = std::chrono::microseconds; //std::chrono::duration<int64_t,std::ratio<std::micro>>
using milliseconds = std::chrono::milliseconds; //std::chrono::duration<int64_t,std::ratio<1,1000>>;
using seconds = std::chrono::seconds;           //std::chrono::duration<int64_t>;
using mins = std::chrono::minutes;               //std::chrono::duration<int64_t,std::ratio<60>>;
using hours = std::chrono::hours;               //std::chrono::duration<int64_t,std::ratio<3600>>;
using days = std::chrono::duration<int64_t,std::ratio<86400L>>;
using TimePoint = std::chrono::system_clock::time_point;

class DateTime {
    using int64 = int64_t;
    private:
    struct tm tm;
    time_t t ;
public:
    int64_t Year(){return tm.tm_year+1900L;};
    int64_t Month(){return tm.tm_mon+1L;};
    int64_t Day(){return tm.tm_mday;};
    hours Hour(){return hours(tm.tm_hour);};
    mins Min(){return mins(tm.tm_min);};
    seconds Sec(){return seconds(tm.tm_sec);};
    milliseconds Millisec{0};
    microseconds Microsec{0};
    nanoseconds Nanosec{0};
    DateTime(int64_t year, int64_t month, int64 day, int64_t hour, int64_t min, int64 sec)
    {
        tm.tm_year = year-1900;
        tm.tm_mon = month-1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = min;
        tm.tm_sec = sec;
        t = mktime(&tm);
    }
    DateTime(const TimePoint& tp = std::chrono::system_clock::now()){
        t = tp.time_since_epoch().count() /1000000000L;
        tm =*(localtime(&t));
        Millisec=milliseconds((tp.time_since_epoch().count() - (tp.time_since_epoch().count()/1000000000)*1000000000) / 1000000);
        Microsec = microseconds((tp.time_since_epoch().count() - (tp.time_since_epoch().count()/1000000)*1000000) / 1000);
        Nanosec = nanoseconds((tp.time_since_epoch().count() - (tp.time_since_epoch().count()/1000)*1000));
    }
    TimePoint toTimePoint(){
        return TimePoint(nanoseconds(t*1000000000L + Millisec.count()*1000000L + Microsec.count()*1000L + Nanosec.count()));
    }
    DateTime& AddYear(const int& years){
        tm.tm_year += years;   
        t = mktime(&tm);
        return *this;        
    }
    DateTime& AddMonths(const int& months){
        tm.tm_mon += months;   
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddDays(const int& days){
        tm.tm_mday += days;
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddHours(const int& hours){
        tm.tm_hour += hours;
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddMinutes(const int& minutes){
        tm.tm_min = minutes;
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddSeconds(const int& seconds){
        tm.tm_sec = seconds;
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddMilliseconds(const int& milliseconds){
        *this = DateTime(toTimePoint()+=std::chrono::milliseconds(milliseconds));
        return *this;
    }
    DateTime& AddMicroseconds(const int& microseconds){
        *this = DateTime(toTimePoint()+=std::chrono::microseconds(microseconds));
        return *this;
    }
    DateTime& AddNanoseconds(const int& nanoseconds){
        *this = DateTime(toTimePoint()+=std::chrono::nanoseconds(nanoseconds));
        return *this;
    }
    
    std::string toString(std::string fmt="yyyy-MM-dd HH:mm:ss milli.micro.nano"){
        std::stringstream ss;
        if(fmt=="yyyy-MM-dd"){
             ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " ;
        }
        else if(fmt=="yyyy-MM-dd HH:mm:ss"){
             ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " 
            <<std::setw(2)<< std::setfill('0')<< Hour().count() << ":" <<std::setw(2)<< std::setfill('0')<<Min().count() << ":" << std::setw(2)<< std::setfill('0')<<Sec().count()<< " " ;        
        }
        else{
            ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " 
            <<std::setw(2)<< std::setfill('0')<< Hour().count() << ":" <<std::setw(2)<< std::setfill('0')<<Min().count() << ":" << std::setw(2)<< std::setfill('0')<<Sec().count()<< " " 
            <<std::setw(3)<< std::setfill('0')<< Millisec.count() << "." <<std::setw(3)<< std::setfill('0')<< Microsec.count() << "." << std::setw(3)<< std::setfill('0')<<Nanosec.count();   
        }
        return ss.str();
    }
};


void testduration(){
    milliseconds ms(2500);
    seconds s(61);
    mins mi(61);
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
}

int main(int argc, char **argv)
{
    //std::cout << "int64_t:max:"<< std::numeric_limits<int64_t>::max() << std::endl;
    //testduration();
    //testsystemClock();
    testDateTime();
    return 0;
}