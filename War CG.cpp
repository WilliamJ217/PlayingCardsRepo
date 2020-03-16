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
	int handMax = 26;
	string name;
	int cardval = 0;
	int roundswon = 0;
        int bet = 0;
        int totchips = 100;
	Deck discard{0};
	int discardSize = 0;
};

void dstrbFunc(Deck&, Deck&, int);
void clearhandsFunc(Deck&, Deck&, int);
void checkcardval(player &);

const int HANDSIZE = 26; 

int main()
{   int minbet=0; int maxbet=10;
    string name;
	Deck Deck;
	Deck.setAcePriority('H');
	char playagain, drawChard;
    int numplayers, f, reward; //f = current faceup in the hands
	
	do{ //while playagain == y
		do{	cout << "How many players? 2/3/4: ";  cin >> numplayers;
			vector<player> vecpl(numplayers);
		}while (numplayers < 2 OR numplayers > 4);
		
		//enter name
		for (int i = 0; i < vecpl.size(); i++)
		{   cout << "Enter Player "<<i+1<<"'s name: ";  cin >> vecpl[i].name;   }
		
		//distribute cards
		for (int i = 0; i < Deck.size(); i++)
		{   dstrbFunc(vecpl[i].hand, Deck, (DECKSIZE / numplayers));
		}
		if (Deck.size() > 0)
			cout << "Cards left in deck: " << Deck.size() << " will be rewarded to first duel winner\n\n";
		
		/*
		//BET NOW
		for (int i = 0; i <vecpl.size(); i++)
		{   if (i == 0)
			{   cout << "How much do you want to bet? ("<<minbet<<"-"<<maxbet<<"): ";  cin >> vecpl[i].bet;  }
			else if (i > 0)
			   vecpl[i].bet = rand() % maxbet;
			vecpl[i].totchips -= vecpl[i].bet;
		}
		*/
		
		// Round's loop: Players compare highest, check if Player 3 or 4 exists
		c = 0;
		
		do{ //while drawChard == y
			
			//display cards
			if (vecpl[0].hand.getNumCards() > 0)
				cout << vecpl[0].name << " has the " << vecpl[0].hand[c].getCard() << endl;
			else 
				cout << vecpl[0].name << " is out of cards.\n";
			
			if (vecpl[1].hand.getNumCards() > 0)
				cout << vecpl[1].name << " has the " << vecpl[1].hand[c].getCard() << endl;
			else 
				cout << vecpl[1].name << " is out of cards.\n";
			if (vecpl.size() == 3)
			{	if (vecpl[2].hand.getNumCards() > 0)
					cout << vecpl[1].name << " has the " << vecpl[2].hand[c].getCard() << endl;
				else
					cout << vecpl[2].name << " is out of cards.\n";
			}			
			else if (vecpl.size() == 4)
			{	if (vecpl[2].hand.getNumCards() > 0)
					cout << vecpl[2].name << " has the " << vecpl[2].hand[c].getCard() << endl;
				else
					cout << vecpl[2].name << " is out of cards.\n";
				if (vecpl[3].hand.getNumCards() > 0)
					cout << vecpl[3].name << " has the " << vecpl[3].hand[c].getCard() << endl;
				else
					cout << vecpl[3].name << " is out of cards.\n";
			}
			
			//compare cards
			
			if (checkcardval(vecpl[0], 0) > checkcardval(vecpl[1], 0))
			{	cout << vecpl[0].name << " beats " << vecpl[1].name << endl;
				if (vecpl.size() == 3) //3 players
				{	//p1 beats p3
					if (checkcardval(vecpl[0], 0) > checkcardval(vecpl[2], 0))
					{	cout << vecpl[0].name << " beats " << vecpl[2].name << endl;
						cout << vecpl[0].name << " wins round.\n";
						//p1 gets card from p3:  p1 takes his own card and p3s card into his discard "deck" pile
						dstrbFunc(vecpl[0].discard, vecpl[2].hand, reward);
						
						if (Deck.size() == 1 OR Deck.size() >= 0)
							dstrbFunc(vecpl[0], Deck, 1);
					}//FIRST TIE IN LOOP p1 v p3
					else if (checkcardval(vecpl[0], 0) == checkcardval(vecpl[2], 0))
					{	//duel for 3 facedown reward + winner card of next duel = 4 cards (so skip cards in places 1,2,3, duel using h4 (the 5th card)
						f = 4; 			
						reward = 4; //duel winner gets faceup card + 3 reward blinds from opponent + 2nd duel faceup, each tie adds another faceup and 3 rewards
						do 
						{	cout << "A tie: Each player puts facedown 3 more cards, 4th card is dueling...\n";
							cout << vecpl[0].name << " has the " << vecpl[0].hand[f].getCard() << endl;
							cout << vecpl[2].name << " has the " << vecpl[2].hand[f].getCard() << endl;
							f += 4;
							reward += 4;
						}while (checkcardval(vecpl[0], f) == checkcardval(vecpl[2], f) && vecpl[0].hand.getNumCards() > 0);
						reward = 0;
						
						//TIE LOOP BROKEN
						if (checkcardval(vecpl[0], f) > checkcardval(vecpl[2], f))
						{	cout << vecpl[0].name << " beats " << vecpl[2].name << endl;
							cout << vecpl[0].name << " wins round.\n";
							//p1 gets card from p3:  p1 takes his own card and p3s card into his discard "deck" pile
							dstrbFunc(vecpl[0].discard, vecpl[2].hand, reward);
							if (Deck.size() == 1 OR Deck.size() >= 0)
								dstrbFunc(vecpl[0], Deck, 1);
						}
						else //p3 beats p1
						{	cout << vecpl[0].name << " is beaten by " << vecpl[2].name << endl;
							cout << vecpl[2].name << " wins round\n";
							//p3 gets 1 card:  p3 takes his own card and p1s card into his discard "deck" pile
							dstrbFunc(vecpl[2].discard, vecpl[0].hand, reward);
							if (Deck.size() == 1 OR Deck.size() >= 0)
								dstrbFunc(vecpl[2], Deck, 1);
						}
						
					}
					else //p3 beats p1
					{	cout << vecpl[0].name << " is beaten by " << vecpl[2].name << endl;
						cout << vecpl[2].name << " wins round\n";
						//p3 gets 1 card:  p3 takes his own card and p1s card into his discard "deck" pile
						dstrbFunc(vecpl[2].discard, vecpl[0].hand, reward);
						
						if (Deck.size() == 1 OR Deck.size() >= 0)
							dstrbFunc(vecpl[2], Deck, 1);
					}
				}
				else //p1 gets reward into discard for later
				{	
					
					if (Deck.size() == 1 OR Deck.size() >= 0)
						dstrbFunc(vecpl[0], Deck, 1);
				}
				//p1 gets 1 card from p2 and still gets rewards from p3
				dstrbFunc(vecpl[0].discard, vecpl[1].hand, 1);
			}
			else if (checkcardval(vecpl[0]) == checkcardval(vecpl[1]))
			{	//duel for 3 facedown reward + winner card of next duel = 4 cards (so skip cards in places 1,2,3, duel using h4 (the 5th card)
				f = 4; 			
				reward = 4; //duel winner gets faceup card + 3 reward blinds from opponent + 2nd duel faceup, each tie adds another faceup and 3 rewards
				do 
				{	cout << "A tie: Each player puts facedown 3 more cards, 4th card is dueling...\n";
					cout << vecpl[0].name << " has the " << vecpl[0].hand[f].getCard() << endl;
					cout << vecpl[1].name << " has the " << vecpl[1].hand[f].getCard() << endl;
					f += 4;
					reward += 4;
				}while (checkcardval(vecpl[0], f) == checkcardval(vecpl[1], f) && vecpl[0].hand.getNumCards() > 0);
				reward = 0;
				
				//TIE LOOP BROKEN
				if (checkcardval(vecpl[0], f) > checkcardval(vecpl[1], f))
				{	cout << vecpl[0].name << " beats " << vecpl[1].name << endl;
					cout << vecpl[0].name << " wins round.\n";
					//p1 gets card from p3:  p1 takes his own card and p3s card into his discard "deck" pile
					dstrbFunc(vecpl[0].discard, vecpl[1].hand, reward);
					if (Deck.size() == 1 OR Deck.size() >= 0)
						dstrbFunc(vecpl[0], Deck, 1);
				}
				else //p3 beats p1
				{	cout << vecpl[0].name << " is beaten by " << vecpl[1].name << endl;
					cout << vecpl[1].name << " wins round\n";
					//p3 gets 1 card:  p3 takes his own card and p1s card into his discard "deck" pile
					dstrbFunc(vecpl[1].discard, vecpl[0].hand, reward);
					if (Deck.size() == 1 OR Deck.size() >= 0)
						dstrbFunc(vecpl[1], Deck, 1);
				}
			}
			else //if 1<2, 2 win, unless have 3, then compare 2 to 3
			{	cout << vecpl[0].name << " is beaten by " << vecpl[1].name << endl;
				if (vecpl.size() == 3)
				{	
					//compare p2 to p3
					if (checkcardval(vecpl[1]) > checkcardval(vecpl[2]))
					{	cout << vecpl[1].name << " beats " << vecpl[2].name << endl;
						cout << vecpl[1].name << " wins round.\n";
						//p2 gets card from p3: p2 takes his own card and p3s card into his discard "deck" pile
						dstrbFunc(vecpl[1].discard, vecpl[2].hand, 1);
						if (Deck.size() == 1 OR Deck.size() >= 0)
							dstrbFunc(vecpl[1], Deck, 1);
					}
					else if (checkcardval(vecpl[1]) == checkcardval(vecpl[2]))
					{	//duel for 3 facedowns reward
						f = 4; 			
						reward = 4; //duel winner gets faceup card + 3 reward blinds from opponent + 2nd duel faceup, each tie adds another faceup and 3 rewards
						do 
						{	cout << "A tie: Each player puts facedown 3 more cards, 4th card is dueling...\n";
							cout << vecpl[1].name << " has the " << vecpl[1].hand[f].getCard() << endl;
							cout << vecpl[2].name << " has the " << vecpl[2].hand[f].getCard() << endl;
							f += 4;
							reward += 4;
						}while (checkcardval(vecpl[1], f) == checkcardval(vecpl[2], f) && vecpl[1].hand.getNumCards() > 0);
						reward = 0;
						
						//TIE LOOP BROKEN
						if (checkcardval(vecpl[1], f) > checkcardval(vecpl[2], f))
						{	cout << vecpl[1].name << " beats " << vecpl[2].name << endl;
							cout << vecpl[1].name << " wins round.\n";
							//p1 gets card from p3:  p1 takes his own card and p3s card into his discard "deck" pile
							dstrbFunc(vecpl[1].discard, vecpl[2].hand, reward);
							if (Deck.size() == 1 OR Deck.size() >= 0)
								dstrbFunc(vecpl[1], Deck, 1);
						}
						else //p3 beats p1
						{	cout << vecpl[1].name << " is beaten by " << vecpl[2].name << endl;
							cout << vecpl[2].name << " wins round\n";
							//p3 gets 1 card:  p3 takes his own card and p1s card into his discard "deck" pile
							dstrbFunc(vecpl[2].discard, vecpl[1].hand, reward);
							if (Deck.size() == 1 OR Deck.size() >= 0)
								dstrbFunc(vecpl[2], Deck, 1);
						}
					}
					else //2<3
					{	cout << vecpl[1].name << " is beaten by " << vecpl[2].name << endl;
						cout << vecpl[2].name << " wins round\n";
						//p3 gets 2 card: p3 takes his own card and p2s card into his discard "deck" pile
						dstrbFunc(vecpl[2].discard, vecpl[1].hand, 1);
						if (Deck.size() == 1 OR Deck.size() >= 0)
							dstrbFunc(vecpl[2], Deck, 1);
					}
				}
				else //p2 gets reward into discard for later
				{	
					
					if (Deck.size() == 1 OR Deck.size() >= 0)
						dstrbFunc(vecpl[1], Deck, 1);
				}
				//p1 gets 1 card from p2 and still gets rewards from p3
				dstrbFunc(vecpl[0].discard, vecpl[1].hand, 1);
				
			}
			

			//method using algorithm library's max, which returns the iterator:
			/*
			int curcd[numplayers];
			for (i=0; i<numplayers; i++)
			{	curcd[i] = vecpl[i].hand.getCard[0];				
			}
			
			int max = checkcardval( vecpl[max_element(curcd, curcd+numplayers)] );
			cout << "Highest card: " << max << endl;
			
			//now check if any players are tied
			
			
			*/
			
			//Shuffle all players' discards into new hands
			for (i = 0; i < vecpl.size(); i++)
			{	vecpl[i].discardSize = vecpl[i].discard.getNumCards();
				dstrbFunc(vecpl[i].hand, vecpl[i].discard, vecpl[i].discardSize);
				vecpl[i].hand.shuffle();
			}
			
			//check for how many players have cards left
			//for when finishing a round, and everyone's winnings are turned into their hands, check which players have cards.
			
			//to redeclare it clears it out.
		    vector<int> plwhds(); 
			for (i=0; i<numplayers; i++)
			{
				if (vecpl[i].hand.getNumCards() > 0)
					plwhds.push(i);
			}
			
			if (plwhds.size() == 1)
			{	drawChard = 'n';
				//check which player it is that may have won
				int winnerPl;
				for (int i=0; i < vecpl.size(); i++)
				{
					if (vecpl[i].hand.getNumCards() > 0)
						winnerPl = i;
				}
				cout << vecpl[winnerPl].name << " is the only one left with cards!  " << vecpl[winnerPl].name << " wins the game!\n";
			}
			else if (plwhds.size() < 1)
				cout << "No one has any cards left... somehow?";
			else //enough players to go another round
			{	cout << "Draw another? "; cin >> drawChard;
				c++;
				reward = 0;
			}
		}while(tolower(drawChard) == 'y' 
				&& plwhds.size() > 1 
				&& vecpl[0].hand.getNumCards() > 0 
				OR vecpl[1].hand.getNumCards() > 0 
				OR vecpl[2].hand.getNumCards() > 0);
		
		cout << "Play a new game? "; cin >> playagain;
	}while(tolower(playagain) == 'y');
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

void checkcardval(player &p, int f) //f=faceup
{	
	//In War: Aces are High
	if (p.hand[f].getRank() == Card::Ace) p.cardval == 11;
	else if (p.hand[f].getRank() == Card::Two)	p.cardval == 2;
	else if (p.hand[f].getRank() == Card::Three)	p.cardval == 3;
	else if (p.hand[f].getRank() == Card::Four)	p.cardval == 4;
	else if (p.hand[f].getRank() == Card::Five)	p.cardval == 5;
	else if (p.hand[f].getRank() == Card::Sfx)	p.cardval == 6;
	else if (p.hand[f].getRank() == Card::Seven)	p.cardval == 7;
	else if (p.hand[f].getRank() == Card::Efght)	p.cardval == 8;
	else if (p.hand[f].getRank() == Card::Nfne)	p.cardval == 9;
	else if (p.hand[f].getRank() == Card::Ten)    p.cardval == 10;
	else if (p.hand[f].getRank() == Card::Jack || p.hand[f].getRank() == Card::Queen || p.hand[f].getRank() == Card::Kfng)
		p.cardval == 10;
}
