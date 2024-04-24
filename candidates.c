#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES_PER_CONSTITUENCY 10
#define MAX_CONSTITUENCIES 10

struct Candidate {
    int candidateID;
    char fullName[100]; 
    long int votes;     
};

struct TreeNode {
    char constituency[100];
    struct Candidate candidates[MAX_CANDIDATES_PER_CONSTITUENCY];
    int candidateCount; 
    struct TreeNode *nextConstituency; 
};

struct TreeNode *createNode(char constituency[]) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->constituency, constituency);
        newNode->candidateCount = 0;
        newNode->nextConstituency = NULL;
    }
    return newNode;
}

void addCandidate(struct TreeNode *constituencyNode, int candidateID, char fullName[], long int votes) {
    if (constituencyNode == NULL || constituencyNode->candidateCount >= MAX_CANDIDATES_PER_CONSTITUENCY) {
        printf("Invalid constituency or candidate limit reached.\n");
        return;
    }

    struct Candidate *newCandidate = &(constituencyNode->candidates[constituencyNode->candidateCount]);
    newCandidate->candidateID = candidateID;
    strcpy(newCandidate->fullName, fullName);
    newCandidate->votes = votes;

    constituencyNode->candidateCount++;
}

void displayCandidates(struct TreeNode *root) {
    struct TreeNode *currentNode = root;
    while (currentNode != NULL) {
        printf("Constituency: %s\n", currentNode->constituency);
        for (int i = 0; i < currentNode->candidateCount; ++i) {
            printf("  Candidate ID: %d, Name: %s, Votes: %ld\n", currentNode->candidates[i].candidateID,
                   currentNode->candidates[i].fullName, currentNode->candidates[i].votes);
        }
        printf("\n");
        currentNode = currentNode->nextConstituency;
    }
}

int main() {
    struct TreeNode *root = NULL;
    struct TreeNode *currentConstituency = NULL;

    root = createNode("National");

    char choice;
    do {
        char constituencyName[100];
        printf("Enter constituency name: ");
        scanf(" %[^\n]", constituencyName);

        struct TreeNode *newConstituency = createNode(constituencyName);
        if (newConstituency == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }

        if (currentConstituency == NULL) {
            root->nextConstituency = newConstituency;
        } else {
            currentConstituency->nextConstituency = newConstituency;
        }
        currentConstituency = newConstituency;

        do {
            int candidateID;
            char fullName[100];
            long int votes;

            printf("Enter candidate ID for %s: ", constituencyName);
            scanf("%d", &candidateID);
            printf("Enter candidate's full name: ");
            scanf(" %[^\n]", fullName);
            printf("Enter number of votes: ");
            scanf("%ld", &votes);

            addCandidate(currentConstituency, candidateID, fullName, votes);

            printf("Do you want to add another candidate for %s? (Y/N): ", constituencyName);
            scanf(" %c", &choice);
        } while (choice == 'Y' || choice == 'y');

        printf("Do you want to add candidates for a new constituency? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    printf("Candidate Database by Constituency:\n");
    displayCandidates(root);

    return 0;
}
