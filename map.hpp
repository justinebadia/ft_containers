#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <algorithm>

#include "utility.hpp"
#include "iterator.hpp"
#include "avl_iterator.hpp"

namespace ft {
/*
	The first template argument is the type of the element's key, and the second template argument is the type of the element's value;
	The optional third template argument defines the sorting criterion;
	The optional fourth template parameter defines the memory model;
*/
template<typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

	private:
		struct Node
		{
			typedef Node*	    		node_pointer;

			ft::pair<const Key, T>		value; /*holds the key in first*/
			node_pointer        		parent;
			node_pointer        		left;
			node_pointer        		right;
		};

	/*MEMBER TYPES*/
	public:
		typedef Key										key_type; /*type de données de clé stockées*/
		typedef T										mapped_type; /*type de données stockées dans chaque élément d'une classe map*/
		typedef Compare									key_compare; /*objet de fonction qui peut comparer deux clés de tri pour déterminer l'ordre relatif de deux éléments d'un map*/
		typedef Allocator 								allocator_type;
		
		typedef ft::pair<const key_type, mapped_type>	value_type; /*type d'objet stockés comme élément d'une classe map*/
		typedef std::ptrdiff_t 							difference_type; /*nombre d'éléments d'une classe map comprise dans une plage d'éléments pointés par des itérateurs*/
		typedef std::size_t 							size_type; /*nombre d'éléments*/
		
		typedef value_type& 							reference; /*référence à un élément stocké dans une classe map*/
		typedef const value_type& 						const_reference;/*référence à un const élément stocké dans une carte pour la lecture et l’exécution d’opérations const*/
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		
		typedef typename ft::map_iterator<Key, T, Compare, Node>				iterator;
		typedef typename ft::const_map_iterator<Key, T, Compare, Node>			const_iterator;	
		
		typedef typename ft::map_reverse_iterator<Key, T, Compare, Node>					reverse_iterator;
		typedef typename ft::map_reverse_iterator<Key, T, Compare, Node> 					const_reverse_iterator;

		typedef Node*	    		node_pointer;

		/* template member function that creates a new allocator object of a different type, which can be used to allocate objects of a different type. 
		* When you call rebind, you pass a new type as a template argument, and it returns a new allocator object that is templated on that type.*/
		typedef typename Allocator::template rebind<Node>::other node_alloc;

		/*objet de fonction qui peut comparer les éléments d'un map en comparant les valeurs de leurs clés pour déterminer leur ordre relatif dans le map.*/
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			public:
			friend class map<Key, T, Compare, Allocator>;
			bool operator()(const value_type& lhs, const value_type& rhs) const 
			{ 
				return comp(lhs.first, rhs.first); 
			}

			protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c){}
		}; // value_compare

		
		/* -- CONSTRUCTORS - DESTUCTORS -- */

		/**
        *  @brief  Creates a %map with no elements.
        *  @param  comp  A comparison object.
        *  @param  a  An allocator object.
        */
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_node_count(0),
			_alloc(alloc),
			_comp(comp)
		{
			_end = new_node(ft::pair<const key_type, mapped_type>());
			_root = _end;
			_end->left = _end;
			_end->right = _end;
		}

 		/**
        *  @brief  Builds a %map from a range.
        *  @param  first  An input iterator.
        *  @param  last  An input iterator.
        *  @param  comp  A comparison functor.
        *  @param  a  An allocator object.
        *
        *  Create a %map consisting of copies of the elements from [first,last).*/
		template<typename InputIt>
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_node_count(0),
			_alloc(alloc),
			_comp(comp)
		{
			_end = new_node(ft::pair<const key_type, mapped_type>());
			_root = _end;
			_end->left = _end;
			_end->right = _end;

			insert(first, last);
		}

		/**
        *  @brief  %Map copy constructor.
        *  @param  other  A %map of identical element and allocator types.
        */
		map(const map& other) :
			_node_count(0),
			_alloc(other._alloc),
			_node_alloc(other._node_alloc),
			_comp(other._comp)
		{
			_end = new_node(ft::pair<const key_type, mapped_type>());
			_root = _end;
			_end->left = _end;
			_end->right = _end;
			
			insert(other.begin(), other.end());
		}

		~map()
        {
            clear();
            dealloc_node(_end);
        }

		/**
        *  @brief  %Map assignment operator.
        *  @param  other  A %map of identical element and allocator types.
        *
        *  All the elements of other are copied, but unlike the copy constructor,
        *  the allocator object is not copied.
        */
		map& operator=(const map& other)
		{
			map temp(other);
			swap(temp);
			return *this;
		}

