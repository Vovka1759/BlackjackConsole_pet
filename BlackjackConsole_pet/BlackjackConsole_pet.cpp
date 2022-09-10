#include <iostream>
#include <random>
#include <windows.h>

bool gameFlag = true;


char getRandomCard();
int cardToPoint(char card);
int askBid(int& money);
void newGame(int& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards);
void writeCards(std::string dCards, std::string pCards, int bid);
void gameLoop(int& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards);
bool selectOption();
void drawCardPlayer(std::string& pCards, int& pPoints);
bool isAceInCards(std::string& cards);
void gameLose(int why);
bool ynLoop();

char getRandomCard() {
    char cards[12] = { '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A' };
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 11); 
    return cards[distr(gen)];
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

int askBid(int& money) {
    system("CLS");
    std::cout << "You have " << money << "$ on your account.\n" << "Enter your bid: ";
    while (true)
    {
        int new_bid;
        std::cin >> new_bid;
        if (!(new_bid > money)) {
            money = money - new_bid;
            return new_bid;
        }
        else {
            std::cout << "You have entered more, than you have on your account. Try one more time: ";
        }
    }

}

void newGame(int& money, int &dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards) {
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

    bid = askBid(money);;

    gameLoop(money, dPoints, pPoints, bid, dCards, pCards);
}

void writeCards(std::string dCards , std::string pCards, int bid) {
    system("CLS");
    std::cout << "Dealer:\t" << dCards << "\nYou:\t" << pCards << "\nBid:\t" << bid << "$";

}
void writeCards1(std::string dCards, std::string pCards, int bid, int dPoints, int pPoints) {
    system("CLS");
    std::cout << "Dealer:\t" << dCards << " Points: " <<dPoints << "\nYou:\t" << pCards << " Points: " << pPoints << "\nBid:\t" << bid << "$";

}

bool selectOption() {
    std::cout << "\nDo you want to take another card?[y/n]: ";
    return ynLoop();
}

void drawCardPlayer(std::string& pCards, int& pPoints) {
    char new_pCard = getRandomCard();
    pCards.push_back(new_pCard);
    pPoints = pPoints + cardToPoint(new_pCard);

    if (pPoints > 21 and isAceInCards(pCards)) {
        pPoints = pPoints - 10;
    }
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

void gameLose(int why) {
    std::cout << "\n\nYou lost this hand because ";
    switch (why) {
    case(1):
        std::cout << "you are out of points!\n";
        break;

    default:
        std::cout << "idk why!\n";
    }

    std::cout << "Do you want to start a new game? [y/n]:";
    if (!ynLoop()) {
        gameFlag = false;
    }
        
}

bool ynLoop()
{
    char choice;
    while (true)
    {
        std::cin >> choice;
        if (choice == 'y') {
            return true;
        }
        else if (choice == 'n') {
            return false;
        }
        else {
            std::cout << "You wrote wrong option. Try again [y/n]:";
        }
    }
}

void gameLoop(int& money, int& dPoints, int& pPoints, int& bid, std::string& dCards, std::string& pCards) {
    writeCards1(dCards, pCards, bid, dPoints, pPoints);

    while (true)
    { 
        if (selectOption()) {
            drawCardPlayer(pCards, pPoints);
            writeCards1(dCards, pCards, bid, dPoints, pPoints);
            if (pPoints>21) {
                gameLose(1);
                break;
            }
        }
        else {
            break;
        }
    }
    
    
    std::cout << "GGWP";
    std::cin.get();
}
int main()
{
    SetConsoleOutputCP(CP_UTF8); 

    int dPoints = 0, pPoints = 0, bid = 0, money = 1000;
    std::string dCards = "", pCards = "";
    
    

    while (gameFlag)
    {
        newGame(money, dPoints, pPoints, bid, dCards, pCards);    
    }
    
}

