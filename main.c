#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct course *Course;
typedef struct topic *Topic;
typedef struct hashNode *Hash;
struct course {
    char name[30];
    int hour;
    char code[30];
    char department[30];
    Topic topicsList;

};
struct topic {
    char topic[30];
    Topic next;
};
struct hashNode {
    int flag; // -1= deleted, 0= empty, 1=Occupied.
    Course value;
    char key[30];
};

int ifPrime(int n);

int getPrime(int n);

int getPrime2(int n);

int isLast(Topic);

int isEmpty(Topic);

Topic makeEmpty(Topic);

Topic Find(char key[30], Topic list);

Topic FindPrev(char key[30], Topic list);

void Delete(char key[30], Topic list);

void Insert(char data[30], Topic list);

void DeleteList(Topic list);

void printTopics(Topic topicsList);

void printCourse(Course element);

void hashInitial(int size);

void hashInitial2(int size);

void hashFree();

int initialIndex(char key[30]);

void insertLinearHash(char key[30], Course value);

void insertDoubleHash(char key[30], Course value);

void linearHashTableDelete();

int linearHashFind(char *key);

int doubleHashFind(char *key);

void linearHashDisplay();

void doubleHashDisplay();

float loadFactor1(int, int);

void deleteLinearElement(char key[30]);

void deleteDoubleElement(char key[30]);

void reInsert(struct hashNode);

void reHash();

int summation(char key[30]);

int hashCode1(char key[30]);

int hashCode2(char key[30]);

int linearCapacity = 77;
int doubleCapacity = 77;
int linearSize = 0;
int doubleSize = 0;
int numberOfCollision1 = 0;
int numberOfCollision2 = 0;

Hash linearHashTable;
Hash doubleHashTable;

int main() {

    // Create initialize hash tables.
    linearHashTable = (Hash) malloc(sizeof(struct hashNode) * linearCapacity);
    hashInitial(linearSize);
    doubleHashTable = (Hash) malloc(sizeof(struct hashNode) * doubleCapacity);
    hashInitial2(doubleCapacity);

    FILE *file;
    file = fopen("offered_courses.txt", "r");
    char line[200];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            char name[30], code[30], dep[30], topicLine[120];
            int hours = 0;
            Topic topics = NULL;
            topics = makeEmpty(topics);
            sscanf(line, "%[^:]:%d#%[^#]#%[^/]/%[^\n]", name, &hours, code, dep, topicLine);
            char *token = strtok(topicLine, ",");
            while (token != NULL) {
                Insert(topicLine, topics);
                token = strtok(NULL, ",");
            }
            // create new node with inserted data.
            Course temp;
            temp = (Course) malloc(sizeof(struct course));
            strcpy(temp->name, name);
            strcpy(temp->code, code);
            strcpy(temp->department, dep);
            temp->hour = hours;
            temp->topicsList = topics;
            // insert the nodes in the hash tables.
            insertLinearHash(name, temp);
            insertDoubleHash(name, temp);
            //printf("%s   %d   %s   %s    %s\n", name, hours, code, dep, topicLine);
        }
    }
