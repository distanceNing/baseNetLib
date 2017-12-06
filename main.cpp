#include "app.h"

int main(int argc, char* argv[])
{

    net::EventLoop loop(net::POLL);
    App app(&loop);
    app.run();



    return 0;
}


