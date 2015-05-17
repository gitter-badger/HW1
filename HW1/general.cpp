/* 
	Paolo Villanueva
	CS202 - Hw1 - Go Fish
	Spring 2015
	general.cpp

	The purpose of this module is to organize all related classes for players.
	The classes:
		*l_node is derived from Card. l_node is a sorted LLL data structure
		for the player's hand. Main functions are setting next node and 
		card and get data of the card.

		*General is the base class of the players' hierarchy. The purpose
		is to represent what all players can do in the game. General class
		can draw a card from the deck, display all cards in the hand, get
		a card from another player, remove a particular card, check if the
		player's hand is mepty, check for books, and yell go fish.

		*Computer and Player classes represent the players of the game.
		Their unique function is to decide a number 	


*/

#include "general.h"


//constructor

l_node::l_node(): next(NULL)
{
}


//constructor get card and attach to a node
l_node::l_node(Card & card_): Card(card_)
{
	next = NULL;


}


//destructor  
l_node::~l_node()
{
	next = NULL;

}

//Set the next node
//INPUT: l_node 
//OUTPUT: points this node's next pointer to another node
void l_node::set_next(l_node * next_)
{
	if(next_ == NULL)
		next = NULL;
	else
		next = next_;


}

//Copy data from a card object
//INPUT: card object
//OUTPUT: copies data (number and suit) from a card
void l_node::set_card(Card & card_)
{
	number = card_.get_num();
	suit = card_.get_suit();

}


//Get the data of the node and copy it to an empty card obj
//INPUT: card obj with no relevant data
//OUTPUT: Get the data of the card
void l_node::get_card(Card & empty)
{
	empty.set_num(number);
	empty.set_suit(suit);
}


//Get the next node
//INPUT: nothing
//OUTPUT: returns the next node
l_node * l_node::get_next()
{
	return next;

}

//constructor 
//set hands to empty
General::General()
{
	my_hand = NULL;	
}


//General's very own copy constructor
//INPUT: General object
//OUTPUT: calls copy_all function and copies LLL
General::General(const General & copy)
{
	copy_all(my_hand, copy.my_hand);


}

//destructor
General::~General()
{
	l_node * current = my_hand;
	while(current != NULL)
	{
		current = my_hand -> get_next();
		delete my_hand; 
		my_hand = current;
	}	
	delete current;
	my_hand = NULL;
	current = NULL;

}


//copy LLL
//INPUT: destination and source 
//OUTPUT: copies all the data in the LLL
void General::copy_all(l_node *& dest, l_node * source)
{
	if(source == NULL)
	{	
		dest = NULL;
		return;
	}
	while(source != NULL)
	{
		if(dest == NULL)
			dest = new l_node(*source);
		else
		{
			l_node * temp = new l_node(*source);
			temp -> set_next(dest);
			source = source -> get_next();
		}
	}
}

//Getting a card either from deck or someone else
//INPUT: Card object -- wrapper
//OUTPUT: Put it in a node and call the other  draw function 
void General::draw(Card & card_)
{
	l_node * temp = new l_node(card_);
	draw(temp);
	temp = NULL;
}


