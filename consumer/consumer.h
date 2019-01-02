#ifndef _CONSUMER_H_
#define _CONSUMER_H_


class Consumer{
public:
    Consumer(){}

    bool register();

    void process();
    // topic
    // msg info
    void  push_msg();

    ~Consumer(){}

    private:


};
#endif // _CONSUMER_H_
