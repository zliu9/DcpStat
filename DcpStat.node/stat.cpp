#include <node.h>
#include <v8.h>

#include <dcp_stat.h>

using namespace v8;

Handle<Value> DumpStat(const Arguments& args) {
  HandleScope scope;
  TCHAR buffer[4096];
  memset(buffer, 0, sizeof(buffer));
  Stat2Str(buffer, g_dcpStat);

  return scope.Close(String::New(buffer));  
}

void init(Handle<Object> target) {
  InitDcpStat();
  target->Set(String::NewSymbol("dump"),
      FunctionTemplate::New(DumpStat)->GetFunction());
}

NODE_MODULE(dcp_stat_addon, init)