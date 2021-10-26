//Red and Black Tree INSERTION program by Siddhartha Bobba
//Period 1, C++

#include <iostream>
#include <cstring>
#include <fstream>

#include "Node.h"

#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define BLUE    "\033[34m"

using namespace std;


struct Trunk {
  Trunk *prev;
  char* string;
  
  Trunk(Trunk *prev, char* string) {
    this -> prev = prev;
    this -> string = string;
  }
};

void HelperTrunk(Trunk *h) {//helper method for printing, used stackoverflow help
  if (h == NULL)
    return;
  
  HelperTrunk(h -> prev);
  
  cout << h -> string;
}


//functions
void ADD(Node* &head, Node* &current, Node*& prev, int value); //done
void READ(Node* &head); //done
void PRINT(Node* root, Trunk *prev, bool isLeft); //done

void parse(char* in, int* mod, int &count);

Node* SEARCH(Node* current, int value);

//functions for deletion

void DELETE(Node* &head, Node* &va);

Node* getSibling(Node* &x);

Node* successor(Node* &x);

Node* replaceNode(Node* &x);

void fixDoubleBlack(Node* &head, Node* &x);

bool hasRedChild(Node* &x);

void swapNodeValues(Node* &u, Node* &v);

//functions for balancing
void Balance(Node* &head, Node* &current); //done

void RotateLeff(Node* &head, Node* &current); //done 
void RotateRite(Node* &head, Node* &current); //done 





//MAIN function
int main() {
  
  //variables
  
  char input[10]; //user input
  char fileinp[10000];  //input for file
  
  int mod[100]; //modified input for insertion
  
  Node* head = NULL;
  
  cout << "This is the Red & Black Tree INSERTION Program." << endl;
  
  bool run = true;
  while (run) {
    
    cout << endl << "You have SIX commands: 'ADD', 'SEARCH', 'FILE', 'PRINT', 'DELETE',  'QUIT'." << endl;
    
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    
    if (input[0] == 'A' && input[1] == 'D' && input[2] == 'D') {
      
      int value;
      
      cout << "Add the value: ";
      cin >> value;
      cin.clear();
      cin.ignore(10000, '\n');
      
      Node* current = head;
      Node* prev = NULL;
      
      ADD(head, current, prev, value);
      
      if(current != head) {
	
        Balance(head, current);
	
      }
      
      cout << endl << value << " has been added:" << endl;
    }
    else if (input[0] == 'F' && input[1] == 'I' && input[2] == 'L' && input[3] == 'E') {
      
      READ(head); 
      
    }
    else if (input[0] == 'P' && input[1] == 'R' && input[2] == 'I' && input[3] == 'N' && input[4] == 'T') {
      
      PRINT(head, NULL, false);
      cout << "Printing..." << endl;
      
    }
    else if (input[0] == 'Q' && input[1] == 'U' && input[2] == 'I' && input[3] == 'T') {
      
      cout << endl << "GOODBYE!" << endl;
      run = false;
      
    }
    else if (input[0] == 'S' && input[1] == 'E' && input[2] == 'A' && input[3] == 'R' && input[4] == 'C' && input[5] == 'H') {
      
      /* int value;
	 
	 cout << ">Input value to search for: ";
	 
	 cin >> value;
	 cin.clear();
	 cin.ignore(10000, '\n');
	 
	 bool ser = SEARCH(head, value);
	 
	 if (ser == true) {
	 cout << value << " is in the tree." << endl;
	 } 
	 else {
	 cout << value << " could NOT be found in the tree." << endl;
	 }
	 }
	 else if (input[0] == 'D' && input[1] == 'E' && input[2] == 'L' && input[3] == 'E' && input[4] == 'T' && input[5] == 'E') {
	 
	 cout << endl << "GOODBYE!" << endl;
	 run = false;
	 
	 }
	 else {
	 cout << endl << "Invalid input. You can try again." << endl;
	 }
	 
	 
	 
	 }
	 return 0; */
      
      int value;
      cout << "Enter the search value: ";
      cin >> value;
      cin.clear();
      cin.ignore(10000, '\n');
      Node* temp = SEARCH(head, value);
      
      if (temp != NULL) {
	cout << endl << value << " is a part of the tree." << endl;
      } 
      else {
	cout << endl << value << " could NOT be found in the tree." << endl;
      }
    }
    
    else if (input[0] == 'D' && input[1] == 'E' && input[2] == 'L' && input[3] == 'E' && input[4] == 'T' && input[5] == 'E') {
      
      while (true) {
	int val = 0;
	cout << ">Input value to delete: ";
	cin >> val;
	cin.clear();
	cin.ignore(10000, '\n');
	bool d = SEARCH(head, val);

	if (d == false) {
	  cout << endl << "Value not found, try agian." << endl;
	}
	else {

	  //find node to be deleted
	  Node* v = head;
	  while (v->getData() != val) {
	    if (val < v->getData()) {
	      v = v->getLeft();
	    } else if (val > v->getData()) {
	      v = v->getRight();
	    }
	  }
	  DELETE(head, v);
	  break;
	}
      }
    }
    else {
      cout << endl << "Invalid input. You can try again." << endl;
    }
  }
}












