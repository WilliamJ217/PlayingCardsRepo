//  Created by Bill Struwe on 4/19/16.

#include "Card.h"
#include "Deck.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct player
{	Deck hand{0};
	int handMax = 11; //4 aces, 4 2s, 3 3s for 4+8+9 = 21
	string name;
	int handvalue = 0;
	int roundswon = 0;
        int bet = 0;
        int totchips = 100;
    int numSplits = 0;
};

void dstrbFunc(Deck&, Deck&, int);
void clearhandsFunc(Deck&, Deck&, int);
void checkcardval(player &);

const int HANDSIZE = 2; //least num of cards to get 21: Ace + J/Q/K AKA natural

int main()
{   player dealer;
    dealer.name = "Dealer";
    int minbet=0; int maxbet=10;
    string name;
	Deck Deck;
	Deck.setAcePriority('H');
	char playagain, splitq, ntlDubBetq;
    int numplayers;
    cout << "How many players? ";  cin >> numplayers;
    vector<player> vecpl(numplayers);
    //enter name
	do{
		for (int i = 0; i < vecpl.size(); i++)
		{   cout << "Enter Player "<<i+1<<"'s name: ";  cin >> vecpl[i].name;   }
		
		//BET NOW
		for (int i = 0; i <vecpl.size(); i++)
		{   if (i == 0)
			{   cout << "How much do you want to bet? ("<<minbet<<"-"<<maxbet<<"): ";  cin >> vecpl[i].bet;  }
			else if (i > 0)
			   vecpl[i].bet = rand() % maxbet;
			vecpl[i].totchips -= vecpl[i].bet;
		}
		
		for (int i = 0; i <vecpl.size(); i++)
		{   dstrbFunc(vecpl[i].hand, Deck, HANDSIZE);
			//PASS CARDS OUT
			while (vecpl[i].hand[0].getRank() == vecpl[i].hand[1].getRank() && vecpl[i].numSplits > 3)
			{   cout << vecpl[i].name << " has pair of same rank, want split into new hand? ";  cin >> splitq;
				if (tolower(splitq) == 'y')
				{   //new hand is made here somehow
					SplitP = new player;
					vecpl[i].numSplits += 1;
					numplayers++;
					
					SplitP.hand.add(vecpl[i].hand[1].getCard());
					vecpl[i].hand.remove(vecpl[i].hand[1].getCard());
					
					SplitP.name = vecpl[i].name+"Split"+numSplits;
					SplitP.totchips = vecpl[i].totchips;
					SplitP.bet = vecpl[i].bet;
					
					if (vecpl[i].hand[0].getRank() == 9 OR 10 OR 11)
					{	cout << "9,10,11 split: Double bet on each hand?"; cin >> ntlDubBetq;
						if (tolower(ntlDubBetq) == 'y')
						{	vecpl[i].bet *= 2;
							SplitP.bet *= 2;
						}
					}
					
					dstrbFunc(vecpl[i].hand, Deck, 1);
					dstrbFunc(SplitP.hand, Deck, 1)
					vecpl[i].handvalue = 0; checkcardval(vecpl[i]);
					SplitP.handvalue = 0; checkcardval(SplitP);
					
					vecpl.push_back(SplitP);
					delete SplitP;
				}
			}
		}
		dstrbFunc(dealer.hand, Deck, HANDSIZE);
		for (int i = 0; i < vecpl.size(); i++)
		{   cout <<vecpl[i].name<<"'s hand:\n";  vecpl[i].hand.printDeck();  cout<<vecpl[i].handvalue<<endl;
		}
		cout <<"Dealer's up card: "<<dealer.hand[0].getCard()<<endl;
		
		/*check scores now.  if someone has Nat 21 now, pay his bet 1.5x. check for other 21s.
		If dealer and player both have naturals, bet of player is stand-off (a tie), and player takes back  chips.  check who has less cards.
		Then everyone gets chance to hit,stand,fold; 1 player at time goes until stand,fold,bust.
			Dealer: If hand is 17+, must stand.  If 16-, must hit.
		If player's first two cards are same rank, ie two J or two 6, may choose to treat them as separate hands on his turn. His bet goes on one card, equal amount must be on other.
			Can double bet when first two cards = 9,10,11. When turn comes, places bet equal original, dealer gives one card face down, not turned up until bets are settled at end round.
		When dealer's upcard is good one, 7, 8, 9, 10-card, or ace, the player should not stop until total of 17+.
		*/
		//Natural 21 check
		for (int i = 0; i < vecpl.size(); i++)
		{   cout << vecpl[i].name<<"'s Natural 21 check...\n"; 
			if (vecpl[i].handvalue == 21)
			{   if (dealer.handvalue < 21)
				{  cout << "Immediate BlackJack: Win 1.5x bet.\n";
				   vecpl[i].roundswon++;
				   vecpl[i].totchips += (vecpl[i].bet * 1.5);    }
				else if (dealer.handvalue == 21)
				{   cout << "Tie with dealer: return bet.\n";
					vecpl[i].totchips += vecpl[i].bet;  //when player and dealer both have BJ, pl gets bet back
				}
					//Here is where split hands merge with owner (if won, add bet to original player)
					for (int i = 0; i < numplayers; i++)
					{   cout << vecpl[i].name << "'s bet and chips: " << vecpl[i].bet << " & " << vecpl[i].totchips << endl;
						cout << vecpl[numplayers + numSplit - i].name << "'s split bet and chips: " << vecpl[numplayers + numSplit - i].bet << " & " << vecpl[numplayers + numSplit - i].totchips << endl;
						vecpl[i].totchips += vecpl[numplayers + numSplit - i].bet;
						cout << vecpl[i].totchips << endl;
						cout << "Erasing " << vecpl[numplayers + numSplit - i].name << "...\n";
						vecpl.erase(vecpl.begin+ numplayers + numSplit - i);
					}
					
			}
		}	
		
		// Round's loop: Players try to not bust
		for (int i = 0; i < vecpl.size(); i++) //player by player
		{   char hsf;
			do{
				cout << vecpl[i].name << " can hit/stand/fold (h/s/f): "; cin >> hsf;
				while (tolower(hsf) != 'h' && tolower(hsf) != 's' && tolower(hsf) != 'f')
					cout << "Not recognized, choose h s or f";
				if (tolower(hsf) == 'h')
				{   dstrbFunc(vecpl[i].hand, Deck, 1);
					cout <<vecpl[i].name<<"'s hand: " << vecpl[i].hand.getNumCards() << " cards: \n";
					vecpl[i].hand.printDeck();
					vecpl[i].handvalue=0;
					checkcardval(vecpl[i]);
					cout << vecpl[i].handvalue<<endl;
					if(vecpl[i].handvalue > 21)  
					{	cout << "Bust: lost chips\n";
						clearhandsFunc(vecpl[i].hand, Deck, vecpl[i].hand.getNumCards());
						vecpl[i].handvalue = 0;
					}
					else if (vecpl[i].handvalue == 21)
					{   cout << "21: win chips\n";
						vecpl[i].totchips += vecpl[i].bet;
					}
				}
				else if (tolower(hsf) == 's')
					break;	
				else if (tolower(hsf) == 'f')  cout << "Fold: lost chips\n";
			}while(vecpl[i].handvalue < 21 && hsf == 'h');
			//player is now out or standing with their value
		}
		
		//Dealer
		
		while (dealer.handvalue < 17) //draw until over 17 (including risk of bust)
		{	dstrbFunc(dealer.hand, Deck, 1);
			checkcardvalD(dealer);
		}
		if (dealer.handvalue > 21)
		{   //All active players auto win
			cout << "Dealer busted: Reset cards, players win back bets.\n";
			for (int i = 0; i < vecpl.size(); i++)
			{   vecpl[i].totchips += vecpl[i].bet; //return same amt
				clearhandsFunc(vecpl[i].hand, Deck, vecpl[i].hand.getNumCards());
				vecpl[i].handvalue = 0;
				vecpl[i].roundswon++;
			}
			clearhandsFunc(dealer.hand, Deck, dealer.hand.getNumCards());
			dealer.handvalue = 0;
		}
		else //dealer is between 17 and 21
		{
			//WHAT'S NEXT IS TO COMPARE TO DEALER P b P
			for (int i = 0; i < vecpl.size(); i++) //player by player
			{	cout << "Beating the dealer: " << vecpl[i].name << " scored " << vecpl[i].handvalue << "\n";
				if (vecpl[i].handvalue > dealer.handvalue)
				{	cout << "You win! Recieve x bet!/n";
					vecpl[i].totchips += vecpl[i].bet * 2;
					vecpl[i].roundswon++;
				}
				else if (vecpl[i].handvalue == dealer.handvalue)
				{	cout << "Push: bet returned./n";
					vecpl[i].totchips += vecpl[i].bet;
				}
				else //less than dealer (including those who busted
				{	cout << "Dealer wins./n";
				}
			}
		}
		cout << "Play again? (y/n): "; cin >> playagain;
	}
	while (playagain == 'y')
}
void dstrbFunc(Deck& giveto, Deck& takefrom, int howmany)
{	srand (time(NULL));
	bool addedbool, removedbool;
	int found = -1;
	int startsize = giveto.getNumCards();
	while (giveto.getNumCards() < startsize+howmany)
	{	Card::Rank r = static_cast<Card::Rank>(rand() % 13+1);
		Card::Suit s = static_cast<Card::Suit>(rand() % 4);
		found = takefrom.search(r,s);
		if (found > -1)
		{   addedbool = giveto.add(r,s);
		    removedbool = takefrom.remove(r,s);
		}
	}
}

