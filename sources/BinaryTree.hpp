#include <stdio.h>
#include <stack>
#include <queue>
#pragma once

namespace ariel
{

	template <typename T>
	class BinaryTree
	{

		class Node
		{

		public:
			Node *left;
			Node *right;
			Node *parent;
			T value;
			Node() = default;
			Node(const T &val) : left(nullptr), right(nullptr), parent(nullptr), value(val){};
			bool operator==(const Node &other) const
			{
				return this->value == other->value && this->left == other->left &&
					   this->right == other.right && this->parent == other.parent;
			}

			bool operator!=(const Node &other) const
			{
				return this->value != other->value || this->left != other->left ||
					   this->right != other.right || this->parent != other.parent;
			}
		};

	private:
		Node *root;
		
	public:
		BinaryTree() : root(nullptr){};

		BinaryTree<T> &add_root(T val)
		{
			if (root == nullptr)
			{
				root = new Node(val);
			}
			else
			{
				root->value = val;
			}
			return *this;
		};

		BinaryTree<T> &add_left(T exists, T val)
		{
			if (root == nullptr)
			{
				throw "the tree is empty";
			}
			Node *node = find_node_in_tree(root, exists);
			if (node == nullptr)
			{
				throw "the node doesnt exists";
			}
			if (node->left == nullptr)
			{
				Node *new_node = new Node(val);
				node->left = new_node;
			}
			else
			{
				node->left->value = val;
			}

			return *this;
		};

		BinaryTree<T> &add_right(T exists, T val)
		{
			if (root == nullptr)
			{
				throw "the tree is empty";
			}
			Node *node = find_node_in_tree(root, exists);
			if (node == nullptr)
			{
				throw "the node doesnt exists";
			}
			if (node->right == nullptr)
			{
				Node *new_node = new Node(val);
				node->right = new_node;
			}
			else
			{
				node->right->value = val;
			}

			return *this;
		};
         
        BinaryTree& operator=(BinaryTree && bt) noexcept {
            if (root){ delete root;}
            root  = bt.root;
            bt.root = nullptr;
            return *this;
        }

		BinaryTree &operator=(const BinaryTree<T> &bt)
		{
			if (this == &bt)
			{
				return *this;
			}
			if (root != nullptr)
			{
				delete root;
			}
			if (bt.root != nullptr)
			{
				root = new Node{bt.root->value};
				copy_constructor(root, bt.root);
			}
			return *this;
		}

		BinaryTree(const BinaryTree &bt)
		{
			if (bt.root == nullptr)
			{
				root = nullptr;
				return;
			}
			
				this->root = new Node(bt.root->value);
				copy_constructor(root, bt.root);
			
		}

		BinaryTree(BinaryTree &&bt)  noexcept {
        this->root = bt.root;
        bt.root = nullptr;
    }
	 
    void delete_tree(Node *node) {
        if(node != nullptr){
            delete_tree(node->right);
            delete_tree(node->left);
            delete node;
        }
    }
	~BinaryTree(){
        delete_tree(this->root);
    }

		void copy_constructor(Node *node, const Node *other)
		{
			if (other->left != nullptr)
			{
				node->left = new Node(other->left->value);
				copy_constructor(node->left, other->left);
			}
			if (other->right != nullptr)
			{
				node->right = new Node(other->right->value);
				copy_constructor(node->right, other->right);
			}
		};

		Node *find_node_in_tree(Node *node, T key)
		{

			if (node == nullptr){
				return nullptr;}

			if (node->value == key){
				return node;}

			Node *res1 = find_node_in_tree(node->left, key);
			
			if (res1)
			{
				return res1;
			};

			Node *res2 = find_node_in_tree(node->right, key);

			return res2;
		}

		class in_order_iter
		{

		private:
			std::queue<Node *> nodes_queue;
			Node *ptr_to_node;

		public:
			in_order_iter(Node *ptr = nullptr)
			{

				if (ptr == nullptr)
				{
					ptr_to_node = ptr;
				}
				else
				{
					std::stack<Node *> stack;

				
					Node *curr = ptr;

				
					while (!stack.empty() || curr != nullptr)
					{
						
						
						if (curr != nullptr)
						{
							stack.push(curr);
							curr = curr->left;
						}
						else
						{
							
							curr = stack.top();
							stack.pop();
							nodes_queue.push(curr);

							curr = curr->right;
						}
					}
					ptr_to_node = nodes_queue.front();
				}
			}

			T &operator*() const
			{
				
				return ptr_to_node->value;
			}