void ADD(Node* &head, Node* &current, Node*& prev, int value) {
  
  if (head == NULL) {
    
    head = new Node();
    current = head;
    
    head->setData(value);
    head->setColor(0);  //head is always black
    
    return;
  } 
  else {
    
    if (value < current->getData()) {  //lower goes left
      
      prev = current;
      current = current->getLeft();
      
      if (current == NULL) {  //if empty then insert
	
	current = new Node();
	current->setData(value);
	
	prev->setLeft(current);
	current->setParent(prev);
	
	Balance(head, current);  //balance tree
	
	return;
      }
      else {  //if !empty then keep going
	
	ADD(head, current, prev, value);
      }
      
    }
    else {
      prev = current;
      current = current->getRight();  //higher to the right
      
      if (current == NULL) {  //if empty
	
	current = new Node();
	current->setData(value);
	
	prev->setRight(current);
	current->setParent(prev);
	
	Balance(head, current);  //balance tree
	
	return;
	
      }
      else {  //if !empty then keep going
	
	ADD(head, current, prev, value);
	
      }
    }
  }
}

void PRINT(Node* root, Trunk *prev, bool isLeft) { //what a pain...fix later (done)
  
  if (root == NULL) {
  
    return;
  
  }
  
  char* prev_string = (char*)("    ");
  Trunk *trunk = new Trunk(prev, prev_string);
  
  PRINT(root->getLeft(), trunk, true);
  
  if (!prev) {
    trunk -> string = (char*)("----"); //straight
  }
  else if (isLeft) {
    
    trunk -> string = (char*)(".----"); //up
    prev_string = (char*)("   ||"); //transition/extention
  }
  else {
    
    trunk -> string = (char*)("`----"); //down
    prev -> string  = prev_string;
  //r
  }
  
  HelperTrunk(trunk);
  
  if (root->getColor() == 0) {  //black
    cout << BLUE << root->getData() << RESET << endl;
  }
  else {  //red
  
    cout << RED << root->getData() << RESET << endl;
  
  }
  
  if (prev) {
  
    prev -> string = prev_string;
  
  }
  
  trunk -> string = (char*)("   ||");
  
  PRINT(root->getRight(), trunk, false);
}

void READ(Node* &head) {
  
  char in[10000];
  char FileName[100];
  
  int mod[100];
  int siz = 0;
  int count = 0;
  
  
  memset(in, 0, 10000);
  memset(FileName, 0, 100);
  memset(mod, 0, 100);
  //read in the file name
  
  cout << endl << "Enter the name of the file:" << endl << ">> ";
  
  cin.get(FileName, 30);
  cin.clear();
  cin.ignore(100000, '\n');
  
  streampos size;
  ifstream file(FileName, ios::in | ios::binary | ios::ate);
  if (file.is_open()) {
    
    size = file.tellg();
    file.seekg(0, ios::beg);
    file.read(in, size);
    file.close();
    parse(in, mod, count);  //parse input to the modified array
    cout << "IN: ";
    
    for (int i = 0; i < 100; i++) {
      
      if (mod[i] != 0) {

	cout << mod[i] << " ";
	siz++;

      }
    }
    
    cout << endl << "Size: " << siz << endl;;

    //add to tree
    Node* curr = NULL;
    Node* prev = NULL;
  
    for (int i = 0; i < siz; i++) {
  
      if(mod[i] == 0) break;
      curr = head;
      
      ADD(head, curr, prev, mod[i]);
    }
  } 
}


/////////////////////////////////
void rotateLeff(Node* &head, Node* &current) {
  
  Node* rightPtr = current->getRight(); 
  
  //*rotation
  current->setRight(rightPtr->getLeft()); 
  
  if (current->getRight() != NULL) {
    (current->getRight())->setParent(current); 
  }
  
  rightPtr->setParent(current->getParent());
  
  //if working with head
  if (current->getParent() == NULL) {
    head = rightPtr; 
  } 
  else if (current == (current->getParent())->getLeft()) {
    (current->getParent())->setLeft(rightPtr); 
  } 
  else {
    (current->getParent())->setRight(rightPtr); 
  }
  
  rightPtr->setLeft(current); 
  
  current->setParent(rightPtr);
}


