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

void testregex_search(){

    std::string str = "wanghaofu is a rich man!";
    std::smatch sm;
    if(std::regex_search(str,sm,std::regex("(fu)(.*)\\b(ri.*)"))){
        std::cout << sm.prefix().str() << std::endl;
        for(auto x:sm) std::cout << x << std::endl;
        std::cout << sm.suffix().str() << std::endl;
    }
    std::cmatch cm;
    if(std::regex_search("there is a subsequence in the string\n",cm,std::regex("\\b(sub)([^ ]*)"))){
        for(auto x: cm) std::cout << x << std::endl;

    }
}

void testregex_replace(){
    std::cout << std::regex_replace("wanghao is rich man,wanghao is good!",std::regex("\\b(wanghao) \\b(is)"),"$1fu is too") << std::endl;
}


int main(int argc, char **argv){

    //testregex_match();
    //testmarchresults();
    //testregex_search();
    testregex_replace();
    return 0;
}