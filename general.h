/* 
	Paolo Villanueva
	CS202 - HW1 - Go Fish
	Spring 2015
	general.h

	The purpose of this file is to gather up all related classes for players. 
	The classes:
		*l_node is derived from Card. l_node is used for sorted linear linked list 
		data structure for the player's hand. Main functions are to set the next
		node, get the data of the card, and setting the value of the card.

		*General is the base class of the players' hierarchy. 
		The purpose is to present what all players can do in the game.
		Its main functions are to be able to draw from the deck,
		display hands, get a card from another player, 
		remove a card from a hand, check for "book", and  check if 
		their hand is empty

		*Computer is derived from General. The goal for class is to represent
		the computer which is the user's opponent for this program.
		It's unique function is to generate random number to ask a player.

		*Player is also derived from General. The purpose is to represent 
		the user. It's unique function is to prompt the user what number
		they want to ask to the computer. 
*/

#ifndef GENERAL00
#define GENERAL00
#include "deck.h"


//l_node - used for linear linked list data structure. l_node is a Card
class l_node: public Card
{
	public:
		l_node(); //constructors
		l_node(Card & card_);
		~l_node(); //destructor
		void set_next(l_node * next_); //set next node
		void set_card(Card & card_); //set the data of the card (both suit and num)
		void get_card(Card & empty); //takes the data and copies 
		l_node * get_next(); //get the next node
	protected:
		l_node * next;

};

//Base class of the players. Each player has a hand	
class General
{
	public:
		General(); //set hand to NULl
		General(const General & copy); //copy constructor for the data struc
		~General(); //destructor 
		void draw(Card & card_); //wrapper 
		//void draw(l_node * temp)
		void display_all(); //display hand
		int get_card(General & general, int num); //get card from another player
		void remove(int num); //remove cards that contains that number
		void book(); //check for 4 sets of numbers to remove from hand
		int is_empty(); //check if hand is empty
		int go_fish(); //Notifies user is there is a go_fish

	protected: 
		l_node * my_hand; //player's hand
		void draw(l_node * temp); //draw a card from either someone's hand or deck
		void copy_all(l_node *& dest, l_node * source); //copy a LLL
};


class Computer: public General
{
	public:
		Computer(); 
		int decision(); //Use for deciding what number the computer will ask
				//the user

};

class Player: public General
{
	public:
		Player();
		int decision(); //prompts the user what number they want to ask the 
				//computer
};


#endif
