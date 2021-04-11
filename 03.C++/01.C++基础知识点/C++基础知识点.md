* 1. 当表达式里既有有符号数，又有无符号数，**有符号数会自动转换成无符号数**。
```
signed int a = -3;
unsigned int b = 1;
auto c = a+b;
cout << c << endl; // 输出4294967294
```
**但如果是unsigned char与signed char运算，或者unsigned short与short运算，结果还是有符号数**。因为，C语言中比int小的整型（包括short 、unsigned short 、 unsigned char和char）在运算中都要转换成int然后进行运算，至于为什么选择转换为int，应该是从效率上考虑的，因为通常情况下int的长度被定义为机器处理效率最高的长度，比如32位机上，一次处理4个字节效率是最高的，所以虽然short（我机器上占2个字节）更节省内存，但是在运算中的效率，是int更高。所以上面，无论是逻辑运算a>b还是算术运算a+b中a和b都默认转换成了int，所以算术运算的结果也是带符号的。