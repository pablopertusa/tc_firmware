#pragma once
#include <functional>
#include <iostream>

template <typename T>
class Machine;

template <typename T>
class State {
private:
    std::function<void(Machine<T>*, Machine<T>*)> enter_func;
    std::function<void(Machine<T>*, Machine<T>*)> exit_func;
    std::function<void(Machine<T>*, Machine<T>*)> update_func;
    std::function<void(Machine<T>*, Machine<T>*, T)> transition_func;
    
    Machine<T>* nestedMachine;

public:
    State(
        std::function<void(Machine<T>*, Machine<T>*)> on_enter = nullptr,
        std::function<void(Machine<T>*, Machine<T>*)> on_exit = nullptr,
        std::function<void(Machine<T>*, Machine<T>*)> on_update = nullptr,
        std::function<void(Machine<T>*, Machine<T>*, T)> on_trans = nullptr,
        Machine<T>* nested = nullptr
    ): enter_func(on_enter), 
        exit_func(on_exit), 
        update_func(on_update), 
        transition_func(on_trans), 
        nestedMachine(nested) 
    {
        std::cout << "Estado instanciado correctamente." << std::endl;
    }

    void enter(Machine<T>* machine) {
        if (enter_func) enter_func(machine, nestedMachine);
    };

    void exit(Machine<T>* machine) {
        if (exit_func) exit_func(machine, nestedMachine);
    };

    void update(Machine<T>* machine) {
        if (update_func) update_func(machine, nestedMachine);
    };

    void transition(Machine<T>* machine, T input) {
        if (transition_func) transition_func(machine, nestedMachine, input);
    };
};