#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

int main() {
    std::string input_hours, input_minutes;
    
    std::cin >> input_hours >> input_minutes;
    
    // Проверяем, что ввод состоит только из цифр
    for (char c : input_hours) {
        if (!std::isdigit(c)) {
            std::cout << "введены недопустимые данные" << std::endl;
            return 1;
        }
    }
    for (char c : input_minutes) {
        if (!std::isdigit(c)) {
            std::cout << "введены недопустимые данные" << std::endl;
            return 1;
        }
    }
    
    // Проверяем на ведущие нули (если число не "0")
    if (input_hours.size() > 2 && input_hours[0] == '0') {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }
    if (input_minutes.size() > 2 && input_minutes[0] == '0') {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }
    
    
    int hours = std::stoi(input_hours); // Преобразуем в числа
    int minutes = std::stoi(input_minutes); // Преобразуем в числа
    
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }
    
    if (hours == 0 && minutes == 0) {
        std::cout << "полночь" << std::endl;
        return 0;
    }
    if (hours == 12 && minutes == 0) {
        std::cout << "полдень" << std::endl;
        return 0;
    }
    
    std::string time_of_day;
    if (hours >= 5 && hours < 12) time_of_day = "утра";
    else if (hours >= 12 && hours < 18) time_of_day = "дня"; 
    else if (hours >= 18 && hours <= 23) time_of_day = "вечера";
    else if (hours >= 0 && hours < 5) time_of_day = "ночи";
    
    int display_hours = hours % 12;
    if (display_hours == 0) display_hours = 12;
    
    std::string hour_form;
    if (display_hours == 1) hour_form = "час";
    else if (display_hours >= 2 && display_hours <= 4) hour_form = "часа";
    else hour_form = "часов";
    
    std::string minute_form;
    if (minutes % 10 == 1 && minutes % 100 != 11) minute_form = "минута";
    else if (minutes % 10 >= 2 && minutes % 10 <= 4 && 
             (minutes % 100 < 10 || minutes % 100 >= 20)) {
        minute_form = "минуты";
    }
    else minute_form = "минут";
    
    std::cout << display_hours << " " << hour_form << " ";
    if (minutes > 0) {
        std::cout << minutes << " " << minute_form << " ";
    }
    std::cout << time_of_day;
    
    if (minutes == 0) {
        std::cout << " ровно";
    }
    
    std::cout << std::endl;
    
    return 0;
}