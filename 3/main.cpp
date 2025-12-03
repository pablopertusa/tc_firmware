#include <iostream>
#include <string>

class Peripheral {
    private:
    // supongo que no debería cambiar
    const std::string pin;
    bool enabled;
    public:
    Peripheral(const std::string& pin): pin(pin) {
        std::cout << "Creado Peripheral" << std::endl;
        enabled = false;
    }
    void enable() {
        enabled = true;
    }
    void disable() {
        enabled = false;
    }
    virtual void display() {
        std::cout << "Peripheral en estado " << enabled << std::endl;
    }
};

class PWM: public Peripheral {
    private:
    double frequency;
    double duty_cycle;
    public:
    PWM(const std::string& pin): Peripheral(pin) {
        frequency = 0;
        duty_cycle = 0;
    }
    void display() override {
        Peripheral::display();
        std::cout << "Tipo PWM" << std::endl;
        std::cout << "Frecuencia: " << frequency << std::endl;
        std::cout << "Duty cycle: " << duty_cycle << std::endl;
    }
    void set_frequency(double frequency) {
        this->frequency = frequency;
    }
    double get_frequency() {
        return frequency;
    }
    void set_duty_cycle(double duty_cycle) {
        this->duty_cycle = duty_cycle;
    }
    double get_duty_cycle() {
        return duty_cycle;
    }
};

int main() {
    const std::string pin = "ejemplo";
    PWM pwm(pin);
    pwm.get_frequency();
    pwm.set_frequency(12);
    pwm.set_duty_cycle(50);
    pwm.display();
    pwm.get_frequency();
    pwm.set_frequency(18);
    pwm.set_duty_cycle(53);
    pwm.enable();
    pwm.display();

    return 0;
}