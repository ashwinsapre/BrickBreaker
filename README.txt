Compilation instructions:

	Navigate to the folder containing the files listed above. The server needs to be run before the clients.

Server:
g++ -std=c++17 -o server GameServer.cpp Timeline.cpp -lsfml-graphics -lsfml-window -lsfml-system -lzmq

./server

Client:
g++ -std=c++17 -I/usr/include/v8 -o client MAIN.cpp Game.cpp StaticPlatform.cpp Event.cpp EventManager.cpp Character.cpp CollisionEventHandler.cpp v8helpers.cpp ScriptManager.cpp -lsfml-graphics -lsfml-window -lsfml-system -lzmq -lv8

./client

(you might not need the -I/usr/include/v8) part

Game controls:
	
	Move left: Left arrow key
	Move right: Right arrow key
	Jump: Up arrow key
	Make platform bigger: B key