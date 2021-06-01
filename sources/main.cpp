// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <stdexcept>
// using namespace std;

// #include "BinaryTree.hpp"
// using namespace ariel;

// int main(){
//     BinaryTree<int> tree_of_ints;
//   tree_of_ints.add_root(1)
//   .add_left(1, 9)      // Now 9 is the left child of 1
//   .add_left(9, 4)      // Now 4 is the left child of 9
//   .add_right(9, 5)     // Now 5 is the right child of 9
//   .add_right(1, 3)     // Now 3 is the right child of 1
//   .add_left(1, 2);     
//   cout<<tree_of_ints<<endl;


//   BinaryTree<string> tree_of_strings;
//   tree_of_strings.add_root("1")     
//   .add_left("1", "9")      // Now 9 is the left child of 1
//   .add_left("9", "4")      // Now 4 is the left child of 9
//   .add_right("9", "5")     // Now 5 is the right child of 9
//   .add_right("1", "3")     // Now 3 is the right child of 1
//   .add_left("1", "2");     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
//   cout << tree_of_strings << endl; 

//     return 0;
// }