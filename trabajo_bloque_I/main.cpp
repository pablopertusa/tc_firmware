#include <iostream>
#include "machines.h"
#include "concreteStates.h"

void initPCU(Machine<char>& pcu) {
    pcu.addState("Connecting", PCUFactory::CreateConnecting());
    pcu.addState("Operational", PCUFactory::CreateOperational());
    pcu.addState("Fault", PCUFactory::CreateFault());

    pcu.setState("Connecting");
}

int main() {
    Machine<char> machine;
    initPCU(machine);
    
    char userInput;
    bool running = true;

    std::cout << "--- PCU Machine Control ---" << std::endl;
    std::cout << "Introduce un caracter para transicionar (o 'q' para salir):" << std::endl;

    machine.update();

    while (running) {
        std::cout << "\n> Esperando input: ";
        std::cin >> userInput;

        if (userInput == 'q' || userInput == 'Q') {
            running = false;
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        }

        machine.transition(userInput);

        machine.update();
        
        std::cin.ignore(1000, '\n');
    }

    return 0;
}