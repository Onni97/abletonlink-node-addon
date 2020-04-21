#include "myLink.h"

Napi::FunctionReference MyLink::constructor;

Napi::Object MyLink::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "MyLink",
                  {InstanceMethod("getTempo", &MyLink::tempo),
                   InstanceMethod("getQuantum", &MyLink::getQuantum)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MyLink", func);
  return exports;
}

MyLink::MyLink(const Napi::CallbackInfo& info): Napi::ObjectWrap<MyLink>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if (info.Length() <= 0 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }
    
    Napi::Number value = info[0].As<Napi::Number>();
    //set tempo
}











    
Napi::Value isEnabled(const Napi::CallbackInfo& info) {
    bool = 
}

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





















Napi::Value MyLink::getTempo(const Napi::CallbackInfo& info) {
    double res = state.link.captureAppSessionState().tempo();
    
    return Napi::Number::New(info.Env(), res);
}


Napi::Value MyLink::getQuantum(const Napi::CallbackInfo& info) {
    double res = this->quantum;

    return Napi::Number::New(info.Env(), res);
}