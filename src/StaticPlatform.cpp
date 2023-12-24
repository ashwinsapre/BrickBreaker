#include "StaticPlatform.h"
#include "ScriptManager.h"
#include "v8helpers.h"

StaticPlatform::StaticPlatform(float sizeX, float sizeY, float initX, float initY, sf::Color c){
        xsize = sizeX;
        ysize = sizeY;
        setSize(sf::Vector2f(xsize, ysize));
        setPosition(sf::Vector2f(initX, initY));
        setFillColor(c);
}

void StaticPlatform::setPower(){
    if (power.loadFromFile("./Assets/star.png")) {
        setTexture(&power);
    }
}

void StaticPlatform::resetPower(){
    setTexture(nullptr);
}

sf::FloatRect StaticPlatform::getBoundingBox(){
        return getGlobalBounds();
}

v8::Local<v8::Object> StaticPlatform::exposeToV8(v8::Isolate *isolate, v8::Local<v8::Context> &context, std::string context_name)
{
    std::vector<v8helpers::ParamContainer<v8::AccessorGetterCallback, v8::AccessorSetterCallback>> v;
    v.push_back(v8helpers::ParamContainer("xsize", getGameObjectX, setGameObjectX));
    v.push_back(v8helpers::ParamContainer("newColor", getGameObjectVisible, setGameObjectVisible));
    return v8helpers::exposeToV8("someID", this, v, isolate, context, context_name);
}

void StaticPlatform::setGameObjectX(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Local<v8::Object> self = info.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    static_cast<StaticPlatform*>(ptr)->xsize =  static_cast<float>(value->Int32Value());
}

void StaticPlatform::getGameObjectX(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> self = info.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int c = static_cast<StaticPlatform*>(ptr)->xsize;
    info.GetReturnValue().Set(c);
}

void StaticPlatform::setGameObjectVisible(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Local<v8::Object> self = info.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    static_cast<StaticPlatform*>(ptr)->newColor =  static_cast<float>(value->Int32Value());
}

void StaticPlatform::getGameObjectVisible(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> self = info.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int c = static_cast<StaticPlatform*>(ptr)->newColor;
    info.GetReturnValue().Set(c);
}

void StaticPlatform::ScriptedGameObjectFactory(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Isolate *isolate = args.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::EscapableHandleScope handle_scope(args.GetIsolate());
    v8::Context::Scope context_scope(context);

    std::string context_name("default");
    if(args.Length() == 1)
    {
        v8::String::Utf8Value str(args.GetIsolate(), args[0]);
        context_name = std::string(v8helpers::ToCString(str));
#if GO_DEBUG
        std::cout << "Created new object in context " << context_name << std::endl;
#endif
    }
    StaticPlatform *new_object = new StaticPlatform(100.f, 10.f, 350.f, 500.f, sf::Color::Green);
    v8::Local<v8::Object> v8_obj = new_object->exposeToV8(isolate, context);
    args.GetReturnValue().Set(handle_scope.Escape(v8_obj));
    //delete new_object;
}