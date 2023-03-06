#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define READ_BUFFER 1024

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), sock(_sock), channel(nullptr){
    if (loop != nullptr){
        channel = new Channel(loop, sock->getFd());
        channel->enableReading();
    }
    
    // std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    // channel->setCallback(cb); // 绑定回调函数echo
    // channel->enableReading(); // 打开读事件监听

    read_buffer_ = new Buffer();
    send_buffer_ = new Buffer();
    state_ = State::Connected;
}

Connection::~Connection(){
    delete channel;
    delete sock;
    delete read_buffer_;
  delete send_buffer_;
}

void Connection::Read() {
//   ASSERT(state_ == State::Connected, "connection state is disconnected!");
  read_buffer_->clear();
  ReadNonBlocking();
  // if (sock->IsNonBlocking()) {
  //   ReadNonBlocking();
  // } else {
  //   ReadBlocking();
  // }
}
void Connection::Write() {
  // if (sock->IsNonBlocking()) {
  //   WriteNonBlocking();
  // } else {
  //   WriteBlocking();
  // }
  WriteNonBlocking();
  send_buffer_->clear();
}

void Connection::ReadNonBlocking() {
  int sockfd = sock->getFd();
  char buf[1024];  // 这个buf大小无所谓
  while (true) {   // 使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
    memset(buf, 0, sizeof(buf));
    ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
    if (bytes_read > 0) {
      read_buffer_->append(buf, bytes_read);
    } else if (bytes_read == -1 && errno == EINTR) {  // 程序正常中断、继续读取
      printf("continue reading\n");
      continue;
    } else if (bytes_read == -1 &&
               ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {  // 非阻塞IO，这个条件表示数据全部读取完毕
      break;
    } else if (bytes_read == 0) {  // EOF，客户端断开连接
      printf("read EOF, client fd %d disconnected\n", sockfd);
      state_ = State::Closed;
      break;
    } else {
      printf("Other error on client fd %d\n", sockfd);
      state_ = State::Closed;
      break;
    }
  }
}
void Connection::WriteNonBlocking() {
  int sockfd = sock->getFd();
  char buf[send_buffer_->size()];
  memcpy(buf, send_buffer_->c_str(), send_buffer_->size());
  int data_size = send_buffer_->size();
  int data_left = data_size;
  while (data_left > 0) {
    ssize_t bytes_write = write(sockfd, buf + data_size - data_left, data_left);
    if (bytes_write == -1 && errno == EINTR) {
      printf("continue writing\n");
      continue;
    }
    if (bytes_write == -1 && errno == EAGAIN) {
      break;
    }
    if (bytes_write == -1) {
      printf("Other error on client fd %d\n", sockfd);
      state_ = State::Closed;
      break;
    }
    data_left -= bytes_write;
  }
}

// void Connection::echo(int sockfd){
//     printf("Connection::echo被回调...\n");
//     char buf[READ_BUFFER];
//     while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
//         bzero(&buf, sizeof(buf));
//         ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
//         if(bytes_read > 0){
//             // write(sockfd, buf, sizeof(buf));
//             // 原方法是来一点就write一点，buf也是就地声明的
//             // 新方法是来了就统一读到Connection的缓冲区里，等读完了再从缓冲区统一write回去
//             readBuffer->append(buf, bytes_read);
//         } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
//             printf("continue reading");
//             continue;
//         } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
//             printf("finish reading once\n");
//             printf("message from client fd %d: %s\n", sockfd, readBuffer->c_str());
//             write(sockfd, readBuffer->c_str(), readBuffer->size());
//             // 全部读到缓冲区里后，再统一write回给客户端
//             readBuffer->clear();
//             break;
//         } else if(bytes_read == 0){  //EOF，客户端断开连接
//             printf("EOF, client fd %d disconnected\n", sockfd);
//             // close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
//             deleteConnectionCallback(sock);
//             break;
//         }
//     }
// }

void Connection::Close() { delete_connectioin_callback_(sock); }

Connection::State Connection::GetState() { return state_; }
void Connection::SetSendBuffer(const char *str) { send_buffer_->setBuf(str); }
Buffer *Connection::GetReadBuffer() { return read_buffer_; }
const char *Connection::ReadBuffer() { return read_buffer_->c_str(); }
Buffer *Connection::GetSendBuffer() { return send_buffer_; }
const char *Connection::SendBuffer() { return send_buffer_->c_str(); }


void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _cb){
    delete_connectioin_callback_ = _cb;
}

void Connection::SetOnConnectCallback(std::function<void(Connection *)> const &callback) {
  on_connect_callback_ = callback;
  channel->SetReadCallback([this]() { on_connect_callback_(this); });
}

void Connection::GetlineSendBuffer() { send_buffer_->getline(); }

Socket *Connection::GetSocket() { return sock; }

