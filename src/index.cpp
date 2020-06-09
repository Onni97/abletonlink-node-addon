#include <napi.h>
#include "webAudioLink.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return webAudioLink::Init(env, exports);
}

NODE_API_MODULE(AbletonLink, InitAll);