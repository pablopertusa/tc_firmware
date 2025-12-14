#include <iostream>

class Math {
    public:
    Math() {
        std::cout << "Instancia de Math creada" << std::endl;
    }
    //constexpr long factorial(int x) {
        //if (x <= 0) {
            //return x;
        //}
        //return x * factorial(x-1);
    //}

    template<int N>
    constexpr long factorial() {
        static_assert(N >= 0, "El factorial solo se puede calcular para N >= 0");
        if constexpr (N <= 1) {
            return 1;
        }
        else {
            return (long)N * factorial<N-1>();
        }
    }

    // EN SERIO ESTO NO FUNCIONA?
    //template<int N>
    //constexpr long factorial() {
        //static_assert(N >= 0, "El factorial solo se puede calcular para N >= 0");
        //if constexpr (N <= 1) {
            //return 1;
        //}
        //return (long)N * factorial<N-1>();
        //}
    //}

    constexpr double pow(double x, int y) {
        if (y == 0) {
            return 1.0;
        }
        else if (y > 0) {
            return x * pow(x, y -1);
        }
        else {
            return 1.0 / pow(x, -y);
        }
    }
    //constexpr long sum(int N) {
        //if (N < 0) {
            //return 0;
        //}
        //else {
            //if (N % 2 == 0) {
                //return (N / 2) * (N + 1);
            //}
            //else {
                //return N + (((N-1) / 2) * N);
            //}
        //}
    //}
    template<int N>
    constexpr long sum() {
        static_assert(N >= 0, "N tiene que ser no negativo");
        if (N % 2 == 0) {
            return (N / 2) * (N + 1);
        }
        else {
            return N + (((N-1) / 2) * N);
        }
    }
};

int main() {
    Math m;
    //constexpr long result = m.sum(100);
    constexpr long result = m.factorial<5>();

    //long result_2 = m.sum(50);
    constexpr long result_2 = m.sum<100>();
    long result_3 = m.sum<50>();
    constexpr double result_4 = m.pow(3.14,-3);

    std::cout << "El resultado es: " << result << std::endl;
    std::cout << "El resultado es: " << result_2 << std::endl;
    std::cout << "El resultado es: " << result_3 << std::endl;
    std::cout << "El resultado es: " << result_4 << std::endl;
}