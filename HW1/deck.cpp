/* 
	Paolo Villanueva
	CS202 - HW1 - Go fish
	Spring 2015
	deck.cpp
	
	The purpose of this moedule is to construct a deck for the game.

	All functions for Deck, Card, and node are here. Deck uses 4 doubly 
	linked list for data structure. 
		*Card class:
			Use to represent a single card which contains a number
			and a suit. Card class contains a get functions which 
			gets the value of the number and the suit. It also 
			has setter functions for both data members. Card 
			can display the data and has some comparison functions. 

		*node
			A node is derived from Card. This is used to create 
			an array of double linked list for the deck
			A node has a pointer to the next and previous node. It has 
			a setter (next, previous, and for card object) and a getter 
			function for getting the data of the card. 

		*Deck
			Use to represent a deck of the game. Deck has an insert
			function for putting a node in the data structure, a function
			that draws a card from the deck. It has isplay a particular 
			number or all the cards in the deck. It can shuffle and check
			if the deck is empty. 
			Deck has dynamic arrays of cards which construct the
			 ordered set of cards. Shuffle function shuffles that array
			instead of the DLL. My reason is that I feel like it is 
			easier to implement and more efficient. Deck also contains
			double pointer which can create the 4 doubly linked list.
*/

#include "deck.h"


//Constructor sets up the deck 
//INPUT: nothign
//OUTPUT: generates the deck
Deck::Deck()
{
	card_ = NULL;
	head = NULL;
	card_ = new Card[52]; //create 52 dynamically allocated instances of Cards
	head = new node*[4]; //create 4 doubly linked list dynamically
	//Generate the deck with the 52 cards. 
	for(int i = 1; i <= 52; ++i)
	{
		//index 1 to 13 creates the diamond suit set
		
		if(i <= 13)
		{
			//i-1 because i starts at 1 and we want to store
			//it in index 0 first
			card_[i-1].set_num(i);
			card_[i-1].set_suit('D');
		}
		//index 14 to 26 creates the spades suit set
		else if(i > 13 && i <= 13*2)
		{
			card_[i-1].set_num(i-13);
			card_[i-1].set_suit('S');
		}
		//creates the clubs suit set
		else if(i > 13*2 && i <= 13*3)
		{
			card_[i-1].set_num(i-(13*2));
			card_[i-1].set_suit('C');
		}
		//creates the hearts set
		else
		{
			card_[i-1].set_num(i-(13*3));
			card_[i-1].set_suit('H');
	
		}
		
	
	}
	shuffle(); //this shuffles the arrays of dynamically allocated cards.

	/*
	//constructs the head pointers of each DLL 
	for(int i = 0; i < 4; i++)
	{
		head[i] = new node();
	} */
	//add data to the head
	//I decided to do it this way because of valgrind issue saying the this is 
	//uninitialised 
	/*
	head[0] -> set_card(card_[0]);
	head[1] -> set_card(card_[13]);
	head[2] -> set_card(card_[13*2]);
	head[3] -> set_card(card_[13*3]);
	*/
	for(int i = 0; i < 4; ++i)
		head[i] = NULL;
	
	head[0] = new node(card_[0]);
	head[1] = new node(card_[13]);
	head[2] = new node(card_[13*2]);
	head[3] = new node(card_[13*3]); 
	//add data to the rest but ignore 0 and any divisible by 13. 
	//this gives each arrays 13 cards each but shuffled. 
	//REASON why I chose this method is because I feel like it is easier
	//to implement and more efficient rather than traversing to a random number 
	//each time to shuffle it.
	for(int i = 0; i < 52; i++)
	{
		//ignore 0 and any number divisible by 13
		if(i == 0 || i % 13 == 0)
		{}
		else if(i <= 13) 
			insert(head[0], card_[i]);
		else if(i > 13 && i <= 13*2)
			insert(head[1], card_[i]);
		else if(i > 13*2 && i <= 13*3)
			insert(head[2], card_[i]);
		else
			insert(head[3], card_[i]);

	}
	//delete [] card_;
	//card_ = NULL;

}

