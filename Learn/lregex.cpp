#include <iostream>
#include <string>
#include <regex>


void testregex_match(){
    if( std::regex_match("wanghaofu",std::regex("(wa)(.*)"))){
        std::cout << "wanghaofu"  << std::endl;
    }
    std::string s="wanghaofu";
    if(std::regex_match(s.begin(),s.end(),std::regex("(wan)(.*)"))) std::cout << "wan" << std::endl;
    std::cmatch cm;
    std::regex_match("wanghaofu",cm,std::regex("(wang)(hao)(.*)"),std::regex_constants::match_default);
    std::cout << "cm:";
    for (size_t i = 0; i < cm.size(); i++)
    {
        std::cout << "["<< cm[i] <<"] ";
    }
    std::cout << std::endl;
}


int main(int argc, char **argv){

    testregex_match();
    return 0;
}