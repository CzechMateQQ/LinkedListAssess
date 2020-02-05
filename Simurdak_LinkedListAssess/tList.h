#pragma once
#include <iostream>
using namespace std;

template <typename T>
class tList
{
	struct Node
	{
		T data;			// Data for the element stored.
		Node * prev;	// Pointer to node following this node.
		Node * next;	// Pointer to node following this node.
		Node()
		{
			prev = nullptr;
			next = nullptr;
		}
		Node(const T& val, Node* pre, Node* nxt)
		{
			data = val;
			prev = pre;
			next = nxt;
		}
	};

	Node * pHead;	// Pointer to fake head of linked list.
	Node * pTail;	// Pointer to fake tail of linked list.

public:

	// Initializes fake head and tail.
	// Also closes list loop by linking tail to head.
	tList()
	{
		pHead = new Node();
		pTail = new Node();
		pHead->next = pTail;
		pTail->prev = pHead;
	}

	// Copy-constructor.
	tList(const tList& original)            
	{
		if (original.pHead->next == nullptr)
		{
			pHead->next = nullptr;
		}
		else
		{
			pHead->next = new Node(original.pHead->next->data, pHead, pHead->next->next);
			Node * current = pHead->next;
			Node * originalCurr = original.pHead->next;
			while (originalCurr->next != pTail)
			{
				current->next = new Node(originalCurr->next->data, pHead, pHead->next->next);
				originalCurr = originalCurr->next;
				current = current->next;
			}
			pTail->prev = current;
		}
	}

	// Copy-assignment.
	tList& operator=(const tList &rhs)
	{
		this->clear();
		this->pHead->next = new Node(rhs.pHead->next->data, pHead, pHead->next->next);
		Node * current = this->pHead->next;
		Node * originalCurr = rhs.pHead->next;
		while (originalCurr->next != rhs.pTail)
		{
			current->next = new Node(originalCurr->next->data, pHead, pHead->next->next);
			originalCurr = originalCurr->next;
			current = current->next;
		}
		current->next = this->pTail;
		pTail->prev = current;
		return *this;
	}

	// Destructor deletes all nodes.
	~tList()                             
	{
		//clear();
		delete(pHead);
		delete(pTail);
	}

	// Adds element to front (i.e. head).
	void push_front(const T& val)
	{
		Node * oldHead = pHead->next;
		Node * n = new Node(val, pHead, oldHead);
		pHead->next = n;

		if (oldHead != pTail)
		{
			oldHead->prev = pHead->next;
		}
		if (pTail->prev == pHead)
		{
			pTail->prev = pHead->next;
		}
	}

	// Removes element from front.
	void pop_front()
	{
		Node * n = new Node();
		if (pHead->next == nullptr)
		{
			cout << "List is empty" << endl;
			return;
		}
		else if (pHead->next->next == nullptr)
		{
			cout << "List cannot be made empty" << endl;
			return;
		}
		else
		{
			pHead->next->data = pHead->next->next->data;
			n = pHead->next->next;
			pHead->next->next = pHead->next->next->next;
			delete(n);
			return;
		}
	}

	// Adds element to back (i.e. before back).
	void push_back(const T& val)
	{
		Node * oldTail = pTail->prev;
		Node * n = new Node(val, oldTail, pTail);
		pTail->prev = n;
		Node* tmp = n;
		
		if (oldTail != pHead)
		{
			oldTail->next = pTail->prev;
		}
		if (pHead->next == pTail)
		{
			pHead->next = pTail->prev;
		}
	}

	// Removes element from back.
	void pop_back()
	{
		if (pHead->next == nullptr)
		{
			cout << "List is empty" << endl;

			return;
		}

		else if (pHead->next->next == nullptr)
		{
			cout << "List cannot be made empty" << endl;

			return;
		}
		else
		{
			Node * del = pTail->prev;
			pTail->prev = pTail->prev->prev;
			delete(del);
			pTail->prev->next = pTail;
			pTail->next = nullptr;
		}
	}

	// Returns the element at the head.
	T& front()                     
	{
		return pHead->next->data;
	}

