#include <iostream>
#include <string>
using namespace std;

// Node for Queue
struct Node
{
    int jobID;
    string document;
    int pages;

    Node* next;
};

// Queue class
class Queue
{
private:
    Node* front;
    Node* rear;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Add job at rear
    void addJob(int id, string doc, int pageCount)
    {
        Node* newNode = new Node;

        newNode->jobID = id;
        newNode->document = doc;
        newNode->pages = pageCount;
        newNode->next = nullptr;

        // If queue is empty
        if (rear == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Job " << id << " added." << endl;
    }

    // Process job from front
    void processJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No job to process." << endl;
            return;
        }

        Node* temp = front;

        cout << "Processing Job: "
             << temp->jobID << " | "
             << temp->document << " | "
             << temp->pages << " pages" << endl;

        front = front->next;

        // If last job was removed
        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }

    // View next job
    void viewNextJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Next Job: "
             << front->jobID << " | "
             << front->document << " | "
             << front->pages << " pages" << endl;
    }

    // Display all jobs
    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }

        Node* current = front;

        cout << "\nJobs in Queue:" << endl;

        while (current != nullptr)
        {
            cout << "Job ID: " << current->jobID
                 << " | Document: " << current->document
                 << " | Pages: " << current->pages
                 << endl;

            current = current->next;
        }
    }

    // Count jobs
    int countJobs()
    {
        int count = 0;
        Node* current = front;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        return count;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return front == nullptr;
    }

    // Clear queue
    void clear()
    {
        while (!isEmpty())
        {
            Node* temp = front;

            front = front->next;

            delete temp;
        }

        rear = nullptr;
    }

    // Destructor
    ~Queue()
    {
        clear();
    }
};

int main()
{
    Queue printer;

    cout << "===== TASK 2: PRINTER JOB QUEUE =====" << endl;

    // Add jobs
    printer.addJob(101, "Assignment1.pdf", 10);
    printer.addJob(102, "Report.docx", 25);
    printer.addJob(103, "Notes.pdf", 5);
    printer.addJob(104, "LabTask.docx", 15);

    // 1. Display all jobs
    cout << "\n1. DISPLAY ALL JOBS" << endl;
    printer.displayQueue();

    // 2. Process two jobs
    cout << "\n2. PROCESS TWO JOBS" << endl;
    printer.processJob();
    printer.processJob();

    // 3. Display remaining jobs
    cout << "\n3. REMAINING JOBS" << endl;
    printer.displayQueue();

    // 4. Add new job
    cout << "\n4. ADD NEW JOB" << endl;
    printer.addJob(105, "Project.pdf", 20);

    // 5. Display next job
    cout << "\n5. NEXT JOB" << endl;
    printer.viewNextJob();

    // Count jobs
    cout << "Number of waiting jobs: "
         << printer.countJobs() << endl;

    // 6. Process all remaining jobs
    cout << "\n6. PROCESS ALL REMAINING JOBS" << endl;

    while (!printer.isEmpty())
    {
        printer.processJob();
    }

    // 7. Try processing from empty queue
    cout << "\n7. PROCESS FROM EMPTY QUEUE" << endl;
    printer.processJob();

    return 0;
}
