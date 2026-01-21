#include "Dictionary.hpp"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {

const int kInitialCapacity = 10;
const int kInputBufferSize = 256;
const int kMaxLineLength = 100;

[[nodiscard]] char* copyString(const char* source) {
    if (!source) {
        return nullptr;
    }

    const std::size_t length = std::strlen(source);
    char* destination = new char[length + 1];
    std::strcpy(destination, source);
    return destination;
}

[[nodiscard]] bool compareStrings(const char* str1, const char* str2) {
    if (!str1 || !str2) {
        return false;
    }
    return std::strcmp(str1, str2) == 0;
}

void safeDeleteString(char*& str) {
    delete[] str;
    str = nullptr;
}

void printRecord(const Dictionary::DictionaryRecord& record) {
    if (record.english && record.russian) {
        std::cout << record.english << " - " << record.russian << '\n';
    }
}

[[nodiscard]] int binarySearch(const Dictionary::DictionaryRecord* records, int size, const char* englishWord) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        const int mid = left + (right - left) / 2;
        const int comparison = std::strcmp(records[mid].english, englishWord);

        if (comparison == 0) {
            return mid;
        } else if (comparison < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void bubbleSort(Dictionary::DictionaryRecord* records, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (std::strcmp(records[j].english, records[j + 1].english) > 0) {
                Dictionary::DictionaryRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

[[nodiscard]] bool ensureCapacity(Dictionary::DictionaryData& dictionaryData, int requiredCapacity) {
    if (dictionaryData.capacity >= requiredCapacity) {
        return true;
    }

    int newCapacity = dictionaryData.capacity * 2;
    if (requiredCapacity > newCapacity) {
        newCapacity = requiredCapacity;
    }

    auto* newRecords = new Dictionary::DictionaryRecord[newCapacity];

    if (!newRecords) {
        return false;
    }

    for (int i = 0; i < dictionaryData.size; ++i) {
        newRecords[i] = dictionaryData.records[i];
    }

    delete[] dictionaryData.records;
    dictionaryData.records = newRecords;
    dictionaryData.capacity = newCapacity;
    return true;
}

void inputWord(const char* prompt, char* buffer) {
    std::cout << prompt;
    std::cin.getline(buffer, kInputBufferSize);
}

void trimNewline(char* str) {
    if (!str) {
        return;
    }

    const std::size_t length = std::strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

}  // namespace

namespace Dictionary {

[[nodiscard]] bool runApplication() {
    DictionaryData dictionaryData = {};

    if (!initializeDictionary(dictionaryData, kInitialCapacity)) {
        std::cout << "Ошибка: Не удалось инициализировать словарь\n";
        return false;
    }

    bool continueRunning = true;
    while (continueRunning) {
        const MenuOption option = showMenu();

        if (option == MenuOption::Exit) {
            continueRunning = false;
        } else {
            handleMenuOption(option, dictionaryData);
        }
    }

    cleanupDictionary(dictionaryData);
    return true;
}

[[nodiscard]] MenuOption showMenu() {
    std::cout << "\n=== Англо-русский словарь ===\n";
    std::cout << static_cast<int>(MenuOption::AddWord) << ". Добавить слово\n";
    std::cout << static_cast<int>(MenuOption::RemoveWord) << ". Удалить слово\n";
    std::cout << static_cast<int>(MenuOption::EnglishToRussian) << ". Перевод с английского на русский\n";
    std::cout << static_cast<int>(MenuOption::RussianToEnglish) << ". Перевод с русского на английский\n";
    std::cout << static_cast<int>(MenuOption::ViewDictionary) << ". Просмотреть словарь\n";
    std::cout << static_cast<int>(MenuOption::SaveToFile) << ". Сохранить словарь в файл\n";
    std::cout << static_cast<int>(MenuOption::LoadFromFile) << ". Загрузить словарь из файла\n";  // Новый пункт
    std::cout << static_cast<int>(MenuOption::Exit) << ". Выход\n";
    std::cout << "Выберите действие: ";

    int choice = 0;
    std::cin >> choice;
    std::cin.ignore();

    if (choice < static_cast<int>(MenuOption::Exit) || choice > static_cast<int>(MenuOption::LoadFromFile)) {
        std::cout << "Неверный выбор. Попробуйте снова.\n";
        return MenuOption::Exit;
    }

    return static_cast<MenuOption>(choice);
}

void handleMenuOption(MenuOption option, DictionaryData& dictionaryData) {
    switch (option) {
        case MenuOption::AddWord:
            addWord(dictionaryData);
            break;
        case MenuOption::RemoveWord:
            removeWord(dictionaryData);
            break;
        case MenuOption::EnglishToRussian:
            translateEnglishToRussian(dictionaryData);
            break;
        case MenuOption::RussianToEnglish:
            translateRussianToEnglish(dictionaryData);
            break;
        case MenuOption::ViewDictionary:
            viewDictionary(dictionaryData);
            break;
        case MenuOption::SaveToFile:
            saveToFile(dictionaryData);
            break;
        case MenuOption::LoadFromFile:
            loadFromFile(dictionaryData);
            break;
        case MenuOption::Exit:
            break;
    }
}

[[nodiscard]] bool initializeDictionary(DictionaryData& dictionaryData, int initialCapacity) {
    dictionaryData.records = new DictionaryRecord[initialCapacity];
    if (!dictionaryData.records) {
        return false;
    }

    dictionaryData.capacity = initialCapacity;
    dictionaryData.size = 0;

    const char* defaultEnglish[] = {"apple", "book", "cat", "dog", "house", "sun", "water", "tree", "car", "friend"};

    const char* defaultRussian[] = {"yabloko", "kniga", "kot", "sobaka", "dom", "solntse", "voda", "derevo", "mashina", "drug"};

    for (int i = 0; i < 10; ++i) {
        dictionaryData.records[i].english = copyString(defaultEnglish[i]);
        dictionaryData.records[i].russian = copyString(defaultRussian[i]);

        if (!dictionaryData.records[i].english || !dictionaryData.records[i].russian) {
            cleanupDictionary(dictionaryData);
            return false;
        }

        ++dictionaryData.size;
    }

    bubbleSort(dictionaryData.records, dictionaryData.size);
    return true;
}

void cleanupDictionary(DictionaryData& dictionaryData) {
    if (dictionaryData.records) {
        for (int i = 0; i < dictionaryData.size; ++i) {
            safeDeleteString(dictionaryData.records[i].english);
            safeDeleteString(dictionaryData.records[i].russian);
        }
        delete[] dictionaryData.records;
        dictionaryData.records = nullptr;
    }

    dictionaryData.capacity = 0;
    dictionaryData.size = 0;
}

void addWord(DictionaryData& dictionaryData) {
    if (!ensureCapacity(dictionaryData, dictionaryData.size + 1)) {
        std::cout << "Ошибка: Не удалось выделить память\n";
        return;
    }

    char englishBuffer[kInputBufferSize] = {};
    char russianBuffer[kInputBufferSize] = {};

    inputWord("Введите английское слово: ", englishBuffer);
    inputWord("Введите русский перевод (латинскими буквами): ", russianBuffer);

    for (int i = 0; i < dictionaryData.size; ++i) {
        if (compareStrings(dictionaryData.records[i].english, englishBuffer)) {
            std::cout << "Ошибка: Слово уже существует в словаре\n";
            return;
        }
    }

    dictionaryData.records[dictionaryData.size].english = copyString(englishBuffer);
    dictionaryData.records[dictionaryData.size].russian = copyString(russianBuffer);

    if (!dictionaryData.records[dictionaryData.size].english || !dictionaryData.records[dictionaryData.size].russian) {
        std::cout << "Ошибка: Не удалось выделить память для нового слова\n";
        safeDeleteString(dictionaryData.records[dictionaryData.size].english);
        safeDeleteString(dictionaryData.records[dictionaryData.size].russian);
        return;
    }

    ++dictionaryData.size;
    bubbleSort(dictionaryData.records, dictionaryData.size);
    std::cout << "Слово успешно добавлено\n";
}

void removeWord(DictionaryData& dictionaryData) {
    if (dictionaryData.size == 0) {
        std::cout << "Словарь пуст\n";
        return;
    }

    char englishBuffer[kInputBufferSize] = {};
    inputWord("Введите английское слово для удаления: ", englishBuffer);

    const int index = binarySearch(dictionaryData.records, dictionaryData.size, englishBuffer);

    if (index == -1) {
        std::cout << "Слово не найдено в словаре\n";
        return;
    }

    safeDeleteString(dictionaryData.records[index].english);
    safeDeleteString(dictionaryData.records[index].russian);

    for (int i = index; i < dictionaryData.size - 1; ++i) {
        dictionaryData.records[i] = dictionaryData.records[i + 1];
    }

    --dictionaryData.size;
    std::cout << "Слово успешно удалено\n";
}

void translateEnglishToRussian(const DictionaryData& dictionaryData) {
    if (dictionaryData.size == 0) {
        std::cout << "Словарь пуст\n";
        return;
    }

    char englishBuffer[kInputBufferSize] = {};
    inputWord("Введите английское слово: ", englishBuffer);

    const int index = binarySearch(dictionaryData.records, dictionaryData.size, englishBuffer);

    if (index == -1) {
        std::cout << "Перевод не найден\n";
    } else {
        std::cout << "Перевод: " << dictionaryData.records[index].russian << '\n';
    }
}

void translateRussianToEnglish(const DictionaryData& dictionaryData) {
    if (dictionaryData.size == 0) {
        std::cout << "Словарь пуст\n";
        return;
    }

    char russianBuffer[kInputBufferSize] = {};
    inputWord("Введите русское слово (латинскими буквами): ", russianBuffer);

    bool found = false;
    for (int i = 0; i < dictionaryData.size; ++i) {
        if (compareStrings(dictionaryData.records[i].russian, russianBuffer)) {
            std::cout << "Перевод: " << dictionaryData.records[i].english << '\n';
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Перевод не найден\n";
    }
}

void viewDictionary(const DictionaryData& dictionaryData) {
    if (dictionaryData.size == 0) {
        std::cout << "Словарь пуст\n";
        return;
    }

    std::cout << "\n=== Словарь (" << dictionaryData.size << " слов) ===\n";
    for (int i = 0; i < dictionaryData.size; ++i) {
        std::cout << i + 1 << ". ";
        printRecord(dictionaryData.records[i]);
    }
}

void saveToFile(const DictionaryData& dictionaryData) {
    std::ofstream file("dictionary.txt");

    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл для записи\n";
        return;
    }

    for (int i = 0; i < dictionaryData.size; ++i) {
        if (dictionaryData.records[i].english && dictionaryData.records[i].russian) {
            file << dictionaryData.records[i].english << '\n';
            file << dictionaryData.records[i].russian << '\n';
        }
    }

    file.close();
    std::cout << "Словарь сохранен в файл 'dictionary.txt'\n";
}

void loadFromFile(DictionaryData& dictionaryData) {
    char filename[kInputBufferSize] = {};
    inputWord("Введите имя файла для загрузки (по умолчанию: dictionary.txt): ", filename);

    if (filename[0] == '\0') {
        std::strcpy(filename, "dictionary.txt");
    }

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл '" << filename << "' для чтения\n";
        return;
    }

    char englishBuffer[kMaxLineLength] = {};
    char russianBuffer[kMaxLineLength] = {};
    int wordsLoaded = 0;

    cleanupDictionary(dictionaryData);

    dictionaryData.records = new DictionaryRecord[kInitialCapacity];
    if (!dictionaryData.records) {
        std::cout << "Ошибка: Не удалось выделить память для словаря\n";
        file.close();
        return;
    }
    dictionaryData.capacity = kInitialCapacity;
    dictionaryData.size = 0;

    while (file.getline(englishBuffer, kMaxLineLength)) {
        trimNewline(englishBuffer);

        if (englishBuffer[0] == '\0') {
            continue;
        }

        if (!file.getline(russianBuffer, kMaxLineLength)) {
            std::cout << "Предупреждение: Неполная пара слов в файле\n";
            break;
        }
        trimNewline(russianBuffer);

        if (!ensureCapacity(dictionaryData, dictionaryData.size + 1)) {
            std::cout << "Ошибка: Не удалось выделить память для новых слов\n";
            break;
        }

        dictionaryData.records[dictionaryData.size].english = copyString(englishBuffer);
        dictionaryData.records[dictionaryData.size].russian = copyString(russianBuffer);

        if (!dictionaryData.records[dictionaryData.size].english || !dictionaryData.records[dictionaryData.size].russian) {
            std::cout << "Ошибка: Не удалось выделить память для слова\n";
            safeDeleteString(dictionaryData.records[dictionaryData.size].english);
            safeDeleteString(dictionaryData.records[dictionaryData.size].russian);
            continue;
        }

        ++dictionaryData.size;
        ++wordsLoaded;

        englishBuffer[0] = '\0';
        russianBuffer[0] = '\0';
    }

    file.close();

    if (dictionaryData.size > 0) {
        bubbleSort(dictionaryData.records, dictionaryData.size);
        std::cout << "Успешно загружено " << wordsLoaded << " слов из файла '" << filename << "'\n";
    } else {
        std::cout << "Файл '" << filename << "' пуст или не содержит корректных данных\n";

        const bool initSuccess = initializeDictionary(dictionaryData, kInitialCapacity);
        if (!initSuccess) {
            std::cout << "Ошибка: Не удалось инициализировать словарь значениями по умолчанию\n";
            return;
        }
        std::cout << "Словарь инициализирован значениями по умолчанию\n";
    }
}

}  // namespace Dictionary
