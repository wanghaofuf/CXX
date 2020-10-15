#include <iostream>
#include <ratio>
using one_third_ratio= std::ratio<1,3> ;
using two_fourths_ratio = std::ratio<2,4> ;

void testratio(){
    std::cout << one_third_ratio::num << "/" << one_third_ratio::den << std::endl;
    std::cout << two_fourths_ratio::num << "/" << two_fourths_ratio::den << std::endl;
    std::ratio_add<one_third_ratio,two_fourths_ratio> sum;
    std::cout << sum.num << "/" << sum.den << std::endl;
    std::ratio_subtract<one_third_ratio,two_fourths_ratio> subtract;
    std::cout << subtract.num << "/" << subtract.den << std::endl;
    std::ratio_multiply<one_third_ratio,two_fourths_ratio> multiply;
    std::cout << multiply.num << "/" << multiply.den << std::endl;
    std::ratio_divide<one_third_ratio,two_fourths_ratio> div;
    std::cout << div.num << "/" << div.den << std::endl;
    std::ratio_equal<one_third_ratio,two_fourths_ratio> equal;
    std::cout << std::boolalpha << equal.value << std::endl;
    std::ratio_greater<one_third_ratio,two_fourths_ratio> greater;
    std::cout << greater.value << std::endl;
    std::ratio_less<one_third_ratio,two_fourths_ratio>  less;
    std::cout << less.value << std::endl;

}


int main(int argc, char **argv){
    testratio();
    return 0;
}

