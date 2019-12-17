#include <nan.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

bool compare(std::string &s1,std::string &s2);

bool compare(std::string &s1,std::string &s2)
{
    return s1.size() > s2.size();
}

void getTenLong(const Nan::FunctionCallbackInfo<v8::Value>& info)
{

    v8::Local<v8::Array> incomingArray = v8::Local<v8::Array>::Cast(info[0]);
    std::vector<std::string> vec;
    v8::Local<v8::Array> outgoingArray = Nan::New<v8::Array>(10);

    for (unsigned int i = 0, len=incomingArray->Length(); i < len; ++i) {

        v8::String::Utf8Value args((incomingArray->Get(i))->ToString());
        std::string result = std::string(*args);
        vec.push_back(result);
    }

    sort(vec.begin(), vec.end(), compare);

    for (int i = 0; i < 10; ++i) {
        std::string data = vec.at(i);
        v8::Local<v8::String> feed = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), data.c_str());
        outgoingArray->Set(i, feed);
    }

    info.GetReturnValue().Set(outgoingArray);
}

void Init(v8::Local<v8::Object> exports) {
exports->Set(Nan::New("getSetGo").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(getTenLong)->GetFunction());
}


NODE_MODULE(addon, Init)
