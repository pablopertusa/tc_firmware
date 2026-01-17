#pragma once

class PCUMachine;
class OperationalMachine;

class PCUState {
    public:
    virtual void enter(PCUMachine *machine) = 0;
    virtual void exit(PCUMachine *machine) = 0;
    virtual void transition(PCUMachine *machine, char input) = 0;
    virtual void update(PCUMachine *machine) = 0;
    virtual ~PCUState() {}
};

class OperationalState {
    public:
    virtual void enter(OperationalMachine *machine) = 0;
    virtual void exit(OperationalMachine *machine) = 0;
    virtual void transition(OperationalMachine *machine, char input) = 0;
    virtual void update(OperationalMachine *machine) = 0;
    virtual ~OperationalState() {}
};

