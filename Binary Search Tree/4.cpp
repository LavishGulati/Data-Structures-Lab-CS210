#include <iostream>
#include <fstream>
using namespace std;

typedef struct queueNode{
    string fileName;
    struct queueNode *next;
} queueNode;

typedef struct queue{
    queueNode *front;
    queueNode *rear;
    int size;
} queue;

typedef struct folder{
    struct folder *parentFolder;
    string folderName;
    struct folder *subFolder;
    queue *file;
} folder;

queue *createQueue(){
    queue *newQueue = new queue;
    newQueue->front = NULL;
    newQueue->rear = NULL;
    newQueue->size = 0;
    return newQueue;
}

folder *createFolder(string name){
    folder *newFolder = new folder;
    newFolder->folderName = name;
    newFolder->parentFolder = NULL;
    newFolder->subFolder = NULL;
    newFolder->file = createQueue();
    return newFolder;
}

queueNode *createQueueNode(string name){
    queueNode *newQueueNode = new queueNode;
    newQueueNode->fileName = name;
    newQueueNode->next = NULL;
    return newQueueNode;
}

void insertFile(queue *file, string name){
    if(file->front == NULL){
        queueNode *newQueueNode = createQueueNode(name);
        file->front = newQueueNode;
        file->rear = newQueueNode;
        file->size = 1;
    }
    else{
        queueNode *newQueueNode = createQueueNode(name);
        file->rear->next = newQueueNode;
        file->rear = newQueueNode;
        (file->size)++;
    }
}

void createFile(folder *root, string name){
    insertFile(root->file, name);
    cout << "Created " << name << " in " << root->folderName << endl;
}

folder *createFolder(folder *root, string name){
    folder *newFolder = createFolder(name);
    newFolder->parentFolder = root;
    root->subFolder = newFolder;

    cout << "Made " << name << " in " << root->folderName << endl;
    return newFolder;
}

void deleteList(queueNode *head){
    if(head == NULL) return;

    deleteList(head->next);
    delete head;
}

void deleteQueue(queue *file){
    deleteList(file->front);
    delete file;
}

void deleteFolder(folder *root){
    if(root == NULL) return;

    deleteFolder(root->subFolder);

    deleteQueue(root->file);
    delete root;
}

folder *back(folder *root){
    if(root->parentFolder == NULL){
        cout << "Cannot back from root" << endl;
        return root;
    }

    folder *parent = root->parentFolder;
    parent->subFolder = NULL;

    cout << "Back from " << root->folderName << endl;

    deleteFolder(root);
    return parent;
}

void deleteFile(folder *root){
    queue *q = root->file;

    if(q->size == 0){
        cout << "Cannot delete from " << root->folderName << endl;
        return;
    }

    queueNode *temp = q->front;
    q->front = temp->next;
    if(q->front == NULL) q->rear = NULL;
    cout << "Deleted " << temp->fileName << " from " << root->folderName << endl;
    delete temp;
    (q->size)--;
}

int main(){
    folder *root = createFolder("root");

    ifstream inputFile;
    inputFile.open("input.txt");

    string command, name;

    while(1){
        inputFile >> command;
        if(command == "-1") break;

        if(command == "CREATE"){
            string name;
            inputFile >> name;
            createFile(root, name);
        }
        else if(command == "NEW"){
            string name;
            inputFile >> name;
            root = createFolder(root, name);
        }
        else if(command == "BACK"){
            root = back(root);
        }
        else if(command == "DELETE"){
            deleteFile(root);
        }
    }
}
