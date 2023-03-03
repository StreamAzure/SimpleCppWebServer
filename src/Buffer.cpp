#include "Buffer.h"
#include <string.h>
#include <iostream>
Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

/**
 * 将给定字符串_str写入到缓冲区buf中
*/
void Buffer::append(const char* _str, int _size){
    for(int i = 0; i < _size; ++i){
        if(_str[i] == '\0') break;
        buf.push_back(_str[i]);
    }
}

/**
 * 从标准输入获取要输入的字符，以'\n'为终止符，并写入到buf中
*/
void Buffer::getline(){
    buf.clear();
    std::getline(std::cin, buf);
}

ssize_t Buffer::size(){
    return buf.size();
}

const char* Buffer::c_str(){
    return buf.c_str();
}

void Buffer::clear(){
    buf.clear();
}