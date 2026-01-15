#pragma once

class PCUState;
class OperationalState;

class PCUMachine {
    public:
    PCUMachine();
    void transition(char input);
    void setState(PCUState &newState);
    void update();
    PCUState* getCurrentState();

    private:
    PCUState *currentState;
    float usage;
};

class OperationalMachine {
    public:
    OperationalMachine();
    void transition(char input);
    void setState(OperationalState &newState);
    void update();
    OperationalState* getCurrentState();

    private:
    OperationalState *currentState;
    float speed;
};