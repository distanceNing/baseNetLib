#ifndef _CONSUMER_H_
#define _CONSUMER_H_


class Consumer{
public:
    Consumer(int type):type_(type){}

    bool register_node();

    int getSubscribeMsgType()const{
        return type_;
    }

    ~Consumer(){}

private:
    int type_;

};
#endif // _CONSUMER_H_
