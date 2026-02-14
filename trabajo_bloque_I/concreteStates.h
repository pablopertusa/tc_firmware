#pragma once
#include "states.h"
#include "machines.h"
#include <iostream>

using PCUState = State<char>;
using PCUMachine = Machine<char>;

namespace PCUFactory {

    inline PCUState CreateConnecting() {
        return PCUState(
            [](PCUMachine* pcu, PCUMachine* nested) {
                std::cout << "Entrando a connecting" << std::endl;
            },
            [](PCUMachine* pcu, PCUMachine* nested) {
                std::cout << "Saliendo de connecting" << std::endl;
            },
            [](PCUMachine* pcu, PCUMachine* nested) {
                std::cout << "Actualmente estamos en Connecting" << std::endl;
            },
            [](PCUMachine* pcu, PCUMachine* nested, char input) {
                if (input == 'o') pcu->setState("Operational");
                else std::cout << "Input no válido" << std::endl;
            }
        );
    }

    inline PCUState CreatePropulsion() {
        return PCUState(
            nullptr, nullptr,
            [](PCUMachine* pcu, PCUMachine* nested) {
                auto* op = static_cast<OperationalMachine<char>*>(pcu);
                op->set_speed(op->check_speed() + 5);
                op->set_usage(op->check_usage() + 2);
            },
            [](PCUMachine* pcu, PCUMachine* n, char input) {
                if (input == 'i') pcu->setState("Idle");
                else if (input == 'b') pcu->setState("Braking");
            }
        );
    }

    inline PCUState CreateBraking() {
        return PCUState(
            nullptr, nullptr,
            [](PCUMachine* pcu, PCUMachine* nested) {
                auto* op = static_cast<OperationalMachine<char>*>(pcu);
                op->set_speed(op->check_speed() - 5);
                op->set_usage(op->check_usage() + 5);
            },
            [](PCUMachine* pcu, PCUMachine* n, char input) {
                if (input == 'i') pcu->setState("Idle");
                else if (input == 'p') pcu->setState("Propulsion");
            }
        );
    }

    inline PCUState CreateIdle() {
        return PCUState(
            nullptr, nullptr,
            [](PCUMachine* pcu, PCUMachine* nested) {
                auto* op = static_cast<OperationalMachine<char>*>(pcu);
                op->set_usage(op->check_usage() + 1);
            },
            [](PCUMachine* pcu, PCUMachine* n, char input) {
                if (input == 'i') pcu->setState("Idle");
                else if (input == 'p') pcu->setState("Propulsion");
                else if(input == 'b') pcu->setState("Braking");
            }
        );
    }

    inline PCUState CreateOperational() {

        auto* internal = new OperationalMachine<char>(); 
        internal->addState("Idle", PCUFactory::CreateIdle());
        internal->addState("Propulsion", PCUFactory::CreatePropulsion());
        internal->addState("Braking", PCUFactory::CreateBraking());

        internal->setState("Idle");

        return PCUState(
            [](PCUMachine* pcu, PCUMachine* nested) {
                std::cout << "Entrando a Operational" << std::endl;
            },
            [](PCUMachine* pcu, PCUMachine* nested) {
                std::cout << "Saliendo de Operational" << std::endl;
                auto* op = static_cast<OperationalMachine<char>*>(nested);
                op->set_speed(0.0);
                op->set_usage(0.0);
                op->setState("Idle");
            },
            [](PCUMachine* pcu, PCUMachine* nested) {
                auto* op = static_cast<OperationalMachine<char>*>(nested);
                op->update();
                std::cout << "- Velocidad = " << op->check_speed() << std::endl;
                std::cout << "- Uso = " << op->check_usage() << std::endl;
            },
            [](PCUMachine* pcu, PCUMachine* nested, char input) {
                auto* op = static_cast<OperationalMachine<char>*>(nested);
                if (op->check_usage() >= 20) {
                    pcu->setState("Fault");
                } else {
                    nested->transition(input);
                }
            },
            internal
        );
    }

    inline PCUState CreateFault() {
        return PCUState(
            [](PCUMachine* pcu, PCUMachine* n) { std::cout << "Entrando a Fault" << std::endl; },
            nullptr,
            [](PCUMachine* pcu, PCUMachine* n) { std::cout << "Actualmente en Fault" << std::endl; },
            [](PCUMachine* pcu, PCUMachine* n, char input) {
                if (input == 'r') pcu->setState("Connecting");
            }
        );
    }

}