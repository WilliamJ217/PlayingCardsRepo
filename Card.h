//  Created by Bill Struwe on 2/13/16.
//  Copyright (c) 2016 Bill Struwe. All rights reserved.

#include <iostream>
using namespace std;

class Card
{	public:
         //enum Typename { values=ints };
        enum Rank { Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
        enum Suit { Spades=0, Hearts=1, Diamonds=2, Clubs=3 };
		
		//constructor with default vals
        Card(): m_suit(Spades), m_rank(Ace){};
        //constructor when object call is Card cardobj(7, Hearts);
        Card(Rank r, Suit s): m_rank(r), m_suit(s){}
    	
    	void setAcePriority(char alh){ AceLowHigh = alh; }
    	char getAcePriority(){	return AceLowHigh;	}
        void setRank(Rank r){   m_rank=r; }
        void setSuit(Suit s){   m_suit=s; }
        Rank getRank(){   return m_rank;    };
        Suit getSuit(){   return m_suit;    };
        string getCard();
        
    protected:
        char AceLowHigh = 'L';
        Rank m_rank;  Suit m_suit;
};

string Card::getCard()
{	string rankStr, suitStr;
	switch(m_rank)
	{	case 1: rankStr =  "Ace"; break;    case 2: rankStr =  "Two"; break;
		case 3: rankStr =  "Three"; break;  case 4: rankStr =  "Four"; break;
		case 5: rankStr =  "Five"; break;	case 6: rankStr =  "Six"; break;
		case 7: rankStr =  "Seven"; break;  case 8: rankStr =  "Eight"; break;
		case 9: rankStr =  "Nine"; break;   case 10: rankStr =  "Ten"; break;
		case 11: rankStr =  "Jack"; break;  case 12: rankStr =  "Queen"; break;
		case 13: rankStr =  "King"; break;  default: rankStr =  "N/A";
	}
	switch (m_suit)
    {   case 0:  suitStr = "Spades"; break;    case 1:  suitStr = "Hearts"; break;
        case 2:  suitStr = "Diamonds"; break;  case 3:  suitStr = "Clubs"; break;
        default: return "N/A";
    }	
	return(rankStr + " of " + suitStr);
}
