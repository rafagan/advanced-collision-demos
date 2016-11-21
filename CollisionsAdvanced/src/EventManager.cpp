#include "EventManager.h"

using namespace std;

unordered_map<int, bool> EventManager::keyOn;
int EventManager::lastKeyPressed = -9999999;

bool EventManager::getKeyState(int key)
{
	return keyOn[towlower(key)];
}

int EventManager::getLastKeyPressed()
{
	return lastKeyPressed;
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}
