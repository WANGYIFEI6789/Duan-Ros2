#include <iostream>
#include <functional>  // 函数包装器头文件

// 自由函数
void save_with_free_func(const std::string& file_name){
    std::cout << "自由函数：" << file_name << std::endl;
}

// 类成员函数
class FileSave{
private:
    //
public:
    FileSave() = default;
    ~FileSave() = default;

    void save_with_member_func(const std::string& file_name){
        std::cout << "成员方法：" << file_name << std::endl;
    }
};

int main(){
    FileSave file_save;

    // Lambda函数
    auto save_with_lambda_func = [](const std::string& file_name) -> void{
        std::cout << "Lambda函数: " << file_name << std::endl;
    };
    // save_with_free_func("file.txt");
    // file_save.save_with_member_func("file_txt");
    // save_with_lambda_func("file.txt");

    // 将三种函数统一起来
    std::function<void(const std::string&)> save1 = save_with_free_func;
    std::function<void(const std::string&)> save2 = save_with_lambda_func;
    // 将成员函数放入包装器
    std::function<void(const std::string&)> save3 = std::bind(&FileSave::save_with_member_func, &file_save, std::placeholders::_1);
    // 统一的调用方法
    save1("file.txt");
    save2("file.txt");
    save3("file.txt");
    return 0;
}