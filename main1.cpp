#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTaskOne = '1';
const int kTaskTwo = '2';
const int kTaskThree = '3';
const int kTaskFour = '4';

const int kPrecision = 6;
}  // namespace

void taskOne() {
    const int kIStep = 5;
    int n = 0;
    int m = 0;
    std::cout << "Введите натуральные числа n и m (m < n):" << '\n';
    std::cin >> n >> m;

    if (m <= 0 || n <= 0 || m >= n) {
        std::cout << "Были введены неправильные данные." << '\n';
        return;
    }

    int naturalSum = 0;
    int i = 0;
    while (i <= n) {
        if (i % m != 0) {
            naturalSum += i;
        }
        i += kIStep;
    }
    std::cout << "Ответ на задачу: " << naturalSum << '\n';
}

void taskTwo() {
    double a = 0.;
    std::cout << "Введите число a:" << '\n';
    std::cin >> a;

    double sum = 1.;
    if (a >= 0) {
        const int kMinI = 2;
        const int kMaxI = 8;
        const int kStepI = 2;
        int i = kMinI;
        while (i <= kMaxI) {
            sum *= i * i;
            i += kStepI;
        }
        sum -= a;
    } else {
        const int kMinI = 3;
        const int kMaxI = 9;
        const int kStepI = 3;
        const int kTwo = 2;
        int i = kMinI;
        while (i <= kMaxI) {
            sum *= (i - kTwo);
            i += kStepI;
        }
    }
    std::cout << "Ответ на задачу: " << std::fixed << sum << '\n';
}

void taskThree() {
    const int kSetOutputNumberWidth = 11;
    const int kPrecisionForX = 1;
    const double kEpsilon = 1e-6;
    const double kCosPi4 = std::cos(M_PI / 4);
    const double kMinX = 0.;
    const double kMaxX = 1.;
    const double kStepX = 0.2;

    std::cout << std::setw(kSetOutputNumberWidth) << 'x';
    std::cout << std::setw(kSetOutputNumberWidth) << 'Y';
    std::cout << std::setw(kSetOutputNumberWidth) << 'S';
    std::cout << std::setw(kSetOutputNumberWidth) << 'N' << '\n';

    double x = kMinX;
    while (x <= kMaxX) {
        double Y = 1 + x * std::exp(x) * kCosPi4;

        double summand = kCosPi4 * x;
        double sum = 1 + kCosPi4 * x;
        int n = 1;
        while (std::fabs(summand) > kEpsilon) {
            summand *= x / n;
            sum += summand;
            ++n;
        }

        std::cout << std::setprecision(kPrecisionForX) << std::fixed << std::setw(kSetOutputNumberWidth) << x;
        std::cout << std::setprecision(kPrecision) << std::fixed << std::setw(kSetOutputNumberWidth) << Y;
        std::cout << std::fixed << std::setw(kSetOutputNumberWidth) << sum;
        std::cout << std::setw(kSetOutputNumberWidth) << n << std::endl;

        x += kStepX;
    }
}

void taskFour() {
    const int kIntermediateSumCaseOne = 3;
    const int kIntermediateSumCaseTwo = 5;
    const int kIntermediateSumCaseThree = 10;
    double y = .0;
    int n = 0;
    double x = .0;
    std::cout << "Введите числа n (n - натуральное число) и x (|x| < 1):" << '\n';
    std::cin >> n >> x;

    if (n <= 0 || std::fabs(x) > 1.) {
        std::cout << "Были введены неправильные данные." << '\n';
        return;
    }

    double summand = x;
    int i = 1;
    while (i <= n) {
        y += summand / i;
        summand = summand * x * (-1);
        if (i != n && (i == kIntermediateSumCaseOne || i == kIntermediateSumCaseTwo || i == kIntermediateSumCaseThree)) {
            std::cout << "Промежуточное значение суммы при n = " << i << ": " << std::setprecision(kPrecision) << y << '\n';
        }
        ++i;
    }
    std::cout << "Значение искомой суммы: " << std::fixed << std::setprecision(kPrecision) << y << "\n\n";
}

int main(int, char**) {
    char userTaskChoice = '0';
    char continueExecution = 'y';

    while (continueExecution == 'y' || continueExecution == 'Y') {
        std::cout << "Выберите задачу из списка и напишите её номер для выполнения:" << '\n';
        std::cout << "Задача №1 (сумма натуральных чисел на отрезке)" << '\n';
        std::cout << "Задача №2 (произведение чисел на заданном отрезке)" << '\n';
        std::cout << "Задача №3 (таблица значений для x)" << '\n';
        std::cout << "Задача №4 (вычисление y по формуле)" << '\n';

        std::cin >> userTaskChoice;

        std::cout << "Задача №" << userTaskChoice << '\n';
        switch (userTaskChoice) {
            case kTaskOne:
                taskOne();
                break;
            case kTaskTwo:
                taskTwo();
                break;
            case kTaskThree:
                taskThree();
                break;
            case kTaskFour:
                taskFour();
                break;
            default:
                std::cout << "Неправильный ввод" << '\n';
                break;
        }

        std::cout << "Продолжить работу? (y/n)" << '\n';
        std::cin >> continueExecution;
    }
    return 0;
}
