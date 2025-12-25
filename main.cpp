#include <cstdio>

namespace {

const int kMaxTextLength = 1000;
const int kMaxWordLength = 100;

struct Word {
    char characters[kMaxWordLength];
    int length;
};

bool IsLowerLatin(char symbol) {
    return symbol >= 'a' && symbol <= 'z';
}

bool IsSpace(char symbol) {
    return symbol == ' ' || symbol == '\n' || symbol == '\t';
}

bool IsDot(char symbol) {
    return symbol == '.';
}

void ReadText(char* text) {
    char currentChar = '\0';
    int index = 0;

    while (!IsDot(currentChar)) {
        currentChar = static_cast<char>(getchar());

        if (index == 0 && IsSpace(currentChar)) {
            continue;
        }

        if (IsLowerLatin(currentChar) || IsSpace(currentChar) || IsDot(currentChar)) {
            if (index > 0 && IsSpace(text[index - 1]) && IsSpace(currentChar)) {
                continue;
            }

            text[index] = currentChar;
            ++index;
        }
    }

    text[index] = '\0';
}

int ExtractWords(const char* text, Word* words) {
    int wordCount = 0;
    int currentIndex = 0;

    while (text[currentIndex] != '\0') {
        if (IsLowerLatin(text[currentIndex])) {
            int wordLength = 0;

            while (IsLowerLatin(text[currentIndex])) {
                words[wordCount].characters[wordLength] = text[currentIndex];
                ++wordLength;
                ++currentIndex;
            }

            words[wordCount].length = wordLength;
            ++wordCount;
        } else {
            ++currentIndex;
        }
    }

    return wordCount;
}

void RemoveSubsequentFirstLetters(Word* word) {
    if (word->length <= 1) {
        return;
    }

    char firstLetter = word->characters[0];
    int writeIndex = 1;

    for (int readIndex = 1; readIndex < word->length; ++readIndex) {
        if (word->characters[readIndex] != firstLetter) {
            word->characters[writeIndex] = word->characters[readIndex];
            ++writeIndex;
        }
    }

    word->length = writeIndex;
}

bool AreWordsEqual(const Word& first, const Word& second) {
    if (first.length != second.length) {
        return false;
    }

    for (int i = 0; i < first.length; ++i) {
        if (first.characters[i] != second.characters[i]) {
            return false;
        }
    }

    return true;
}

void PrintWord(const Word& word) {
    for (int i = 0; i < word.length; ++i) {
        putchar(word.characters[i]);
    }
}

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    char text[kMaxTextLength] = {};
    Word words[kMaxTextLength] = {};

    ReadText(text);

    int wordCount = ExtractWords(text, words);

    if (wordCount == 0) {
        return 0;
    }

    const Word& lastWord = words[wordCount - 1];

    for (int i = 0; i < wordCount - 1; ++i) {
        if (!AreWordsEqual(words[i], lastWord)) {
            Word processedWord = words[i];
            RemoveSubsequentFirstLetters(&processedWord);
            PrintWord(processedWord);
            putchar(' ');
        }
    }

    putchar('\n');

    return 0;
}
