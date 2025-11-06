namespace TrigonometricEquationSolver {
enum class MethodOptions {
    IterationMethod = 1,
    NewtonsMethod = 2,
    BisectionMethod = 3,
};

struct MethodResult {
    double x;
    int iterationsCount;
    bool isRoot = true;
    bool isMaxIterationsError = true;
};

void StartApp();

void PrintMenu();

void RunNewtonsMethod();
void RundBisectionMethod();
void RunIterationMethod();

[[nodiscard]] MethodResult CalculateIterationMethod(double epsilon, double coefficient);
[[nodiscard]] MethodResult CalculateNewtonsMethod(double initialApproximation, double epsilon, double coefficient);
[[nodiscard]] MethodResult CalculateBisectionMethod(double leftBoundary, double rightBoundary, double epsilon, double coefficient);
}  // namespace TrigonometricEquationSolver
