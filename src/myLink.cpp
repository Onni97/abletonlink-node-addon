#include "myLink.h"

Napi::FunctionReference MyLink::constructor;

Napi::Object MyLink::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "MyLink",
                  {InstanceMethod("tempo", &MyLink::tempo),
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





Napi::Value MyLink::tempo(const Napi::CallbackInfo& info) {
    double res = state.link.captureAppSessionState().tempo();
    
    return Napi::Number::New(info.Env(), res);
}


Napi::Value MyLink::getQuantum(const Napi::CallbackInfo& info) {
    double res = this->quantum;

    return Napi::Number::New(info.Env(), res);
}