//copy constructor creates DLL and the  dynamically allocated arrays of cards
//input: Instance of the class Deck
//ouput: copies all the data
Deck::Deck(const Deck & deck_)
{
	head = new node*[4]; //creates 4 DLLs

	//copies the data by calling copy_all function
	for(int i = 0; i < 4; ++i)
	{
		copy_all(head[i], deck_.head[i]);
	}

	//creates 52 instances of cards and copy all data
	card_ = new Card[52];
	for(int i = 0; i < 52; ++i)
	{
		card_[i].set_num(deck_.card_[i].get_num());
		card_[i].set_suit(deck_.card_[i].get_suit());
	}
}

//non recursive copy all DLL
//I attempted it, but I failed....but this works
//INPUT: node destination and source
//OUTPUT: copies all the data in the source to the destination
void Deck::copy_all(node *& dest, node * source)
{
	//if source is NULL, set your destination to null
	if(source == NULL)
	{	
		dest = NULL;
		return;
	}

	//copies every node from the source to dest
	while(source != NULL)
	{
		if(dest == NULL)
			dest = new node(*source);
		node * temp = new node(*source);
		temp -> set_next(dest);
		source = source -> get_next();
		temp = NULL;
	}

}

//Destructor 
//INPUT: no input
//Ouput: Dealloctes all dynamic memory
Deck::~Deck()
{

	//deallocates card pointer
	delete [] card_ ;
	card_ = NULL;

	//deallocates the arrays of DLLs
	node * current;
	for(int i = 0; i <4 ; i++)
	{
		current = head[i];
		/*
		while(current != NULL)
		{
			temp = current;
			current -> set_previous(NULL);
			current = current -> get_next();
			delete temp;
			//temp -> set_next(NULL);
			temp = NULL;	
		} */
		while(head[i] != NULL)
		{
			current = current -> get_next();
			current -> set_previous(NULL);
			head[i] -> set_next(NULL);
			delete head[i];
			head[i] = NULL;
			head[i] = current;
		}

	}
	//delete current;
	delete [] head;
	head = NULL;
	current = NULL;
	//delete current;
	//delete temp;
}

//shuffles the arrays of objects of Cards
//INPUT: no input
//OUTPUT: shuffled "deck" 
void Deck::shuffle()
{
	int a = 0; //store RNG a
	int b = 0; //store RNG b
	srand(time(NULL)); //generate seed

	//makes sure that the 0 index will get shuffled
	b = rand() % 52 ;
	Card first(card_[a]);
	card_[a].set_num(card_[b].get_num());
	card_[a].set_suit(card_[b].get_suit());
	card_[b].set_num(first.get_num());
	card_[b].set_suit(first.get_suit());
	
	//loop this many of times to make sure that it is completely  randomized
	for(int i = 0; i < 500; ++i)
	{
		a = rand() % 52;
		b = rand() % 52;
		Card temp(card_[a]);
		card_[a].set_num(card_[b].get_num());
		card_[a].set_suit(card_[b].get_suit());
		card_[b].set_num(temp.get_num());
		card_[b].set_suit(temp.get_suit());
	}
	/*
	for(int i = 0; i < 52; ++i)
		cout << card_[i].get_num() << card_[i].get_suit() << endl;
	*/
}

//display all the stored data in the DLL
//INPUT: nothing
//OUPUT: displays all data in the deck
void Deck::display_all()
{

	for(int i = 0; i < 4; i++)
	{
		node * temp = head[i];
		while(temp != NULL)
		{
			temp -> display();
			temp = temp -> get_next();		
		}
		cout << endl << endl;
		temp = NULL;
		delete temp;
	}
}

//attach a Card object to a node and sets up DLL structure
//INPUT: node called current and instance of Card class caled card_
//OUTPUT: Attaches the card to a node and inserts the node at the beginning of the DLL
void Deck::insert(node *& current, Card & card_)
{
	
	if(current == NULL)
	{
		current = new node(card_);
	} 
	else
	{
		node * temp =  new node(card_);
		//node * temp = new node();
		//temp  -> set_card(card_);
		temp -> set_next(current);
		temp -> set_previous(NULL);
		current -> set_previous(temp);
		current = temp;
		temp = NULL;
		//delete current;
		delete temp;
	}
}

//Draws a card from a deck.
//INPUT: Card object which has default data
//OUTPUT: Get the data and remove that node from the deck
void Deck::draw(Card & empty)
{
	node * temp; //temp node pointer

	//checks all indecies 
	for(int i = 0; i < 4; i++)
	{
		//do this until the DLL is empty then go to the next index
		while(head[i] != NULL)
		{
			//get data and put it in an empty Card object
			head[i] -> get_card(empty);
			//deletes that node
			temp = head[i];
			head[i] = head[i] -> get_next();
			head[i] -> set_previous(NULL);
			temp -> set_next(NULL);
			return;
		}
	}
	temp = NULL;
	delete temp;
}

