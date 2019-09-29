#include <iostream>
#include <cstdlib>


class RBT;

class Node
{
private:
	Node* left;
	Node* right;
	Node* parent;
	int val;
	bool color;//0 for black , 1 for red
	 friend class RBT;
	bool isNIL; //check if itis NIL NODE

public:
	Node();
	Node(int val);
	bool isRed();
	void print();
};

class RBT
{
	private:
		Node* root;
		Node* NIL;

		void leftRotation(Node* &p);
		void rightRotation(Node* &p);
	public:
		RBT();
		RBT(Node* root);
		void insert(int x);
		bool search(int x);
		void erase(int x);
		void print();
};

Node::Node()
{
	this -> val = 0;
	this -> left = NULL;
	this -> right = NULL;
	this -> parent = NULL;
	this -> color = 0;
	this -> isNIL = 0;
}

Node::Node(int val)
{
	this -> val = val;
	this -> left = NULL;
	this -> right = NULL;
	this -> parent = NULL;
	this -> color = 0;
	this -> isNIL = 0;
}


RBT::RBT()
{
	this -> NIL = new Node;
	this -> root = NIL;

	this -> NIL -> parent = this -> NIL;
	this -> NIL -> left = this -> NIL;
    this -> NIL -> right = this -> NIL;
    this -> NIL -> isNIL = 1;
}

RBT::RBT(Node* root)
{
	this -> root = root;
	this -> NIL = new Node;

	this -> root -> parent = this -> NIL;
	this -> root -> left = this -> NIL;
	this -> root -> right = this -> NIL;

	this -> NIL -> parent = this -> NIL;
	this -> NIL -> left = this -> NIL;
    this -> NIL -> right = this -> NIL;
    this -> NIL -> isNIL = 1;
}

bool Node::isRed()
{
	return this -> color;
}


void RBT::leftRotation(Node* &p)
{
	p -> parent -> right = p -> left;  //p 的 parent的right child 接 p 的left child
	p -> left -> parent = p -> parent;

	p -> left = p -> parent; // p的leftChild 接p 的parent

	
    if (p -> parent == p -> parent -> parent -> left)//判斷p的parent是的grandParent的哪個child
    	p -> parent -> parent -> left = p;
    else
        p -> parent -> parent -> right = p; 
    p -> parent = p -> parent -> parent;   //p 的parent 改為 p 的grandParent
    
    p -> parent -> parent = p; //p的原parent的parent設為p

    p -> color = 1;
    p -> left -> color = 0;
    p -> right ->color = 0;

}

void RBT::rightRotation(Node* &p)
{
	p-> parent -> left = p -> right;
	p -> right -> parent = p -> parent;

	p -> right = p -> parent;
    
    if (p -> parent == p -> parent -> parent -> left)
    	{
    		p -> parent -> parent -> left = p;
    	}
    else
    	{
    		p -> parent -> parent -> right = p;
    	}
	p -> parent = p -> parent -> parent;

    p -> parent -> parent = p;

    p -> color = 1;
    p -> left -> color = 0;
    p -> right ->color = 0;
}


void RBT::insert(int x)
{
	if (this -> root == NIL)
	{
		root = new Node(x);
		root -> parent = NIL;
		root -> left = NIL;
		root -> right = NIL;
		return;
	}

	std::cout << "insert:" << x << std::endl;

	Node* present = this -> root;

	while(present != NIL)
	{
		std::cout << "present Node is:" <<std::endl;
		present -> print();

		if (present -> left -> isRed() && present -> right -> isRed())

			{
				std::cout << "Both Points are red." << std::endl;
				present -> color = 1;
				present -> left -> color = 0;
				present -> right -> color = 0;

				if (present -> parent -> isRed())
				{
					if (present == present -> parent -> right) // _R
					{
						if (present -> parent == present -> parent -> parent -> right) //RR
						{
							leftRotation(present -> parent);  
						}

						else//LR
						{
							leftRotation(present -> parent);
							rightRotation(present -> parent); 
						}

					}

				    if (present == present -> parent -> left) // _L
					{
						if (present -> parent == present -> parent -> parent -> left) //LL
						{
							leftRotation(present -> parent);  
						}

						else//RL
						{
							leftRotation(present -> parent);
							rightRotation(present -> parent); 
						}

					}
				}
				
			}

		if (x >= present -> val)
		{
			if (present -> right == NIL)   //LR RR
				{
					present -> right = new Node(x);
					present -> right -> parent = present;
					present -> right -> right = NIL;
					present -> right -> left = NIL; 
					present -> right -> color = 1; //Must Be Red
					

					if (present -> isRed())
					{
						if (present == present -> parent -> right) //RR
						{
							leftRotation(present);
						}

						else //LR
						{
							leftRotation(present -> right);
							rightRotation(present);
						}

						present -> color = 0;
						if (present -> left != NIL)
						{
							present -> color = 1;
						}

						if (present -> right != NIL)
						{
							present -> color = 1;
						}
					}
					return;
					
				}
			else 
				{
					present = present -> right; 
				}
		}

		else
		{
			if (present -> left == NIL) //RL LL
				{
					present -> left = new Node(x);
					present -> left -> parent = present;
					present -> left -> left = NIL;
					present -> left -> right = NIL;
					present -> left -> color = 1; //Must Be Red
					
					if (present -> isRed())
					{
						if (present == present -> parent -> left) //LL
						{
							rightRotation(present);
						}

						else //RL
						{
							rightRotation(present -> left);
							leftRotation(present);
						}

						present -> color = 0;
						if (present -> left != NIL)
						{
							present -> color = 1;
						}

						if (present -> right != NIL)
						{
							present -> color = 1;
						}
					}

					

					return;
				}
			else present = present -> left;
		}

	}	
	this -> root -> color = 0; 

}

bool RBT::search(int x) //就BST.......
{
	if (root == NIL)
	{
		std::cout << x << " Not Found." << std::endl;
		return 0; 
	}
    Node* present = root;

    while(present != NIL)
    {
    	if (x < present -> val)
    	{
    		present = present -> left;
    	}

    	else if (x == present -> val)
    	{
    		std::cout << x << " found!" << std::endl;
    		return 1;
    	}	 

    	else
    	{
    		present = present -> right;
    	}
    }

    std::cout << x << " Not Found." << std::endl;
	return 0;
}

void RBT::erase(int x)
{
	if (root == NIL)
	{
		std::cout << x << " Not Found." << std::endl;
		return ; 
	}
    Node* present = root;

    while(present != NIL)
    {
    	if (x < present -> val)
    	{
    		present = present -> left;
    	}

    	else if (x == present -> val)
    	{
    		present = NIL;
    		return ;
    	}	 

    	else
    	{
    		present = present -> right;
    	}
    }

    std::cout << x << " Not Found." << std::endl;
	return ;
}

void RBT::print()
{
	if (root == NIL) return;

	root -> print();
}

void Node::print()
{
	if (this->isNIL) return ;

	std::cout << "Value :" << this -> val << std::endl \
	          << "color :" << this -> color << std::endl\
	          << std::endl;

	 this -> left -> print();
	 this -> right -> print();

}