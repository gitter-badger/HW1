/*	
	Paolo Villanueva
	CS202 HW1 - Go Fish
	Spring 2015
	game.cpp
	
	Function implementations are here. The purpose of this class is to 
	connect all important classes (Player, Computer, and Deck) to create 
	the game. 

*/


#include "game.h"


//Game class constructor. This is to start having each player draw 7 cards from the deck.
Game::Game()
{

	//draw 7 cards 
	for(int i = 0; i < 7; ++i)
	{
		draw(player);
		draw(computer);
	}
}


/*This is the core of the program. This function starts the game and follows 
how the game plays. 
		*First, the function asks the user to press 'Enter' to play the game
		*Next, this will show how the game plays and some legends such as
		 	H stands for the suit Hearts and 11 is the Jack.
		*Once the user is finished, the user must press 'Enter' again to start
			playing the game.
		*The game starts by displaying the user's hand and the user must 
			ask a number to the computer. If the computer has that number,
			the computer will give all their cards that contains that 
			number. The user will keep on going until 
			the computer says 'Go fish' . If the computer does 
			not have that number in their hand, the comptuer will say 
			"Go fish" and the user must draw a card.
		*Once the user's turn is over, the computer will do the same thing.
		*Computer's decision to ask a number is based on Random Number Generator.
Inputs: User input to 'Press Enter to play' twice.
	response = used for god_mode() function to display computer's hand. Y/N question.
	num = user input for asking the computer and store RNG for computer.
	repeat = use for checking the other player's hand if it has that number. 
		If it has that number, other player must give all those cards. 
		This will keep looping until repeat is 0 (which means that their
		hand does not have that particular card).
Output: Output of this function is when one of them wins (empty hand).
*/
void Game::play()
{
	//Ask the press 'Enter' to start the game
	cout << "Press Enter to start the game.";
	cin.ignore(100, '\n');


	char response; //Use for god_mode() funnction. Y/N question
	int repeat = 0; //
	int num; //used for user input for asking a number

	// Game rules
	cout << "***************GO FISH - GAME RULES******************" 
	<< endl << "*Every player will draw 7 cards at the start of game."
	<< endl << "*The user will ask the computer  if they have a particular"
	<< " number." << endl << "*If the player  does not have that number"
	<< " on their hand, the player  will say 'Go fish!'  and player who"
	<< " asked will draw a card." << endl
	<< "*If the player  does have that number, that player must give all"
	<< " the cards with that number to the player who asked  and it will still be the their  turn until opposing player says 'Go fish'" << endl
	<< "*The goal is to get all 4 of a kind (called 'book') and are removed from the hand." << endl
	<< "Player who runs out of cards wins the game!" << endl << endl << endl	
	<< "H = Hearts" << endl << "D = Diamond" << endl << "S = Spades" << endl << "C = Clubs" << endl
	<< "1 = Ace" << endl <<  "11 = Jack" << endl <<  "12 = Queen" << endl << "13 = King" << endl << endl; 
	
	//Press 'Enter' again to start playing
	cout << "Press Enter to start playing the game" << endl;
	cin.ignore(100, '\n');

	//Asking for God mode
	cout << "Would you like God mode on (See Computer's hand!) Y/N?: ";
	cin >> response;
	cin.ignore(100,'\n');
	response = toupper(response);

	//Generate seed for RNG
	srand(time(NULL));

	/*Real game starts here
	Loop stops if one player has an empty hand 
	*/
	cout << endl << endl;
	if(response == 'Y')
		God_mode();
	cout << endl << "Player's hand: " << endl;
	player.display_all();
	cout << endl;
	while((player.is_empty() != 1) && (computer.is_empty() != 1) )
	{
		//display hand 
	//	if(response == 'Y')
	//		God_mode();
	//	cout << endl <<  "Player's hand:" << endl;
	//	player.display_all();
	//	cout << endl << endl;
		//end display

		//Player's turn
		cout << "Player's turn: " << endl;

		//Keeps looking until user fails to take a card from computer
		//and one of the players' hand is empty
		do
		{
			cout << "Ask a number:"; //prompts user for input
			cin >> num;
			cin.ignore(100, '\n');
			repeat = player.get_card(computer, num); //look for that number
						//on the computer's hand
			player.book(); //check for books 
			computer.book();
			cout << endl;
			if(deck.is_empty() == 1)
				cout << """DECK IS EMPTY""" << endl; //notifies that Deck 
							//is now empty. 

			//draw a card if player fails to take a card from computer
			//deck must not be empty
			if(repeat == 0 && deck.is_empty() == 0)
				draw(player);
			cout << endl;
			
			//Display hands		
			if(response == 'Y')
				God_mode();
			cout << endl;
			computer.book();
			player.book();
			cout << "Player's hand: " << endl;
			player.display_all();
			cout << endl;
			//end display hands

		}while(repeat == 1  && player.is_empty() != 1 && computer.is_empty() != 1);
		//End player's turn

		cout << endl << endl;
		//break now if one of the players' have an empty hand
		if(player.is_empty() == 1 || computer.is_empty() == 1)
			break;

		//reset repeat for computer
		repeat = 0;

		//computer's turn
		cout << "Computer's turn: " << endl;
		do
		{
			num = computer.decision(); //generate RN
			cout << ">*Computer: Do you have a #" << num << "?" << endl;
			repeat = computer.get_card(player,num); //look at player's
					//hand for the generated number
			computer.book(); //check for books 
			player.book();
			cout << endl;
			//let computer draw if it fails to get a card from user
			//Deck must not be empty
			if(repeat  == 0 && deck.is_empty() == 0)
				draw(computer);
			//Display hands
			if(response == 'Y')
				God_mode();
			cout << endl;
			computer.book(); //look for books
			player.book();
			cout << "Player's hand: " << endl;
			player.display_all();
			cout << endl;
			//End display 
		}while(repeat == 1 && player.is_empty() != 1 && computer.is_empty() != 1);
		//stopping condition is the same as players' 
	
		player.book(); //check for books and ready for next roudn
		computer.book();
	}

	//Happens when other player has 3 cards left with the same number
	//and player asks for that number. Both players have empty hand
	if(player.is_empty() == 1 && computer.is_empty() == 1)
		cout << endl << endl << "Both players are out of cards!" << endl
		<< "It's a tie!!!!! " << endl;
	//wins if player's hand is empty
	else if(player.is_empty() == 1)
		cout << endl << endl << "Player wins!" << endl;
	else
		cout << endl << endl << "Computer wins!" << endl;
}	


/* Displays the computer's hand for the user's advantage.
Input: No input
Output: Display's computer's hand 
*/
void Game::God_mode()
{
	cout << "Computer's hand: " << endl;
	computer.display_all();
	cout << endl;

}

/* Purpose of this function is to be able to draw a card from the deck
	Input: Player object
	Ouput: New card in their hand
*/

void Game::draw(General & general)
{	
	Card temp; //Create an empty card 
	deck.draw(temp); //draw a card from a deck
	general.draw(temp);	//Player now takes the card to their hand

}


