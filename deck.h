/*
	Paolo Villanueva
	CS202 - HW1 - Go Fish!
	Spring 2015
	deck.h

	The purpose of this header file is to construct a deck for the 
	game. This header contains these classes:
		*Card
			Use to Represent an instance of a single card.
			A card contains a number and a suit. 
		*node
			A node is a Card. This is used to create an array 
			of doubly linked list (DLL) for the deck.
		*Deck
			Use to represent a deck of the game. It contains 52 
			(Dynamically allocated array) instances of Card class.
			The data structure contains 4 arrays of doubly linked list.
			The class can shuffle the deck, display all, display a number, 
			draw a card, insert a card to DLL, check if the deck is empty,
			and a copy constructor.
*/

#ifndef DECK00
#define DECK00
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <time.h>
using namespace std;



class Card
{

	public:
		Card(); //default constructor
		~Card(); //destructor
		int get_num(); //get the number of the card
		char get_suit(); //get the suit letter
		void set_num(int num_); //set the number
		void set_suit(char suit_); //set the suit 
		void display();	//display the card (number and suit)
		int equal_to(const Card & card_);
		int is_greater(const Card & card_);
		int is_less(const Card & card_);
		int find_num(int num);
	
	protected:
		int number;
		char  suit;

};


class node: public Card
{
	public:
		node(); 
		node(Card & card_); 
		~node();
		void set_next(node * next_); //set the next node
		void set_previous(node * prev); //set the previous node
		void set_card(Card & card_); //set the card
		void get_card(Card & empty); //get the card
		node * get_next(); //get next node
		node * get_previous(); //get next node

	protected:
		node * next;
		node * previous;
};

class Deck
{
	public:
		Deck();
		~Deck();
		Deck(const Deck & deck_); //copy cons
		void insert(Card & card_); //insert card to a node wrapper
		void draw(Card & empty); //draw a card
		void display(int num); //display card based on num
		void display_all(); //display all cards
		void shuffle(); //shuffle the deck
		int is_empty(); //check if it's empty
	protected:
		void insert(node *& current, Card & card_); //insert card to a node
		void copy_all(node *& dest, node * source); //copy list
		Card * card_; //use to create temporary deck 
		node ** head;
};

#endif
