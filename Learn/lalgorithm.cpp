#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

void test_all_of(){
    std::array<int,8> arr{1,1,1,1,1,1,1,1};
    if(std::all_of(arr.begin(), arr.end(),[](auto& i)->bool{return i==1;})){
        std::cout << "都是1" << std::endl;
    }
}
void test_any_of(){
    std::string str{"abcdrf"};
    if(std::any_of(str.begin(), str.end(),[](auto& a){return a=='c';})){
        std::cout << "有c" << std::endl;
    }    
}

void test_binary_search(){
    std::vector<int> nums{1,2,3,3,4,5,7,8,9,10,6,4,3,2};
    for (size_t i = 0; i < 10; i++)
    {
        if(std::binary_search(nums.begin(), nums.end(),i)){
            std::cout << i<<" 是按照顺序存在" << std::endl;
        }
        else{
            std::cout << i<<" 不是按照顺序存在" << std::endl;
        }       
    }
    std::sort(nums.begin(), nums.end());    
    for (size_t i = 0; i < 10; i++)
    {
        if(std::binary_search(nums.begin(), nums.end(),i)){
            std::cout << i<<" 是按照顺序存在" << std::endl;
        }
        else{
            std::cout << i<<" 不是按照顺序存在" << std::endl;
        }       
    }
}

void test_copy(){
    int arr[10] {0,1,2,3,4,5,6,7,8,9};
    int arr2[10] {10,11,12,13,14,15,16,17,18,19};
    std::vector<int> copyarr(10);
    std::copy(arr2, arr2+10, copyarr.begin());
    auto copyendit = std::copy(arr+1, arr+4, copyarr.begin());
    while(copyendit != copyarr.end()){
        std::cout << *copyendit << ",";copyendit++;
    }
    for (auto it = copyarr.begin(); it != copyarr.end(); ++it)
        std::cout << *it << "," ;
    std::cout << std::endl;
}