void Balance(Node* &head, Node* &current) {
  
  Node* parent = NULL;
  Node* grandparent = NULL;
  
  while ((current != head) && (current->getColor() != 0) &&
	 ((current->getParent())->getColor() == 1)) {
    parent = current->getParent();
    grandparent = parent->getParent();
    
    //Case A: parent = left child of grandparent
    if (parent == grandparent->getLeft()) {
      Node* uncle = grandparent->getRight();
      
      //Case 1: uncle = red, then only recolor    
      if (uncle != NULL && uncle->getColor() != 0) {
	grandparent->setColor(1);//red
	parent->setColor(0);//black
	uncle->setColor(0);//black
	
	current = grandparent;
	
      }
      else {
	
	//Case :: if current is equal to the right child of parent, then rotate to the left
	if (current == parent->getRight()) {
	  
	  rotateLeff(head, parent);
	  
	  current = parent;
	  parent =  current->getParent();
	  
	}
	
	//Case:: if current is the left child of parent, then rotate to the right
	RotateRite(head, grandparent);
	
	//swap colors of parent and grandparent
	int tempC = parent->getColor();
	
	parent->setColor(grandparent->getColor());
	
	grandparent->setColor(tempC);
	
	current = parent;
      }
    }
    //Case :: if parent is the right child of the 'grandparent'
    else {
      Node* uncle = grandparent->getLeft();
      
      //Case:: if uncle is equal to red, then program should recolor
      
      if (uncle != NULL && uncle->getColor() != 0) {
	
	grandparent->setColor(1);//red
	parent->setColor(0);//black
	uncle->setColor(0);//black
	
	current = grandparent;
	
      }
      else {
	
	//Case:: if current is the left child of parent, then rotate to the right
	if (current == parent->getLeft()) {
	  
	  RotateRite(head, parent);
	  current = parent;
	  parent = current ->getParent();
	  
	}
	
	//Case :: if current is the right child of parent, then rotate to the left
	rotateLeff(head, grandparent);
	
	//swap the colors between parent and grandparent
	int tempC = parent->getColor();
	
	parent->setColor(grandparent->getColor());
	
	grandparent->setColor(tempC);
	
	current = parent;
      }
    }
  }
  
  head->setColor(0);
}

void SwapValues(Node* &u, Node* &v) { 
  //swap values between the two nodes

  int temp; 

  temp = u->getData(); 
  u->setData(v->getData()); 
  v->setData(temp); 
}

void DELETE(Node* &head, Node* &v) {
  Node* u = replaceNode(v);
  Node* parent = v->getParent();
  bool bothBlack = ((u==NULL || u->getColor()==0) && (v==NULL || v->getColor()==0));
  
  if (u == NULL) {
    //then v has no children
    if (v == head) {
      //make head null
      head = NULL;
    }
    else {
      if (bothBlack) {
	fixDoubleBlack(head, v);
      }
      else {
	//one is red
	//then sibling = red
	if (getSibling(v) != NULL)
	  getSibling(v)->setColor(1);
      }
      //delete v from the tree
      if (v == parent->getLeft()) {
	parent->setLeft(NULL);
      }
      else {
	parent->setRight(NULL);
      }
    }
    //delete v
    v->~Node();
    return;
  }
  
  //if v = 1 child
  if (v->getRight() == NULL || v->getLeft() == NULL) {
    if (v == head) {
      //assign value of u to v
      v->setData(u->getData());
      v->setLeft(NULL);
      v->setRight(NULL);
      //delete u
      u->~Node();
    }
    else {
      //detach v from tree
      if (v == parent->getLeft()) {
	parent->setLeft(u);
      }
      else {
	parent->setRight(u);
      }
      //delete v
      v->~Node();
      u->setParent(parent);
      if(bothBlack) {
	fixDoubleBlack(head, u);
      }
      else {
	//if one is red, make it black
	u->setColor(0);
      }
    }
    return;
  }
  

  //swap the values with successor and re curse
  SwapValues(u, v);
  DELETE(head, u);
}

Node* getSibling(Node* &v) {
  if (v->getParent() == NULL) {
    return NULL;
  }
  if (v == v->getParent()->getLeft()) {
    return v->getParent()->getRight();
  }
  else {
    return v->getParent()->getLeft();
  }
}


Node* successor(Node* &x) {
  //
  Node* a = x;
  while (a->getLeft() != NULL) {
    a = a->getLeft();
  }
  return a;
}



Node* replaceNode(Node* &x) {
  //if node = 2 children 
  if (x->getLeft() != NULL && x->getRight() != NULL) {
    Node* r = x->getRight();
    return successor(r); 
  }
  //if node = no children 
  else if (x->getLeft() == NULL && x->getRight() == NULL) {
    return NULL;
  }
  //if node = one child 
  else {
    if (x->getLeft() != NULL) { 
      return x->getLeft();
    }
    else {
      return x->getRight();
    }
  }
}


