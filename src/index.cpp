#include <napi.h>
#include "myLink.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return MyLink::Init(env, exports);
}

NODE_API_MODULE(AbletonLink, InitAll);