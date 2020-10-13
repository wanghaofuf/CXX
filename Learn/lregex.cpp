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

void testmarchresults(){
    std::smatch sm;
    std::string str {"wanghaofu"};
    if(std::regex_match(str,sm,std::regex("wanghao(.*)")))
    {
        for (auto i = sm.begin(); i != sm.end();i++)
        {
            std::cout << *i << std::endl;
        }
    }   
    std::cmatch cm;
    if(std::regex_match("wanghaofu",cm,std::regex("wan(.*)(hao)(.*)"))){
        for (auto i = cm.begin(); i != cm.end();i++){
            std::cout << *i << std::endl;
        }
    }
}

int main(int argc, char **argv){

    //testregex_match();
    testmarchresults();
    return 0;
}