//    int code = summation("ab");
//    printf("key = %d\tHash 2 = %d\n", code, hashCode2("ab"));

    printf("\n1. Print hashed tables (including empty spots).\n"
           "2. Print out table size and the load factor.\n"
           "3. Print out the used hash functions.\n"
           "4. Insert a new record to hash table (insertion will be done on both hash tables).\n"
           "5. Search for a specific word (specify which table to search in).\n"
           "6. Delete a specific record (from both tables).\n"
           "7. Compare between the two methods in terms of number of collisions occurred.\n"
           "8. Save hash table back to a file named saved_courses.txt (of the double hashing)\n"
           "Enter 0 to exit.\n");

    int s;
    printf("Select your choice \n");
    scanf("%d", &s);
    while (s != 0) {
        switch (s) {
            case 1: {//display data in the hash tables
                linearHashDisplay();
                doubleHashDisplay();
                printf("Number Of Collision in Table 1 = %d\n", numberOfCollision1);
                printf("Number Of Collision in Table 2 = %d\n", numberOfCollision2);
                break;
            }
            case 2: {//print out the size and Load Factor for both tables.
                printf(" Table 1 size = %d, Number of element in the table = %d, Load Factor = %0.2f\n", linearCapacity,
                       linearSize, loadFactor1(linearCapacity, linearSize));
                printf(" Table 2 size = %d, Number of element in the table = %d, Load Factor = %0.2f\n", doubleCapacity,
                       doubleSize, loadFactor1(doubleCapacity, doubleSize));
                break;
            }
            case 3: {//print out the function used in probing the indexes.
                printf("Linear Probing Function : h(x) = (i+1) Module (Table Size)\n");
                printf("Double Probing Function : h(x) = (Hash1(key)+Hash2(key)) Module (Table Size)\n");
                break;
            }
            case 4: {//insert new node from user into both tables.
                //Introduction to reFnch:3#FREN111#French Language/letters, numbers, greetings, grammars, statements
                printf("Please enter the data of the new record, in this form:\n"
                       "Course:CreditHours#CourseCode/topic1, topic2, ..,topicN\n");
                char dataLine[200], out, name[30], code[30], dep[30], topicLine[120];
                int hours = 0;
                scanf("%c", &out);
                scanf("%[^\n]", dataLine);
                Topic topics = NULL;
                topics = makeEmpty(topics);
                sscanf(dataLine, "%[^:]:%d#%[^#]#%[^/]/%[^\n]", name, &hours, code, dep, topicLine);
                char *token = strtok(topicLine, ",");
                while (token != NULL) {
                    Insert(topicLine, topics);
                    token = strtok(NULL, ",");
                }
                Course temp;
                temp = (Course) malloc(sizeof(struct course));
                strcpy(temp->name, name);
                strcpy(temp->code, code);
                strcpy(temp->department, dep);
                temp->hour = hours;
                temp->topicsList = topics;
                insertLinearHash(name, temp);
                insertDoubleHash(name, temp);
                break;
            }
            case 5: {//search for a specific node in a specific table.
                printf("Enter a Key to search for:\n");
                char out, key[30];
                scanf("%c", &out);
                scanf("%[^\n]", key);
                printf("Please choose witch table:\n"
                       "1-) Table 1\n2-) Table 2\n");
                int selection = 0, result = 0;
                scanf("%d", &selection);
                if (selection == 1)
                    result = linearHashFind(key);
                else if (selection == 2)
                    result = doubleHashFind(key);
                else
                    printf("Search Failed, you should choose one of the two cases.\n");
                if (result == -1)
                    printf("The key not found!\n");
                else
                    printf("The key has been found at index %d\n", result);
                break;
            }
            case 6: {//delete a node by its key from both tables.
                printf("Enter a Key to delete:\n");
                char out, key[30];
                scanf("%c", &out);
                scanf("%[^\n]", key);

                deleteLinearElement(key);
                deleteDoubleElement(key);
                break;
            }
            case 7: {//compare between the two hash tables.
                printf("Table 1 \"Linear Probing\" : Number Of Collision = %d\n", numberOfCollision1);
                printf("Table 2 \"Double Probing\" : Number Of Collision = %d\n", numberOfCollision2);
                //printf("Hence, Double Probing is better than the other one\n");
                break;
            }
            case 8: {//print out the double probing hash table to the output file.
                FILE *outFile;
                outFile = fopen("saved_courses.txt", "w");
                if (outFile) {
                    for (int i = 0; i < doubleCapacity; ++i) {
                        if (doubleHashTable[i].flag == 1) {
                            fprintf(outFile, "%d. %-30s,    %-7d,    %-15s,    %-25s,   ", i,
                                    doubleHashTable[i].value->name,
                                    doubleHashTable[i].value->hour, doubleHashTable[i].value->code,
                                    doubleHashTable[i].value->department);
                            Topic ptr;
                            ptr = doubleHashTable[i].value->topicsList;
                            if (isEmpty(doubleHashTable[i].value->topicsList))
                                fprintf(outFile, "Empty List!\n");
                            else {
                                ptr = ptr->next;
                                while (ptr != NULL) {
                                    fprintf(outFile, "\"%s\"", ptr->topic);//keep printing all topics
                                    if (ptr->next == NULL)//print . at the end of the topics
                                        fprintf(outFile, ".");
                                    else
                                        fprintf(outFile, ", ");
                                    ptr = ptr->next;
                                }
                            }
                            fprintf(outFile, "\n");
                        } else if (doubleHashTable[i].flag == -1) {
                            fprintf(outFile, "%d-) Deleted Node\n");
                        } else
                            fprintf(outFile, "%d-) ---------- \n", 1 + i);
                        // print topics.
                    }
                    //printf("Number Of Collision in Table 1 = %d\n", numberOfCollision1);
                    fprintf(outFile, "Number Of Collision in Table 2 = %d\n", numberOfCollision2);
                } else
                    printf("File Not Found\n");
                fclose(outFile);
                break;
            }
            default:
                printf("No case with number %d, please select 1-9", s);
        }
        printf("\n1. Print hashed tables (including empty spots).\n"
               "2. Print out table size and the load factor.\n"
               "3. Print out the used hash functions.\n"
               "4. Insert a new record to hash table (insertion will be done on both hash tables).\n"
               "5. Search for a specific word (specify which table to search in).\n"
               "6. Delete a specific record (from both tables).\n"
               "7. Compare between the two methods in terms of number of collisions occurred.\n"
               "8. Save hash table back to a file named saved_courses.txt (of the double hashing)\n"
               "Enter 0 to exit.\n");
        printf("Your selection :\n");
        scanf("%d", &s);
    }

    fclose(file);
    return 0;
}