//check if the deck is empty
//INPUT: nothing
//OUPUT: Returns 1 if it's empty, otherwise 0;
int Deck::is_empty()
{
	//head[3] because 4 is not being used. for '\0'
	if(head[3] == NULL)
		return 1;
	return 0;
}

//sets pointers to NULL
node::~node()
{
	next = previous = NULL;

}

//get the next pointer
//INPUT: nothing
//OUTPUT: returns next node
node * node::get_next()
{
	return next;
}

//get the previous pointer
//INPUT: nothing
//OUTPUT: returns previous node
node * node::get_previous()
{
	return previous;
}


//Get the data and store it to an empty Card object
//INPUT: Card object
//OUTPUT: Get the data and store it in an empty card
void node::get_card(Card & empty)
{
	empty.set_num(number); 
	empty.set_suit(suit);

}

//constructor
node::node(): Card(), next(NULL), previous(NULL)
{
	//next = NULL;
	//previous = NULL;
}

//constructor
//Input: Card object
//OUTPUT: Another way to attach data to a node
node::node(Card & card_):  Card(card_), next(NULL), previous(NULL) 
{


}


//Set the next node (connect)
//INPUT: node pointer 
//OUTPUT: connect the input to the DLL
void node::set_next(node * next_)
{
	if(next_ == NULL)
		next = NULL;
	else
		next = next_;

}
//Set the previous node
//INPUT: node pointer
//OUTPUT: connect the input to the DLL
void node::set_previous(node * prev)
{
	if(prev == NULL)
		prev = NULL;

	else
		previous = prev;
}

//Set the data to of the card to card_ (input)
//INPUT: Card object with data
//OUPUT: Copy the data of card_ to its own Card object
void node::set_card(Card & card_)
{
	number = card_.get_num();
	suit = card_.get_suit();
}

//Constructor of Card
Card::Card()
{
	number = 0;
	suit = 'z';
}

//Destructor of Card class
Card::~Card()
{
	number = 0;
	suit = '\0';
}
/*
Card::Card(char suit_, int num_)
{

	suit = suit_;
	number = num_;
}
*/

//Sets number to num_ 
//INPUT: integer
//OUTPUT: Sets the number to num_
void Card::set_num(int num_)
{
	number = num_;
}


//Set the suit to suit_
//INPUT: single char
//OUTPUT: set the suit value to the input
void Card::set_suit(char suit_)
{
	suit = suit_;
	//strcpy(suit, suit_);
}


//returns number of the card
//INPUT: nothing
//OUTPUT: number of the card
int Card::get_num()
{
	return number;
}

//returns the suit 
//INPUT: nothing
//OUTPUT: returns a char 
char Card::get_suit()
{
	return suit;

}	

//Display the card
//INPUT: nothin
//OUTPUT: displays the card 
void Card::display()
{
	cout << number << suit << " ";
}


//Compare if both numbers of the card are equal
//INPUT: object called card_
//OUTPUT: returns 1 if it's the same, otherwise it returns 0
int Card::equal_to(const Card & card_)
{
	if(number == card_.number)
		return 1;
	return 0;


}

//Compare if the number of the  card is greater than the number of the card_
//INPUT: object called card_
//OUTPUT: returns 1 if it is greater, returns 2 if it's the same, returns 0 it fails
int Card::is_greater(const Card & card_)
{
	if(number > card_.number)
		return 1;
	else if(number == card_.number)
		return 2;
	return 0;
}

//Compare if the nubmer of the card is less than the number of card_
//INPUT: object called card_
//OUTPUT: returns 1 if it is lesser, returns 2 if it's equal, returns 0 if it fails
int Card::is_less(const Card & card_)
{
	if(number < card_.number)
		return 1;
	else if(number == card_.number)
		return 2;
	return 0;
}

//check if the card is equal to the number that is being asked
//INPUT: a number
//OUTPUT: returns 1 if they are equal and returns 0 if not.
int Card::find_num(int num)
{
	if(number == num)
		return 1;
	return 0;
}
