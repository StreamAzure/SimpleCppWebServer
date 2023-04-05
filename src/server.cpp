#include "Server.h"
#include <iostream>
#include "Buffer.h"
#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "HttpConnect.h"

int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  server->OnConnect([](Connection *conn) {
    conn->Read();
    //从conn->ReadBuffer取出客户端发送的消息
    //解析HTTP报文
    //定义回复消息Buffer reply
    //通过conn->SetSendBuffer(reply)设置发送缓冲区
    //conn->Write()发送给客户端
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      return;
    }
    HttpConnect* hc = new HttpConnect();
    hc->process_read(conn->ReadBuffer());
    conn->SetSendBuffer(hc->process_respond());
    conn->Write();
  });

  loop->loop();
  delete server;
  delete loop;
  return 0;
}
