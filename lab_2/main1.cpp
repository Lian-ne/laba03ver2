#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const double kEpsilon = 1e-6;
const double kStepX = 0.2;
const double kMinX = 0.0;
const double kMaxX = 1.0;
const int kPrecision = 6;
const int kPrecisionForX = 1;
const int kSetOutputNumberWidth = 11;
const double kCosPi4 = std::cos(M_PI / 4);
const int kOutputPrecision = 8;
}  // namespace

[[nodiscard]] int CalculateSumDivisibleByFiveNotByM(int n, int m);
[[nodiscard]] double CalculateProduct(double a);
void CalculateFunctionTable();
void CalculateSeries(double x, int n);

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    char continueChoice;  // NOLINT(cppcoreguidelines-init-variables)

    do {  // NOLINT(cppcoreguidelines-avoid-do-while)
        std::cout << "\n=== Лабораторная работа ===" << std::endl;
        std::cout << "1. Задача 1 - Сумма чисел, делящихся на 5 и не делящихся на m" << std::endl;
        std::cout << "2. Задача 2 - Вычисление произведения" << std::endl;
        std::cout << "3. Задача 3 - Таблица значений S(x) и Y(x)" << std::endl;
        std::cout << "4. Задача 4 - Вычисление ряда с промежуточными суммами" << std::endl;
        std::cout << "Выберите задание (1-4): ";

        int taskChoice;  // NOLINT(cppcoreguidelines-init-variables)
        std::cin >> taskChoice;

        switch (taskChoice) {
            case 1: {
                int nValue;  // NOLINT(cppcoreguidelines-init-variables)
                int mValue;  // NOLINT(cppcoreguidelines-init-variables)
                std::cout << "Введите n: ";
                std::cin >> nValue;
                std::cout << "Введите m (m < n): ";
                std::cin >> mValue;

                if (mValue >= nValue) {
                    std::cout << "Ошибка: m должно быть меньше n!" << std::endl;
                } else {
                    int result = CalculateSumDivisibleByFiveNotByM(nValue, mValue);
                    std::cout << "Сумма чисел: " << result << std::endl;
                }
                break;
            }

            case 2: {
                double aValue;  // NOLINT(cppcoreguidelines-init-variables)
                std::cout << "Введите a: ";
                std::cin >> aValue;

                double result = CalculateProduct(aValue);
                std::cout << "Результат: " << std::fixed << std::setprecision(kPrecision) << result << std::endl;
                break;
            }

            case 3:
                CalculateFunctionTable();
                break;

            case 4: {
                double xValue;  // NOLINT(cppcoreguidelines-init-variables)
                int nValue;     // NOLINT(cppcoreguidelines-init-variables)
                std::cout << "Введите x (|x| < 1): ";
                std::cin >> xValue;
                std::cout << "Введите n: ";
                std::cin >> nValue;

                if (std::fabs(xValue) >= 1.0) {
                    std::cout << "Ошибка: |x| должно быть меньше 1!" << std::endl;
                } else {
                    CalculateSeries(xValue, nValue);
                }
                break;
            }

            default:
                std::cout << "Неверный выбор!" << std::endl;
        }

        std::cout << "\nПродолжить работу? (y/n): ";
        std::cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    std::cout << "Программа завершена." << std::endl;
    return 0;
}

[[nodiscard]] int CalculateSumDivisibleByFiveNotByM(int n, int m) {
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % 5 == 0 && i % m != 0) {  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            sum += i;
        }
    }

    return sum;
}

[[nodiscard]] double CalculateProduct(double a) {
    double product = 1.0;

    if (a >= 0) {
        const int kMinI = 2;
        const int kMaxI = 8;
        const int kStepI = 2;

        for (int i = kMinI; i <= kMaxI; i += kStepI) {
            product *= i * i;
        }
        product -= a;
    } else {
        const int kMinI = 3;
        const int kMaxI = 9;
        const int kStepI = 3;
        const int kTwo = 2;

        for (int i = kMinI; i <= kMaxI; i += kStepI) {
            product *= (i - kTwo);
        }
    }

    return product;
}

void CalculateFunctionTable() {
    std::cout << std::setw(kSetOutputNumberWidth) << 'x';
    std::cout << std::setw(kSetOutputNumberWidth) << 'Y';
    std::cout << std::setw(kSetOutputNumberWidth) << 'S';
    std::cout << std::setw(kSetOutputNumberWidth) << 'N' << std::endl;

    double x = kMinX;
    while (x <= kMaxX) {
        // Вычисление Y(x) = 1 + x * exp(x) * cos(π/4)
        double yValue = 1.0 + x * std::exp(x) * kCosPi4;

        // Вычисление суммы ряда S(x)
        double summand = kCosPi4 * x;
        double sumValue = 1.0 + kCosPi4 * x;
        int n = 1;

        // Вычисление суммы пока очередной член больше погрешности
        while (std::fabs(summand) > kEpsilon) {
            summand *= x / n;
            sumValue += summand;
            ++n;
        }

        // Вывод результатов в таблицу
        std::cout << std::setprecision(kPrecisionForX) << std::fixed << std::setw(kSetOutputNumberWidth) << x;
        std::cout << std::setprecision(kPrecision) << std::fixed << std::setw(kSetOutputNumberWidth) << yValue;
        std::cout << std::fixed << std::setw(kSetOutputNumberWidth) << sumValue;
        std::cout << std::setw(kSetOutputNumberWidth) << n << std::endl;

        x += kStepX;
    }
}

void CalculateSeries(double x, int n) {
    double sum = 0.0;

    std::cout << "Промежуточные суммы:" << std::endl;

    for (int i = 1; i <= n; ++i) {
        double term = std::pow(-1, i - 1) * std::pow(x, i) / i;
        sum += term;

        if (i == 3 || i == 5 || i == 10) {  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            std::cout << "Сумма при " << i << " слагаемых: " << std::fixed << std::setprecision(kOutputPrecision) << sum << std::endl;
        }
    }

    std::cout << "Финальная сумма при " << n << " слагаемых: " << std::fixed << std::setprecision(kOutputPrecision) << sum << std::endl;
}
