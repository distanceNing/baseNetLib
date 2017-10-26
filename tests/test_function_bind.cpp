//
// Created by yangning on 17-10-26.
//
// Descriprion : test std::function bind
//
// Copyright (c) yangning All rights reserved.
//

#include <random>
#include <iostream>
#include <memory>
#include <functional>
using namespace std::placeholders;  // for _1, _2, _3...
void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1)
{
    return n1;
}

struct Foo {

  void print_sum(int n1, int n2)
  {
      std::cout << n1+n2 << '\n';
  }
  int data = 10;
};

int main()
{

    // demonstrates argument reordering and pass-by-reference
    // (_1 and _2 are from std::placeholders, 代表期望用户输入的参数
    // 当为_1,只需一个参数,_2,_3...以此类推.
    // arguments that will be passed to f1)

    auto func=std::bind(f,_1,1,2,3,4);
    func(0);

    // nested bind subexpressions share the placeholders
    auto func2=std::bind(f,_1,std::bind(g,1),1,2,3);
    func2(0,2);

    // common use case: binding a RNG with a distribution
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    auto rnd = std::bind(d, e); // a copy of e is stored in rnd
    for(int n=0; n<10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';

    // bind to a pointer to member function
    Foo foo;
    std::function<int(Foo const&)> f_num = &Foo::data;
    std::cout << "num_: " << f_num(foo) << '\n';

    std::function<void(int)> f_add_display2 = std::bind( &Foo::print_sum, &foo, _1 ,1);
    f_add_display2(1);

    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);
    auto event=std::bind(&Foo::print_sum, _1,2, _2);
    event(&foo,2);

    // bind to a pointer to data member
    auto f4 = std::bind(&Foo::data, _1);
    //cppreference 上的例子无法编译通过
    //std::cout << f4(foo) << '\n';
    //参数代入为foo的地址时,正常运行
    std::cout << f4(&foo) << '\n';

    // smart pointers can be used to call members of the referenced objects, too
    //std::cout << f4(std::make_shared<Foo>(foo)) << '\n';
    // << f4(std::make_unique<Foo>(foo)) << '\n';
}