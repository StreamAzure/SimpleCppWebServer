#include "HttpConnect.h"
#include <regex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>

HttpConnect::HTTP_CODE HttpConnect::process_read(const char* text){
    std::string request = text;

    // 解析请求行
    std::regex request_line_regex("^(\\S+) (\\S+) (\\S+)\r\n");
    std::smatch request_line_match;
    std::regex_search(request, request_line_match, request_line_regex);

    std::string method = request_line_match[1];
    std::string uri = request_line_match[2];
    std::string version = request_line_match[3];

    std::cout << "Method: " << method << std::endl;
    std::cout << "URI: " << uri << std::endl;
    std::cout << "Version: " << version << std::endl;

    // 解析头部
    std::regex header_regex("^(\\S+):\\s+(\\S+)\\r\n");
    std::sregex_iterator header_iterator(request.begin() + request_line_match.length(), request.end(), header_regex);
    std::sregex_iterator end_iterator;

    while (header_iterator != end_iterator) {
        std::string header_name = (*header_iterator)[1];
        std::string header_value = (*header_iterator)[2];

        std::cout << header_name << ": " << header_value << std::endl;

        ++header_iterator;
    }
}

const char* HttpConnect::process_respond(){
    std::ifstream file("../../index.html", std::ios::binary);
    std::cout << std::filesystem::current_path()<<std::endl;
    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::string response = "HTTP/1.1 200 OK\r\n"
                            "Connection: keep-alive\r\n"
                            "Content-Type: text/html\r\n"
                            "Content-Length: " + std::to_string(file_contents.length()) + "\r\n\r\n"
                            
    return response.c_str();
}
// HttpConnect::HTTP_CODE HttpConnect::parse_request_line(char * text){

// } //解析首行
// HttpConnect::HTTP_CODE HttpConnect::parse_headers(char* text){

// } //解析头部
// HttpConnect::HTTP_CODE HttpConnect::parse_content(char* text){

// } //解析请求体

// HttpConnect::LINE_STATUS parse_line(){

//     return LINE_OK;
// }