#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FRIEND_REQUESTS 100

struct User {
    int id;
    char name[100];
    int* friendRequests;
    int numFriendRequests;
};

struct Graph {
    int V;
    struct User* users;
    int** adjMatrix;
};

struct User createUser(int id, const char* name) {
    struct User user;
    user.id = id;
    strcpy(user.name, name);
    user.numFriendRequests = 0;
    user.friendRequests = (int*)malloc(sizeof(int) * 100);
    return user;
}

struct Graph* createSocialMediaGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->users = (struct User*)malloc(V * sizeof(struct User));
    graph->adjMatrix = (int**)malloc(V * sizeof(int*));

    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

int getUserIdByName(struct Graph* graph, const char* username) {
    for (int i = 0; i < graph->V; i++) {
        if (strcmp(graph->users[i].name, username) == 0) {
            return i;
        }
    }
    return -1; 
}
const char* getUsernameById(struct Graph* graph, int userId) {
    if (userId >= 0 && userId < graph->V) {
        return graph->users[userId].name;
    } else {
        return NULL; 
    }
}

void sendFriendRequest(struct Graph* graph,int senderId, const char* receiverName) {
    const char* senderName = getUsernameById(graph, senderId);
    //int senderId = getUserIdByName(graph, senderName);
    int receiverId = getUserIdByName(graph, receiverName);

    if (senderId != -1 && receiverId != -1) {
        for (int i = 0; i < graph->users[receiverId].numFriendRequests; i++) {
            if (graph->users[receiverId].friendRequests[i] == senderId) {
                printf("%s already has a friend request from %s.\n", receiverName, senderName);
                return;
            }
        }
        if (graph->users[receiverId].numFriendRequests < MAX_FRIEND_REQUESTS) {
            graph->users[receiverId].friendRequests[graph->users[receiverId].numFriendRequests] = senderId;
            graph->users[receiverId].numFriendRequests++;
            printf("Friend request sent from %s to %s.\n", senderName, receiverName);
        } else {
            printf("%s has too many pending friend requests.\n", receiverName);
        }
    } else {
        printf("User not found.\n");
    }
}
void addFriendship(struct Graph* graph, int userId1, int userId2) {
    if (userId1 >= 0 && userId1 < graph->V && userId2 >= 0 && userId2 < graph->V) {
        // graph->adjMatrix[userId1][userId2] = 1;
        graph->adjMatrix[userId2][userId1] = 1;
    }
}

void acceptFriendRequest(struct Graph* graph, int userId, int senderId) {
    if (userId >= 0 && userId < graph->V) {
        for (int i = 0; i < graph->users[userId].numFriendRequests; i++) {
            if (graph->users[userId].friendRequests[i] == senderId) {
                addFriendship(graph, userId, senderId);
                for (int j = i; j < graph->users[userId].numFriendRequests - 1; j++) {
                    graph->users[userId].friendRequests[j] = graph->users[userId].friendRequests[j + 1];
                }
                graph->users[userId].numFriendRequests--;
                break;
            }
        }
    }
}

void rejectFriendRequest(struct Graph* graph, int userId, int senderId) {
    if (userId >= 0 && userId < graph->V) {
        for (int i = 0; i < graph->users[userId].numFriendRequests; i++) {
            if (graph->users[userId].friendRequests[i] == senderId) {
                for (int j = i; j < graph->users[userId].numFriendRequests - 1; j++) {
                    graph->users[userId].friendRequests[j] = graph->users[userId].friendRequests[j + 1];
                }
                graph->users[userId].numFriendRequests--;
                break;
            }
        }
    }
}

