#include "Dictionary.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    const bool success = Dictionary::runApplication();

    if (!success) {
        return 1;
    }

    return 0;
}
