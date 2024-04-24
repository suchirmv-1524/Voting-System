#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_VOTERS 100

typedef struct VOTER {
    int voterID;
    char password[50];
    char fullName[100];
    char constituency[100];
    bool isvoted;
} v;

#define MAX_CANDIDATES_PER_CONSTITUENCY 10
#define MAX_CONSTITUENCIES 10

struct Candidate {
    int candidateID;
    char fullName[100];
    int votes;     
};

struct TreeNode {
    char constituency[100];
    struct Candidate candidates[MAX_CANDIDATES_PER_CONSTITUENCY]; 
    int candidateCount;
    struct TreeNode *nextConstituency; 
};

struct TreeNode *createNode(const char *constituency) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->constituency, constituency);
        newNode->candidateCount = 0;
        newNode->nextConstituency = NULL;
    }
    return newNode;
}

void addCandidate(struct TreeNode *constituencyNode, int candidateID, const char *fullName, long int votes) {
    if (constituencyNode == NULL || constituencyNode->candidateCount >= MAX_CANDIDATES_PER_CONSTITUENCY) {
        printf("Invalid constituency or candidate limit reached!!!\n");
        return;
    }

    struct Candidate *newCandidate = &(constituencyNode->candidates[constituencyNode->candidateCount]);
    newCandidate->candidateID = candidateID;
    strcpy(newCandidate->fullName, fullName);
    newCandidate->votes = votes;

    constituencyNode->candidateCount++;
}

void displayCandidatesUnderConstituency(struct TreeNode *root, const char *constituencyName) {
    struct TreeNode *currentNode = root;
    while (currentNode != NULL) {
        if (strcmp(currentNode->constituency, constituencyName) == 0) {
            printf("Candidates under Constituency: %s\n", constituencyName);
            for (int i = 0; i < currentNode->candidateCount; ++i) {
                printf("%d  %s  %d\n",currentNode->candidates[i].candidateID, currentNode->candidates[i].fullName,currentNode->candidates[i].votes);
            }
            return;
        }
        currentNode = currentNode->nextConstituency;
    }
    printf("Constituency '%s' not found or has no candidates!!!\n", constituencyName);
}

struct TreeNode *createCandidates() {
    struct TreeNode *root = NULL;
    struct TreeNode *currentConstituency = NULL;
    char choice;

    root = createNode("National");

