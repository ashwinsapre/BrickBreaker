#include <exception>
#include <signal.h>
#include <stdlib.h>
#include "Game.h"
#include "Character.h"
#include "StaticPlatform.h"
#include "MAIN.h"
#include <v8.h>
#include <libplatform/libplatform.h>
#include "v8helpers.h"


int main()
{
    Game *game = new Game();
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.release());
    v8::V8::InitializeICU();
    v8::V8::Initialize();
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate *isolate = v8::Isolate::New(create_params);

    {
        v8::Isolate::Scope isolate_scope(isolate); // must enter the virtual machine to do stuff
        v8::HandleScope handle_scope(isolate);

        // Best practice to isntall all global functions in the context ahead of time.
        v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
        // Bind the global 'print' function to the C++ Print callback.
        global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, v8helpers::Print));
        // Bind the global static factory function for creating new GameObject instances
        global->Set(isolate, "gameobjectfactory", v8::FunctionTemplate::New(isolate, StaticPlatform::ScriptedGameObjectFactory));
        // Bind the global static function for retrieving object handles
        global->Set(isolate, "gethandle", v8::FunctionTemplate::New(isolate, ScriptManager::getHandleFromScript));
        v8::Local<v8::Context> default_context =  v8::Context::New(isolate, NULL, global);
        v8::Context::Scope default_context_scope(default_context); // enter the context

        ScriptManager *sm = new ScriptManager(isolate, default_context);

        v8::Local<v8::Context> object_context = v8::Context::New(isolate, NULL, global);
        sm->addContext(isolate, object_context, "object_context"); 
        game->init();

        std::vector<StaticPlatform*> *bricks = new std::vector<StaticPlatform*>();
        Character *ball = new Character(20.f);
        StaticPlatform *platform = new StaticPlatform(100.f, 10.f, 350.f, 550.f, sf::Color::Red);
        init(game, ball, bricks);

        platform->exposeToV8(isolate, object_context);

        // With the "object_context" parameter, these scripts are put in a
        // different context than the prior three scripts
        sm->addScript("change_size", "scripts/change_size.js", "object_context");
        sm->addScript("handle_event", "scripts/handle_event.js", "object_context");
        sm->addScript("raise_event", "scripts/raise_event.js", "object_context");

        //time management
        float dt = 0;
        float lastTime=0;
        float curr_time=0;
        float mul = 40;
        while (game->window.isOpen())
        {
            curr_time = game->globalTimeline->getCurrentTime();
            dt = curr_time - lastTime;
            if (!game->paused){
                game->dt = dt;
            }
            lastTime = curr_time;
            //std::cout<<game->dt<<std::endl;
            sf::Event event;
            eventService(game, event); 
            inputService(game, ball, bricks, platform, sm);
            if (game->gameStarted && !game->paused){
                    physicsService(game, ball);
                    collisionService(game, platform, ball, bricks, sm);
                    send(game);
                    receive(game, bricks);
            }
            renderService(game, ball, bricks, platform);
        }
        
        
    }
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete game;
    
    
    return 0;
}