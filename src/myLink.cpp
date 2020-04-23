#include "myLink.h"

Napi::FunctionReference MyLink::constructor;

Napi::Object MyLink::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "MyLink",
                  {
                    InstanceMethod("isEnabled", &MyLink::isEnabled),
                    InstanceMethod("enable", &MyLink::enable),
                    InstanceMethod("disable", &MyLink::disable),
                    InstanceMethod("isStartStopSyncEnabled", &MyLink::isStartStopSyncEnabled),
                    InstanceMethod("enableStartStopSync", &MyLink::enableStartStopSync),
                    InstanceMethod("disableStartStopSync", &MyLink::disableStartStopSync),
                    InstanceMethod("isPlaying", &MyLink::isPlaying),
                    InstanceMethod("play", &MyLink::play),
                    InstanceMethod("stop", &MyLink::stop),
                    InstanceMethod("getNumPeers", &MyLink::getNumPeers),
                    InstanceMethod("setNumPeersCallback", &MyLink::setNumPeersCallback),
                    InstanceMethod("setTempoCallback", &MyLink::setTempoCallback),
                    InstanceMethod("setStartStopCallback", &MyLink::setStartStopCallback),
                    InstanceMethod("getTempo", &MyLink::getTempo),
                    InstanceMethod("setTempo", &MyLink::setTempo),
                    InstanceMethod("getQuantum", &MyLink::getQuantum),
                    InstanceMethod("setQuantum", &MyLink::setQuantum),
                    InstanceMethod("getBeat", &MyLink::getBeat),
                    InstanceMethod("requestBeat", &MyLink::requestBeat),
                    InstanceMethod("forceBeat", &MyLink::forceBeat),
                    InstanceMethod("getPhase", &MyLink::getPhase),
                    InstanceMethod("isAudioThread", &MyLink::isAudioThread),
                    InstanceMethod("setAppThread", &MyLink::setAppThread),
                    InstanceMethod("setAudioThread", &MyLink::setAudioThread),
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MyLink", func);
  return exports;
}





//CONSTRUCTOR
MyLink::MyLink(const Napi::CallbackInfo& info): Napi::ObjectWrap<MyLink>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if (info.Length() <= 0 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }
    
    //if peer = 0 set tempo
    Napi::Number newTempo = info[0].As<Napi::Number>();
    
    //set defaults
    this->quantum = 4;
    this->useAppThreadFunctions = true;
}





//METHODS

//
Napi::Value MyLink::isEnabled(const Napi::CallbackInfo& info) {
    bool res = container.link.isEnabled();
    return Napi::Boolean::New(info.Env(), res);
}

void MyLink::enable(const Napi::CallbackInfo& info) {
    container.link.enable(true);
}

void MyLink::disable(const Napi::CallbackInfo& info) {
    container.link.enable(false);
}





Napi::Value MyLink::isStartStopSyncEnabled(const Napi::CallbackInfo& info) {
    bool res = container.link.isStartStopSyncEnabled();
    return Napi::Boolean::New(info.Env(), res);
}

void MyLink::enableStartStopSync(const Napi::CallbackInfo& info) {
    container.link.enableStartStopSync(true);
}

void MyLink::disableStartStopSync(const Napi::CallbackInfo& info) {
    container.link.enableStartStopSync(false);
}





Napi::Value MyLink::getNumPeers(const Napi::CallbackInfo& info) {
    int res = container.link.numPeers();
    return Napi::Number::New(info.Env(), res);
}





void MyLink::setNumPeersCallback(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsFunction()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    
    Napi::Function cb = info[0].As<Napi::Function>();
    
    numPeersCallback = Napi::ThreadSafeFunction::New(info.Env(), cb, "numPeersCallback", 0, 1, []( Napi::Env ) {});
    container.link.setNumPeersCallback([this](double numPeers) {
        napi_status status = numPeersCallback.BlockingCall([numPeers](Napi::Env env, Napi::Function jsCallback) {
            Napi::HandleScope scope(env);
            jsCallback.Call({ Napi::Number::New(env, numPeers) });
        });
    });
}

void MyLink::setTempoCallback(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsFunction()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    
    Napi::Function cb = info[0].As<Napi::Function>();
    
    tempoCallback = Napi::ThreadSafeFunction::New(info.Env(), cb, "tempoCallback", 0, 1, []( Napi::Env ) {});
    container.link.setTempoCallback([this](double tempo) {
        napi_status status = tempoCallback.BlockingCall([tempo](Napi::Env env, Napi::Function jsCallback) {
            Napi::HandleScope scope(env);
            jsCallback.Call({ Napi::Number::New(env, tempo) });
        });
    });
}

