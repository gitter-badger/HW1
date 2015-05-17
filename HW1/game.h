/****
	Paolo Villanueva
	CS202 HW1 -GO FISH!
	Spring 2015 
	game.h

	The purpose of this file is to connect together all the important  classes 
	that are needed to construct this game: Player class, Computer class, 
	and Deck class. 
****/
#ifndef GAME00
#define GAME00
#include "general.h"
#include "deck.h"


class Game
{
	public:
		//constructor -- lets players draw a card from the deck.
		Game(); 

		/*This is the core of the entire program. This function 
		starts the game and does how the game plays. 
	
		First, this function will let the user read the rules of the game. 
		Once the user is ready, they have to press 'Enter' to start
		playing. God mode is included to see your opponents hand. 
		Use it to your advantage.
		
		*/
		void play();
		
		/*
		Be able to draw a card from the deck
		*/
		void draw(General & player);
		
		/*Let the user of this program be able to see the computer's hand.	
		*/
		void God_mode();
	protected:
		/*Objects */
		Player player; 
		Computer computer;
		Deck deck;
};


#endif
