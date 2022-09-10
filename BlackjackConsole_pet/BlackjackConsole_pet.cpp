#include <iostream>
#include <random>
int getRandomCard() {

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 11); 
    return distr(gen);
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

int main()
{   
    char cards[12] = { '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};
    while (true)
    {
        int num = getRandomCard();
        std::cout << cards[num]<< " " << cardToPoint(cards[num]);

        std::cin.get();
    }
    
}

