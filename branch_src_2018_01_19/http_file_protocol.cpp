#include <iostream>
#include <map>

#include "base_64.h"
#include "bit_buffer.h"
#include "common_define.h"
#include "global.h"
#include "http_file_protocol.h"
#include "http_sender.h"
#include "io_buffer.h"
#include "tcp_socket.h"

using namespace std;

HttpFileProtocol::HttpFileProtocol(Epoller* epoller, Fd* socket)
    :
    epoller_(epoller),
    socket_(socket),
    upgrade_(false)
{
}

HttpFileProtocol::~HttpFileProtocol()
{
}

int HttpFileProtocol::Parse(IoBuffer& io_buffer)
{
    int ret = http_parse_.Decode(io_buffer);

    if (ret == kSuccess)
    {
        if (http_parse_.GetFileName() == "webrtc_test" && http_parse_.GetFileType() == "html")
        {
            string webrtc_test = Util::ReadFile("webrtc_test.html");

            if (webrtc_test.empty())
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("404");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent("fuck you");

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
            else
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("200");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent(webrtc_test);

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
        }
        else if (http_parse_.GetFileName() == "hello" && http_parse_.GetFileType() == "html")
        {
            string hello = Util::ReadFile("hello.html");

            if (hello.empty())
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("404");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent("fuck you");

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
            else
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("200");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent(hello);

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
        }
        else if (http_parse_.GetFileName() == "publish" && http_parse_.GetFileType() == "html")
        {
            string publish = Util::ReadFile("publish.html");

            if (publish.empty())
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("404");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent("fuck you");

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
            else
            {
				HttpSender http_rsp;
                http_rsp.SetStatus("200");
                http_rsp.SetContentType("html");
                http_rsp.SetClose();
                http_rsp.SetContent(publish);

                string http_response = http_rsp.Encode();

                GetTcpSocket()->Send((const uint8_t*)http_response.data(), http_response.size());
            }
        }
    }

    return ret;
}

int HttpFileProtocol::Send(const uint8_t* data, const size_t& len)
{
    return kSuccess;
}

int HttpFileProtocol::OnStop()
{
    return 0;
}

int HttpFileProtocol::EveryNSecond(const uint64_t& now_in_ms, const uint32_t& interval, const uint64_t& count)
{
    return 0;
}