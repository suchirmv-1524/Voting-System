#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for voter information
struct Voter {
    int voterID;
    char username[50];
    char password[50];
    // Additional voter details can be added here
};

// Define structure for n-ary tree node
struct TreeNode {
    char name[50]; // Name of the node (constituency or party)
    struct Voter voterData; // Voter information
    struct TreeNode *firstChild; // Pointer to the first child node (constituency or party)
    struct TreeNode *nextSibling; // Pointer to the next sibling node
};

// Create a new node with given name and voter information
struct TreeNode *createNode(char name[], int voterID, char username[], char password[]) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->name, name);
        newNode->voterData.voterID = voterID;
        strcpy(newNode->voterData.username, username);
        strcpy(newNode->voterData.password, password);
        newNode->firstChild = NULL;
        newNode->nextSibling = NULL;
    }
    return newNode;
}

// Insert a child node to a parent node (for constituencies and parties)
void insertChild(struct TreeNode *parentNode, struct TreeNode *childNode) {
    if (parentNode == NULL || childNode == NULL) {
        printf("Invalid node.\n");
        return;
    }
    if (parentNode->firstChild == NULL) {
        parentNode->firstChild = childNode;
    } else {
        struct TreeNode *currentChild = parentNode->firstChild;
        while (currentChild->nextSibling != NULL) {
            currentChild = currentChild->nextSibling;
        }
        currentChild->nextSibling = childNode;
    }
}

// Pre-order traversal to display the tree
void displayTree(struct TreeNode *node, int level) {
    if (node == NULL) {
        return;
    }

    // Display the node with appropriate indentation based on the level
    printf("%*s%s\n", level * 4, "", node->name);

    struct TreeNode *child = node->firstChild;
    while (child != NULL) {
        displayTree(child, level + 1);
        child = child->nextSibling;
    }
}

// Example usage
int main() {
    // Creating the tree structure for constituencies and parties
    struct TreeNode *root = createNode("National", -1, "", "");

    // Constituency 1
    struct TreeNode *constituency1 = createNode("State1", -1, "", "");
    struct TreeNode *party1 = createNode("Party1", 1, "user1", "pass1");
    struct TreeNode *party2 = createNode("Party2", 2, "user2", "pass2");

    // Constituency 2
    struct TreeNode *constituency2 = createNode("State2", -1, "", "");
    struct TreeNode *party3 = createNode("Party3", 3, "user3", "pass3");

    insertChild(root, constituency1);
    insertChild(root, constituency2);

    insertChild(constituency1, party1);
    insertChild(constituency1, party2);

    insertChild(constituency2, party3);

    // Displaying the tree structure
    printf("Voters' Database by Constituencies and Parties:\n");
    displayTree(root, 0);

    // Remember to handle memory deallocation (free nodes) when done using the tree

    return 0;
}