	// Returns the element at the head (const).
	const T& front() const         
	{
		return pHead->next->data;
	}

	// Returns the element at the tail.
	T& back()
	{
		return pTail->prev->data;
	}

	// Returns the element at the tail (const).
	const T& back() const
	{
		return pTail->prev->data;
	}

	// Removes all elements equal to the given value.
	void remove(const T& val)      
	{
		while(pHead->next->data == val || pHead->next == nullptr)
		{
			pop_front();
		}

		Node * n = pHead->next;

		while (n->next != pTail)
		{
			if (n->next->data == val)
			{
				Node * del = n->next;
				n->next = n->next->next;
				delete(del);
				if (n->next != nullptr)
				{
					n->next->prev = n;
				}
				else
				{
					pTail->prev = n;
				}
			}
			else
			{
				n = n->next;
			}
		}
	}

	// Returns true if there are no elements.
	bool empty() const             
	{
		if (pHead->next == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Destroys every single node in the linked list.
	void clear()
	{
		if (size() > 0)
		{
			Node * cur = pHead->next;
			Node * del = cur;
			while (cur != pTail->prev)
			{

				cur = cur->next;
				delete(del);
				del = cur;
			}
			pHead->next = nullptr;
			delete(pHead->next);
		}
	}

	// Returns size of list.
	int size()
	{
		int count = 0;
		Node * cur = pHead->next;
		while (cur != pTail)
		{
			count++;
			cur = cur->next;
		}
		return count;
	}

	// Resizes the linked list to contain the given number of elements.
	// New elements are default-initialized to 0.
	void resize(size_t newSize)
	{
		int _size = size();
		if (newSize < _size)
		{
			for (int i = 0; i < (_size - newSize); ++i)
			{
				pop_back();
			}
		}
		else
		{
			for (int i = _size; i < newSize; ++i)
			{
				push_back(0);
			}
		}
	}

	// Prints all elements of list.
	void printList()
	{
		Node * cur = pHead->next;
		cout << "\nPrinting list:" << endl;
		while (cur != pTail)
		{
			cout << cur->data << " ";

			cur = cur->next;
		}
		cout << endl << endl;
		system("pause");
	}

	class iterator
	{
		// Current node being operated upon.
		Node * cur;

	public:
		// Initializes an empty iterator pointing to null.
		iterator()
		{
			cur = nullptr;
		}

		// Initializes an iterator pointing to the given node.
		iterator(Node * startNode)
		{
			cur = startNode;
		}

		// Returns true if the iterator points to the same node.
		bool operator==(const iterator& rhs) const
		{
			if (cur == rhs.cur)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		// Returns false if the iterator does not point to the same node.
		bool operator!=(const iterator& rhs) const
		{
			if (cur != rhs.cur)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		// Returns a reference to the element pointed to by the current node.
		T& operator*()
		{
			return cur->data;
		}

		// Returns a reference to the element pointed to by the current node.
		const T& operator*() const
		{
			return (*cur).data;
		}

		// Pre-increment (returns a reference to this iterator after it is incremented).
		iterator& operator++()
		{
			this.cur = this.cur->next;
			return *this;
		}

		// Post-increment (returns an iterator as it was before it was incremented).
		iterator operator++(int)
		{
			cur = cur->next;
			return *this;
		}

		// Pre-decrement (returns a reference to this iterator after it is decremented).
		iterator& operator--()
		{
			this.cur = this.cur->prev;
			return *this;
		}

		// Post-decrement (returns an iterator as it was before it was decremented).
		iterator operator--(int)
		{
			cur = cur->prev;
			return *this;
		}
	};
	// Returns an iterator pointing to the first element.
	iterator begin()               
	{
		return iterator(pHead->next);
	}

	// Returns a const iterator pointing to the first element.
	const iterator begin() const
	{
		return iterator(pHead->next);
	}

	// Returns an iterator pointing to one past the last element.
	iterator end()
	{
		return iterator(pTail);
	}

	// Returns a const iterator pointing to one past the last element.
	const iterator end() const
	{
		return iterator(pTail);
	}

};