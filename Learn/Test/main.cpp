#include "teststatic.h"

/*
在头文件中定义了static 的变量 包涵了该头文件的源文件对于其他源文件来说都把该变量隐藏了。
充分展示了 static 的隐藏特性。
*/
int main(int argc, char **argv){
    Aset(3);
    BtoString();
    AtoString();
    return 0;
}