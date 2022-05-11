/*
* Programmer: Christoffer Willander								Date completed: Jan 5th, 2019
* Instructor: Johanna Törnquist Krasemann, Marie Netz		    Class: DV1490
*
* Offline scheduling program (First fit decreasing, Best fit decreasing)
* 
* 
*/

#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
private: // Private nested class Node
	class Node
	{
	public:
		Node();
		virtual ~Node();
		T dataContent;
		Node* next;
	};

private: // Private member variables
	int nrOfNodes;
	Node *first, *last;

private: // Private member functions
	// Help function - used for finding a node at a given index
	Node* traverse(int toIndex) const;

	// Help function - used for destructor & operator =
	void freeMemory();

	// Help functions - used for insertAt
	void insertFirst(const T& element);
	void insertLast(const T& element);
	void insertAtIndex(const T& element, int index) const;

	// Help functions - used for removeAt & removeElement
	void deleteFirst();
	void deleteLast();
	void deleteAtIndex(int index);

public: // Public member functions
	List();
	virtual ~List();
	List(const List& other);
	List& operator = (const List& other);
	void insertAt(int pos, const T& element) throw(...);
	T getAt(int pos) const throw(...);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	int length() const;
	void getAll(T arr[], int cap) throw(...);
};

// Public member function definitions

template <typename T>
List<T>::Node::Node()
{
	this->next = nullptr;
}

template <typename T>
List<T>::Node::~Node()
{

}

template <typename T>
List<T>::List()
{
	this->nrOfNodes = 0;
	this->first = nullptr;
	this->last = nullptr;
}

template <typename T>
List<T>::~List()
{
	this->freeMemory();
}

template <typename T>
List<T>::List(const List<T>& other)
{
	int indexCounter = 0;

	this->first = nullptr;
	this->last = nullptr;
	this->nrOfNodes = 0;

	Node* walker = other.first;

	while (walker != nullptr)
	{
		this->insertAt(indexCounter, walker->dataContent);
		
		walker = walker->next;
		indexCounter++;
	}
}

template <typename T>
List<T>& List<T>::operator = (const List<T>& other)
{
	if (this != &other)
	{
		int indexCounter = 0;

		this->freeMemory();

		Node* walker = other.first;

		while (walker != nullptr)
		{
			this->insertAt(indexCounter, walker->dataContent);

			walker = walker->next;
			indexCounter++;
		}
	}

	return *this;
}

template <typename T>
void List<T>::insertAt(int pos, const T& element)
{
	if (!(pos >= 0 && pos <= this->nrOfNodes)) // If the chosen position for insertion is out of bounds
	{
		throw ("The chosen position for insertion is out of bounds - please try again");
	}

	if (pos == 0) // Insert element in the beginning of the list
	{
		this->insertFirst(element);
	}
	else if (pos > 0 && pos < this->nrOfNodes) // Insert element at given position in the list
	{
		this->insertAtIndex(element, pos);
	}
	else if (pos == this->nrOfNodes) // Insert element in the end of the list
	{
		this->insertLast(element);
	}

	this->nrOfNodes++;
}

template <typename T>
T List<T>::getAt(int pos) const
{
	if (!(pos >= 0 && pos < this->nrOfNodes)) // If the chosen position for data retrieval is out of bounds
	{
		throw ("The chosen position for data retrieval is out of bounds - please try again");
	}

	Node* walker = this->traverse(pos);

	return walker->dataContent;
}

template <typename T>
void List<T>::removeAt(int pos)
{
	if (!(pos >= 0 && pos < this->nrOfNodes)) // If the chosen position for deletion is out of bounds
	{
		throw ("The chosen position for deletion is out of bounds - please try again");
	}

	if (pos == 0) // If the element to be deleted is the first
	{
		this->deleteFirst();
	}
	else if (pos > 0 && pos < (this->nrOfNodes - 1)) // If the element to be deleted is somewhere inbetween the first and last
	{
		this->deleteAtIndex(pos);
	}
	else if (pos == (this->nrOfNodes - 1) && pos != 0) // If the element to be deleted is the last
	{
		this->deleteLast();
	}

	this->nrOfNodes--;

	if (this->nrOfNodes == 0)
	{
		this->first = nullptr;
		this->last = nullptr;
	}
}

template <typename T>
bool List<T>::removeElement(const T& element)
{
	bool deletionPerformed = false;
	Node* walker = this->first;

	for (int i = 0; i < this->nrOfNodes && !deletionPerformed; i++)
	{
		if (walker->dataContent == element)
		{
			this->removeAt(i);
			deletionPerformed = true;
		}

		walker = walker->next;
	}

	return deletionPerformed;
}

template <typename T>
bool List<T>::findElement(const T& toFind) const
{
	bool foundElement = false;

	Node* walker = this->first;

	while (walker != nullptr && !foundElement)
	{
		if (walker->dataContent == toFind)
		{
			foundElement = true;
		}

		walker = walker->next;
	}

	return foundElement;
}

template <typename T>
int List<T>::length() const
{
	return this->nrOfNodes;
}

template <typename T>
void List<T>::getAll(T arr[], int cap)
{
	if (cap < this->nrOfNodes)
	{
		throw "The capacity of the given array is insufficient - please try again";
	}

	Node* walker = this->first;

	for (int i = 0; i < this->nrOfNodes && walker != nullptr; i++)
	{
		arr[i] = walker->dataContent;
		walker = walker->next;
	}
}


//Private member function definitions

template <typename T>
typename List<T>::Node* List<T>::traverse(int toIndex) const
{
	Node* walkerPtr = this->first;

	for (int i = 0; i < toIndex; i++)
	{
		walkerPtr = walkerPtr->next;
	}

	return walkerPtr;
}

template <typename T>
void List<T>::freeMemory()
{
	Node* walker = this->first;
	Node* temp = nullptr;

	while (walker != nullptr)
	{
		temp = walker;
		walker = walker->next;

		if (temp != nullptr)
		{
			delete temp;
		}
	}

	this->first = nullptr;
	this->last = nullptr;
	this->nrOfNodes = 0;
}

template <typename T>
void List<T>::insertFirst(const T& element)
{
	Node* temp = nullptr;

	if (this->first == nullptr)
	{
		temp = new Node;
		temp->dataContent = element;

		this->first = temp;
		this->last = temp;
	}
	else
	{
		temp = new Node;
		temp->dataContent = element;
		temp->next = this->first;
		
		this->first = temp;
	}
}

template <typename T>
void List<T>::insertLast(const T& element)
{
	Node* temp = nullptr;

	temp = new Node;
	temp->dataContent = element;
	this->last->next = temp;
	this->last = temp;
}

template <typename T>
void List<T>::insertAtIndex(const T& element, int index) const
{
	Node* temp = nullptr;
	Node* walker = this->traverse(index - 1);

	temp = new Node;
	temp->dataContent = element;

	temp->next = walker->next;
	walker->next = temp;
}

template <typename T>
void List<T>::deleteFirst()
{
	Node* toDelete = this->first;
	this->first = this->first->next;

	delete toDelete;
}

template <typename T>
void List<T>::deleteLast()
{
	Node* toDelete = this->last;
	Node* walker = this->traverse(this->nrOfNodes - 2);

	this->last = walker;
	this->last->next = nullptr;
	delete toDelete;
}

template <typename T>
void List<T>::deleteAtIndex(int index)
{
	Node* toDelete = this->traverse(index);
	Node* walker = this->traverse(index - 1);

	walker->next = toDelete->next;
	delete toDelete;
}
#endif
