



#include <iostream>
#include <vector>
#include <algorithm> 
#include <ctime>    
#include <sstream>
#include <set>

void shuffle(int* array, int n) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  
    for (int i = n - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(array[i], array[j]);  
    }
}

class Code {
public:
    Code(const std::vector<int>& numbers) : numbers_(numbers) {}

    const std::vector<int>& getNumbers() const { return numbers_; }

    std::pair<int, int> compare(const Code& other) const {
        int hits = 0;
        int blows = 0;
        std::vector<int> this_counts(10, 0);
        std::vector<int> other_counts(10, 0);

        for (size_t i = 0; i < numbers_.size(); ++i) {
            if (numbers_[i] == other.numbers_[i]) {
                ++hits;
            }
            else {
                ++this_counts[numbers_[i]];
                ++other_counts[other.numbers_[i]];
            }
        }

        for (int i = 0; i < 10; ++i) {
            blows += std::min(this_counts[i], other_counts[i]);
        }

        return { hits, blows };
    }

private:
    std::vector<int> numbers_;
};

class Game {
public:
    Game() : secretCode(generateRandomCode(4)) {}

    void play() {
        printRules();
        while (true) {
            std::vector<int> guess = getPlayerGuess();
            Code guessCode(guess);
            auto result = secretCode.compare(guessCode);
            int hits = result.first;
            int blows = result.second;
            std::cout << "ヒット: " << hits << ", ブロー: " << blows << std::endl;
            if (hits == 4) {
                std::cout << "おめでとうございます！" << std::endl;
                break;
            }
        }
    }

private:
    Code secretCode;

    Code generateRandomCode(int length) {
        std::vector<int> numbers(10);
        for (int i = 0; i < 10; ++i) {
            numbers[i] = i;
        }
        shuffle(numbers.data(), numbers.size()); 
        std::vector<int> code(numbers.begin(), numbers.begin() + length);  
        return Code(code);
    }

    std::vector<int> getPlayerGuess() {
        std::vector<int> guess(4);
        std::cout << "数字を入力してください（例: 1 2 3 4）: ";

        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss(input);

        std::set<int> unique_numbers;
        for (int i = 0; i < 4; ++i) {
            int number;
            if (!(ss >> number) || number < 0 || number > 9 || !unique_numbers.insert(number).second) {
                std::cout << "※0から9の重複のない4桁の数字をスペースで区切って入力してください: ";
                return getPlayerGuess();
            }
            guess[i] = number;
        }

        if (ss >> input) {
            std::cout << "※正確に4桁の数字を入力してください: ";
            return getPlayerGuess();
        }

        return guess;
    }

    void printRules() const {
        std::cout << "HIT&BLOWのルール" << std::endl;
        std::cout << "ゲームの目的: プレイヤーがコンピュータがランダムに選んだ4桁の数字を正しく当てることを目指します。" << std::endl;
        std::cout << "ゲームの進行:" << std::endl;
        std::cout << "1. ゲーム開始時に、コンピュータがランダムに選んだ4桁の数字が設定されます。この数字の桁はすべて異なります。" << std::endl;
        std::cout << "2. プレイヤーは1回の入力で4つの数字をスペースで区切って入力します。例: 1 2 3 4" << std::endl;
        std::cout << "3. プレイヤーの入力した数字と正解の数字を比較し、以下の2つの情報が与えられます。：" << std::endl;
        std::cout << "   - ヒット (Hit): 位置と数字の両方が合っている数。" << std::endl;
        std::cout << "   - ブロー (Blow): 数字のみが合っている数。" << std::endl;
        std::cout << "4. プレイヤーが数字を当てた場合、ゲームは終了し、「おめでとうございます！」というメッセージが表示されます。" << std::endl;
        std::cout << "   - プレイヤーが正しい数字を当てるまで繰り返します。" << std::endl;
        std::cout << "入力のルール:" << std::endl;
        std::cout << "   - 各数字は0から9の範囲内でなければなりません。" << std::endl;
        std::cout << "   - 1行で4つの数字を入力してください。数字の間はスペースで区切ってください。" << std::endl;
        std::cout << "   - 数字は重複してはなりません。" << std::endl;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}

