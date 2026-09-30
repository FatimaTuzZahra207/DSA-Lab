#include <iostream>
using namespace std;
struct Person {
    int id;
    Person *next;
    Person(int i) : id(i), next(nullptr) {}
};
// Create Circle
Person* createCircle(int n) {
    Person *head = new Person(1), *tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Person(i);
        tail = tail->next;
    }
    tail->next = head; // last node points back to first -->> circle
    return head;
}
// Display the circle once around
void displayCircle(Person *head) {
    Person *p = head;
    do { cout << p->id << " "; p = p->next; } while (p != head);
    cout << "\n";
}
int main() {
    int n, k;
    cout << "Enter number of people (N): "; cin >> n;
    cout << "Enter step count (k): ";       cin >> k;
    if (n < 1 || k < 1) { cout << "N and k must be positive.\n"; return 1; }
    Person *head = createCircle(n);
    cout << "Initial circle: "; displayCircle(head);
    // prev always trails the current person so we can unlink current
    Person *prev = head;
    while (prev->next != head) prev = prev->next;   // prev = last node
    Person *cur = head;
    cout << "Elimination order: ";
    int remaining = n;
    while (remaining > 1) {
        for (int i = 1; i < k; i++) { prev = cur; cur = cur->next; }  // count k people
        cout << cur->id << " ";
        prev->next = cur->next;    // unlink eliminated person
        delete cur;                // free memory
        cur = prev->next;          // counting resumes from next person
        remaining--;
    }
    cout << "\nSurvivor: Person " << cur->id << "\n";
    delete cur;
    return 0;
}