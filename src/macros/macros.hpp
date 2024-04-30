#pragma once

#define SDL_SetRenderDrawColour SDL_SetRenderDrawColor
#define SDL_WINDOWPOS_CENTRED SDL_WINDOWPOS_CENTERED

#define GETTER_CPP(type, className, name, name2) \
    type className::get##name2(void) { return this->name; }

#define GETTER_HPP(type, name, name2) \
protected:                            \
    type name;                        \
                                      \
public:                               \
    type get##name2(void);

#define GETTER_AND_SETTER_CPP(type, className, name, name2) \
    GETTER_CPP(type, className, name, name2)                \
    void className::set##name2(type newValue) { this->name = newValue; }

#define GETTER_AND_SETTER_HPP(type, name, name2) \
    GETTER_HPP(type, name, name2)                \
    void set##name2(type newValue);
