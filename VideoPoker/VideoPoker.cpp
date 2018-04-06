// VideoPoker.cpp : Defines the entry point for the console application.

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif


#include "stdafx.h"
#include<iostream>
#include<cstdlib>
#include<random>
#include<string>
#include<iomanip>
using namespace std;

random_device rd;				//random seed 
mt19937 gen(rd());				//generate random seed

int inputLim = 0;
int limit = 52;
int sanityP = 0;
int sanityT = 0;
float cash = 10.0;
bool broke = false;
bool trips = false;
bool quads = false;
bool onePair = false;
bool hFlush = false;
bool hStraight = false;
bool rFlush = false;
bool fh = false;
bool refill = true;
int score = 0;

void Refill();

struct Card
{
	int rank;
	char suit;
	Card* next;	
};

struct linked_list
{
	Card* head;
};

linked_list* create_linked_list()
{
	linked_list* list = new linked_list;
	list->head = nullptr;
	return list;
}

void add_first(linked_list* list, int rank, char suit)
{
	Card* n = new Card;
	n->rank = rank;
	n->suit = suit;
	n->next = list->head;
	list->head = n;
}

void add_last(linked_list* list, int rank, char suit)
{
	if (list->head == nullptr)
	{
		add_first(list, rank, suit);
		return;
	}
	Card* temp = list->head;
	while (temp->next != nullptr)
		temp = temp->next;
	Card* n = new Card;
	n->rank = rank;
	n->suit = suit;
	n->next = nullptr;
	temp->next = n;
}

int check_list(linked_list* list)
{
	Card*n = list->head;
	int counter = 0;
	while (n != nullptr)
	{
		n = n->next;
		counter++;
	}
	return counter;
}

void print_items(linked_list* list)
{
	Card* n = list->head;
	int counter = 1;
	while (n != nullptr)
	{
		string type;
		string face;
		if (n->suit == 'C')
		{
			type = "Clubs";
		}
		else if (n->suit == 'D')
		{
			type = "Diamonds";
		}
		else if (n->suit == 'H')
		{
			type = "Hearts";
		}
		else if (n->suit == 'S')
		{
			type = "Spades";
		}
		cout<<" " << counter << ".) ";

		if (n->rank==1)
		{
			face = "Ace";
			cout << face;
		}
		else if ( n->rank>1 && n->rank <= 10)
		{
			cout<< n->rank;
		}
		else if (n->rank == 11)
		{
			face = "Jack";
			cout << face;
		}
		else if (n->rank == 12)
		{
			face = "Queen";
			cout << face;
		}
		else if (n->rank == 13)
		{
			face = "King";
			cout << face;
		}
		cout<<" of " <<type;
		n = n->next;
		if (counter % 10 == 0)
		{
			cout << endl;
		}
		counter++;
	}
	cout << endl <<endl;
}

void print_hand(linked_list* list)
{
	Card* n = list->head;
	char counter = 1;
	while (n != nullptr)
	{
		string type;
		string face;
		if (n->suit == 'C')
		{
			type = "Cunts";
		}
		else if (n->suit == 'D')
		{
			type = "Dicks";
		}
		else if (n->suit == 'H')
		{
			type = "Balls";
		}
		else if (n->suit == 'S')
		{
			type = "Boobs";
		}

		char which;
		if (counter == 1)
		{
			which = 'A';
		}
		else if (counter == 2)
		{
			which = 'B';
		}
		else if (counter == 3)
		{
			which = 'C';
		}
		else if (counter == 4)
		{
			which = 'D';
		}
		else if (counter == 5)
		{
			which = 'E';
		}
		cout << which << ".) ";

		if (n->rank == 1)
		{
			face = "Ace";
			cout << face;
		}
		else if (n->rank>1 &&  n->rank<= 10)
		{
			cout << n->rank;
		}
		else if (n->rank == 11)
		{
			face = "Jack";
			cout << face;
		}
		else if (n->rank == 12)
		{
			face = "Queen";
			cout << face;
		}
		else if (n->rank == 13)
		{
			face = "King";
			cout << face;
		}
		cout << " of " << type << "\n";
		n = n->next;
		counter++;
	}
}

Card ShowHand(linked_list* list, int index)
{
	Card* n = list->head;
	while (index > 0)
	{
		n = n->next;
		--index;
	}
	return *n;
}

linked_list* list = create_linked_list();
linked_list* hand = create_linked_list();
linked_list* discard = create_linked_list();

