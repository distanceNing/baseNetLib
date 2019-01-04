#include <iostream>

using namespace std;
//消息传输类型
class Message_type
{
	public:
		virtual void subscribemess_Imp() {}
};
class XML: public Message_type
{
	public:
		void subscribemess_Imp() { cout<<"以XML方式显示"<<endl; } 
};
class HTML: public Message_type
{
	public:
		void subscribemess_Imp() { cout<<"以HTML方式显示"<<endl; } 
};
class JSON: public	Message_type
{
public:
	void subscribemess_Imp() { cout<<"以JSON方式显示"<<endl; } 
};
//消息 MSG
class Notify
{
public:
	virtual void subscribe(Message_type *mess_type) {}
};
//通告
class Announce: public Notify	
{
	public:
		void subscribe(Message_type *mess_type)
		{ 
		 	mess_type->subscribemess_Imp();
		}
};
//提醒
class Remind: public Notify
{
	public:
		void subscribe(Message_type *mess_type)
		{ 
			mess_type->subscribemess_Imp();
		}
};
//信息
class Message: public Notify
{
	public:
		void subscribe(Message_type *mess_type)
		{ 
			mess_type->subscribemess_Imp();
		}
};

int main()
{
	Notify *Notify1 = new Announce();
	Notify *Notify2 = new Remind();
	Message_type *mess_type1 = new HTML();
	Message_type *mess_type2 = new XML();
	Notify1->subscribe(mess_type1);
	Notify2->subscribe(mess_type2);

	return 0;
}