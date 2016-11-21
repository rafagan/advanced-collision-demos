#pragma once
#include <unordered_map>

class EventManager
{
	friend class ofApp; //ofApp extension
	static std::unordered_map<int, bool> keyOn;
public:
	static bool getKeyState(int key);

	explicit EventManager();
	virtual ~EventManager();
};

#define KEY(key) EventManager::getKeyState(key)