void printUserProfile(struct Graph* graph, int userId) {
    if (userId >= 0 && userId < graph->V) {
        struct User user = graph->users[userId];
        printf("User Profile for %s (ID: %d)\n", user.name, user.id);
        printf("Friends: ");
        for (int i = 0; i < graph->V; i++) {
            if (graph->adjMatrix[userId][i] == 1) {
                printf("%s," ,graph->users[i].name);
                printf("\n");
            }
        }
        printf("\n");
        printf("Friend Requests: ");
        for (int i = 0; i < user.numFriendRequests; i++) {
            int senderId = user.friendRequests[i];
            printf("%s, ", graph->users[senderId].name);
            printf("(A) Accept or (R) Reject? ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'A' || choice == 'a') {
                acceptFriendRequest(graph, userId, senderId);
            } else if (choice == 'R' || choice == 'r') {
                rejectFriendRequest(graph, userId, senderId);
            }
        }
        printf("\n");
    } else {
        printf("User not found with ID: %d\n", userId);
    }
}

void displayMutualFriends(struct Graph* graph, int userId1, const char* receiverName) {
    int userId2 = getUserIdByName(graph, receiverName);
    if (userId1 >= 0 && userId1 < graph->V && userId2 >= 0 && userId2 < graph->V) {
        printf("Mutual Friends of %s and %s: ", graph->users[userId1].name, graph->users[userId2].name);
        for (int i = 0; i < graph->V; i++) {
            if (graph->adjMatrix[userId1][i] == 1 && graph->adjMatrix[userId2][i] == 1) {
                printf("%s,", graph->users[i].name);
            }
        }
        printf("\n");
    }
}

int searchUsersByName(struct Graph* graph, const char* name) {
    int found = 0;
    for (int i = 0; i < graph->V; i++) {
        if (strcmp(graph->users[i].name, name) == 0) {
            printf("User found: %s\n", name);
            found = 1;

        }
    }
    if (!found) {
        printf("User not found: %s\n", name);
    }
    return found;
}

void displayUserList(struct Graph* graph) {
    printf("User List:\n");
    for (int i = 0; i < graph->V; i++) {
        printf("%s\n", graph->users[i].name);
    }
}

void welcomeMessage() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}
void clearScreen() {
    printf("\033[H\033[J"); 
}
int main() {
int choice;
struct Graph* socialMedia;
clearScreen();
printf("Welcome to the Our Social Media App!\n");
welcomeMessage();
clearScreen();
int i;
int j;
char s[10];
    do {
        printf("\nMenu:\n");
        printf("1. Create ID.\n");
        printf("2. View all User.\n");
        printf("3. Veiw ur Profile.\n");
        printf("4. Send Friend request.\n");
        printf("5. View Mutuals.\n");
        printf("6. Search by Username.\n");
        printf("7. Exit the App.\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        

        switch (choice) {
            case 1:
             printf("enter the no of members:");
             int n;
             scanf("%d",&n);
             socialMedia = createSocialMediaGraph(n);
             int id=0;
             char a[10];
             char b[16];
             for(int i=0;i<n;i++){
                     printf("\n");
                     printf("enter your name:");
                     scanf("%s",&a);
                     socialMedia->users[i] = createUser(id,a); 
                     printf("Your ID number is:%d\nRemember your ID for future purpose.\n",id);
                     printf("Dont share your ID to anyone for Privacy purposes...");
                     id++;
                     printf("\n");
                   }
                break;
            case 2:
                displayUserList(socialMedia);
                break;
            case 3:
                printf("enter your id:");
                scanf("%d",&i);
                printUserProfile(socialMedia,i);
                break;
            case 4:
                printf("enter your id:");
                scanf("%d",&j);
                printf("enter the name whom you want to send friend request:");
                scanf("%s",&s);
                sendFriendRequest(socialMedia,j,s);
                break;
            case 5:
                printf("enter your id:");
                scanf("%d",&j);
                printf("enter the name whom you want to see the mutuals:");
                scanf("%s",&s);
                displayMutualFriends(socialMedia,j,s);
                break;
            case 6:
                printf("enter the name whom you want to search in the social media app:");
                scanf("%s",&s);
                searchUsersByName(socialMedia,s);
                break;
            case 7:
                clearScreen();
                printf("\nYou logged out from Social Media App...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1-4.\n");
                break;
        }
    } while (choice != 7);
  
}