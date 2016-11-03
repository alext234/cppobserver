[![Build Status](https://travis-ci.org/networkshark/cppobserver.svg?branch=master)](https://travis-ci.org/networkshark/cppobserver)

# cppobserver
Generic observer pattern in c++.


Below is a simple example:

```c++
#include <iostream>
#include <string>
#include <memory>
#include "cpp_observer.h"

struct EventMsg {
    EventMsg (std::string  message): msg{message} {}
    std::string msg;
};

class A: public Observable<EventMsg>{
public:
    void doSomeWorkAndNotify () {
        notifyObservers (EventMsg{"hello from A!"});        
    }
};

class B: public AbstractObserver<EventMsg>{
public:    

    void onNotified (const EventMsg& msg) override {
        std::cout <<"B received message : "<< msg.msg <<std::endl;
    }

    
};



int main (int argc, char* argv[]) {
    auto a = std::make_unique<A> ();

    auto b = std::make_shared<B> ();
    
    a->registerObserver(b);

    a->doSomeWorkAndNotify();
}
```
