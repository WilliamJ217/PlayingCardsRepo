//  Created by Bill Struwe on 4/19/16.

#include "Card.h"
#include "Deck.h"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct player
{	Deck hand{0};
	int handMax = 11; //4 aces, 4 2s, 3 3s for 4+8+9 = 21
	string name;
	int handvalue = 0;
	int roundswon = 0;
};

void distributeFunc(Deck&, Deck&, int);
void checkcardval(player &);


const int HANDSIZE = 2; //least num of cards to get 21: Ace + J/Q/K AKA natural

int main()
{   string name;
	Deck Deck;
	Deck.setAcePriority('H');
	char anotherround;
    int numplayers;
    
	//might need a vector of players for an unknown number of players with NEW keyword
    cout << "How many players? ";  cin >> numplayers;
    vector<player> vecpl(numplayers);

    for (int i = 0; i < vecpl.size(); i++)
    {   cout << "Enter Player "<<i+1<<"'s name: ";  cin >> vecpl[i].name;
    }
	//begin distributing cards
	//might need a for loop to go through a vector of players
    for (int i = 0; i <vecpl.size(); i++)
        distributeFunc(vecpl[i].hand, Deck, HANDSIZE);
    for (int i = 0; i < vecpl.size(); i++)
    {   cout <<vecpl[i].name<<"'s hand:\n";
        vecpl[i].hand.printDeck();
    }
    //begin totaling cards in each hand
    //display player hand, and determine H/L of any Aces
    for (int i = 0; i < vecpl.size(); i++)
    {   cout <<vecpl[i].name<<"'s score:\n";
        //checkcardval(vecpl[i]);  This should wait until later, because most players will start with "soft" hands (ace&<10).
        cout << vecpl[i].handvalue << endl;
    }
/*check scores now.  if someone has Nat 21 now, pay his bet 1.5x. check for other 21s.
If the dealer and another player both have naturals, the bet of that player is a stand-off (a tie), and the player takes back his chips.  check who has less cards.
Then everyone gets a chance to hit,stand,fold; 1 player at a time goes until stand,fold,bust.
	Dealer: If hand is 17+, must stand.  If 16-, must hit.
If player's first two cards are same rank, ie two J or two 6, he may choose to treat them as separate hands on his turn. His bet goes on one card, an equal amount must be placed on the other.
    He can double bet when first two cards = 9,10,11. When turn comes, places bet equal to original, dealer gives one card, face down, not turned up until bets are settled at end round.
When dealer's upcard is a good one, 7, 8, 9, 10-card, or ace, the player should not stop until a total of 17+.

*/
    
}
void distributeFunc(Deck& giveto, Deck& takefrom, int howmany)
{	srand (time(NULL));
	bool addedbool, removedbool;
	int found = -1;
	while (giveto.getNumCards() < howmany)
	{	Card::Rank r = static_cast<Card::Rank>(rand() % 13+1);
		Card::Suit s = static_cast<Card::Suit>(rand() % 4);
		found = takefrom.search(r,s);
		if (found > -1)
		{	addedbool = giveto.add(r,s);
			removedbool = takefrom.remove(r,s);
		}
	}
}

void checkcardval(player &p)
{	char highorlow;
    for (int i = 0; i < HANDSIZE; i++)
    {   //if p.handvalue >   10, ace low
        if (p.hand[i].getRank() == Card::Ace)
        {   if (p.handvalue > 10)
                p.handvalue += 1;
            else
            {   cout << "Want this Ace to be High or Low? H/L: ";	cin >> highorlow;
                if (highorlow == 'H' || highorlow == 'h')  p.handvalue += 11;
                else p.handvalue += 1;
            }
        }
        else if (p.hand[i].getRank() == Card::Two)	p.handvalue += 2;
        else if (p.hand[i].getRank() == Card::Three)	p.handvalue += 3;
        else if (p.hand[i].getRank() == Card::Four)	p.handvalue += 4;
        else if (p.hand[i].getRank() == Card::Five)	p.handvalue += 5;
        else if (p.hand[i].getRank() == Card::Six)	p.handvalue += 6;
        else if (p.hand[i].getRank() == Card::Seven)	p.handvalue += 7;
        else if (p.hand[i].getRank() == Card::Eight)	p.handvalue += 8;
        else if (p.hand[i].getRank() == Card::Nine)	p.handvalue += 9;
        else if (p.hand[i].getRank() == Card::Ten)    p.handvalue += 10;
        else if (p.hand[i].getRank() == Card::Jack || p.hand[i].getRank() == Card::Queen || p.hand[i].getRank() == Card::King)
            p.handvalue += 10;
    }
}