void test_copy_backward(){
    std::vector<int> arr;
    for (size_t i = 1; i <= 5; i++)
    {
        arr.push_back(i*10);
    }
    arr.resize(8);
    //重后往前复制，顺序不变
    std::copy_backward(arr.begin(), arr.begin()+5,arr.end());
    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void test_copy_if(){
    //这个方法特别好
    std::array<int,10> arr{0,1,2,3,4,5,6,7,8,9};
    std::vector<int> vals(10);
    std::copy_if(arr.begin(), arr.end(),vals.begin(),[](auto i){return i %2 == 1;});
    for (auto it = vals.begin(); it != vals.end();it++)
        std::cout << *it << ",";
        std::cout << std::endl;    
}

void test_copy_n(){
    std::array<int,10> arr{0,1,2,3,4,5,6,7,8,9};
    std::vector<int> vals(10);
    std::copy_n(arr.begin(),5,vals.begin());
    for (auto it = vals.begin(); it != vals.end();it++)
        std::cout << *it << ",";
        std::cout << std::endl;    
}
void test_count(){
    std::vector<std::string> vals{"1","2","3","4","5","6","7","8","9","10","11","12","13","14","5"};
    std::cout << "5 出现了 " <<std::count(vals.begin(),vals.end(),"5") << "次" << std::endl;
 }
void test_count_if(){
    std::vector<int> vals{1,2,3,4,5,6,7,8,9,10};
    std::cout << "奇数的个数是" << std::count_if(vals.begin(),vals.end(),[](auto& i){return i%2==1;}) <<"个" << std::endl;
}

void test_equal(){
    std::array<int,6> vals{1,2,3,4,5,6};
    std::array<int,6> vals2{1,2,3,4,5,6};
    if(std::equal(vals.begin(), vals.end(),vals2.begin())){
        std::cout << "相等"  << std::endl;
    }
    else{
        std::cout << "不相等"  << std::endl;
    }
    std::vector<int> vals3{1,3,5,7,8,9};
    std::vector<int> vals4{1*2,3*2,5*2,7*2,8*2,9*2};
    if(std::equal(vals3.begin(), vals3.end(),vals4.begin(),[](auto a,auto b){ return b == a*2;})){
        std::cout << "vals4 是 vals3 的2倍 如果是直线的话 两条直线平行" << std:: endl;
    }
    else{
        std::cout << "不平行" << std::endl;
    }

}
void test_equal_range(){
    std::vector< int> vals{1,2,3,1,2,3,4,5,6,1,2,3,4,5,6};
    std::sort(vals.begin(), vals.end());
    auto range = std::equal_range(vals.begin(),vals.end(),2);
    std::cout <<"一共有：" <<range.second - range.first << "个2  =" << std::count(vals.begin(),vals.end(),2) << std::endl;
    std::cout << *range.first << *range.second << std::endl;
    std::cout << "起始下标：" << range.first - vals.begin() << " 截止下标：" << range.second - vals.begin() << std::endl;
    std::vector<int> ranges(range.first,range.second);
    for(auto i : ranges){
        std:: cout << i  << ",";
    }
    
}

void test_fill(){
    std::array<int,5> range;
    std::fill(range.begin(), range.end(),5);
    for(auto i : range){
        std::cout << i << ",";
    }
    std::cout << std::endl;
    std::fill_n(range.begin(),3,6);
    for(auto i : range){
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

void test_find(){
    std::array<int,5> range{1,2,3,4,5};
    std::cout << "4 所在的下标是：" << std::find(range.begin(),range.end(),4) - range.begin() << std::endl;
}

void test_find_end() {
    std::vector<int> vals{1,2,3,4,5,6,1,2,3,4,5};
    std::array<int,3> range{1,2,3};
    auto findit = std::find_end(vals.begin(),vals.end(),range.begin(),range.end());
    std::cout << "在 vals 中找到了 最后一个与 range 匹配的序列" << std::endl;
    std::cout <<  "下标是 ：" << findit - vals.begin() << std::endl;
}

void test_find_first_of(){
    //查找vals中一个元素可以和rang中的任何一个元素匹配。
    std::vector<int> vals{1,2,3,4,5,6,1,2,3,4,5};
    std::array<int,3> range123{1,2,3};
    std::array<int,3> range223{2,2,3};
    std::array<int,3> range323{3,2,3};
    std::array<int,3> range333{3,3,3};
    std::array<int,3> range321{3,2,1};
    auto findit = std::find_first_of(vals.begin(),vals.end(),range123.begin(),range123.end());
    std::cout << "查到 vals 中 下标为 " << findit - vals.begin() 
    << " 的元素与 range123中的任何一个元素匹配 " << *findit << std::endl;
    findit = std::find_first_of(vals.begin(),vals.end(),range223.begin(),range223.end());
    std::cout << "查到 vals 中 下标为 " << findit - vals.begin() 
    << " 的元素与 range223中的任何一个元素匹配 " << *findit << std::endl;
    findit = std::find_first_of(vals.begin(),vals.end(),range323.begin(),range323.end());
    std::cout << "查到 vals 中 下标为 " << findit - vals.begin() 
    << " 的元素与 range323中的任何一个元素匹配 " << *findit << std::endl;
    findit = std::find_first_of(vals.begin(),vals.end(),range333.begin(),range333.end());
    std::cout << "查到 vals 中 下标为 " << findit - vals.begin() 
    << " 的元素与 range333中的任何一个元素匹配 " << *findit << std::endl;    
    findit = std::find_first_of(vals.begin(),vals.end(),range321.begin(),range321.end());
    std::cout << "查到 vals 中 下标为 " << findit - vals.begin() 
    << " 的元素与 range321中的任何一个元素匹配 " << *findit << std::endl;        
}

void test_find_if(){
    //找到符合条件的第一个元素
    //如果想知道符合条件的所有元素，使用 copy_if
    std::vector<int> vals{1,2,3,4,5,6,7,8,9,10,11};
    auto findit = std::find_if(vals.begin(),vals.end(),[](auto i){ return i %10 == 1;});
    std::cout << "符合条件的数是 " << *findit << std::endl;
}

void test_find_if_not(){
    //找到不符合条件的第一个元素
    //如果想知道符合条件的所有元素，使用 copy_if
    std::vector<int> vals{4,4,3,4,5,6,7,8,9,10,11};
    auto findit = std::find_if_not(vals.begin(), vals.end(),[](auto i){return (i*2)%3==2;});
    std::cout << "不符合条件的是 " << *findit << "  所在位置是 " << findit - vals.begin() << std::endl;
}

void test_for_each(){
    std::vector<int> vals{1,2,3,4};
    std::for_each(vals.begin(), vals.end(),[](int& i){ 
        std::cout << i << std::endl;
        i++;
    });
    for(auto i:vals){
        std::cout << i << std::endl;
    }
}

void test_generate(){
    std::array<int,5> vals;
    std::generate(vals.begin(),vals.end(),[](){return 1;});  
    for(auto i:vals){
        std::cout << i << std::endl;
    }  
    std::generate_n(vals.begin(),3,[](){return 0;});
    for (auto i:vals)
        std::cout << i << std::endl;
}

void test_includes(){
    int arr[]{1,2,3,4,5,6,7,8,9,10,11};
    int arr1[]{2,2,3};
    std::cout << "arr 中 是否包括 arr1 1-3 " << std::boolalpha << std::includes(arr,arr+10,arr1+1,arr1+3) << std::endl;
    std::cout << "arr 中 是否包括 arr1 0-3 " << std::boolalpha << std::includes(arr,arr+10,arr1,arr1+3)<< std::endl;
}

int  main(int argc, char **argv){
    // test_all_of();
    // test_any_of();
    // test_binary_search();
    // test_copy();
    // test_copy_backward();
    // test_copy_if();
    // test_copy_n();
    // test_count();
    // test_count_if();
    // test_equal();
    // test_equal_range();
    // test_fill();
    // test_find();
    // test_find_end();
    // test_find_first_of();
    // test_find_if();
    // test_find_if_not();
    // test_for_each();
    // test_generate();
    test_includes();

    return 0;
}