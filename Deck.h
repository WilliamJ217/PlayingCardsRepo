//  Created by Bill Struwe on 2/13/16.
//  Copyright (c) 2016 Bill Struwe. All rights reserved.

#ifndef PlayingCards_Deck_h
#define PlayingCards_Deck_h

#include <vector>
#include <cstdlib>
using namespace std;

class Deck: public Card
{   private:
        const static int DECKSIZE = 52;
       int numCards = 0;
        vector<Card> theDeck;
        vector<Card> origDeck;
    public:
        Deck();//default, filled with all 52 cards
        Deck(int);//custom size, still 52 allowed
        bool add(Rank, Suit);
        bool add(Card);
        bool remove(Rank, Suit);
        int search(Rank, Suit);
        void shuffle();
        void sort();
        void clear(){   theDeck.clear();  numCards=0; }
        void swapCards(Card&, Card&);//pass by reference to keep the changes!!!!!
        int getNumCards(){  return numCards; }
        void printDeck();
        Card& operator[](int);
};
Card& Deck::operator[](int index)
{	return theDeck[index];	}
Deck::Deck()
{   cout << "Calling the constructor with 52\n";
	for (int s = 0; s <= 3; s++)
    {   for (int r = 1; r <= 13 && numCards < DECKSIZE; r++)
        {   Card acard(static_cast<Rank>(r),static_cast<Suit>(s));
            theDeck.push_back(acard);
            numCards++;
        }
    }
}
Deck::Deck(int pileSize)
{   cout << "Calling the constructor with less than 52\n";
	int r, s, pos;
    while (numCards < pileSize && pileSize > 0)
    {   r = rand() % 13+1;
        s = rand() % 4;
        pos = search(static_cast<Rank>(r),static_cast<Suit>(s));
        if (pos < 0 || pos > pileSize)
        {   Card acard(static_cast<Rank>(r),static_cast<Suit>(s));
            theDeck.push_back(acard);
            numCards++;
        }
    }
}
bool Deck::add(Rank r, Suit s)
{   if (numCards == DECKSIZE) //already full
    {	//cout << "Full already.\n";
		return false;
	}
    else
    {   int pos = search(r,s); //return -1 if not fnd
        if (pos < numCards && pos > -1) //if in theDeck
        {	return false;
		}
        else //not in deck (not fnd or past numCards)
        {   Card acard(r,s); //make the card
            theDeck.push_back(acard); //put the valid card in theDeck
            numCards++;
            return true;
        }
    }
}
bool Deck::add(Card c)
{	if (numCards == DECKSIZE)
	{	cout << "Full\n";
		return false;
	}
	else
	{   int pos = search(c.getRank(),c.getSuit()); //return -1 if not fnd
        if (pos < numCards && pos > -1) //if in theDeck
        {	return false;
		}
        else //not in deck (not fnd or past numCards)
        {   theDeck.push_back(c); //put the valid card in theDeck
            numCards++;
            return true;
        }
    }
}
bool Deck::remove(Rank r, Suit s)
{   if (numCards <= 0) //already empty
    {	cout << "Empty already.\n";
		return false;
	}
    else
    {   int pos = search(r,s);
        if (pos == -1 && pos > numCards) //not fnd
        {	cout << "Can't remove a card not in deck.\n";
			return false;
		}
        else
        {   theDeck.erase(theDeck.begin()+pos); //erase the card based on distance from the first position
            numCards--;
			return true;
        }
    }
}
int Deck::search(Rank r, Suit s)
{   int i, pos = -1; //if pos was 0, it'd return the first card
    for (i = 0; i < numCards;)
    {   if (r == theDeck[i].getRank() && s == theDeck[i].getSuit() && r > 0 && r < 14 && s >= 0 && s <= 3)
        {    pos = i;
            break;
        }
        else
            i++;
    }
    return pos;
}
void Deck::shuffle()
{	cout << "Shuffling...\n";
	for (int i = 0; i < numCards; i++)
	{	for (int j = 1; j < numCards; j++)
		{	int random = rand() % numCards;
			swap(theDeck[j],theDeck[random]);
		}
	}
}
void Deck::sort()
{   char sortby;
    int lowestSortedPos = 0;
    int nextPos = 1;
    int r = 1;
    int s = 0;
    cout<<"Sort by suit or rank? S/R:  "; cin >> sortby;
    if (sortby == 'S'||sortby=='s')
    {   for (int i = 0; i < numCards; i++)
        {   for (s = 0; s < 4; s++)
            {   for (r = 1; r < 14; r++)
                {   nextPos = search(static_cast<Rank>(r),static_cast<Suit>(s));
                    if (nextPos >= lowestSortedPos)
                    {   swapCards(theDeck[lowestSortedPos], theDeck[nextPos]);
                        lowestSortedPos++;
                    }
                }
            }
        }
    }
    else if (sortby == 'R'||sortby=='r')
    {   for (int i = 0; i < numCards; i++)
        {   for (r = 1; r < 14; r++)
            {   for (s = 0; s < 4; s++)
                {   nextPos = search(static_cast<Rank>(r),static_cast<Suit>(s));
                    if (nextPos >= lowestSortedPos)
                    {   swapCards(theDeck[lowestSortedPos], theDeck[nextPos]);
                        lowestSortedPos++;
                    }
                }
            }
        }
    }
}
void Deck::swapCards(Card& curr, Card& dest)
{   Card temp;
    temp = curr;
    curr = dest;
    dest = temp;
}
void Deck::printDeck() {
    for (int i = 0; i < numCards; i++)
        cout << theDeck[i].getCard() << "\n";
}

#endif