Card get_item(linked_list* pile, int index)
{
	int cardRem = check_list(list);
	if (cardRem == 0 && refill)
	{
		Refill();
		refill = false;
	}

	Card* n = pile->head;
	Card* prev = new Card();


	int cnt = index - 1;

	if (cnt == 0)
	{
		n = pile->head;
		pile->head = n->next;
	}
	while (cnt > 0) //This is the problem when input=1 cnt=0 and skips while loop
	{
		if (cnt == 1)
		{
			prev = n;
		}
		n = n->next;
		if (n != nullptr)
		{
			if (n->next != nullptr)
			{
				prev->next = n->next;
			}
			else
			{
				prev->next = nullptr;
			}

			//std::cerr << "Null ptr at " << cnt << std::endl;
		}

		--cnt;
	}
	return *n;
}

Card get_item2(linked_list* pile, int index)
{
	Card* n = pile->head;
	Card* prev = new Card();


	int cnt = index - 1;

	if (cnt == 0)
	{
		n = pile->head;
		pile->head = n->next;
	}
	while (cnt > 0) //This is the problem when input=1 cnt=0 and skips while loop
	{
		if (cnt == 1)
		{
			prev = n;
		}
		n = n->next;
		if (n != nullptr)
		{
			if (n->next != nullptr)
			{
				prev->next = n->next;
			}
			else
			{
				prev->next = nullptr;
			}

			//std::cerr << "Null ptr at " << cnt << std::endl;
		}
		else
		{
			std::cerr << "Null ptr at " << cnt << std::endl;
		}
		

		--cnt;
	}
	return *n;
}

void Refill()
{
//	cout << "Deck\n";
//	print_items(list);
	cout << endl << endl;
//	cout << "Discard\n";
//	print_items(discard);
	int cardRem = check_list(list);
//	cout << "Cards Remaining =" << cardRem << endl;
	int cardDiscarded = check_list(discard);
//	cout << "Discard Pile =" << cardDiscarded << endl;
	limit = cardDiscarded;
	if (cardRem == 0)
	{
		for (int i = 1; i <= cardDiscarded; i++)
		{
			Card c = get_item2(discard, 1);
			add_last(list, c.rank, c.suit);
		}

//		cout << "Deck\n";
//		print_items(list);
		cout << endl << endl;
//		cout << "Discard\n";
//		print_items(discard);
	}
}

void DealHand()
{
	cout << "You currently have $" << cash<<endl;
	cash--;
	cout << "------------------\n";
	for (int i = 0; i < 5; i++)
	{
		string su;
		uniform_int_distribution<>dis(1, limit);
		limit--;
		int dealt = dis(gen);
		Card c1 = get_item(list, dealt);

		if (c1.suit == 'C')
		{
			su = "Clubs";
		}
		else if (c1.suit == 'D')
		{
			su = "Diamonds";
		}
		else if (c1.suit == 'H')
		{
			su = "Hearts";
		}
		else if (c1.suit == 'S')
		{
			su = "Spades";
		}
		
		//cout << c1.rank << " of " << su << endl;
		add_last(hand, c1.rank, c1.suit);
	}
	cout << "--------------------\n";
	cout << "Your hand is" << endl;
	print_hand(hand);
}

