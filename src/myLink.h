#ifndef LINK_OBJECT
#define LINK_OBJECT

#include <ableton/Link.hpp>
#include <napi.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>


class MyLink : public Napi::ObjectWrap<MyLink> {
    public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    MyLink(const Napi::CallbackInfo& info);

    private:
    static Napi::FunctionReference constructor;
    
    //Napi::Boolean isEnabled(const Napi::CallbackInfo& info);
    //void enable(const Napi::CallbackInfo& info);
    //Napi::Boolean isStartStopSyncEnabled(const Napi::CallbackInfo& info);
    //void enableStartStopSync(const Napi::CallbackInfo& info);
    //Napi::Number numPeers(const Napi::CallbackInfo& info);
    //void setNumPeersCallback(const Napi::CallbackInfo& info);
    //void setTempoCallback(const Napi::CallbackInfo& info);
    Napi::Value tempo(const Napi::CallbackInfo& info);
    Napi::Value getQuantum(const Napi::CallbackInfo& info);
    
    
    struct State
    {
      ableton::Link link;

      State(): link(120)
      {
        link.enable(true);
      }
    };
    
    Napi::Number quantum;
    State state;
};

#endif
