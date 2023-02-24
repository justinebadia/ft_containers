#ifndef AVL_ITERATOR_HPP
#define AVL_ITERATOR_HPP

#include <iterator>
#include <cstddef>

namespace ft {
template <typename Key, typename T, typename Compare, typename Node>
	class map_iterator;

template <typename Key, typename T, typename Compare, typename Node>
class const_map_iterator;

template <typename Key, typename T, typename Compare, typename Node>
	class map_iterator {
		public:
			typedef Key													key_type; 
			typedef T													mapped_type;
			typedef Compare												key_compare; 
			typedef ft::pair<const key_type, mapped_type>				value_type;
			typedef ptrdiff_t											difference_type;
			typedef std::size_t 										size_type;
			typedef std::bidirectional_iterator_tag 					iterator_category;

			typedef value_type&											reference;
			typedef value_type*											pointer;
			
			typedef const_map_iterator<const Key, T, Compare, Node>		const_iterator;
			typedef Node*												node_pointer;

		private:
			node_pointer												_current_ptr;
			node_pointer												_end;
			key_compare													_comp;


		public:
			/* -- CONSTRUCTORS - DESTRUCTORS -- */	
			map_iterator(node_pointer node = NULL, node_pointer end = NULL, const key_compare& comp = key_compare()):
			_current_ptr(node), 
			_end(end), 
			_comp(comp) 
			{}

			map_iterator(const map_iterator<Key, T, Compare, Node>& other)
			{
				_current_ptr = other.getNode();
				_end = other.getEnd();
				_comp = other.getComp();
			}

			map_iterator(const const_map_iterator<Key, T, Compare, Node>& other)
			{
				_current_ptr = other.getNode();
				_end = other.getEnd();
				_comp = other.getComp();
			}

			~map_iterator() {}

			map_iterator& operator=(const map_iterator& other)
			{
				if (this != &other)
				{
					_current_ptr = other._current_ptr;
					_end = other._end;
					_comp = other._comp;
				}
				return *this;
			}
			
			node_pointer getNode() const { return _current_ptr; }
			node_pointer getEnd() const { return _end; }
			key_compare getComp() const { return _comp; }


			node_pointer base() { return _current_ptr; }
			const node_pointer base() const { return _current_ptr; }

			reference operator*() const { return _current_ptr->value; }
			pointer operator->() const { return &_current_ptr->value; }

			map_iterator& operator++()
			{
				_current_ptr = successor(_current_ptr);
				return *this;
			}

			map_iterator operator++(int)
			{
				map_iterator tmp(*this);
	
				++(*this);
				return tmp;
			}

			map_iterator& operator--()
			{
				_current_ptr = predecessor(_current_ptr);
				return *this;
			}

			map_iterator operator--(int)
			{
				map_iterator tmp = *this;
		
				--(*this);
				return tmp;
			}

			bool operator==(const map_iterator& x) const { return x._current_ptr == _current_ptr; }
			bool operator==(const const_iterator& x) const { return _current_ptr != x._current_ptr; }

			bool operator!=(const map_iterator& x) const { return !(*this == x); }
			bool operator!=(const const_iterator& x) const { return !(*this == x); }

		private:
			/*find the node with the maximum key*/
		node_pointer maximum(node_pointer node)
		{
			if (node && node != _end && node->right && node->right != _end)
				return maximum(node->right);
			return node;
		}

		/*find the node with the minimum key*/
		node_pointer minimum(node_pointer node)
		{
			if (node && node != _end && node->left && node->left != _end)
				return minimum(node->left);
			return node;
		}

		/* find the successor of a given node : if the right subtree != null
 		 * the successor is the leftmost node in the right subtree;
 		 * else it is the lowest ancestor of the node;
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


template <typename Key, typename T, typename Compare, typename Node>
	class const_map_iterator {
		public:
			typedef Key												key_type; 
			typedef T												mapped_type;
			typedef Compare											key_compare; 
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef ptrdiff_t										difference_type;
			typedef std::size_t 									size_type;
			typedef std::bidirectional_iterator_tag 				iterator_category;
			typedef map_iterator<Key, T, Compare, Node>				iterator;

			typedef value_type&										reference;
			typedef value_type*										pointer;
			
			typedef Node*											node_pointer;

		private:
			node_pointer											_current_ptr;
			node_pointer											_end;
			key_compare												_comp;


		public:
			/* -- CONSTRUCTORS - DESTRUCTORS -- */	
			const_map_iterator(node_pointer node = NULL, node_pointer end = NULL, const key_compare& comp = key_compare()):
			_current_ptr(node), 
			_end(end), 
			_comp(comp) 
			{}

			const_map_iterator(const map_iterator<Key, T, Compare, Node>& other)
			{
				_current_ptr = other.getNode();
				_end = other.getEnd();
				_comp = other.getComp();
			}

			const_map_iterator(const const_map_iterator<Key, T, Compare, Node>& other)
			{
				_current_ptr = other.getNode();
				_end = other.getEnd();
				_comp = other.getComp();
			}
			
			~const_map_iterator() {}
			
			node_pointer getNode() const { return _current_ptr; }
			node_pointer getEnd() const { return _end; }
			key_compare getComp() const { return _comp; }


			node_pointer base() { return _current_ptr; }
			node_pointer base() const { return _current_ptr; }

			reference operator*() const { return _current_ptr->value; }
			pointer operator->() const { return &_current_ptr->value; }

			const_map_iterator& operator++()
			{
				_current_ptr = successor(_current_ptr);
				
				return *this;
			}

			const_map_iterator operator++(int)
			{
				const_map_iterator tmp(*this);
				
				++(*this);

				return tmp;
			}

			const_map_iterator& operator--()
			{
				_current_ptr = predecessor(_current_ptr);

				return *this;
			}

			const_map_iterator operator--(int)
			{
				const_map_iterator tmp = *this;
				--(*this);

				return tmp;
			}


			bool operator==(const const_map_iterator& x) const { return x._current_ptr == _current_ptr; }
			bool operator==(const iterator& x) const { return x.base() == _current_ptr; }

			bool operator!=(const iterator& x) const { return !(*this == x); }
			bool operator!=(const const_map_iterator& x) const { return !(*this == x); }

		private:
			/*find the node with the maximum key*/
		node_pointer maximum(node_pointer node)
		{
			if (node && node != _end && node->right && node->right != _end)
				return maximum(node->right);
			return node;
		}

		/*find the node with the minimum key*/
		node_pointer minimum(node_pointer node)
		{
			if (node && node != _end && node->left && node->left != _end)
				return minimum(node->left);
			return node;
		}

		/* find the successor of a given node : if the right subtree != null
 		 * the successor is the leftmost node in the right subtree;
 		 * else it is the lowest ancestor of the node;
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
}//namespace

#endif