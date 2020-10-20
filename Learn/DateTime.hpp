#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <regex>

using nanoseconds = std::chrono::nanoseconds;   //std::chrono::duration<int64_t,std::ratio<std::nano>>;
using microseconds = std::chrono::microseconds; //std::chrono::duration<int64_t,std::ratio<std::micro>>
using milliseconds = std::chrono::milliseconds; //std::chrono::duration<int64_t,std::ratio<1,1000>>;
using seconds = std::chrono::seconds;           //std::chrono::duration<int64_t>;
using minutes = std::chrono::minutes;               //std::chrono::duration<int64_t,std::ratio<60>>;
using hours = std::chrono::hours;               //std::chrono::duration<int64_t,std::ratio<3600>>;
using days = std::chrono::duration<int64_t,std::ratio<86400L>>;
using TimePoint = std::chrono::system_clock::time_point;

class DateTime {
    using int64 = int64_t;
    private:
    struct tm tm;
    time_t t ;
public:
    int64 TotalSeconds() const { return t;}
    int64_t Year()const {return tm.tm_year+1900L;}
    int64_t Month()const {return tm.tm_mon+1L;}
    int64_t Day()const {return tm.tm_mday;}
    hours Hour()const {return hours(tm.tm_hour);}
    minutes Minutes()const {return minutes(tm.tm_min);}
    seconds Sec()const {return seconds(tm.tm_sec);}
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
    TimePoint toTimePoint()const {
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
        tm.tm_min += minutes;
        t = mktime(&tm);
        return *this;
    }
    DateTime& AddSeconds(const int& seconds){
        tm.tm_sec += seconds;
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
    nanoseconds operator-(const DateTime& dt){
        return nanoseconds( toTimePoint()- dt.toTimePoint());
    }
    bool operator==(const DateTime& dt){
        return toTimePoint()==dt.toTimePoint();
    }
    bool operator!=(const DateTime& dt){
        return toTimePoint()!=dt.toTimePoint();
    }
    bool operator<=(const DateTime& dt){
        return toTimePoint()<=dt.toTimePoint();
    }
    bool operator>=(const DateTime& dt){
        return toTimePoint()>=dt.toTimePoint();
    }
    bool operator<(const DateTime& dt){
        return toTimePoint()<dt.toTimePoint();
    }
    bool operator>(const DateTime& dt){
        return toTimePoint()>dt.toTimePoint();
    }
    std::string toString(const std::string& fmt="yyyy-MM-dd HH:mm:ss milli.micro.nano") const {
        std::stringstream ss;
        if(fmt=="yyyy-MM-dd"){
             ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " ;
        }
        else if(fmt=="yyyy-MM-dd HH:mm:ss"){
             ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " 
            <<std::setw(2)<< std::setfill('0')<< Hour().count() << ":" <<std::setw(2)<< std::setfill('0')<<Minutes().count() << ":" << std::setw(2)<< std::setfill('0')<<Sec().count()<< " " ;        
        }
        else if(fmt== "yyyy-MM-dd HH:mm:ss milli.micro.nano"){
            ss << Year() << "-" << std::setw(2)<< std::setfill('0')<< Month() << "-" <<std::setw(2)<< std::setfill('0')<< Day() << " " 
            <<std::setw(2)<< std::setfill('0')<< Hour().count() << ":" <<std::setw(2)<< std::setfill('0')<<Minutes().count() << ":" << std::setw(2)<< std::setfill('0')<<Sec().count()<< " " 
            <<std::setw(3)<< std::setfill('0')<< Millisec.count() << "." <<std::setw(3)<< std::setfill('0')<< Microsec.count() << "." << std::setw(3)<< std::setfill('0')<<Nanosec.count();   
        }
        else{
            std::string sb= fmt;
            sb= std::regex_replace(sb,std::regex("yyyy"),std::to_string(Year()));
            sb=std::regex_replace(sb,std::regex("MM"),([this]()->std::string{std::stringstream ss; ss << std::setw(2) << std::setfill('0')<< Month(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("dd"),([this]()->std::string{std::stringstream ss; ss <<std::setw(2) << std::setfill('0')<< Day(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("HH"),([this]()->std::string{std::stringstream ss; ss <<std::setw(2) << std::setfill('0')<< Hour().count(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("mm"),([this]()->std::string{std::stringstream ss; ss <<std::setw(2) << std::setfill('0')<< Minutes().count(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("ss"),([this]()->std::string{std::stringstream ss; ss <<std::setw(2) << std::setfill('0')<< Sec().count(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("milli"),([this]()->std::string{std::stringstream ss; ss <<std::setw(3) << std::setfill('0')<< Millisec.count(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("micro"),([this]()->std::string{std::stringstream ss; ss <<std::setw(3) << std::setfill('0')<< Microsec.count(); return ss.str();})());
            sb=std::regex_replace(sb,std::regex("nano"),([this]()->std::string{std::stringstream ss; ss <<std::setw(3) << std::setfill('0')<< Nanosec.count(); return ss.str();})());
            return sb;
        }
        return ss.str();
    }
};

