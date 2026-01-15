#include "states.h"
#include "machines.h"
#include <iostream>


class Connecting: public PCUState {
    public:
    void enter(PCUMachine *pcu) override;
    void exit(PCUMachine *pcu) override;
    void transition(PCUMachine *pcu, char input) override;
    void check_usage(PCUMachine *pcu) override;
    static PCUState& getInstance();
    private:
    Connecting() {
        std::cout << "creada instancia de Connecting" << std::endl;
    };
};

class OperationalMachine;

class Operational: public PCUState {
    public:
    void enter(PCUMachine *pcu);
    void exit(PCUMachine *pcu);
    void transition(PCUMachine *pcu, char input);
    private:
    Operational();
    OperationalMachine *internalMachine;
};

class Fault: public PCUState {
    public:
    void enter(PCUMachine *pcu);
    void exit(PCUMachine *pcu);
    void transition(PCUMachine *pcu, char input);
    private:
    Fault() {
        std::cout << "creada instancia de Fault" << std::endl;
    };
};