void insertDoubleHash(char key[30], Course value) {
    // get hash codes to reach the index.
    int hash1 = hashCode1(key);
    int hash2 = hashCode2(key);
    int index = hash1;
    int i = 1;
    // check if the  table is full.
    if (doubleSize == doubleCapacity) {
        printf("\\n Hash Table is full, cannot insert more items \\n");
        return;
    }
    /* probing through the table till reach empty node of get the specific node */
    while (doubleHashTable[index].flag == 1) {
        if (strcmp(doubleHashTable[index].key, key) == 0) {
            printf("Key is already present, hence update its value\n");
            doubleHashTable[index].value = value;
            return;
        }
        //update the index by calling hash codes.
        index = (index + hash2) % doubleCapacity;
        // break if the table id full.
        if (index == hash1) {
            printf("\nAdd is failed\n");
            return;
        }
    }
    if (index != hash1)
        numberOfCollision2++;
    // now store the data at the index.
    doubleHashTable[index].value = value;
    doubleHashTable[index].flag = 1;
    strcpy(doubleHashTable[index].key, key);
    doubleSize++;
    //printf("\n Key (%s) has been inserted \n", key);
}

int hashCode1(char key[30]) {
    int hashIndex;
    hashIndex = summation(key);
    return (hashIndex % doubleCapacity);
}

int hashCode2(char key[30]) {//double function.
    int hashIndex;
    hashIndex = summation(key);
    return (67 - (hashIndex % 67));
}

void reHash() {
    // printf("Checking Load Factor\n");
    printf("%0.2f", loadFactor1(linearCapacity, linearSize));
    if (loadFactor1(linearCapacity, linearSize) < 0.6511) {
        printf("No need to reHash\n");
        return;
    }
    printf("ReHashing\n");

    int temp = linearCapacity;
    linearCapacity = getPrime2(2 * linearCapacity);
    struct hashNode backUpTable[temp];
    //backUpTable = (Hash) malloc(sizeof(struct hashNode) * linearCapacity);
    for (int i = 0; i < temp; ++i) {
        backUpTable[i] = linearHashTable[i];
        linearHashTable[i].flag = 0;
        linearHashTable[i].value = NULL;
    }
    hashInitial(linearCapacity);
    linearSize = numberOfCollision1 = 0;
    for (int i = 0; i < temp; ++i) {
        if (backUpTable[i].flag == 1) {
            insertLinearHash(backUpTable[i].key, backUpTable[i].value);
        }
    }
    printf("\nsize = %d  Capacity = %d,    Factor = %0.2f \n", linearCapacity, linearSize,
           loadFactor1(linearCapacity, linearSize));
    printf("Rehashing DONE\n");
}

void hashInitial(int size) {//initialize the values in the  table
    int counter;
    for (counter = 0; counter < size; counter++) {
        linearHashTable[counter].value = NULL;
        linearHashTable[counter].flag = 0;
    }
}

void hashInitial2(int size) {//initialize the values in the  table
    int counter;
    for (counter = 0; counter < size; counter++) {
        doubleHashTable[counter].value = NULL;
        doubleHashTable[counter].flag = 0;
    }
}

