#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Settings.h"
#include <string>

using namespace std;

class GameObject {
    public:
        GameObject();
        GameObject(char type);
        ~GameObject();
    private:
        char type;
};

#endif