void clearhandsFunc(Deck& takefrom, Deck& giveto, int howmany)
{	srand (time(NULL));
	bool addedbool, removedbool;
	int found = -1;
    int n = 0;
	while (takefrom.getNumCards() < giveto.getNumCards() || n < howmany)
	{	Card::Rank r = static_cast<Card::Rank>(rand() % 13+1);
		Card::Suit s = static_cast<Card::Suit>(rand() % 4);
		found = takefrom.search(r,s);
		if (found > -1)
		{   removedbool = takefrom.remove(r,s);
            addedbool = giveto.add(r,s);
            n++;
		}
	}
}

void checkcardval(player &p)
{	char highorlow;
    for (int i = 0; i < p.hand.getNumCards(); i++)
    {   //if p.handvalue >   10, ace low
        if (p.hand[i].getRank() == Card::Ace)
        {   if (p.handvalue > 10)  p.handvalue += 1;
            else
            {   cout << "Want this Soft Ace to be High or Low? H/L: ";	cin >> highorlow;
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
void checkcardvalD(player &p)
{	char highorlow;
    for (int i = 0; i < p.hand.getNumCards(); i++)
    {   //if the dealer draws an ace, and counting it as 11 would bring the total to between 17 and 21, it's 11
        if (p.hand[i].getRank() == Card::Ace)
        {   if (p.handvalue + 11 >= 17 && p.handvalue + 11 < 21)
				p.handvalue += 11;
			else p.handvalue += 1;
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