void PrintTableState(int score)
{
	if (score == 1)
	{
		cout << "Congrats you made a pair. But need Jacks or higher for a payout" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 2)
	{
		cout << "Congrats you made a pair. Take your dollar back" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	if (score == 3)
	{
		cout << "Congrats you made two pairs" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 4)
	{
		cout << "Congrats you made trips!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 5)
	{
		cout << "Congrats you made Quads!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 6)
	{
		cout << "Congrats you made a Straight!!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 7)
	{
		cout << "Congrats you made a flush!!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 8)
	{
		cout << "Congrats you made a Royal Flush!!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 9)
	{
		cout << "Congrats you made a Straight FLush!!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else if (score == 10)
	{
		cout << "Congrats you made a full house!!!!!" << endl;
		cout << "Current Cash= " << cash << "$" << endl;
	}
	else
	{
		cout << "No luck. Try again" << endl;
	}
}

void CheckHand()
{
	//Check for Poker Hands
	int values[5] = { 0,0,0,0,0 };
	char sValues[5] = { 'A','A','A','A','A' };

	for (int i = 0; i < 5; i++)
	{
		Card current = ShowHand(hand, i);
//		cout << endl << "This is for checking hands";
		values[i] = current.rank;
//		cout << values[i] << endl;
		sValues[i] = current.suit;
//		cout << sValues[i] << endl;
	}

	//Sort the hand value
//	cout << "Sorted hand is" << endl;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5 - i - 1; ++j)
		{
			// Comparing consecutive data and switching values if value at j > j+1.
			if (values[j] > values[j + 1])
			{
				values[j] = values[j] + values[j + 1];
				values[j + 1] = values[j] - values[j + 1];
				values[j] = values[j] - values[j + 1];
			}
		}
		// Value at n-i-1 will be maximum of all the values below this index.
	}
	for (int i = 0; i < 5; i++)
	{
//		cout << values[i] << endl;
	}
	//End value sorting of hand


	//Pair Check
	int pairCounter = 0;
	bool pay = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (values[i] == values[j])
			{
				sanityP = values[i];
				pairCounter++;
				onePair = true;
				score = 1;
				if (values[i] > 10)
				{
					pay = true;
				}
			}
		}
	}
	if (pairCounter == 1)
	{
		if (pay)
		{
			score = 2;
			cash = cash + 1;
		}
	}
	else if (pairCounter == 2)
	{
		score = 3;
		cash = cash + 2;
	}
	//End of Pair Check 

	//Trip Check
	int tripCounter = 0;
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 0; j <5; j++)
		{
			if (values[j] == i)
			{
				tripCounter++;
			}
			if (tripCounter == 3)
			{
				sanityT = i;
			}
		}
		if (tripCounter < 3)
		{
			tripCounter = 0;
		}
		else if (tripCounter == 3)
		{
			if (sanityP == sanityT)
			{
				onePair = false;
			}
			trips = true;
		}
		else if (tripCounter == 4)
		{
			quads = true;
		}
	}

	if (trips)
	{
		score = 4;
		cash = cash + 3;
	}
	else if (quads)
	{
		score = 5;
		cash = cash + 25;
	}

	//Check for straight
	int ind = 0;
	if (values[ind] == values[ind + 1] - 1 && values[ind + 1] == values[ind + 2] - 1 && values[ind + 2] == values[ind + 3] - 1 && values[ind + 3] == values[ind + 4] - 1)
	{
		hStraight = true;
		score = 6;
		cash = cash + 4;
	}
	//Check for flush
	int type = 0;

	if ((sValues[type] == sValues[type + 1]) && (sValues[type + 1] == sValues[type + 2]) && (sValues[type + 2] == sValues[type + 3]) && (sValues[type + 3] == sValues[type + 4]))
	{
		if (values[type] == 1 && values[type + 1] == 10 && values[type + 2] == 11 && values[type + 3] == 12 && values[type + 4] == 13)
		{
			rFlush = true;
			score = 8;
			cash = cash + 800;
		}
		else
		{
			hFlush = true;
			score = 7;
			cash = cash + 6;
		}

	}

	//StraightFlush
	if (hStraight == true && hFlush == true)
	{
		score = 9;
		cash = cash + 50;
	}
	//Check for full house
	if (trips == true && onePair == true)
	{
		fh = true;
		score = 10;
		cash = cash + 9;
	}
	//End of Checking Hands
	PrintTableState(score);
}

void NewHand()
{
	cout << endl;
	cash = cash - 1;
	cout << "Cash left= " << cash << "$" << endl;
	string swap = "ABCDE";
	int handLim = 5;
	int swapNo = swap.length();
	int thisCard = 0;
	for (int i = 0; i < swapNo; i++)
	{
		if (swap[i] == 'A' || swap[i] == 'a')
		{
			thisCard = 1;
		}
		else if (swap[i] == 'B' || swap[i] == 'b')
		{
			thisCard = 2;
		}
		else if (swap[i] == 'C' || swap[i] == 'c')
		{
			thisCard = 3;
		}
		else if (swap[i] == 'D' || swap[i] == 'd')
		{
			thisCard = 4;
		}
		else if (swap[i] == 'E' || swap[i] == 'e')
		{
			thisCard = 5;
		}

		thisCard = thisCard - (5 - handLim);
		
		Card dc = get_item(hand, thisCard);
		add_last(discard, dc.rank, dc.suit);
		handLim--;
	}

	for (int j = 0; j < swapNo; j++)
	{
		int swapped;
		if (limit == 0)
		{
			swapped = 1;
		}
		else
		{
			uniform_int_distribution<>dis(1, limit);
			swapped = dis(gen);
		}
		limit--;
		Card c1 = get_item(list, swapped);
		add_last(hand, c1.rank, c1.suit);
	}
}

void Reset()
{
	score = 0;
	trips = false;
	quads = false;
	onePair = false;
	hFlush = false;
	hStraight = false;
	rFlush = false;
	fh = false;
	//Move current cards from hand to discard pile
}

void Options()
{
	cout << endl;
	cout << "Enter the Alphabets of the cards you want to discard" << endl;
	cout << "To see which cards remain in the deck type DECK" << endl;
	cout << "To swap cards directly type SWAP" << endl;
	cout << "To quit program type EXIT" << endl;
}

void Destroy(linked_list* list)
{
	Card* n = list->head;
	while (n != nullptr)
	{
		Card* temp = n;
		n = n->next;
		delete temp;
	}
	delete list;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);


	for (int i = 0; i < 4; i++)
	{
		char su;
		if (i == 0)
		{
			su = 'C';
		}
		else if (i == 1)
		{
			su = 'D';
		}
		else if (i == 2)
		{
			su = 'H';
		}
		else if (i == 3)
		{
			su = 'S';
		}
		for (int j = 1; j <14; j++)
		{
			add_last(list, j, su);
		}
	}
	print_items(list);
	cout << "-------------------Let's Play--------------------------";
	//Deal Hand
	DealHand();
	do {

		//Option Statements
		Options();
		bool user = true;
		//Swap from Hand
		do
		{
			cout << endl << endl;
			cout << "Please enter which cards you wish to discard ";
			string swap;
			bool hasInt = false;
			cin >> swap;  //make sure input is only characters
			hasInt = swap.find_first_of("0123456789") != string::npos;
			swap = swap.substr(0, 5);
			int strLmt = swap.length();
			for (int i = 0; i < strLmt; ++i)
			{
				for (int j = 0; j < strLmt - i - 1; ++j)
				{
					if (swap[j] > swap[j + 1])
					{
						swap[j] = swap[j] + swap[j + 1];
						swap[j + 1] = swap[j] - swap[j + 1];
						swap[j] = swap[j] - swap[j + 1];
					}
				}
			}
			for (int i = 0; i < strLmt; i++)
			{
				inputLim = inputLim + swap[i];
			}

			if (swap == "cdek" || swap == "CDEK")
			{
				print_items(list);
			}
			//Swap Feature
			else if (swap == "apsw" || swap == "APSW")
			{
				print_items(list);
				cout << "-----------------" << endl;
				print_items(hand);

				int changeD, changeH;
				char cont;
				do
				{
					cout << "Enter the number from the deck and the number from the hand you want to exchange with" << endl;
					cin >> changeD >> changeH;
					if (changeD <= check_list(list) && changeH <= 5)
					{
						Card dc = get_item(list, changeD);
						add_last(hand, dc.rank, dc.suit);

						Card cd = get_item(hand, changeH);
						add_last(list, cd.rank, cd.suit);
					}
					else
					{
						cout << "Enter the correct numbers" << endl;
					}
					cout << endl << endl;
					print_items(list);
					cout << "------------------" << endl;
					print_hand(hand);
					cout << "Press y to swap again" << endl;
					cin >> cont;
				} while (cont == 'y');

			}

			else if (swap == "eitx" || swap == "EITX")
			{

				Destroy(list);
				list = nullptr;
				Destroy(hand);
				hand = nullptr;
				Destroy(discard);
				discard = nullptr;

				return 0;
			}

			else if (!hasInt&& (inputLim>65 && inputLim<335))  //sum of ascii input is between 65-335 
			{
				int handLim = 5;
				int swapNo = swap.length();
				int thisCard = 0;
				for (int i = 0; i < swapNo; i++)
				{
					if (swap[i] == 'A' || swap[i] == 'a')
					{
						thisCard = 1;
					}
					else if (swap[i] == 'B' || swap[i] == 'b')
					{
						thisCard = 2;
					}
					else if (swap[i] == 'C' || swap[i] == 'c')
					{
						thisCard = 3;
					}
					else if (swap[i] == 'D' || swap[i] == 'd')
					{
						thisCard = 4;
					}
					else if (swap[i] == 'E' || swap[i] == 'e')
					{
						thisCard = 5;
					}

					thisCard = thisCard - (5 - handLim);

					Card dc = get_item(hand, thisCard);
					add_last(discard, dc.rank, dc.suit);
					handLim--;
				}

				for (int j = 0; j < swapNo; j++)
				{
					uniform_int_distribution<>dis(1, limit);
					limit--;
					int swapped = dis(gen);
					Card c1 = get_item(list, swapped);
					add_last(hand, c1.rank, c1.suit);
				}
				cout << "You kept " << 5 - swapNo << " cards. Your new hand is: " << endl;
				cout << "---------------------" << endl;
				print_hand(hand);
				cout << "-------------------" << endl;
				print_items(discard);
				user = false;
				inputLim=0;
			}
			else
			{
				cout << "Please enter valid characters" << endl;
				user = true;
				inputLim=0;
			}
		}while (user);


		CheckHand();
		Reset();
		NewHand();
//		print_items(list);
		cout << "Your new hand is:" << endl;
		print_hand(hand);
//		print_items(discard);

	} while (cash != 0);
		
	if (cash == 0)
	{
		cout << "You're broke. Come back again." << endl;

		Destroy(list);
		list = nullptr;
		Destroy(hand);
		hand = nullptr;
		Destroy(discard);
		discard = nullptr;
	}

	system("Pause");
	return 0;
}