void MyLink::setStartStopCallback(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsFunction()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    
    Napi::Function cb = info[0].As<Napi::Function>();
    
    startStopCallback = Napi::ThreadSafeFunction::New(info.Env(), cb, "startStopCallback", 0, 1, []( Napi::Env ) {});
    container.link.setStartStopCallback([this](bool isPlaying) {
        napi_status status = startStopCallback.BlockingCall([isPlaying](Napi::Env env, Napi::Function jsCallback) {
            Napi::HandleScope scope(env);
            jsCallback.Call({ Napi::Boolean::New(env, isPlaying) });
        });
    });
}





Napi::Value MyLink::getTempo(const Napi::CallbackInfo& info) {
    double tempo;
    if(this->useAppThreadFunctions) {
        tempo = container.link.captureAppSessionState().tempo();
    } else {
        tempo = container.link.captureAudioSessionState().tempo();
    }
    return Napi::Number::New(info.Env(), tempo);
}

void MyLink::setTempo(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    double newTempo = info[0].As<Napi::Number>().DoubleValue();
    
    //set new tempo
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAppSessionState();
        newState.setTempo(newTempo, time);
        container.link.commitAppSessionState(newState);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAudioSessionState();
        newState.setTempo(newTempo, time);
        container.link.commitAudioSessionState(newState);
    }
}





Napi::Value MyLink::getBeat(const Napi::CallbackInfo& info) {
    double beat;
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        beat = container.link.captureAppSessionState().beatAtTime(time, this->quantum);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        beat = container.link.captureAudioSessionState().beatAtTime(time, this->quantum);
    }
    return Napi::Number::New(info.Env(), beat);
}

void MyLink::requestBeat(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    double newBeat = info[0].As<Napi::Number>().DoubleValue();
    
    //set new beat
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAppSessionState();
        newState.requestBeatAtTime(newBeat, time, this->quantum);
        container.link.commitAppSessionState(newState);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAudioSessionState();
        newState.requestBeatAtTime(newBeat, time, this->quantum);
        container.link.commitAudioSessionState(newState);
    }
}

void MyLink::forceBeat(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    double newBeat = info[0].As<Napi::Number>().DoubleValue();
    
    //force new beat
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAppSessionState();
        newState.forceBeatAtTime(newBeat, time, this->quantum);
        container.link.commitAppSessionState(newState);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAudioSessionState();
        newState.forceBeatAtTime(newBeat, time, this->quantum);
        container.link.commitAudioSessionState(newState);
    }
}





Napi::Value MyLink::getPhase(const Napi::CallbackInfo& info) {
    double phase;
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        phase = container.link.captureAppSessionState().phaseAtTime(time, this->quantum);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        phase = container.link.captureAudioSessionState().phaseAtTime(time, this->quantum);
    }
    return Napi::Number::New(info.Env(), phase);
}





Napi::Value MyLink::isPlaying(const Napi::CallbackInfo& info) {
    bool isPlaying;
    if(this->useAppThreadFunctions) {
        isPlaying = container.link.captureAppSessionState().isPlaying();
    } else {
        isPlaying = container.link.captureAudioSessionState().isPlaying();
    }
    return Napi::Boolean::New(info.Env(), isPlaying);
}

void MyLink::play(const Napi::CallbackInfo& info) {
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAppSessionState();
        newState.setIsPlaying(true, time);
        container.link.commitAppSessionState(newState);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAudioSessionState();
        newState.setIsPlaying(true, time);
        container.link.commitAudioSessionState(newState);
    }
}

void MyLink::stop(const Napi::CallbackInfo& info) {
    if(this->useAppThreadFunctions) {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAppSessionState();
        newState.setIsPlaying(false, time);
        container.link.commitAppSessionState(newState);
    } else {
        std::chrono::microseconds time = container.link.clock().micros();
        ableton::Link::SessionState newState = container.link.captureAudioSessionState();
        newState.setIsPlaying(false, time);
        container.link.commitAudioSessionState(newState);
    }
}





Napi::Value MyLink::isAudioThread(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), !(this->useAppThreadFunctions));
}

void MyLink::setAppThread(const Napi::CallbackInfo& info) {
    this->useAppThreadFunctions = true;
}

void MyLink::setAudioThread(const Napi::CallbackInfo& info) {
    this->useAppThreadFunctions = false;
}





Napi::Value MyLink::getQuantum(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->quantum);
}

void MyLink::setQuantum(const Napi::CallbackInfo& info) {
    //throw exception in case of wrong parameter
    Napi::Env env = info.Env();
    
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    
    //set new quantum
    Napi::Number newQuantum = info[0].As<Napi::Number>();
    this->quantum = newQuantum.DoubleValue();
}