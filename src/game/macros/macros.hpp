#pragma once

#define SDL_SetRenderDrawColour SDL_SetRenderDrawColor
#define SDL_WINDOWPOS_CENTRED SDL_WINDOWPOS_CENTERED

#define GETTER_CPP(type, className, name, name2) \
    const type &className::get##name2(void) { return name; }

#define GETTER_HPP(type, name, name2) \
protected:                            \
    type name;                        \
                                      \
public:                               \
    const type &get##name2(void);
#define GETTER_HPP_DEFAULT(type, name, name2, value) \
protected:                                           \
    type name = value;                               \
                                                     \
public:                                              \
    const type &get##name2(void);

#define GETTER_AND_SETTER_CPP(type, className, name, name2) \
    GETTER_CPP(type, className, name, name2)                \
    void className::set##name2(type newValue) { name = newValue; }

#define GETTER_AND_SETTER_HPP(type, name, name2) \
    GETTER_HPP(type, name, name2)                \
    void set##name2(type newValue);
#define GETTER_AND_SETTER_HPP_DEFAULT(type, name, name2, value) \
    GETTER_HPP_DEFAULT(type, name, name2, value)                \
    void set##name2(type newValue);
