#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

namespace Dictionary {

enum class MenuOption : int {
    Exit = 0,
    AddWord = 1,
    RemoveWord = 2,
    EnglishToRussian = 3,
    RussianToEnglish = 4,
    ViewDictionary = 5,
    SaveToFile = 6,
    LoadFromFile = 7
};

struct DictionaryRecord {
    char* english;
    char* russian;
};

struct DictionaryData {
    DictionaryRecord* records;
    int capacity;
    int size;
};

[[nodiscard]] bool runApplication();
[[nodiscard]] MenuOption showMenu();
void handleMenuOption(MenuOption option, DictionaryData& dictionaryData);
[[nodiscard]] bool initializeDictionary(DictionaryData& dictionaryData, int initialCapacity);
void cleanupDictionary(DictionaryData& dictionaryData);
void addWord(DictionaryData& dictionaryData);
void removeWord(DictionaryData& dictionaryData);
void translateEnglishToRussian(const DictionaryData& dictionaryData);
void translateRussianToEnglish(const DictionaryData& dictionaryData);
void viewDictionary(const DictionaryData& dictionaryData);
void saveToFile(const DictionaryData& dictionaryData);
void loadFromFile(DictionaryData& dictionaryData);

}

#endif
