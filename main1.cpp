#include <iostream>

int main() {
  // Константы для проверки диапазонов
  const int kMinHours = 0;
  const int kMaxHours = 23;
  const int kMinMinutes = 0;
  const int kMaxMinutes = 59;

  // Константы для времен
  const int kMidNightHours = 0;
  const int kMidNightMinutes = 0;
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
  const int kException11 = 11;

  // Константы для проверки ввода
  const int kMaxInputLength = 10;
  const int kMaxDigitsForTime = 2;

  char input_hours[kMaxInputLength];
  char input_minutes[kMaxInputLength];

  std::cin >> input_hours >> input_minutes;

  // Проверяем, что ввод состоит только из цифр
  for (int i = 0; input_hours[i] != '\0'; i++) {
    if (!std::isdigit(input_hours[i])) {
      std::cout << "введены недопустимые данные" << std::endl;
      return 1;
    }
  }
  for (int i = 0; input_minutes[i] != '\0'; i++) {
    if (!std::isdigit(input_minutes[i])) {
      std::cout << "введены недопустимые данные" << std::endl;
      return 1;
    }
  }

  // Проверяем на ведущие нули
  int hours_len = 0;
  while (input_hours[hours_len] != '\0') {
    hours_len++;
  }

  int minutes_len = 0;
  while (input_minutes[minutes_len] != '\0') {
    minutes_len++;
  }

  if (hours_len > kMaxDigitsForTime && input_hours[0] == '0') {
    std::cout << "введены недопустимые данные" << std::endl;
    return 1;
  }
  if (minutes_len > kMaxDigitsForTime && input_minutes[0] == '0') {
    std::cout << "введены недопустимые данные" << std::endl;
    return 1;
  }

  int hours = std::atoi(input_hours);
  int minutes = std::atoi(input_minutes);

  if (hours < kMinHours || hours > kMaxHours || minutes < kMinMinutes ||
      minutes > kMaxMinutes) {
    std::cout << "введены недопустимые данные" << std::endl;
    return 1;
  }

  if (hours == kMidNightHours && minutes == kMidNightMinutes) {
    std::cout << "полночь" << std::endl;
    return 0;
  }
  if (hours == kNoonHours && minutes == kNoonMinutes) {
    std::cout << "полдень" << std::endl;
    return 0;
  }

  const char *time_of_day;
  if (hours >= kMorningStart && hours < kMorningEnd) {
    time_of_day = "утра";
  } else if (hours >= kDayStart && hours < kDayEnd) {
    time_of_day = "дня";
  } else if (hours >= kEveningStart && hours <= kEveningEnd) {
    time_of_day = "вечера";
  } else {
    time_of_day = "ночи";
  }

  int display_hours = hours % kHoursModulo;
  if (display_hours == 0) {
    display_hours = kDisplayHoursMax;
  }

  const char *hour_form;
  if (display_hours == kHourSingular) {
    hour_form = "час";
  } else if (display_hours >= kHourPluralStart &&
             display_hours <= kHourPluralEnd) {
    hour_form = "часа";
  } else {
    hour_form = "часов";
  }

  const char *minute_form;
  if (minutes % kMinuteModulo10 == kMinuteSingular &&
      minutes % kMinuteModulo100 != kException11) {
    minute_form = "минута";
  } else if (minutes % kMinuteModulo10 >= kMinutePluralStart &&
             minutes % kMinuteModulo10 <= kMinutePluralEnd &&
             (minutes % kMinuteModulo100 < kTeenStart ||
              minutes % kMinuteModulo100 >= kTeenEnd)) {
    minute_form = "минуты";
  } else {
    minute_form = "минут";
  }

  if (hours == kMidNightHours && minutes > kMinMinutes) {
    std::cout << "0 часов " << minutes << " " << minute_form << " ночи";
  } else {
    std::cout << display_hours << " " << hour_form << " ";
    if (minutes > kMinMinutes) {
      std::cout << minutes << " " << minute_form << " ";
    }
    std::cout << time_of_day;
  }

  if (minutes == kMinMinutes) {
    std::cout << " ровно";
  }

  std::cout << std::endl;

  return 0;
}