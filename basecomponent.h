#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H


//inherit from QObject to use singals and slots in child classes
class BaseComponent{
public:
    BaseComponent() {}
    virtual ~BaseComponent(){}
};

#endif // BASECOMPONENT_H
