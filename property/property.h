//
// Created by KirkH on 2022/12/4.
//

#ifndef PROPERTY_PROPERTY_H
#define PROPERTY_PROPERTY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class property{
public:
    property(){}
    virtual ~property(){}
};

template <typename T>
class specific_property : public property{
private:
    T data;
public:
    specific_property():property(){}
    void setValue(T& _data){data = _data;}
    T getValue(){ return data; }
};

class State{
private:
    unordered_map<string, property*> props;
public:
    template <typename T>
    void add_property(string name);
    template <typename T>
    void set_property(string name, T& value);
    template <typename T>
    void set_property(string name, T&& value);
    template <typename T>
    T get_value(string name);
    vector<string> get_properties();
};

template <typename T>
void State::add_property(string name)
{
    if(!props[name])
        props[name] = new specific_property<T>;
}

template <typename T>
void State::set_property(string name, T& value)
{
    if(!props[name])
        return;
    specific_property<T>* p;
    p = reinterpret_cast<specific_property<T>*>(props[name]);
    p->setValue(value);
}

template <typename T>
void State::set_property(string name, T&& value)
{
    if(!props[name])
        return;
    specific_property<T>* p;
    p = reinterpret_cast<specific_property<T>*>(props[name]);
    p->setValue(value);
}

template <typename T>
T State::get_value(string name){
    return ((specific_property<T>*)props[name])->getValue();
}

vector<string> State::get_properties()
{
    vector<string> res;
    unordered_map<string, property*>::iterator iter = props.begin();
    while(iter!=props.end())
    {
        res.push_back(iter->first);
        iter++;
    }
    return res;
}

#endif //PROPERTY_PROPERTY_H
