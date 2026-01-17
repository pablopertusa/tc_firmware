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
};

class OperationalMachine {
    public:
    OperationalMachine();
    void transition(char input);
    void setState(OperationalState &newState);
    void update();
    OperationalState* getCurrentState();
    float check_speed();
    float check_usage();
    void set_speed(float s);
    void set_usage(float u);

    private:
    OperationalState *currentState;
    float speed;
    float usage;
};