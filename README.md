# Utilities

This repository contains useful C++ header files for various projects.  
Currently, it provides;

- A generic easily usable **AST** (Abstract Syntax Tree) manager via the `ast.h` file.

All these projects are sub-projects from an other project I'm doing: a scratch interpreter (/compiler maybe) in c++

---

## Provided File

### `ast.h`

This header defines an `AST` structure to manage trees with parent-child relationships and metadata associated with each node.

#### Main Features

- Dynamic node creation and deletion
- Automatic management of children and siblings
- Tree printing for debugging purposes
- Reuse of deleted node indices to avoid memory waste

#### Example Usage

```cpp
#include "ast.h"
#include <iostream>

int main() {
    AST tree;

    // Create nodes with metadata
    size_t root = tree.create_node(100);
    size_t child1 = tree.create_node(200);
    size_t child2 = tree.create_node(300);

    // Build the tree
    tree.add_child(root, child1);
    tree.add_child(root, child2);

    // Print the tree
    tree.print_tree(root);

    // Delete a node
    tree.delete_node(child1);

    std::cout << "\nAfter deleting the first child:\n";
    print_all_tree()  //tree.print_tree(root); works too here, because there is 'one tree in the forest'.

    return 0;
}
```

#### Important Methods

| Method | Description |
|--------|-------------|
| `size_t create_node(size_t metadatas)` | Creates a new node with the given metadata and returns its index. |
| `void add_child(size_t parent, size_t child)` | Adds `child` as a child of `parent`. |
| `void remove_child(size_t parent, size_t child)` | Removes `child` from `parent`. |
| `void delete_node(size_t node_idx)` | Deletes a node and all its descendants. |
| `void print_tree(size_t depth = 0, size_t index = 0) const` | Prints the tree starting from a given node. |
| `void print_all_tree()` | Prints all subtrees in the AST. |

#### Constants

- `AST::NULL_IDX` : special `size_t` value representing the absence of a parent, child or next_slibing.

---

## Installation

Simply include the `ast.h` file in your C++ project:

```cpp
#include "ast.h"
```

No additional installation is required, as this is a single standalone header.

---

## License

MIT
