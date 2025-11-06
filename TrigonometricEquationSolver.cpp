#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kmaxIterations = 1e8 - 1;

struct MethodResult {
    double x;
    int iterationsCount;
    bool isRoot = true;
    bool isMaxIterationsError = true;
};

struct InputData {
    double epsilon;
    double coefficient;  // Для первого уравнения
};

void PrintResult(MethodResult result, int precision) {
    std::cout << std::endl << "Приближённое значение корня уравнения: " << std::fixed << std::setprecision(precision) << result.x << std::endl;
    std::cout << "Количество итераций: " << result.iterationsCount << std::endl << std::endl;
}

// Функции для первого уравнения: x - k*cos(x) = 0
[[nodiscard]] double CalculateIterationMethodX(double coefficient, double x) {
    return coefficient * std::cos(x);
}

[[nodiscard]] double CalculateRootFirstEquation(double x, double coefficient) {
    return (x - coefficient * std::cos(x));
}

[[nodiscard]] double CalculateDerivativeFirstEquation(double x, double coefficient) {
    return 1.0 + coefficient * std::sin(x);
}

// Функции для второго уравнения: x - ln(x) - 2 = 0
[[nodiscard]] double CalculateIterationMethodXSecondEquation(double x) {
    return std::log(x) + 2;  // x = ln(x) + 2
}

[[nodiscard]] double CalculateRootSecondEquation(double x) {
    return (x - std::log(x) - 2);
}

[[nodiscard]] double CalculateDerivativeSecondEquation(double x) {
    return 1.0 - 1.0 / x;  // Производная: 1 - 1/x
}

InputData BasicDataEntry() {
    double epsilon{};
    double coefficient{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Введите коэффициент уравнения при cos(x): ";
    std::cin >> coefficient;

    InputData result = {epsilon, coefficient};

    return result;
}

}  // namespace