//Same description as above, get a card from deck or someone else
//INPUT: a node pointer
//OUTPUT: Takes the card and put it on hand which is a sorted LLL
void General::draw(l_node * temp)
{
	//if your hand is empty, you get a card
	if(my_hand == NULL)
	{
		my_hand = temp; //set my_hand node ptr point to the new card 
		my_hand -> set_next(NULL); 
	}

	//if you have one card in your hand
	else if(my_hand -> get_next() == NULL)	
	{	
	
		//comparison greater number means it will be further in the sorted LLL
		//if(my_hand -> get_num() >= temp -> get_num())
		//^ my initial condition, I had to redo because of the requirement
		//Card class must do the comparison
		if(my_hand -> is_greater(*temp) > 0)
		{
			temp -> set_next(my_hand);
			my_hand = temp;
		}	
		else
		{
			my_hand -> set_next(temp);
			temp -> set_next(NULL);
		}
	}
	//more than 2 cards in the hand
	else
	{
		l_node * previous = my_hand;
		l_node * current = my_hand -> get_next();
		/*Is greater than return values: 0 if not greater
 					1 if it's greater
					2 if it's equal
		*/
		//if(my_hand -> get_num() >= temp -> get_num())
		//if your first card is greater or equal to than the new card
		//this means that temp must go first
		if(my_hand -> is_greater(*temp) > 0)
		{
			temp -> set_next(my_hand);
			my_hand = temp;
			previous = my_hand;
			current = my_hand -> get_next();
			return;
		}	
		while(current != NULL)
		{
			//Insert at the end
			if(current -> get_next() == NULL)
			{
				//if(current -> get_num() > temp -> get_num())
				if(current -> is_greater(*temp) == 1)
				{
					temp -> set_next(current);
					previous -> set_next(temp);
					current = temp;
					return;
				}
				else
				{
					current -> set_next(temp);
					temp -> set_next(NULL);
					return;
				}

			}
		//else if(previous -> get_num() <= temp -> get_num() && temp -> get_num()
		//		<= current -> get_num())

			//inserting in between previous and current 
			/*is_less return values: 0 if it's not less than
						1 if it's less than
						2 if it's equal
			*/
			else if(previous -> is_less(*temp) > 0 && 
					temp -> is_less(*current) > 0)
			{
				temp -> set_next(current);
				previous -> set_next(temp);
				current = temp;
				return;
			}
			/*
			else
			{
				temp -> set_next(current -> get_next());
				current -> set_next(temp);
				return ;
			} */
			previous = current;
			current = current -> get_next();	
		}
	
	}
}


//Display player's hand
//INPUT: nothing
//OUPUT: display player's hand 
void General::display_all()
{
	l_node * temp = my_hand;
	while(temp != NULL)
	{
		temp -> display();
		temp = temp -> get_next();

	} 
	temp = NULL;
	delete temp;
}

//Get a card from another player and look for that number
//INPUT: objects derived from General and a number to look those in the hand
//OUPUT:
int General::get_card(General & general, int num)
{

	//If the other player's hand is empty, do nothing.
	if (general.my_hand == NULL)
	{
		cout << "Hand is empty" << endl;
		return 0;
	}
	//important ptr for taking card(s)
	l_node * current = general.my_hand;
	l_node * previous = general.my_hand;
	l_node * temp = NULL; //use to point and store data back to player's hand

	//If there's only one card
	if(current -> get_next() == NULL)
	{
		//if(current -> get_num() == num)
		if(current -> find_num(num) == 1)
		{
			temp = current;	
			draw(temp);
			general.my_hand = NULL;
			return 0;
		}
	}
	//If there's two or more
	else
	{
		//while(current -> get_num() == num)
		//If the first consecutive numbers are the same
		while(current -> find_num(num) == 1)
		{
			temp = current;
			current = current -> get_next();
			previous = current;
			temp -> set_next(NULL);
			general.my_hand = current;
			draw(temp);
			if(current == NULL)
				return 0;
		}
	
		current = current -> get_next();
		while(current != NULL)
		{
			//if(general.my_hand -> get_num() == num)	
			//if the number is on the first hand
			if(general.my_hand -> find_num(num) == 1)
			{
				temp = general.my_hand;
				general.my_hand = temp -> get_next();
				temp -> set_next(NULL);
				draw(temp);
			}
				
			//else if(current -> get_num() == num)
			//anywhere else as long as you find that number
			else if(current -> find_num(num) == 1)
			{
				//while(current -> get_num() == num)
				while(current -> find_num(num) == 1)
				{
					if(current -> get_next() == NULL)
					{
						temp = current;
						previous -> set_next(NULL);
						draw(temp);
						current = NULL;
						return 0;
					}

					else
					{
						temp = current;
						current = current -> get_next();
						previous -> set_next(current);
						temp -> set_next(NULL);
						draw(temp);
					} 
				}
			}
			previous = current;
			current = current -> get_next();
		}
	}
	//If temp is NULL, that means you failed to find that card
	//So go fish!
	if(temp == NULL)
	{
		go_fish();	
		return 0;
	}
	else
	{
		return 1;
	}
}

