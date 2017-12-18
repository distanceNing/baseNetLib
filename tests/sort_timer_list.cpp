//
// Created by yangning on 17-11-29.
//
// Descriprion :test echo server
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "Acceptor.h"
#include "tcp_server.h"
#include "tcp_connection.h"
#include "timerfd/SortTimerList.h"
#include <signal.h>
SortTimerList sortTimerList;
#define  PIPE_READ_FD 0
#define  PIPE_WRITE_FD 1
static int signalPipeFd[2];

void signalHandle(int sig)
{
    int save_errno = errno;
    int msg = sig;
    ::write(signalPipeFd[PIPE_WRITE_FD], &msg, sizeof(msg));
    errno = save_errno;
}

void timerHandle()
{
    sortTimerList.process();
    alarm(1);
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signalHandle;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

static const uint32_t MS = 1000;
int main()
{
    addsig(SIGALRM);
    addsig(SIGTERM);
    alarm(1);
    int flag = socketpair(PF_UNIX, SOCK_STREAM, 0, signalPipeFd);
    assert(flag != -1);
    Timer timer1, timer2, timer3, timer4, timer5;
    timer1.exptime_ = net::TimeStamp::nowTime() + MS * 1000;
    timer1.setTimerCallBack([]() {
      printf(" Timer timeout \n");
    });
    timer2.exptime_ = timer1.exptime_ + 1000;
    timer2.setTimerCallBack([]() {
      printf(" Timer timeout \n");
    });
    timer3.exptime_ = timer2.exptime_ + 1000;
    timer3.setTimerCallBack([]() {
      printf(" Timer timeout \n");
    });
    timer4.exptime_ = timer3.exptime_ + 1000;
    timer4.setTimerCallBack([]() {
      printf(" Timer timeout \n");
    });

    timer5.exptime_ = timer4.exptime_ + 1000;
    timer5.setTimerCallBack([]() {
      printf(" Timer timeout \n");
    });

    sortTimerList.addTimer(&timer1);
    sortTimerList.addTimer(&timer2);
    sortTimerList.addTimer(&timer3);
    sortTimerList.addTimer(&timer4);
    sortTimerList.addTimer(&timer5);

    timer1.exptime_ += 2;
    sortTimerList.adjustTimer(&timer1);
    sortTimerList.deleteTimer(&timer2);

    sleep(1);
    int msg;
    while (true)
    {
        ::read(signalPipeFd[PIPE_READ_FD], &msg, sizeof(msg));
        if ( msg == SIGALRM )
            timerHandle();
        if(sortTimerList.empty())
            break;
    }
    //sortTimerList.process();
    return EXIT_SUCCESS;
}