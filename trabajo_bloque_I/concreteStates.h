#include "states.h"
#include "machines.h"
#include <iostream>


class Connecting: public PCUState {
    public:
    void enter(PCUMachine *pcu) override;
    void exit(PCUMachine *pcu) override;
    void transition(PCUMachine *pcu, char input) override;
    void update(PCUMachine *pcu) override;
    static PCUState& getInstance();
    private:
    Connecting() {
        std::cout << "-- creada instancia de Connecting" << std::endl;
    };
};

class OperationalMachine;

class Operational: public PCUState {
    public:
    void enter(PCUMachine *pcu) override;
    void exit(PCUMachine *pcu) override;
    void transition(PCUMachine *pcu, char input) override;
    void update(PCUMachine *pcu) override;
    static PCUState& getInstance();
    private:
    Operational() {
        std::cout << "-- creada instancia de Operational" << std::endl;
    }
    OperationalMachine *internalMachine;
};

class Fault: public PCUState {
    public:
    void enter(PCUMachine *pcu) override;
    void exit(PCUMachine *pcu) override;
    void transition(PCUMachine *pcu, char input) override;
    void update(PCUMachine *pcu) override;
    static PCUState& getInstance();
    private:
    Fault() {
        std::cout << "-- creada instancia de Fault" << std::endl;
    };
};

class Idle: public OperationalState {
    public:
    void enter(OperationalMachine *pcu) override;
    void exit(OperationalMachine *pcu) override;
    void transition(OperationalMachine *pcu, char input) override;
    void update(OperationalMachine *pcu) override;
    static OperationalState& getInstance();
    private:
    Idle() {
        std::cout << "-- creada instancia de Idle" << std::endl;
    };
};

class Propulsion: public OperationalState {
    public:
    void enter(OperationalMachine *pcu) override;
    void exit(OperationalMachine *pcu) override;
    void transition(OperationalMachine *pcu, char input) override;
    void update(OperationalMachine *pcu) override;
    static OperationalState& getInstance();
    private:
    Propulsion() {
        std::cout << "-- creada instancia de Propulsion" << std::endl;
    };
};

class Braking: public OperationalState {
    public:
    void enter(OperationalMachine *pcu) override;
    void exit(OperationalMachine *pcu) override;
    void transition(OperationalMachine *pcu, char input) override;
    void update(OperationalMachine *pcu) override;
    static OperationalState& getInstance();
    private:
    Braking() {
        std::cout << "-- creada instancia de Braking" << std::endl;
    };
};