/// Get a copy of the memory allocation object.
		allocator_type get_allocator() const 
		{
			return (allocator_type());
		}

	/* ---------- ITERATORS --------------------------------------------------------- */
		iterator begin()
		{
			return iterator(_end->right, _end, _comp);
		}

		const_iterator begin() const
		{
			return const_iterator(_end->right, _end, _comp);

		}

		iterator end()
		{
			return iterator(_end, _end, _comp);
		}

		const_iterator end() const
		{
			return const_iterator(_end, _end, _comp);

		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_end->left, _end, _comp);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_end->left, _end, _comp);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_end, _end, _comp);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_end, _end, _comp);
		}
	/*
	* ---------- CAPACITY --------------------------------------------------------- *
	*/

		bool empty()
        {
			return _node_count == 0;
        }

		size_type max_size() const
		{
			const size_t diff_max = std::numeric_limits<difference_type>::max();
			const size_t alloc_max = _node_alloc().max_size();

			return std::min(diff_max, alloc_max);
		}

		size_type size() const 
		{
			return _node_count;
		}

	/*
	* ---------- ELEMENT ACCESS ----------------------------------------------------- *
	*/

		/* return a reference to the data whose key is equivalent to key, if
        *  such a data is present in the map.
        *  @throw  std::out_of_range  If no such data is present.*/
		mapped_type& at(const key_type& key)
		{
			node_pointer temp = search_by_key(_root, key);
			if (!temp)
				throw std::out_of_range("map::at:  key not found");
			iterator it(temp, _end, _comp);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}

		const mapped_type at(const key_type& key) const 
		{
			node_pointer temp = search_by_key(_root, key);
			if (!temp)
				throw std::out_of_range("map::at:  key not found");
			const_iterator it(temp, _end, _comp);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}

		/* Returns a reference to the value that is mapped to a key 
		* equivalent to key, performing an insertion if such key 
		* does not already exist.*/
		mapped_type& operator[](const key_type& key)
		{
			node_pointer temp = search_by_key(_root, key);

			if (temp)
				return temp->value.second;
			_node_count++;
			return insertNode(_root, ft::make_pair<key_type, mapped_type>(key, mapped_type()))->value.second;
		}

	/*
	* --------------- MODIFIERS ------------------------------------------------------ *
	*/
		/* Erases all elements from the container. 
		* After this call, size() returns zero.*/
		void clear()
		{
			while (_node_count != 0)
			{
				delete_node(_root, _root->value.first);
				_node_count--;
			}
		}

		void erase(iterator pos)
		{
			delete_node(pos.getNode(), pos->first);
			_node_count--;
		}

		void erase(iterator first, iterator last)
		{
			for(; first != last;)
			{
				iterator temp(first);
				first++;
				erase(temp);
			}
		}

		size_type erase(const key_type& key)
		{
			bool success = delete_node(_root, key);
			_node_count -= success;
			return success;
			
		}

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			/*recherche sur la clé est déjà présente et retourne un iterator le cas échéant*/
			node_pointer existing = search_by_key(_root, value.first);
			if(existing)
				return ft::make_pair<iterator, bool>(iterator(existing, _end, _comp), false);
			_node_count++;
			return ft::pair<iterator, bool>(iterator(insertNode(_root, value), _end, _comp), true);
			/*insère la clé dans l'arbre et retourne un iterateur à sa position*/
		}

 		/**
        *  @brief Attempts to insert a std::pair into the %map.
        *  @param  position  An iterator that serves as a hint as to where the
        *                    pair should be inserted.
        *  @param  value  Pair to be inserted 
        *  @return  An iterator that points to the element with key of @a value (may
        *           or may not be the %pair passed in).
        *
        *  This function is not concerned about whether the insertion
        *  took place, and thus does not return a boolean like the
        *  single-argument insert() does.  Note that the first
        *  parameter is only a hint and can potentially improve the
        *  performance of the insertion process.  A bad hint would
        *  cause no gains in efficiency.
        */
		iterator insert(iterator pos, const value_type& value)
		{
			if (pos->first > value.first) // on decremente
			{
				iterator previous(pos);
				previous--;
				while (previous != end() && previous->first >= value.first)
				{
					previous--;
					pos--;
				}
			}
			else if (pos->first < value.first ) // on incremente
			{
				iterator next(pos);
				next++;
				while(next != end() && next->first <= value.first)
				{
					next++;
					pos++;
				}
			}

			if (pos != end() && pos->first == value.first)
				return pos;

			_node_count++;
			return iterator(insertNode(pos.getNode(), value), _end, _comp);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for(; first != last; ++first)
				insert(*first);
		}

		void swap(map& other)
		{
			std::swap(_root, other._root);
			std::swap(_end, other._end);
			std::swap(_node_count, other._node_count);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_alloc, other._alloc);
			std::swap(_comp, other._comp);
		}

	/*
	* --------------- LOOK-UP --------------------------------------------------- *
	*/	
		/**
        *  @brief  Finds the number of elements with given key.
        *  @param    Key of (key, value) pairs to be located.
        *  @return  Number of elements with specified key.
        *
        *  This function only makes sense for multimaps; for map the result will
        *  either be 0 (not present) or 1 (present).
        */
		size_type count(const key_type& key) const
		{
			node_pointer temp = search_by_key(_root, key);
			return temp ? 1: 0;
		}

		/*  This function takes a key and tries to locate the element with which
        *  the key matches.  If successful the function returns an iterator
        *  pointing to the sought after %pair.  If unsuccessful it returns the
        *  past-the-end iterator.
        */
		iterator find(const key_type& key)
		{
			node_pointer temp  = search_by_key(_root, key);
			if (temp)
				return iterator(temp, _end, _comp);
			return end();
		}

		const_iterator find(const key_type& key) const 
		{
			node_pointer temp  = search_by_key(_root, key);
			if (temp)
				return const_iterator(temp, _end, _comp);
			return end();
		}

	 	/* Returns an iterator pointing to 
		* the first element that is not less than (i.e. greater or equal to) key
        */
		iterator lower_bound(const key_type& key)
		{
			iterator it = begin();
			for(; it != end(); ++it)
				if (!(_comp(it->first, key))) //_comp = std::less = operator<
					break;
			return it;
		}

		const_iterator lower_bound(const key_type& key) const
		{
			iterator it = begin();
			for(; it != end(); ++it)
				if (!(_comp(it->first, key))) //_comp = std::less = operator< = !(it < key)
					break;
			return it;
		}

		/* Returns an iterator pointing to the first element 
		* that is greater than key.*/
		iterator upper_bound(const key_type& key)
		{
			iterator it = begin();
			for(; it != end(); ++it)
				if (_comp(key, it->first)) //_comp = (key<it)
					break;
			return it;
		}

		const_iterator upper_bound(const key_type& key) const
		{
			iterator it = begin();
			for(; it != end(); ++it)
				if (_comp(key, it->first)) 
					break;
			return it;
		}

		/* Returns a range containing all elements with the given key in the container. 
		* The range is defined by two iterators, one pointing to the first element 
		* that is not less than key and another pointing to the first element greater than key. 
		* Alternatively, the first iterator may be obtained with lower_bound(), 
		* and the second with upper_bound().
		*
		* If there are no elements not less than key, past-the-end iterator is returned as the first
		*  element. Similarly if there are no elements greater than key, past-the-end iterator 
		* is returned as the second element.
		*/
		ft::pair<iterator, iterator> equal_range(const key_type& key)
		{
			return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

	/*
	* --------------- OBSERVERS -------------------------------------------------- *
	*/	

	/*  Returns the key comparison object out of which the %map was constructed. */
		key_compare key_comp() const { return _comp; }

	/**
    *  Returns a value comparison object, built from the key comparison
    *  object out of which the %map was constructed.
    */
		value_compare value_comp() const { return value_compare(_comp); }


	private:
		node_pointer	_root;// left child of end
        node_pointer    _end;// parent of root
		size_type 		_node_count; //keeps track oh the size
		allocator_type	_alloc;
        node_alloc 	 	_node_alloc;
		key_compare		_comp;	

		node_pointer new_node(const value_type& value)
		{
			Node* new_node = _node_alloc.allocate(1);
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = NULL;
			
			_alloc.construct(&new_node->value, value);

			return new_node;
		}

		void dealloc_node(node_pointer to_delete)
		{
			_alloc.destroy(&to_delete->value);
			_node_alloc.deallocate(to_delete, 1);
		}

		int getBalanceFactor(node_pointer n)
		{
			if (n == NULL)
				return -1;
			else 
				return(tree_height(n->left) - tree_height(n->right));
		}

		/* the height of a BST is the number of edges between the tree's root
		and its furthest leaf */
		int tree_height(Node* r)
		{
			if (r == NULL || r == _end)
				return -1;
			else 
			{
				int left_height = tree_height(r->left);
				int right_height = tree_height(r->right);
				if (left_height > right_height)
					return (left_height + 1);
				else
					return (right_height + 1);
			}
		}

		node_pointer search_by_key(node_pointer node_r, key_type key) const
		{
			if (node_r == NULL || node_r == _end)
				return NULL;
			
			if (!_comp(node_r->value.first, key) && !_comp(key, node_r->value.first))
				return node_r;
			else if (key < node_r->value.first && node_r->left && node_r->left != _end)
				return search_by_key(node_r->left, key);
			else if (key > node_r->value.first && node_r->right && node_r->right != _end)
				return search_by_key(node_r->right, key);
			return NULL;
		}

		bool check_equal(const key_type& lhs, const key_type&rhs) 
		{
			if (!_comp(lhs, rhs) && !_comp(lhs, rhs)) //check si egal
				return true;
			else 
				return false;
		}

		bool check_left(const key_type& lhs, const key_type& rhs)  //si vrai je vais a gauche
		{
			if (_comp(lhs, rhs))
				return true;
			return false;
		}

		bool check_right(const key_type& lhs,const key_type& rhs)  //si vrai je vais a droite
		{
			if (_comp(rhs, lhs))
				return true;
			return false;

		}

		node_pointer insertNode(node_pointer pos, const value_type& value)
		{
			if (_root == _end)
			{
				_root = new_node(value);

				_root->left = _end;
				_root->right = _end;
				_end->left = _root;
				_end->right = _root;

				return _root;
			}

			if (check_equal(pos->value.first, value.first)) //(pos->value.first == value.first)
				return NULL; //node existe deja

			if (check_left(pos->value.first, value.first) && pos->left && pos->left != _end) //value < pos = a gauche (pos->value.first > value.first
				return insertNode(pos->left, value);
			if (check_right(pos->value.first, value.first) && pos->right && pos->right != _end) // value > pos = a droite
				return insertNode(pos->right, value);

			node_pointer newNode = new_node(value);
			/*cas où je peux insérer dans une leaf node*/
			if (check_right(pos->value.first, newNode->value.first) && !pos->left) //pos->value.first > newNode->value.first
				pos->left = newNode;
			else if (check_left(pos->value.first, newNode->value.first) && !pos->right) //pos->value.first < newNode->value.first
				pos->right = newNode;
			else if (pos->left && check_right(pos->value.first, newNode->value.first)) //  pos->value.first > newNode->value.first
			{
				newNode->left = _end;
				_end->right = newNode;
				pos->left = newNode;
			}
			else if (pos->right && check_left(pos->value.first, newNode->value.first)) // pos->value.first < newNode->value.first
			{
				newNode->right = _end;
				_end->left = newNode;
				pos->right = newNode;
			}
			newNode->parent = pos;

			balance_tree(&_root, newNode);
			return newNode;
		}

		bool delete_node(node_pointer node, key_type key)
		{
			node_pointer to_delete = search_by_key(node, key);
			if (!to_delete)
				return false;
			
			node_pointer to_balance = NULL;
			/*CASE : ROOT NODE TO DELETE */
			if (!to_delete->parent)
			{
				if (to_delete->left == _end && to_delete->right == _end) // root to delete is the only node
				{
					_root = _end;
					_end->left = _end;
					_end->right = _end;
				}
				else if (to_delete->left && to_delete->right == _end)
				{
					to_balance = to_delete->parent;
					_root = to_delete->left;
					to_delete->left->parent = NULL;
					_end->left = to_delete->left;
					to_delete->left->right = _end;
				}
				else if (to_delete->right && to_delete->left == _end)
				{
					to_balance = to_delete->parent;
					_root = to_delete->right;
					to_delete->right->parent = NULL;
					_end->right = to_delete->right;
					to_delete->right->left = _end;
				}
				else
				{
					node_pointer max_node = maximum(to_delete->left);
					_alloc.destroy(&to_delete->value);
					_alloc.construct(&to_delete->value, max_node->value);
					return (delete_node(to_delete->left, max_node->value.first));
				}
			}
			/* CASE : LEAF NODE TO DELETE */
			else if ((!to_delete->left || to_delete->left == _end) && (!to_delete->right || to_delete->right == _end))
			{
				to_balance = to_delete->parent;
				node_pointer temp = NULL;
				if (to_delete->left == _end || to_delete->right == _end)
				{
					temp = _end;
					if (!_comp(to_delete->parent->value.first, to_delete->value.first))
						_end->right = to_delete->parent;
					else if (_comp(to_delete->parent->value.first, to_delete->value.first))
						_end->left = to_delete->parent;
				}
				if (!_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->left = temp;
				else if (_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->right = temp;

			}
			/* CASE : NODE TO DELETE HAVE A LEFT CHILD */
			else if ((to_delete->left && to_delete->left != _end) && (!to_delete->right || to_delete->right == _end))
			{
				to_balance = to_delete->parent;
				if (!_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->left = to_delete->left;
				else if (_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->right = to_delete->left;
				to_delete->left->parent = to_delete->parent;

				if (to_delete->right == _end)
				{
					_end->left = to_delete->left;
					to_delete->left->right = _end;
				}
			}
			/* CASE : NODE TO DELETE HAVE A RIGHT CHILD */
			else if (to_delete->right && to_delete->right != _end && (!to_delete->left || to_delete->left == _end))
			{
				to_balance = to_delete->parent;
				if (!_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->left = to_delete->right;
				else if (_comp(to_delete->parent->value.first, to_delete->value.first))
					to_delete->parent->right = to_delete->right;
				to_delete->right->parent = to_delete->parent;

				if(to_delete->left == _end)
				{
					_end->right = to_delete->right;
					to_delete->right->left = _end;
				}
			} 
			/* CASE : NODE TO DELETE HAVE TWO CHILDREN */
			else 
			{
				node_pointer max_node = maximum(to_delete->left);
				_alloc.destroy(&to_delete->value);
				_alloc.construct(&to_delete->value, max_node->value);
				return (delete_node(to_delete->left, max_node->value.first));
			}
			balance_tree(&_root, to_balance);
			dealloc_node(to_delete);
			return true;
		}

		void balance_tree(node_pointer* root, node_pointer node)
		{
			while (node)
			{
				int balance_factor = getBalanceFactor(node);

				if (balance_factor > 1 && getBalanceFactor(node->left) > 0) //left heavy case
					right_rotate(root, node);
				else if (balance_factor < -1 && getBalanceFactor(node->right) < 0) // right heavy case
					left_rotate(root, node);
				else if (balance_factor < -1 && getBalanceFactor(node->right) >= 0) //right-left case
				{
					right_rotate(root, node->right);
					left_rotate(root, node);
				}
				else if (balance_factor > 1 && getBalanceFactor(node->left) <= 0) //left-right case
				{
					left_rotate(root, node->left);
					right_rotate(root, node);
				}
				node = node->parent;
			}
		}



		void right_rotate(node_pointer* root, node_pointer node)
		{
			node_pointer left_node = node->left;
			node_pointer center_node = left_node->right;

			if (center_node)
				center_node->parent = node;

			left_node->right = node;
			node->left = center_node;

			left_node->parent = node->parent;

			if (node->parent && node->parent->left == node)
				node->parent->left = left_node;
			else if (node->parent)
				node->parent->right = left_node;
			node->parent = left_node;

			if (!left_node->parent)
				*root = left_node;
		}

		void left_rotate(node_pointer* root, node_pointer node)
		{
			node_pointer right_node = node->right;
			node_pointer center_node = right_node->left;

			if (center_node)
				center_node->parent = node;

			right_node->left = node;
			node->right = center_node;

			right_node->parent = node->parent;
			if (node->parent && node->parent->left == node)
				node->parent->left = right_node;
			else if (node->parent)
				node->parent->right = right_node;

			node->parent = right_node;

			if(!right_node->parent)
				*root = right_node;
		}

		/*find the node with the maximum key*/
		node_pointer maximum(node_pointer node)
		{
			while (node->right && node->right != _end)
				return maximum(node->right);
			return node;
		}

		/*find the node with the minimum key*/
		node_pointer minimum(node_pointer node)
		{
			if (node->left && node->left != _end)
				return minimum(node->left);
			return node;
		}

		/* find the successor of a given node : if the right subtree != null
		 * the successor is the leftmost node in the right subtree;
		 * else it is the lowest ancestor of the node;
		 * basically: one step left and right till you can
		*/
		node_pointer successor(node_pointer node)
		{
			if(node->right != NULL)
				return minimum(node->right);
			node_pointer parent = node->parent;
			while (parent != NULL && node == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}

		/* find the predecessor of a given node: if the left subtree != null
		 * the predecessor is the rightmost node in the left subtree
		 * basically : one step left and then right till you can
		*/
		node_pointer predecessor(node_pointer node)
		{
			if(node->left != NULL)
				return maximum(node->left);
			node_pointer parent = node->parent;
			while(parent != NULL && node == parent->left)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}

		
};

/*----------------------------- NON-MEMBER FUNCTIONS ---------------------------------------*/
template<class Key, class T, class Compare, class Alloc>
void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs )
{
	lhs.swap(rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key, T, Compare, Alloc>& x,
                 const ft::map<Key, T, Compare, Alloc>& y )
{
	return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key, T, Compare, Alloc>& x,
                 const ft::map<Key, T, Compare, Alloc>& y )
{
	return !(x == y);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key, T, Compare, Alloc>& x,
                const ft::map<Key, T, Compare, Alloc>& y )
{
	return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key, T, Compare, Alloc>& x,
                 const ft::map<Key, T, Compare, Alloc>& y )
{
	return !(y < x);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key, T, Compare, Alloc>& x,
                const ft::map<Key, T, Compare, Alloc>& y )
{
	return (y < x);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key, T, Compare, Alloc>& x,
                 const ft::map<Key, T, Compare, Alloc>& y )
{
	return !(x < y);
}							


} // namespace

#endif