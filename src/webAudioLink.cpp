#include "webAudioLink.h"

Napi::FunctionReference webAudioLink::constructor;

Napi::Object webAudioLink::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "webAudioLink",
                  {
                    InstanceMethod("isEnabled", &webAudioLink::isEnabled),
                    InstanceMethod("enable", &webAudioLink::enable),
                    InstanceMethod("disable", &webAudioLink::disable),
                    InstanceMethod("isStartStopSyncEnabled", &webAudioLink::isStartStopSyncEnabled),
                    InstanceMethod("enableStartStopSync", &webAudioLink::enableStartStopSync),
                    InstanceMethod("disableStartStopSync", &webAudioLink::disableStartStopSync),
                    InstanceMethod("isPlaying", &webAudioLink::isPlaying),
                    InstanceMethod("play", &webAudioLink::play),
                    InstanceMethod("stop", &webAudioLink::stop),
                    InstanceMethod("getNumPeers", &webAudioLink::getNumPeers),
                    InstanceMethod("setNumPeersCallback", &webAudioLink::setNumPeersCallback),
                    InstanceMethod("setTempoCallback", &webAudioLink::setTempoCallback),
                    InstanceMethod("setStartStopCallback", &webAudioLink::setStartStopCallback),
                    InstanceMethod("getTempo", &webAudioLink::getTempo),
                    InstanceMethod("setTempo", &webAudioLink::setTempo),
                    InstanceMethod("getQuantum", &webAudioLink::getQuantum),
                    InstanceMethod("setQuantum", &webAudioLink::setQuantum),
                    InstanceMethod("getBeat", &webAudioLink::getBeat),
                    InstanceMethod("requestBeat", &webAudioLink::requestBeat),
                    InstanceMethod("forceBeat", &webAudioLink::forceBeat),
                    InstanceMethod("getPhase", &webAudioLink::getPhase),
                    InstanceMethod("isAudioThread", &webAudioLink::isAudioThread),
                    InstanceMethod("setAppThread", &webAudioLink::setAppThread),
                    InstanceMethod("setAudioThread", &webAudioLink::setAudioThread),
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("webAudioLink", func);
  return exports;
}





//CONSTRUCTOR
webAudioLink::webAudioLink(const Napi::CallbackInfo& info): Napi::ObjectWrap<webAudioLink>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    //set defaults
    this->quantum = 4;
    this->useAppThreadFunctions = true;
}





//METHODS

//
Napi::Value webAudioLink::isEnabled(const Napi::CallbackInfo& info) {
    bool res = container.link.isEnabled();
    return Napi::Boolean::New(info.Env(), res);
}

void webAudioLink::enable(const Napi::CallbackInfo& info) {
    container.link.enable(true);
}

void webAudioLink::disable(const Napi::CallbackInfo& info) {
    container.link.enable(false);
}





Napi::Value webAudioLink::isStartStopSyncEnabled(const Napi::CallbackInfo& info) {
    bool res = container.link.isStartStopSyncEnabled();
    return Napi::Boolean::New(info.Env(), res);
}

void webAudioLink::enableStartStopSync(const Napi::CallbackInfo& info) {
    container.link.enableStartStopSync(true);
}

void webAudioLink::disableStartStopSync(const Napi::CallbackInfo& info) {
    container.link.enableStartStopSync(false);
}





Napi::Value webAudioLink::getNumPeers(const Napi::CallbackInfo& info) {
    int res = container.link.numPeers();
    return Napi::Number::New(info.Env(), res);
}





void webAudioLink::setNumPeersCallback(const Napi::CallbackInfo& info) {
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

void webAudioLink::setTempoCallback(const Napi::CallbackInfo& info) {
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

void webAudioLink::setStartStopCallback(const Napi::CallbackInfo& info) {
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





Napi::Value webAudioLink::getTempo(const Napi::CallbackInfo& info) {
    double tempo;
    if(this->useAppThreadFunctions) {
        tempo = container.link.captureAppSessionState().tempo();
    } else {
        tempo = container.link.captureAudioSessionState().tempo();
    }
    return Napi::Number::New(info.Env(), tempo);
}

void webAudioLink::setTempo(const Napi::CallbackInfo& info) {
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





Napi::Value webAudioLink::getBeat(const Napi::CallbackInfo& info) {
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

void webAudioLink::requestBeat(const Napi::CallbackInfo& info) {
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

void webAudioLink::forceBeat(const Napi::CallbackInfo& info) {
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





Napi::Value webAudioLink::getPhase(const Napi::CallbackInfo& info) {
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





Napi::Value webAudioLink::isPlaying(const Napi::CallbackInfo& info) {
    bool isPlaying;
    if(this->useAppThreadFunctions) {
        isPlaying = container.link.captureAppSessionState().isPlaying();
    } else {
        isPlaying = container.link.captureAudioSessionState().isPlaying();
    }
    return Napi::Boolean::New(info.Env(), isPlaying);
}

void webAudioLink::play(const Napi::CallbackInfo& info) {
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

void webAudioLink::stop(const Napi::CallbackInfo& info) {
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





Napi::Value webAudioLink::isAudioThread(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), !(this->useAppThreadFunctions));
}

void webAudioLink::setAppThread(const Napi::CallbackInfo& info) {
    this->useAppThreadFunctions = true;
}

void webAudioLink::setAudioThread(const Napi::CallbackInfo& info) {
    this->useAppThreadFunctions = false;
}





Napi::Value webAudioLink::getQuantum(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->quantum);
}

void webAudioLink::setQuantum(const Napi::CallbackInfo& info) {
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
    this->quantum = newQuantum.Int32Value();
}