#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "avl_tree_map.h"

TEST_CASE("AVLTreeMap Insertion", "[Insertion]") {
    AVLTreeMap<std::string, int> map;

    SECTION("Insert single element") {
        map.insert("apple", 1);
        REQUIRE(map.search("apple") != nullptr);
        REQUIRE(*map.search("apple") == 1);
    }

    SECTION("Insert multiple elements") {
        map.insert("apple", 1);
        map.insert("banana", 2);
        map.insert("cherry", 3);
        REQUIRE(map.search("banana") != nullptr);
        REQUIRE(*map.search("banana") == 2);
    }

    // Continue with other insertion test cases...
}

TEST_CASE("AVLTreeMap Removal", "[Removal]") {
    AVLTreeMap<std::string, int> map;

    SECTION("Remove leaf node") {
        map.insert("apple", 1);
        map.remove("apple");
        REQUIRE(map.search("apple") == nullptr);
    }

    SECTION("Remove node with two children") {
        map.insert("apple", 1);
        map.insert("banana", 2);
        map.insert("cherry", 3);
        map.remove("banana");
        REQUIRE(map.search("banana") == nullptr);
        // Check balance and structure of tree after removal
    }

    SECTION("Remove all nodes") {
        map.insert("apple", 1);
        map.insert("banana", 2);
        map.insert("cherry", 3);
        map.remove("apple");
        map.remove("banana");
        map.remove("cherry");
        REQUIRE(map.search("apple") == nullptr);
        REQUIRE(map.search("banana") == nullptr);
        REQUIRE(map.search("cherry") == nullptr);
        // Check if tree is empty
    }    

}


TEST_CASE("AVLTreeMap Rotations", "[Rotations]") {
    AVLTreeMap<std::string, int> map;

    SECTION("Insert to trigger left-left case") {
        map.insert("c", 3);
        map.insert("b", 2);
        map.insert("a", 1);
        // Check structure and balance factors
    }

    SECTION("Insert to trigger right-right case") {
        map.insert("a", 1);
        map.insert("b", 2);
        map.insert("c", 3);
        // Check rotated tree structure
    }

    SECTION("Insert to trigger right-left case") {
        map.insert("a", 1);
        map.insert("c", 3);
        map.insert("b", 2);
        // Check rotated tree structure
    }}


TEST_CASE("AVLTreeMap Miscellaneous", "[Miscellaneous]") {
    AVLTreeMap<std::string, int> map;

    SECTION("Traverse tree in-order, check node values") {
        map.insert("banana", 2);
        map.insert("apple", 1);
        map.insert("cherry", 3);
        // Perform in-order traversal and check values
    }

    SECTION("Min/max value correctness") {
        map.insert("banana", 2);
        map.insert("apple", 1);
        map.insert("cherry", 3);
        // Check min/max values
    }

        SECTION("Handle duplicates") {
        map.insert("apple", 1);
        map.insert("apple", 2);
        REQUIRE(*map.search("apple") == 2); // Assuming latest value replaces the old one
    }

    SECTION("Tree height, size, empty state") {
        // Check tree height, size, and whether it's empty or not
    }

    SECTION("Search non-existing element") {
        REQUIRE(map.search("non_existing") == nullptr);
    }

    SECTION("Serialize and deserialize") {
        // Assuming serialization and deserialization functions exist
        map.insert("apple", 1);
        map.insert("banana", 2);
        // Serialize the tree, then deserialize and check the structure
    }

}
