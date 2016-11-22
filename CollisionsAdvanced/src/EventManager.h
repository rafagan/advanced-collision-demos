#pragma once
#include <unordered_map>

class EventManager
{
	friend class ofApp; //EventManager is some kind of ofApp global extension

	static std::unordered_map<int, bool> keyOn;
	static int lastKeyPressed;
public:
	static bool getKeyState(int key);
	static int getLastKeyPressed();

	explicit EventManager();
	virtual ~EventManager();
};

#define KEY(key) EventManager::getKeyState(key)