			T *operator->() const
			{
				return &(ptr_to_node->value);
			}

			
			in_order_iter &operator++()
			{
				
				if (!nodes_queue.empty())
				{
					this->nodes_queue.pop();
				}
				if (!nodes_queue.empty())
				{
					ptr_to_node = nodes_queue.front();
				}
				else
				{
					ptr_to_node = nullptr;
				}

				return *this;
			}

			
			 in_order_iter operator++(int)
			{
				in_order_iter tmp = *this;
                ++*this;
                return tmp;
			}

			bool operator==(const in_order_iter &rhs) const
			{
				return ptr_to_node == rhs.ptr_to_node;
			}

			bool operator!=(const in_order_iter &node) const
			{
				return ptr_to_node != node.ptr_to_node;
			}
		}; 

		class pre_order_iter
		{

		private:
			Node *ptr_to_node;
			std::queue<Node *> nodes_queue;

		public:
			pre_order_iter(Node *ptr = nullptr) //pre order traversal with queue and stack
			{

				if (ptr == nullptr)
				{
					ptr_to_node = ptr;
				}
				else
				{

					
					std::stack<Node *> stack;
					stack.push(ptr);

					
					while (!stack.empty())
					{
						
						Node *curr = stack.top();
						stack.pop();

						nodes_queue.push(curr);

						
						if (curr->right)
						{
							stack.push(curr->right);
						}

						
						if (curr->left)
						{
							stack.push(curr->left);
						}

						
					}
					ptr_to_node = nodes_queue.front();
				}
			}

			T &operator*() const
			{
				
				return ptr_to_node->value;
			}

			T *operator->() const
			{
				return &(ptr_to_node->value);
			}

			
			pre_order_iter &operator++()
			{

				if (!nodes_queue.empty())
				{
					this->nodes_queue.pop();
				}
				if (!nodes_queue.empty())
				{
					ptr_to_node = nodes_queue.front();
				}
				else
				{
					ptr_to_node = nullptr;
				}

				return *this;
			}

			
			pre_order_iter operator++(int)
			{
				 pre_order_iter tmp = *this;
                ++*this;
                return tmp;
			}

			bool operator==(const pre_order_iter &rhs) const
			{
				return ptr_to_node == rhs.ptr_to_node;
			}

			bool operator!=(const pre_order_iter &node) const
			{
				return ptr_to_node != node.ptr_to_node;
			}
		};

		class post_order_iter
		{

		private:
			Node *ptr_to_node;
			std::stack<Node *> nodes_stack;

		public:
		  post_order_iter(Node *ptr = nullptr) //iterative post order traversal using 2 stacks
			{
				if (ptr == nullptr)
				{
					ptr_to_node = nullptr;
				}
				else
				{
					std::stack<Node *> post;
					post.push(ptr);
					while (!post.empty())
					{
						Node *curr = post.top();
						post.pop();
						nodes_stack.push(curr);

						if (curr->left)
						{
							post.push(curr->left);
						}
						if (curr->right)
						{
							post.push(curr->right);
						}
					}
					ptr_to_node = nodes_stack.top();
				}
			}

			

			T &operator*() const
			{
				
				return ptr_to_node->value;
			}

			T *operator->() const
			{
				return &(ptr_to_node->value);
			}

			
			post_order_iter &operator++()
			{
				if (!nodes_stack.empty())
				{
					this->nodes_stack.pop();
				}
				if (!nodes_stack.empty())
				{
					ptr_to_node = nodes_stack.top();
				}
				else
				{
					ptr_to_node = nullptr;
				}

				return *this;
			}

			
			 post_order_iter operator++(int)
			{  post_order_iter tmp = *this;
                ++*this;
                return tmp;
			}

			bool operator==(const post_order_iter &rhs) const
			{
				return ptr_to_node == rhs.ptr_to_node;
			}

			bool operator!=(const post_order_iter &node) const
			{
				return ptr_to_node != node.ptr_to_node;
			}
		}; 

		pre_order_iter begin_preorder()
		{
			
			return pre_order_iter{root};
		}

		pre_order_iter end_preorder()
		{
			
			return pre_order_iter{nullptr};
		}

		in_order_iter begin_inorder()
		{
			
			return in_order_iter{root};
		}

		in_order_iter end_inorder()
		{
			
			return in_order_iter{nullptr};
		}

		post_order_iter begin_postorder()
		{
			
			return post_order_iter{root};
		}

		post_order_iter end_postorder()
		{
		
			return post_order_iter{nullptr};
		}

		in_order_iter begin()
		{

			return in_order_iter{root};
		}

		in_order_iter end()
		{
		
			return in_order_iter{nullptr};
		}

		// friend std::ostream& operator<< (std::ostream& os, const BinaryTree& n){return os;};
	};
}

