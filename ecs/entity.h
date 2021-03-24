#pragma once

#include "component.h"

#include <iostream>
#include <string>
#include <map>

class Component;

class Entity
{
private:
	std::string name;
	bool enabled = true;
	std::map<const char*, Component*> components;

public:
	Entity(const std::string& name);
	~Entity();

	void init();
	void events();
	void update();
	void render();

	template<typename T, typename... TArgs>
	inline void addComponent(TArgs&&... args)
	{
		T* component = new T(std::forward<TArgs>(args)...);

		component->owner = this;
		component->init();

		components[typeid(T).name()] = component;
	}

	template<typename T>
	inline T* getComponent()
	{
		T* component = static_cast<T*>(components[typeid(T).name()]);

		if (component == nullptr) {
			std::cerr << "Entity " << this->name << " does not have a " << typeid(T).name() << "\n";
			std::cerr << "Closing the application...\n";
			exit(0);
		}

		return component;
	}
};