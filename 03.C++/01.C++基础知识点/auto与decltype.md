# 1. 类型别名
有两种方式使用类型别名：
### 1.1. typedef
```
typedef double wages; // wages是double的别名，或同义词
```
### 1.2. 别名声明using
新标准规定的一种新方法，使用别名声明using来定义类型的别名：
```
using SI = SalesItem; // SI是类SalesItem的别名，或同义词
```

# 2. auto类型说明符
C++11引入auto类型说明符，能让编译器替我们分析表达式所属的类型。**auto定义的变量必须有初始值**。

注意auto的自动推导原理：
- 1. auto会忽略顶层const，而保留底层const：
```
// ci是一个顶层const，引用cr是ci的别名
const int ci = i, &cr = ci; 

// b是一个整型，ci是一个顶层const整型，而b忽略了顶层const属性
auto b = ci;

// c是一个整型，cr是ci的别名
auto c = cr;
```

如果希望推断出来的auto类型是一个顶层const，则需要在auto前面加上const：
```
// f是const int
const auto f = ci; 
```

- 2. 如果expr是一个引用类型，忽略引用部分;如果忽略了引用之后，expr含有const，同样忽略；volitale情形同const。  
```
// ci是一个顶层const，引用cr是ci的别名
const int ci = i, &cr = ci; 

// c是一个整型，cr是ci的别名。尽管cr是一个引用，但是在下行代码的赋值拷贝过程中，会丢失引用属性，所以c是一个整型
auto c = cr;
```

- 3. 如果是类似 auto & a = b 或者 auto* a = b;则会保持b的const属性
```
int a = 10, &ra = a;
auto & b = ra; // b的类型是int&
```

# 3. decltype类型指示符
如果希望从表达式的类型推导出要定义的变量的类型，但是不想用该表达式的值初始化变量，C++11新标准引入了第二种类型说明符decltype。  
decltype的作用是选择并返回操作数的数据类型。在此过程中，**编译器分析表达式并得到它的类型**，却不实际计算表达式的值。

### 3.1. 推导参数类型
```
decltype(f()) sum = x;  // sum的类型就是函数f的返回类型
```

### 3.2. auto与decltype结合，指定函数返回类型
```
// 错误：x和y尚未声明，decltype不知道他们是什么
decltype(x+y) sum1(int x, int y)
{
    return x+y;
}

// 正确：auto与decltype结合
auto sum2(int x, int y) -> decltype(x+y)
{
    return x+y;
}
```