float loadFactor1(int capacity, int size) {
    return ((float) size / (float) capacity);
}

int initialIndex(char key[30]) {
    int hashIndex = 0;
    hashIndex = summation(key);
    return (hashIndex % linearCapacity);
}

void insertLinearHash(char key[30], Course value) {
    /* get the hash key*/
    int index = initialIndex(key);
    int i = index;

    /* go through the table till reach an empty index.*/
    while (linearHashTable[i].flag == 1) {
        if (strcmp(linearHashTable[i].key, key) == 0) {
            /* case where already existing key matches the given key */
            printf("\n Key already exists, hence update number of collision \n");
            return;
        }
        //prob the hash index
        i = (i + 1) % linearCapacity;
        if (i == index) {
            printf("Hash linearCapacitytable is full, cannot insert any more item\n");
            return;
        }
    }
    if (i != index)
        numberOfCollision1++;
    //insert data into the table.
    linearHashTable[i].flag = 1;
    linearHashTable[i].value = value;
    strcpy(linearHashTable[i].key, key);
    linearSize++;
    //reHash();
}

void reInsert(struct hashNode node) {
    /* get the hash key*/
    int index = initialIndex(node.key);
    int i = index;

    while (linearHashTable[i].flag == 1) {
        if (strcmp(linearHashTable[i].key, node.key) == 0) {
            /* case where already existing key matches the given key */
            printf("\n Key already exists, hence update number of collision \n");
            return;
        }
        i = (i + 1) % linearCapacity;
        if (i == index) {
            printf("Hash table is full, cannot insert any more item\n");
            return;
        }
    }
//    if (i != index)
//        numberOfCollision1++;
    linearHashTable[i] = node;
    // linearSize++;
}

void deleteDoubleElement(char key[30]) {//delete an element from the double hash table.
    // get the hash index.
    int hash1 = hashCode1(key);
    int hash2 = hashCode2(key);
    int index = hash1;

    if (doubleSize == 0) {
        printf("\n Hash Table is empty \n");
    }
    /*probing through other elements*/
    while (doubleHashTable[index].flag != 0) {
        if (strcmp(doubleHashTable[index].key, key) == 0 && doubleHashTable[index].flag == 1) {
            doubleHashTable[index].flag = -1;
            doubleHashTable[index].value = NULL;
            doubleSize--;
            printf("\nkey (%s) has been removed \n", key);
            return;
        }
        index = (index + hash2) % doubleCapacity;
        if (index == doubleCapacity) {
            break;
        }
    }
    printf("\n Key (%d) does not exist \n", key);
}

void deleteLinearElement(char key[30]) {//delete an element from the linear hash table.

    int index = initialIndex(key);
    int i = index;
    /* probing through table until we reach the element.*/

    while (linearHashTable[i].flag != 0) {
        if (linearHashTable[i].flag == 1 && strcmp(linearHashTable[i].key, key) == 0) {
            // case when key matched the given key.
            linearHashTable[i].flag = -1;
            linearHashTable[i].value = NULL;
            linearSize--;
            printf("\nkey = %s has been deleted\n", key);
            return;
        }
        i = (i + 1) % linearCapacity;
        if (i == index) {
            break;
        }
    }
    printf("This key doesn't exist\n");
}

void linearHashTableDelete() {
    for (int i = 0; i < linearCapacity; ++i) {
        if (linearHashTable[i].flag == 1) {
            linearHashTable[i].flag = -1;
            linearHashTable[i].value = NULL;
        }
    }
    printf("This key doesn't exist\n");
}

int linearHashTableSize() {
    return linearSize;
}

int doubleHashFind(char *key) {//find an element by the keys.
    int hash1 = hashCode1(key);
    int hash2 = hashCode2(key);
    int index = hash1;

    if (doubleSize == 0) {
        printf("\n Hash Table is empty \n");
        return -1;
    }
    /*probing through other elements*/
    while (doubleHashTable[index].flag != 0) {
        if (strcmp(doubleHashTable[index].key, key) == 0 && doubleHashTable[index].flag == 1) {
            return index;
        }
        index = (index + hash2) % doubleCapacity;
        if (index == doubleCapacity) {
            break;
        }
    }
    return -1;
}

