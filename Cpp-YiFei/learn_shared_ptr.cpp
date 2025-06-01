 #include <iostream>
 #include <memory>
 #include <string>

 int main(){
    // std::make_shared<数据类型/类>(参数)
    // 返回值：对应类的共享指针 std::shared_ptr<std::string> 可以用auto代替
    // 注意这里访问的方式  具体是使用.去访问 还是使用->去访问
    // .运算符：用于访问智能指针类本身的方法或成员
    // ->运算符：用于访问智能指针所管理对象的方法或成员
    // 显然use_count, get都是智能指针类本身的成员函数 所以使用.
    auto p1 = std::make_shared<std::string>("This is a str.");
    std::cout << "p1的引用计数: " << p1.use_count() << "指向的内存地址: " << p1.get() << std::endl;
    
    auto p2 = p1;
    std::cout << "p1的引用计数: " << p1.use_count() << "指向的内存地址: " << p1.get() << std::endl;
    std::cout << "p2的引用计数: " << p2.use_count() << "指向的内存地址: " << p2.get() << std::endl;

    // p1释放 不指向 "This is a str" 所在内存
    p1.reset();
    std::cout << "p1的引用计数: " << p1.use_count() << "指向的内存地址: " << p1.get() << std::endl;
    std::cout << "p2的引用计数: " << p2.use_count() << "指向的内存地址: " << p2.get() << std::endl;

    // c_str() 是 std::string 类提供的一个成员函数，其主要功能是把 std::string 对象里的内容，
    // 以 C 风格字符串（也就是以空字符 '\0' 结尾的字符数组）的形式返回
    std::cout << "p2所指向内存地址的数据: " << p2->c_str() << std::endl;
    return 0;
 }