//
// Created by yangning on 17-10-23.
//

#include "timerfd/time_stamp.h"
#include "timerfd/timer.h"

int main()
{
    TimeStamp::printTimeNow();
    //建立监听socket
    //TcpSocket server_sock;
    //server_sock.CreateSocket(AF_INET, SOCK_STREAM, kPort);
    //server_sock.Listen();
    Timer timer;
    timer.createTimer();
    //第一个参数为第一次timerfd触发的时间(从现在开始 单位:s)
    timer.setTime(4, 4);

    uint64_t error = 0;
    for (int i = 0; i < 10; ++i)
    {
        ssize_t read_size = read(timer.getTimerFd(), &error, sizeof(uint64_t));
        if (read_size != sizeof(uint64_t)) {
            perror("read error");
        }
        TimeStamp::printTimeNow();
    }

    return 0;
}