namespace TrigonometricEquationSolver {

enum class EquationType {
    FirstEquation = 1,  // x - k*cos(x) = 0
    SecondEquation = 2  // x - ln(x) - 2 = 0
};

enum class MethodOptions {
    IterationMethod = 1,
    NewtonsMethod = 2,
    BisectionMethod = 3,
};

// МЕТОДЫ ДЛЯ ПЕРВОГО УРАВНЕНИЯ: x - k*cos(x) = 0

[[nodiscard]] MethodResult CalculateIterationMethodFirstEquation(double epsilon, double coefficient) {
    double x = 0.0;
    int iterationsCount = 0;

    while (std::abs(coefficient * std::cos(x) - x) >= epsilon && iterationsCount < kmaxIterations) {
        x = CalculateIterationMethodX(coefficient, x);
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateNewtonsMethodFirstEquation(double initialApproximation, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double x = initialApproximation;
    double f{};
    double derivativeF{};

    while (std::abs(CalculateRootFirstEquation(x, coefficient)) >= epsilon && iterationsCount < kmaxIterations) {
        f = CalculateRootFirstEquation(x, coefficient);
        derivativeF = CalculateDerivativeFirstEquation(x, coefficient);  // Используем аналитическую производную
        x = x - f / derivativeF;
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateBisectionMethodFirstEquation(double leftBoundary, double rightBoundary, double epsilon, double coefficient) {
    int iterationsCount = 0;
    double middleValue = 0.0;
    double calculatedMiddleValue = 0.0;
    double calculatedRightBoundary = 0.0;

    if (CalculateRootFirstEquation(leftBoundary, coefficient) * CalculateRootFirstEquation(rightBoundary, coefficient) > 0) {
        return {middleValue, iterationsCount, false, false};
    }
    if (leftBoundary > rightBoundary) {
        return {middleValue, iterationsCount, false};
    }

    while (std::abs(rightBoundary - leftBoundary) > epsilon && iterationsCount < kmaxIterations) {
        calculatedRightBoundary = CalculateRootFirstEquation(rightBoundary, coefficient);
        middleValue = (leftBoundary + rightBoundary) / 2;
        calculatedMiddleValue = CalculateRootFirstEquation(middleValue, coefficient);

        if (calculatedMiddleValue < 0 && calculatedRightBoundary > 0) {
            leftBoundary = middleValue;
        } else {
            rightBoundary = middleValue;
        }
        ++iterationsCount;
    }

    MethodResult result = {middleValue, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

// МЕТОДЫ ДЛЯ ВТОРОГО УРАВНЕНИЯ: x - ln(x) - 2 = 0

[[nodiscard]] MethodResult CalculateIterationMethodSecondEquation(double epsilon) {
    // Используем начальное приближение 3.2 (из условия)
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
    double x = 3.2;
    int iterationsCount = 0;

    while (std::abs(CalculateIterationMethodXSecondEquation(x) - x) >= epsilon && iterationsCount < kmaxIterations) {
        x = CalculateIterationMethodXSecondEquation(x);
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateNewtonsMethodSecondEquation(double initialApproximation, double epsilon) {
    int iterationsCount = 0;
    double x = initialApproximation;
    double f{};
    double derivativeF{};

    while (std::abs(CalculateRootSecondEquation(x)) >= epsilon && iterationsCount < kmaxIterations) {
        f = CalculateRootSecondEquation(x);
        derivativeF = CalculateDerivativeSecondEquation(x);  // Используем аналитическую производную
        x = x - f / derivativeF;
        ++iterationsCount;
    }

    MethodResult result = {x, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

[[nodiscard]] MethodResult CalculateBisectionMethodSecondEquation(double leftBoundary, double rightBoundary, double epsilon) {
    int iterationsCount = 0;
    double middleValue = 0.0;
    double calculatedMiddleValue = 0.0;
    double calculatedRightBoundary = 0.0;

    if (CalculateRootSecondEquation(leftBoundary) * CalculateRootSecondEquation(rightBoundary) > 0) {
        return {middleValue, iterationsCount, false, false};
    }
    if (leftBoundary > rightBoundary) {
        return {middleValue, iterationsCount, false};
    }

    while (std::abs(rightBoundary - leftBoundary) > epsilon && iterationsCount < kmaxIterations) {
        calculatedRightBoundary = CalculateRootSecondEquation(rightBoundary);
        middleValue = (leftBoundary + rightBoundary) / 2;
        calculatedMiddleValue = CalculateRootSecondEquation(middleValue);

        if (calculatedMiddleValue < 0 && calculatedRightBoundary > 0) {
            leftBoundary = middleValue;
        } else {
            rightBoundary = middleValue;
        }
        ++iterationsCount;
    }

    MethodResult result = {middleValue, iterationsCount};

    if (iterationsCount == kmaxIterations) {
        result.isRoot = false;
    }

    return result;
}

// ФУНКЦИИ ЗАПУСКА ДЛЯ ПЕРВОГО УРАВНЕНИЯ

void RunNewtonsMethodFirstEquation() {
    double initialApproximation = {};

    InputData result = BasicDataEntry();

    std::cout << "Введите начальное приближение для поиска корня уравнения: ";
    std::cin >> initialApproximation;

    MethodResult NewtonsMethodResult = CalculateNewtonsMethodFirstEquation(initialApproximation, result.epsilon, result.coefficient);

    if (!NewtonsMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой коэффициент перед cos(x) или другое начальное приближение: " << std::endl;
    } else {
        PrintResult(NewtonsMethodResult, static_cast<int>(std::abs(log10(result.epsilon))));
    }
}

void RunBisectionMethodFirstEquation() {
    double leftBoundary{};
    double rightBoundary{};

    InputData result = BasicDataEntry();

    std::cout << "Введите начало диапазона: ";
    std::cin >> leftBoundary;
    std::cout << "Введите конец диапазона: ";
    std::cin >> rightBoundary;

    MethodResult BisectionMethodResult = CalculateBisectionMethodFirstEquation(leftBoundary, rightBoundary, result.epsilon, result.coefficient);

    if (!BisectionMethodResult.isMaxIterationsError) {
        std::cout << std::endl << "В заданном диапазоне не существует корней" << std::endl;
    } else if (!BisectionMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой диапазон, погрешность или коэффициент при cos(x)" << std::endl;
    } else {
        PrintResult(BisectionMethodResult, static_cast<int>(std::abs(log10(result.epsilon))));
    }
}

void RunIterationMethodFirstEquation() {
    InputData result = BasicDataEntry();

    MethodResult IterationMethodResult = CalculateIterationMethodFirstEquation(result.epsilon, result.coefficient);

    if (!IterationMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой коэффициент при cos(x) или другую погрешность" << std::endl;
    } else {
        PrintResult(IterationMethodResult, static_cast<int>(std::abs(log10(result.epsilon))));
    }
}

// ФУНКЦИИ ЗАПУСКА ДЛЯ ВТОРОГО УРАВНЕНИЯ

void RunNewtonsMethodSecondEquation() {
    double initialApproximation = {};
    double epsilon{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;

    std::cout << "Рекомендуемые начальные приближения: 0.15 или 3.2" << std::endl;
    std::cout << "Введите начальное приближение: ";
    std::cin >> initialApproximation;

    MethodResult NewtonsMethodResult = CalculateNewtonsMethodSecondEquation(initialApproximation, epsilon);

    if (!NewtonsMethodResult.isRoot) {
        std::cout << std::endl << "Введите другое начальное приближение" << std::endl;
    } else {
        PrintResult(NewtonsMethodResult, static_cast<int>(std::abs(log10(epsilon))));
    }
}

void RunBisectionMethodSecondEquation() {
    double leftBoundary{};
    double rightBoundary{};
    double epsilon{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;
    std::cout << "Рекомендуемый диапазон: [0.1, 4.0]" << std::endl;
    std::cout << "Введите начало диапазона: ";
    std::cin >> leftBoundary;
    std::cout << "Введите конец диапазона: ";
    std::cin >> rightBoundary;

    MethodResult BisectionMethodResult = CalculateBisectionMethodSecondEquation(leftBoundary, rightBoundary, epsilon);

    if (!BisectionMethodResult.isMaxIterationsError) {
        std::cout << std::endl << "В заданном диапазоне не существует корней" << std::endl;
    } else if (!BisectionMethodResult.isRoot) {
        std::cout << std::endl << "Введите другой диапазон или погрешность" << std::endl;
    } else {
        PrintResult(BisectionMethodResult, static_cast<int>(std::abs(log10(epsilon))));
    }
}

void RunIterationMethodSecondEquation() {
    double epsilon{};

    std::cout << "Введите погрешность нахождения корня: ";
    std::cin >> epsilon;

    MethodResult IterationMethodResult = CalculateIterationMethodSecondEquation(epsilon);

    if (!IterationMethodResult.isRoot) {
        std::cout << std::endl << "Метод не сошелся. Попробуйте другую погрешность." << std::endl;
    } else {
        PrintResult(IterationMethodResult, static_cast<int>(std::abs(log10(epsilon))));
    }
}

// ОСНОВНОЕ МЕНЮ И УПРАВЛЕНИЕ

void PrintEquationMenu() {
    std::cout << "\n=== ВЫБОР УРАВНЕНИЯ ===" << std::endl;
    std::cout << "1 - x - k*cos(x) = 0" << std::endl;
    std::cout << "2 - x - ln(x) - 2 = 0" << std::endl;
    std::cout << "Выберите уравнение: ";
}

void PrintMethodMenu() {
    std::cout << "\n=== ВЫБОР МЕТОДА ===" << std::endl;
    std::cout << "1 - Метод простых итераций" << std::endl;
    std::cout << "2 - Метод Ньютона" << std::endl;
    std::cout << "3 - Метод половинного деления" << std::endl;
    std::cout << "Введите номер метода: ";
}

void SolveEquation(EquationType equationType) {
    PrintMethodMenu();

    int method{};
    std::cin >> method;

    switch (static_cast<MethodOptions>(method)) {
        case MethodOptions::IterationMethod:
            if (equationType == EquationType::FirstEquation) {
                RunIterationMethodFirstEquation();
            } else {
                RunIterationMethodSecondEquation();
            }
            break;
        case MethodOptions::NewtonsMethod:
            if (equationType == EquationType::FirstEquation) {
                RunNewtonsMethodFirstEquation();
            } else {
                RunNewtonsMethodSecondEquation();
            }
            break;
        case MethodOptions::BisectionMethod:
            if (equationType == EquationType::FirstEquation) {
                RunBisectionMethodFirstEquation();
            } else {
                RunBisectionMethodSecondEquation();
            }
            break;
        default:
            std::cout << "Введён несуществующий номер метода" << std::endl;
            break;
    }
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        PrintEquationMenu();

        int equation{};
        std::cin >> equation;

        switch (static_cast<EquationType>(equation)) {
            case EquationType::FirstEquation:
                std::cout << "\nРешение уравнения: x - k*cos(x) = 0" << std::endl;
                SolveEquation(EquationType::FirstEquation);
                break;
            case EquationType::SecondEquation:
                std::cout << "\nРешение уравнения: x - ln(x) - 2 = 0" << std::endl;
                SolveEquation(EquationType::SecondEquation);
                break;
            default:
                std::cout << "Введён несуществующий номер уравнения" << std::endl;
                break;
        }

        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): ";
        std::cin >> continueExecution;
    }
}
}  // namespace TrigonometricEquationSolver