    do {
        char constituencyName[100];
        printf("\nEnter constituency name: ");
        scanf(" %[^\n]", constituencyName);

        struct TreeNode *newConstituency = createNode(constituencyName);
        if (newConstituency == NULL) {
            printf("Memory allocation failed!!!\n");
            return NULL;
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

            printf("\nDo you want to add another candidate for %s? (Y/N): ", constituencyName);
            scanf(" %c", &choice);
            printf("\n");
        } while (choice == 'Y' || choice == 'y');

        printf("Do you want to add candidates for a new constituency? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    return root;
}

void executeCandidateManagement() {
    struct TreeNode *root = createCandidates();
    char consti[100]; 
    printf("Enter your constituency name: ");
    scanf("%99s", consti);
}

v *a[NUMBER_OF_VOTERS];

void initial() {
    for (int i = 0; i < NUMBER_OF_VOTERS; i++) {
        a[i] = NULL;
    }
}

int Hash(int key) {
    int h;
    h = key % NUMBER_OF_VOTERS;
    return h;
}

int insert() {
    int key;
    printf("Enter your voter id:\n");
    scanf("%d", &key);
    int index = Hash(key);
    int i = 0;
    while (a[index] != NULL && i < NUMBER_OF_VOTERS) {
        index = (index + 1) % NUMBER_OF_VOTERS;
        i++;
    }
    if (i >= NUMBER_OF_VOTERS) {
        printf("Hash table is full!\n");
        return -1;
    }
    v *n2 = (v *)malloc(sizeof(v));
    n2->voterID = key;
    char name[100];
    char pass[50];
    char cons[100];
    printf("Enter your Full Name:\n");
    scanf("%s", name);
    printf("Enter your Password:\n");
    scanf("%s", pass);
    printf("Enter your Constituency:\n");
    scanf("%s", cons);
    strcpy(n2->fullName, name);
    strcpy(n2->password, pass);
    strcpy(n2->constituency, cons);
    n2->isvoted = false;
    a[index] = n2;
    return 1;
}

int search() {
    int key;
    char pass[50];
    printf("Enter your VoterID:\n");
    scanf("%d", &key);
    printf("Enter your password:\n");
    scanf("%s", pass);
    int i = 0;
    int index = Hash(key);
    while (a[index] != NULL && i < NUMBER_OF_VOTERS) {
        if (a[index]->voterID == key && strcmp(a[index]->password, pass) == 0) {
            return index + 1;
        }
        index = (index + 1) % NUMBER_OF_VOTERS;
        i++;
    }
    printf("User does not exist or password is incorrect!!!\n");
    return -1;
}

void cast(int index, const char* constituency, const char* candidate,struct TreeNode* root) {
    bool candidateFound = false;
    struct TreeNode *currentNode = root; 
    while (currentNode != NULL) {
        if (strcmp(currentNode->constituency, constituency) == 0) {
            for (int i = 0; i < currentNode->candidateCount; ++i) {
                if (strcmp(currentNode->candidates[i].fullName, candidate) == 0) {
                    candidateFound = true;
                    currentNode->candidates[i].votes++; 
                    break;
                }
            }
            break;
        }
        currentNode = currentNode->nextConstituency;
    }

    if (!candidateFound) {
        printf("Invalid candidate for the constituency!\n");
        return;
    }

    if (a[index]->isvoted == true) {
        printf("You have already voted. Thank you!\n");
    } else {
        a[index]->isvoted = true;
        printf("Your vote has been cast successfully!\n");
    }
}


int main() {
    int choice, res, index;
    struct TreeNode *root = NULL;

    initial();

    do {
        printf("\n\t\t\t\t\tWELCOME TO ELECTION COMMISSION OF INDIA!!!\n\n1. Register as Candidate\n2. Register as Voters\n3. Voter Login\n4. Cast Votes\n5. Display Constituency details\n6. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 2:
                res = insert();
                if (res == 1) {
                    printf("Registration successful as a voter!\n");
                } else if (res == -1) {
                    printf("Registration failed. Hash table is full!\n");
                }
                printf("\n");
                break;

            case 1:
                root = createCandidates();
                if (root != NULL) {
                    printf("\nRegistered as candidate successfully!!!\n");
                }
                printf("\n");
                break;

            case 3:
                {
                    int res = search();
                    if(res==1)
                        printf("Voter Login done successfully!!!");
                    else
                        printf("Voter Login failed!!!");
                    printf("\n");
                    break;
                }

            case 4:
                if (root == NULL) {
                    printf("Candidates not yet initialized!\n");
                    break;
                }
                int index;
                printf("Enter your VOTER ID: ");
                scanf("%d", &index);
                index=Hash(index);
                if (index < 1 || index > NUMBER_OF_VOTERS) {
                    printf("Invalid index!\n");
                    printf("\n");
                    break;
                }

                char voterConsti[100];
                char candidateName[100];

                printf("Enter your constituency name: ");
                scanf("%99s", voterConsti);
                printf("Enter candidate's name: ");
                scanf("%99s", candidateName);
                cast(index, voterConsti, candidateName, root);
                break;

            case 6:
                printf("Exiting...\n");
                printf("\n");
                break;
            
            case 5:
            {
                char voterConsti[100];
                printf("\nEnter your constituency name: ");
                scanf("%99s", voterConsti);
                displayCandidatesUnderConstituency(root,voterConsti);
                printf("\n");
            }

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}
