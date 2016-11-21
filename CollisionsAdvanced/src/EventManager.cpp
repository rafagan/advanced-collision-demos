#include "EventManager.h"

using namespace std;

unordered_map<int, bool> EventManager::keyOn;

bool EventManager::getKeyState(int key)
{
	return keyOn[towlower(key)];
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}
