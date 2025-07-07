# Inventory Management System using AVL Trees

This is a C-based inventory management system for a store that organizes products into aisles and manages item availability, thresholds, expiry dates, and billing using **AVL Trees** for balanced and efficient search, insert, and delete operations.

## Features

- AVL Tree-based item storage per aisle
- Add, update, and delete items
- Add and update aisles
- Search and check item availability
- Monitor stock levels against thresholds
- Check expiry dates of ready-to-eat foods
- Generate DOT files for visualizing the AVL tree structure
- Merge AVL trees
- Maintain bills using AVL trees and linked lists

## Data Structures Used

- `item_node`: AVL node representing an item
- `aisle_node`: Contains aisle metadata and item AVL tree root
- `bill_node`: Linked list node for items in a bill
- `bill_tree`: AVL node for storing bills

## Files Used

- `aisle_data.txt`: Stores data about aisles
- `store_data.txt`: Stores data about items in aisles
- `avl_tree.dot`: DOT file generated for AVL tree visualization

## Functionalities

### Item Operations
- `add_item`: Add a new item to an aisle
- `update_item`: Update an item’s name, quantity, threshold, or expiry
- `delete_node`: Delete an item from an aisle
- `search`: Search for an item in an aisle
- `check_availbilty`: Check if an item is available before a certain expiry date
- `check_threshold`: Alerts if any item quantity falls below its threshold

### Aisle Operations
- `add_aisle`: Add a new aisle with items
- `update_aisle`: Update aisle name, add item, or update item
- `save_aisle_data`: Load aisle data from file
- `save_item_data`: Load item data from file

### Billing System
- `insert_bill_node`: Add a new bill to the bill tree
- `delete_node`: Delete a bill by its bill number
- `bill_tree`: AVL structure for managing billing efficiently

### Expiry Management
- `check_ready_to_eat_foods`: Checks for expiring or expired ready-to-eat items

### AVL Visualization
- `generateDotFile`: Generates a DOT file to visualize the AVL tree

## How to Run

1. **Compile the program:**
   ```bash
   gcc -o avl AVL_tree.c
   ```

2. **Run the program:**
   ```bash
   ./avl
   ```

3. **Visualize the AVL Tree (optional):**
   After running, `avl_tree.dot` will be created.
   You can convert it to an image using Graphviz:
   ```bash
   dot -Tpng avl_tree.dot -o avl_tree.png
   ```

## Sample File Formats

### `aisle_data.txt`
```
6
1 ready_to_eat
2 beverages
3 dairy
4 snacks
5 frozen
6 bakery
```

### `store_data.txt`
```
1 101 chips 10 20250810 20
1 102 soda 15 20251112 50
2 201 milk 10 20250710 15
...
```

## Notes

- The current implementation supports a maximum of 6 aisles.
- AVL tree ensures operations like insertion, deletion, and search are performed in `O(log n)` time.
