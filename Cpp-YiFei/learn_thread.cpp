#include <iostream>
#include <thread>  // 多线程头文件
#include <chrono>  // 时间相关头文件
#include <functional>  // 函数包装器头文件
#include <cpp-httplib/httplib.h>  // 下载相关的头文件

class Download{
private:
    //
public:
    Download() = default;
    ~Download() = default;
    void download(const std::string& host, const std::string& path, const std::function<void(const std::string&, 
    const std::string&)> &callback_word_count){
        std::cout << "线程" << std::this_thread::get_id() << std::endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if(response && response->status == 200){
            callback_word_count(path, response->body);
        }
    }

    void start_download(const std::string &host, const std::string &path, const std::function<void(const std::string&, 
    const std::string&)> &callback_word_count){
        // 注意download是类成员函数，所以在给thread使用之前，需要先通过bind函数创建一个函数对象
        auto download_func = std::bind(&Download::download, this, std::placeholders::_1, 
        std::placeholders::_2, std::placeholders::_3);
        // 传递给执行线程
        std::thread thread(download_func, host, path, callback_word_count);
        // 避免当前线程阻塞在这里，可使用线程分离
        thread.detach();
    }

};

int main(){
    auto d = Download();
    auto word_count = [](const std::string &path, const std::string &result) -> void{
        std::cout << "下载完成" << path << ":" << result.length() << "->" << result.substr(0, 5) << std::endl;
    };
    d.start_download("http://0.0.0.0:8000", "/novel1.txt", word_count);
    d.start_download("http://0.0.0.0:8000", "/novel2.txt", word_count);
    d.start_download("http://0.0.0.0:8000", "/novel3.txt", word_count);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 10));
    return 0;
}