#include <iostream>
#include <random>
#include <windows.h>

bool gameFlag = true;

int askBid(float& money);
int cardToPoint(char card);
bool drawCardDealer(std::string& dCards, int& dPoints, int pPoints);
void drawCardPlayer(std::string& pCards, int& pPoints);
void gameLoop(float& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards);
void gameLose(int why, float money);
char getRandomCard();
bool isAceInCards(std::string& cards);
void newGame(float& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards);
bool selectOption();
void writeCards(std::string dCards, std::string pCards, int bid);
void writeCards1(std::string dCards, std::string pCards, int bid, int dPoints, int pPoints);
bool ynLoop();



int askBid(float& money) {
    std::cout << "\n\nYou have " << money << "$ on your account.\n" << "Enter your bid: ";
    while (true)
    {
        std::string text_bid;
        float new_bid;
        while (true) {
            std::cin >> text_bid;
            new_bid = atoi(text_bid.c_str());
            if (new_bid != 0 and !(new_bid > money)) {
                money = money - new_bid;
                return new_bid;
            }
            else if (new_bid == 0) {
                std::cout << "You didn't enter a number! Try one more time: ";
            }
            else {
                std::cout << "You have entered more, than you have on your account. Try one more time: ";
            }
        }
    }

}

int cardToPoint(char card) {
    if ((int)(card - '0') < 10) {
        return card - '0';
    }
    else if (card == 'J' or card == 'Q' or card == 'K') {
        return 10;
    }
    else {
        return 11;
    }
}

bool drawCardDealer(std::string& dCards, int& dPoints, int pPoints)
{
    std::size_t place = dCards.find("#");
    dCards.replace(place, 1, "");
    while (dPoints <= pPoints and dPoints <= 21) {
        char new_dCard = getRandomCard();
        dCards.push_back(new_dCard);
        dPoints = dPoints + cardToPoint(new_dCard);
        if (pPoints > 21 and isAceInCards(dCards)) {
            pPoints = pPoints - 10;
        }
    }

    if (dPoints <= 21) {
        return 1;
    }
    else {
        return 0;
    }

}

void drawCardPlayer(std::string& pCards, int& pPoints) {
    char new_pCard = getRandomCard();
    pCards.push_back(new_pCard);
    pPoints = pPoints + cardToPoint(new_pCard);

    if (pPoints > 21 and isAceInCards(pCards)) {
        pPoints = pPoints - 10;
    }
}

void gameLoop(float& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards) {
    //writeCards1(dCards, pCards, bid, dPoints, pPoints);
    writeCards(dCards, pCards, bid);


    while (true)
    {
        if (selectOption()) {
            drawCardPlayer(pCards, pPoints);
            //writeCards1(dCards, pCards, bid, dPoints, pPoints);
            writeCards(dCards, pCards, bid);
            if (pPoints > 21) {
                gameLose(1, money);
                break;
            }
        }
        else {
            if (drawCardDealer(dCards, dPoints, pPoints)) {
                gameLose(2, money);
            }
            else {
                money = money + (float)bid * 1.5f;
            }
            //writeCards1(dCards, pCards, bid, dPoints, pPoints);
            writeCards(dCards, pCards, bid);
            std::cout << "\nYou won this hand! Now you have " << money << "$ on your account!";
            break;
        }
    }

    std::cout << "\nDo you want to start a new game? [y/n]:";
    if (!ynLoop()) {
        gameFlag = false;
    }
    std::cin.get();
}

void gameLose(int why, float money) {
    std::cout << "\n\nYou lost this hand because ";
    switch (why) {
    case(1):
        std::cout << "you are out of points!\n";
        break;
    case(2):
        std::cout << "the dealer has more points than you!\n";
        break;
    default:
        std::cout << "idk why!\n";
    }

    std::cout << "Now you have " << money << "$ on your account!";

}

char getRandomCard() {
    char cards[12] = { '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A' };
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 11); 
    return cards[distr(gen)];
}

bool isAceInCards(std::string& cards) {

    std::size_t place = cards.find("A");
    if (place != std::string::npos) {
        cards.replace(place, 1, u8"А");
        return true;
    }
    else {
        return false;
    }


}

void newGame(float& money, int &dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards) {
    dCards = "";
    pCards = "";


    char new_dCard = getRandomCard();

    
    dCards.push_back(new_dCard);
    dCards.push_back('#');

    dPoints = cardToPoint(new_dCard);

    char new_pCard1 = getRandomCard();
    char new_pCard2 = getRandomCard();


    pCards.push_back(new_pCard1);
    pCards.push_back(new_pCard2);
    pPoints = cardToPoint(new_pCard1) + cardToPoint(new_pCard2);
    if (pPoints == 22) {
        pPoints = 2;
    }


    bid = askBid(money);;

    gameLoop(money, dPoints, pPoints, bid, dCards, pCards);
}

bool selectOption() {
    std::cout << "\nDo you want to take another card?[y/n]: ";
    return ynLoop();
}

void writeCards(std::string dCards , std::string pCards, int bid) {
    system("CLS");
    std::cout << "Dealer:\t" << dCards << "\nYou:\t" << pCards << "\nBid:\t" << bid << "$";

}
void writeCards1(std::string dCards, std::string pCards, int bid, int dPoints, int pPoints) {
    system("CLS");
    std::cout << "Dealer:\t" << dCards << " Points: " <<dPoints << "\nYou:\t" << pCards << " Points: " << pPoints << "\nBid:\t" << bid << "$";

}

bool ynLoop()
{
    std::string choice;
    while (true)
    {
        std::cin >> choice;
        if (choice == "y" or choice == "Y" or choice == "Yes" or choice == "yes") {
            return true;
        }
        else if (choice == "n" or choice == "N" or choice == "No" or choice == "no") {
            return false;
        }
        else {
            std::cout << "You wrote wrong option. Try again [y/n]: ";
        }
    }
}



int main()
{
    SetConsoleOutputCP(CP_UTF8); 

    int dPoints = 0, pPoints = 0, bid = 0;
    float money = 1000;
    std::string dCards = "", pCards = "";
    
    std::cout << "Welcome to Vovka1759 BlackJack.\n";
    system("pause");

    while (gameFlag)
    {
        newGame(money, dPoints, pPoints, bid, dCards, pCards);    
    }
    
}

