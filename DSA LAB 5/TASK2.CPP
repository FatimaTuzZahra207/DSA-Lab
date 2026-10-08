
#include <iostream>
#include <string>
using namespace std;

struct Job {
    int id, pages;
    string document;
    Job* next;
};

class Queue {
    Job* front;
    Job* rear;
    int count;

public:
    Queue() {
        front = rear = NULL;
        count = 0;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void addJob(int id, string doc, int pages) {
        Job* newJob = new Job{id, pages, doc, NULL};

        if (isEmpty())
            front = rear = newJob;
        else {
            rear->next = newJob;
            rear = newJob;
        }

        count++;
        cout << "Job added: " << id << endl;
    }

    void processJob() {
        if (isEmpty()) {
            cout << "Queue is empty. No job to process.\n";
            return;
        }

        Job* temp = front;
        cout << "Processing: " << temp->id << " "
             << temp->document << " (" << temp->pages
             << " pages)\n";

        front = front->next;
        delete temp;
        count--;

        if (front == NULL)
            rear = NULL;
    }

    void viewNextJob() {
        if (isEmpty()) {
            cout << "No jobs waiting.\n";
            return;
        }

        cout << "Next job: " << front->id << " "
             << front->document << ", "
             << front->pages << " pages\n";
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        Job* temp = front;
        while (temp != NULL) {
            cout << temp->id << " | " << temp->document
                 << " | " << temp->pages << " pages\n";
            temp = temp->next;
        }
    }

    void countJobs() {
        cout << "Waiting jobs: " << count << endl;
    }

    void clearQueue() {
        while (!isEmpty()) {
            Job* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
        cout << "Queue cleared.\n";
    }

    ~Queue() {
        clearQueue();
    }
};

int main() {
    Queue q;

    q.addJob(101, "Assignment1.pdf", 10);
    q.addJob(102, "Report.docx", 25);
    q.addJob(103, "Notes.pdf", 5);
    q.addJob(104, "LabTask.docx", 15);

    cout << "\nAll jobs:\n";
    q.displayQueue();

    cout << "\nProcess two jobs:\n";
    q.processJob();
    q.processJob();

    cout << "\nRemaining jobs:\n";
    q.displayQueue();

    cout << "\nAdd a new job:\n";
    q.addJob(105, "Project.pdf", 20);

    q.viewNextJob();
    q.countJobs();

    cout << "\nProcess all remaining jobs:\n";
    while (!q.isEmpty())
        q.processJob();

    cout << "\nTry processing an empty queue:\n";
    q.processJob();

    q.clearQueue();
    return 0;
}