int linearHashFind(char *key) {
    int index = initialIndex(key);
    int i = index;
    /*probing through other elements*/
    while (linearHashTable[i].flag != 0) {
        if (linearHashTable[i].flag == 1 && strcmp(linearHashTable[i].key, key) == 0) {
            return i;
        }
        i = (i + 1) % linearCapacity;
        if (i == index)
            break;
    }
    printf("This key doesn't exist\n");
    return -1;
}

void linearHashDisplay() { // print the data in the table.
    int counter;
    printf("\n-------------- Printing the Hash Table 1 ----------------\n");
    for (counter = 0; counter < linearCapacity; counter++) {
        if (linearHashTable[counter].flag == 1) {
            printf("%d. ", counter);
            printCourse(linearHashTable[counter].value);
        } else if (linearHashTable[counter].flag == -1) {
            printf("%d. Deleted --------\n", counter);
        } else
            printf("%d. ----------\n");
    }
}

void doubleHashDisplay() {// print the data in the table.
    int counter;
    printf("\n-------------- Printing the Hash Table 2 ----------------\n");
    for (counter = 0; counter < doubleCapacity; counter++) {
        if (doubleHashTable[counter].flag == 1) {
            printf("%d. ", counter);
            printCourse(doubleHashTable[counter].value);
        } else if (doubleHashTable[counter].flag == -1) {
            printf("%d. Deleted --------\n", counter);
        } else
            printf("%d. ----------\n");
    }
}

void printTopics(Topic topicsList) {
    Topic ptr = topicsList;
    //int counter = 1;
    if (isEmpty(topicsList))
        printf("Empty List!\n");
    else {
        ptr = ptr->next;
        while (ptr != NULL) {
            printf("\"%s\"", ptr->topic);//keep printing all topics
            if (ptr->next == NULL)//print . at the end of the topics
                printf(".");
            else
                printf(", ");
            ptr = ptr->next;
        }
    }
    printf("\n");
}

void printCourse(Course element) {
    printf("%-30s,     %-5d,     %-15s,     %-25s", element->name, element->hour, element->code, element->department);
    //printTopics(element->topicsList);
    printf("\n");
}

Topic makeEmpty(Topic list) {
    if (list != NULL) {
        DeleteList(list);
    }
    list = (Topic) malloc(sizeof(struct topic));
    if (list == NULL)
        printf("Out Of Space\n");
    list->next = NULL;
    return list;
}

int isEmpty(Topic list) {
    return list->next == NULL;
}

int isLast(Topic ptr) {
    return ptr->next == NULL;
}

Topic Find(char key[30], Topic list) {
    Topic ptr;
    ptr = list->next;
    while (ptr != NULL && strcmp(key, ptr->topic) != 0) {
        ptr = ptr->next;
    }
    return ptr;
}

void DeleteList(Topic list) {
    Topic ptr, temp;
    ptr = list->next;
    list->next = NULL;
    while (ptr != NULL) {
        temp = ptr->next;
        free(temp);
        ptr = temp;
    }
}

Topic FindPrev(char key[30], Topic list) {
    Topic ptr;
    ptr = list;
    while (ptr->next != NULL && strcmp(ptr->next->topic, key) != 0) {
        ptr = ptr->next;
    }
    return ptr;
}

void Delete(char key[30], Topic list) {
    Topic ptr, temp;
    ptr = FindPrev(key, list);
    if (!isLast(ptr)) {
        temp = ptr->next;
        ptr->next = temp->next;
        free(temp);
    }
}

void Insert(char data[30], Topic list) {
    Topic ptr;
    ptr = (Topic) malloc(sizeof(struct topic));
    strcpy(ptr->topic, data);
    ptr->next = list->next;
    list->next = ptr;
}

int summation(char key[30]) {
    int sum = 0, i, len;

    len = (int) strlen(key);
    for (i = 0; i < len; i++) {
        sum = sum + key[i];
    }
    return sum;
}

/* to check if given input (i.e n) is prime or not */
int ifPrime(int n) {
    int i;
    if (n == 1 || n == 0) {
        return 0;
    }
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int getPrime(int n) {
    if (n % 2 == 0) {
        n--;
    }
    for (; !ifPrime(n); n -= 2);
    return n;
}

int getPrime2(int n) {
    if (n % 2 == 0) {
        n++;
    }
    for (; !ifPrime(n); n += 2);
    return n;
}