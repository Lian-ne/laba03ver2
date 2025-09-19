#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

// Константы для проверки диапазонов
const int kMinHours = 0;
const int kMaxHours = 23;
const int kMinMinutes = 0;
const int kMaxMinutes = 59;

// Константы для времен
const int kMidnightHours = 0;
const int kMidnightMinutes = 0;
const int kNoonHours = 12;
const int kNoonMinutes = 0;

// Константы для времени суток
const int kMorningStart = 5;
const int kMorningEnd = 12;
const int kDayStart = 12;
const int kDayEnd = 18;
const int kEveningStart = 18;
const int kEveningEnd = 23;

// Константы для форматирования часов
const int kHoursModulo = 12;
const int kDisplayHoursMax = 12;

// Константы для склонения
const int kHourSingular = 1;
const int kHourPluralStart = 2;
const int kHourPluralEnd = 4;

// Константы для склонения минут
const int kMinuteModulo10 = 10;
const int kMinuteModulo100 = 100;
const int kMinuteSingular = 1;
const int kMinutePluralStart = 2;
const int kMinutePluralEnd = 4;
const int kTeenStart = 10;
const int kTeenEnd = 20;

// Константы для проверки ввода
const int kMaxInputLength = 10;

// ===== Вспомогательные функции работы со строками =====

bool IsValidNumber(const char* str) {
    if (str == nullptr) {
        return false;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-narrowing-conversions)
    const size_t length = std::strlen(str);
    if (length == 0) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }

    return true;
}

bool HasLeadingZero(const char* str) {
    if (str == nullptr) {
        return false;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-narrowing-conversions)
    const size_t length = std::strlen(str);
    if (length == 0) {
        return false;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return (length > 1 && str[0] == '0');
}

// ===== Вывод слов =====

void PrintHourWord(int hours) {
    if (hours == kHourSingular) {
        std::cout << " час";
    } else if (hours >= kHourPluralStart && hours <= kHourPluralEnd) {
        std::cout << " часа";
    } else {
        std::cout << " часов";
    }
}

void PrintMinuteWord(int minutes) {
    if ((minutes % kMinuteModulo100) >= kTeenStart && (minutes % kMinuteModulo100) < kTeenEnd) {
        std::cout << " минут";
    } else {
        int lastDigit = minutes % kMinuteModulo10;
        if (lastDigit == kMinuteSingular) {
            std::cout << " минута";
        } else if (lastDigit >= kMinutePluralStart && lastDigit <= kMinutePluralEnd) {
            std::cout << " минуты";
        } else {
            std::cout << " минут";
        }
    }
}

void PrintDayPart(int hours) {
    if (hours >= kMorningStart && hours < kMorningEnd) {
        std::cout << " утра";
    } else if (hours >= kDayStart && hours < kDayEnd) {
        std::cout << " дня";
    } else if (hours >= kEveningStart && hours <= kEveningEnd) {
        std::cout << " вечера";
    } else {
        std::cout << " ночи";
    }
}

// ===== Основная программа =====

int main() {
    char inputHours[kMaxInputLength];
    char inputMinutes[kMaxInputLength];

    std::cin >> inputHours >> inputMinutes;

    if (!IsValidNumber(inputHours) || !IsValidNumber(inputMinutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }

    if (HasLeadingZero(inputHours) || HasLeadingZero(inputMinutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }

    int hours = std::atoi(inputHours);
    int minutes = std::atoi(inputMinutes);

    if (hours < kMinHours || hours > kMaxHours || minutes < kMinMinutes || minutes > kMaxMinutes) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }

    if (hours == kMidnightHours && minutes == kMidnightMinutes) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    if (hours == kNoonHours && minutes == kNoonMinutes) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    int displayHours = hours % kHoursModulo;
    if (displayHours == 0) {
        displayHours = kDisplayHoursMax;
    }

    std::cout << displayHours;
    PrintHourWord(displayHours);

    if (minutes > 0) {
        std::cout << " " << minutes;
        PrintMinuteWord(minutes);
    }

    PrintDayPart(hours);
    std::cout << std::endl;

    return 0;
}