bool hasRedChild(Node* &x) { 
  if (x->getLeft() != NULL && x->getLeft()->getColor() == 1) {
    return true;
  }
  else if (x->getRight() != NULL && x->getRight()->getColor() == 1) {
    return true;
  }
  else {
    return false;
  }
}

void fixDoubleBlack(Node* &head, Node* &x) {
  if (x == head)
    return;
  
  Node* sibling = getSibling(x);
  Node* parent = x->getParent();
  
  if (sibling == NULL) {
    //push double black up
    fixDoubleBlack(head, parent);
  }
  else {
    if (sibling->getColor() == 1) {
      //red
      parent->setColor(1); //red
      sibling->setColor(0); //black
      if (sibling == parent->getLeft()) {
	RotateRite(head, parent);
      }
      else {
	rotateLeff(head, parent);
      }
      fixDoubleBlack(head, x);
    }
    else {
      //black
      if (hasRedChild(sibling)) {
	//has at least 1 red child
	if (sibling->getLeft() != NULL && sibling->getLeft()->getColor() == 1) {
	  //left child red
	  if (sibling == parent->getLeft()) {
	    //left left
	    sibling->getLeft()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    RotateRite(head, parent);
	  }
	  else {
	    //right left
	    sibling->getLeft()->setColor(parent->getColor());
	    RotateRite(head, sibling);
	    rotateLeff(head, parent);
	  }
	}
	else {
	  //right child is red
	  if (sibling == parent->getLeft()) {
	    //left right
	    sibling->getRight()->setColor(parent->getColor());
	    rotateLeff(head, sibling);
	    RotateRite(head, parent);
	  }
	  else {
	    //right right
	    sibling->getRight()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    rotateLeff(head, parent);
	  }
	}
	parent->setColor(0); //black
      }
      else {
	//two black children
	sibling->setColor(1); //red
	if (parent->getColor() == 0) {
	  fixDoubleBlack(head, parent); //recursion
	} else {
	  parent->setColor(0); //black
	}
      }
    }
  }
}


void parse(char* in, int* mod, int &count) {

  int l = 0;  //keeps track of # of chars before space

  for (int i = 0; i < strlen(in); i++) {

    if (in[i] == ' ') {

      if (l == 1) {

	int temp = 0;

	temp = in[i-1] - '0';
	mod[count] = temp;
	count++;
	l = 0;
      }
      else {

	int temp = 0;

	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i-l+a] - '0');
	}

	mod[count] = temp;
	count++;
	l = 0;

      }
      
    } else {

      int temp = 0;
      l++;

      if (i == strlen(in) - 1) {  //last possible pair of chars

	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i+a+1-l] - '0');
	}

	mod[count] = temp;
	count++;

      }
    }
  } 
}


void RotateRite(Node* &head, Node* & current) {

  Node *leftPointer = current->getLeft(); 
  
  //start rotation
  
  current->setLeft(leftPointer->getRight()); 
  
  
  if (current->getLeft() != NULL) {
    (current->getLeft())->setParent(current); 
  }  
  leftPointer->setParent(current->getParent());
  
  
  if (current->getParent() == NULL) {
    head = leftPointer; 
  }
  else if (current == (current->getParent())->getLeft()) {
    
    (current->getParent())->setLeft(leftPointer); 
    
  }
  else {
    
    (current->getParent())->setRight(leftPointer);
    
  }
  
  leftPointer->setRight(current); 
  current->setParent(leftPointer);
  
}

/* bool SEARCH(Node* current, int value) {
   
   if (value == current->getData()) {
   return true;
   }
   else if (value < current->getData()) {  //lower goes left
   if (current->getLeft() != NULL) {
   SEARCH(current->getLeft(), value);  //recursion
   } else {
   return false;
   }
   }
   else {  //higher goes right
   if (current->getRight() != NULL) {
   SEARCH(current->getRight(), value);  //recursion
   } else {
   return false;
   }
   }
   return false;
   } */

//SCRAPPED CODE AND USED BST SEARCH CODE BECAUSE OF ERRORS

Node* SEARCH(Node* current, int value) {
  
  if (value == current ->getData()) {
    return current;
  }
  
  else if (value < current ->getData()) {  //lower to left
    
    if (current ->getLeft() != NULL) {
      
      return SEARCH(current ->getLeft(), value);  //recursive search
      
    } 
    else {
      return NULL;  //no lower
    }
  } 
  else {  //higher goes right
    
    if (current ->getRight() != NULL) {
      return SEARCH(current ->getRight(), value);
      
    }
    else {
      
      return NULL;  //no higher
    }
  }
  return NULL;
}

