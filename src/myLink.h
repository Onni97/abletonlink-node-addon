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
    
    Napi::Value isEnabled(const Napi::CallbackInfo& info);
    void enable(const Napi::CallbackInfo& info);
    void disable(const Napi::CallbackInfo& info);
    
    Napi::Value isStartStopSyncEnabled(const Napi::CallbackInfo& info);
    void enableStartStopSync(const Napi::CallbackInfo& info);
    void disableStartStopSync(const Napi::CallbackInfo& info);
    
    Napi::Value isPlaying(const Napi::CallbackInfo& info);
    void play(const Napi::CallbackInfo& info);
    void stop(const Napi::CallbackInfo& info);
    
    Napi::Value getNumPeers(const Napi::CallbackInfo& info);
    
    void setNumPeersCallback(const Napi::CallbackInfo& info);
    
    void setTempoCallback(const Napi::CallbackInfo& info);
    
    void setStartStopCallback(const Napi::CallbackInfo& info);
    
    Napi::Value getTempo(const Napi::CallbackInfo& info);
    Napi::Value setTempo(const Napi::CallbackInfo& info);
    
    Napi::Value getQuantum(const Napi::CallbackInfo& info);
    Napi::Value setQuantum(const Napi::CallbackInfo& info);
    
    Napi::Value getBeat(const Napi::CallbackInfo& info);
    void requestBeat(const Napi::CallbackInfo& info);
    void forceBeat(const Napi::CallbackInfo& info);
    
    Napi::Value getPhase(const Napi::CallbackInfo& info);
    
    
    
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