//Notifies user for Go fishes
//INPUT: nothing
//OUTPUT: display fish
int General:: go_fish()
{
	cout << endl << endl << "***************Go ><(((*)>  *************" << endl <<endl;
	return 0;

}

//Remove all cards that has that number
//INPUT: integer called num
//OUPUT: removes all cards that is equal to num
void General::remove(int num)
{
	//empty hand, return now
	if(my_hand == NULL)
		return;

	l_node * current = my_hand;
	l_node * previous = my_hand;
	//if there's only one card
	if(current -> get_next() == NULL)
	{
		//if(current -> get_num() == num)
		//if it's the same card, delete it
		if(current -> find_num(num) == 1)
		{
			current -> set_next(NULL);
			delete current;
			current = NULL;
			my_hand = NULL;
			return;
		}

	}
	//two or more
	else
	{
		//if(current -> get_num() == num)
		//if it's the first card
		if(current -> find_num(num) == 1)
		{
			current = current -> get_next();
			my_hand -> set_next(NULL);
			delete my_hand;
			my_hand = current;
		}
		//anywhere else 
		else
		{
			current = current -> get_next();
			while(current != NULL)
			{
				//if(current -> get_num() == num)
				if(current -> find_num(num) == 1)
				{
					l_node * temp = current;
					current = current -> get_next();
					previous -> set_next(current);
					delete temp;
					temp = NULL;
				}
				else
				{
					previous = current;
					current = current -> get_next();
				}
			}
		}
	}
	/*
	while(current != NULL)
	{
		current = current -> get_next();
		if(current -> get_num() == num)
		{
			l_node * temp = new l_node();
			temp = current;
			current = current -> get_next();
			previous -> set_next(current);
			delete temp;

		}
		previous = previous -> get_next();
	*/
}

//look for books
//INPUT: nothing
//OUTPUT: If there's 4 cards that has the same number, it will delete all 4 cards 
//from their hand
void General::book()
{
	int counter = 0; //use for counting same numbers. If it hits 4, time for book.
	if(my_hand == NULL) //empty hand, nothing to do
		return;


	l_node * current = my_hand;
	int num = current -> get_num(); //get the first number and start comparing
	while(current != NULL)
	{
		//if(num == current -> get_num())
		if(current -> find_num(num) == 1)
			++counter;
		else
		{
			num = current -> get_num();
			counter = 1;	
		}
		if(counter == 4)
			break;	

		current = current -> get_next();
	}
	if(counter == 4)
	{	
		cout << "************************"
	     		<< "**********BOOOK! #" << num << "*****"
	     		<< "************************" << endl;
		for(int i = 0; i < 4; ++i)
			remove(num);	//calls for remove function 4 times for this number
	
	}
}


//Check if player's hand is empty
//INPUT: nothing
//OUTPUT: returns 1 if it's empty, 0 if not.
int General::is_empty()
{
	if(my_hand == NULL)
		return 1;
	return 0;


}

//constructo 
Player::Player() {}

//Prompts the user to look for a number in computer's hand
//INPUT: none
//OUTPUT: returns that number 
int Player::decision()
{
	int num = 0;
	cout << "Enter a number: " << endl;
	cin >> num;	
	cin.ignore(100, '\n');
	return num;
}
Computer::Computer() {}

//RNG
//INPUT: nothing
//OUTPUT: returns random generated number
int Computer::decision()
{
	//srand(time(NULL));
	int num = (rand() % 13) + 1;	
	return num;
}


