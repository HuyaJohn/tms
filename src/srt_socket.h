#ifndef __SRT_SOCKET_H__
#define __SRT_SOCKET_H__

#include "common_define.h"
#include "fd.h"
#include "io_buffer.h"
#include "socket_handle.h"
#include "socket_util.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string>

class IoLoop;
class SocketHandle;

class SrtSocket : public Fd
{
public:
    SrtSocket(IoLoop* io_loop, const int& fd, SocketHandle* handle);
    virtual ~SrtSocket();

    void AsServerSocket()
    {
        server_socket_ = true;
    }

    void SetConnected() { connect_status_ = kConnected; }
    void SetDisConnected() { connect_status_ = kDisconnected; }
    void SetConnecting() { connect_status_ = kConnecting; }
    void SetHandshaking() { connect_status_ = kHandshakeing; }
    void SetHandshaked() { connect_status_ = kHandshaked; }

    bool IsConnected() { return connect_status_ >= kConnected; }
    bool IsDisConnected() { return connect_status_ == kDisconnected; }
    bool IsConnecting() { return connect_status_ == kConnecting; }
    bool IsHandshaking() { return connect_status_ == kHandshakeing; }
    bool IsHandshaked() { return connect_status_ == kHandshaked; }

    virtual int OnRead();
    virtual int OnWrite();

    int ConnectIp(const std::string& ip, const uint16_t& port);
    int ConnectHost(const std::string& host, const uint16_t& port);

    virtual int Send(const uint8_t* data, const size_t& len);

    IoBuffer& read_buffer() { return read_buffer_; }
    IoBuffer& write_buffer() { return write_buffer_; }

protected:
    IoBuffer read_buffer_;
    IoBuffer write_buffer_;

    int connect_status_;

    SocketHandle* handle_;

    bool server_socket_;
};

#endif // __SRT_SOCKET_H__