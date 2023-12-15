#ifndef STATIC_PLATFORM_H
#define STATIC_PLATFORM_H
#include <SFML/Graphics.hpp>

#include <utility>
#include <v8.h>

class StaticPlatform : public sf::RectangleShape{

public:
	float xsize = 0;
	float ysize = 0;
	int isVisible = 1;
	int newColor = 0;
	StaticPlatform(float sizeX, float sizeY, float initX, float initY, sf::Color c);
    sf::FloatRect getBoundingBox();
    v8::Local<v8::Object> exposeToV8(v8::Isolate *isolate, v8::Local<v8::Context> &context, std::string context_name="default");
    static void setGameObjectX(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
    static void getGameObjectX(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info); // note return type
    static void setGameObjectVisible(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
    static void getGameObjectVisible(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info); // note return type
    static StaticPlatform* GameObjectFactory(std::string context_name="default");
    static void ScriptedGameObjectFactory(const v8::FunctionCallbackInfo<v8::Value>& args);
};

#endif // STATIC_PLATFORM_H