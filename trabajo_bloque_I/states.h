#pragma once

template <typename T>
class Machine;

template <typename T>
class State {
    public:
    virtual void enter(Machine<T> *machine) = 0;
    virtual void exit(Machine<T> *machine) = 0;
    virtual void transition(Machine<T> *machine, T input) = 0;
    virtual void update(Machine<T> *machine) = 0;
    virtual ~State() = default;
};