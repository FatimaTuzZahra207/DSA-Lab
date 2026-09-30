#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Node representing one song
struct Song {
    int id;
    string name;
    int minutes, seconds;
    Song *next, *prev;
    Song(int i, string n, int m, int s)
        : id(i), name(n), minutes(m), seconds(s), next(nullptr), prev(nullptr) {}
};

class Playlist {
    Song *head, *tail, *current;   // current = song being "played"
public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~Playlist() {                  // free all nodes (no memory leaks)
        while (head) { Song *t = head; head = head->next; delete t; }
    }

    Song* find(int id) {
        for (Song *p = head; p; p = p->next) if (p->id == id) return p;
        return nullptr;
    }

    // 1. Add song at the end
    void addSong(int id, string name, int m, int s) {
        if (find(id)) { cout << "Song ID already exists!\n"; return; }
        Song *n = new Song(id, name, m, s);
        if (!head) head = tail = current = n;
        else { tail->next = n; n->prev = tail; tail = n; }
        cout << "Song added.\n";
    }

    // 2. Delete song by ID
    void deleteSong(int id) {
        Song *p = find(id);
        if (!p) { cout << "Song not found.\n"; return; }
        if (p == current) current = p->next ? p->next : p->prev;
        if (p->prev) p->prev->next = p->next; else head = p->next;
        if (p->next) p->next->prev = p->prev; else tail = p->prev;
        delete p;
        cout << "Song deleted.\n";
    }

    static void show(Song *p) {
        cout << "ID: " << p->id << " | " << p->name << " | "
             << p->minutes << ":" << (p->seconds < 10 ? "0" : "") << p->seconds << "\n";
    }

    // Display forward
    void displayForward() {
        if (!head) { cout << "Playlist is empty.\n"; return; }
        for (Song *p = head; p; p = p->next) show(p);
    }

    // Display backward
    void displayBackward() {
        if (!tail) { cout << "Playlist is empty.\n"; return; }
        for (Song *p = tail; p; p = p->prev) show(p);
    }

    // Search by ID
    void search(int id) {
        Song *p = find(id);
        if (p) { cout << "Found -> "; show(p); }
        else cout << "Song not found.\n";
    }

    // Play next / previous
    void playCurrent() {
        if (!current) { cout << "Playlist is empty.\n"; return; }
        cout << "Now playing -> "; show(current);
    }
    void playNext() {
        if (!current) { cout << "Playlist is empty.\n"; return; }
        if (!current->next) { cout << "End of playlist reached.\n"; return; }
        current = current->next; playCurrent();
    }
    void playPrev() {
        if (!current) { cout << "Playlist is empty.\n"; return; }
        if (!current->prev) { cout << "Start of playlist reached.\n"; return; }
        current = current->prev; playCurrent();
    }

    //Reverse in place by swapping next/prev of every node
    void reverse() {
        Song *p = head;
        while (p) {
            Song *tmp = p->next;
            p->next = p->prev;
            p->prev = tmp;
            p = tmp;               // tmp was the old next
        }
        Song *t = head; head = tail; tail = t;
        cout << "Playlist reversed.\n";
    }
};

int main() {
    Playlist pl;
    int choice;
    do {
        cout << "\n===== PLAYLIST MENU =====\n"
             << "1. Add Song\n2. Delete Song\n3. Display Forward\n4. Display Backward\n"
             << "5. Search Song\n6. Play Next\n7. Play Previous\n8. Play Current\n"
             << "9. Reverse Playlist\n0. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            int id, m, s; string name;
            cout << "Song ID: "; cin >> id;
            cout << "Song Name: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, name);
            cout << "Duration (minutes seconds): "; cin >> m >> s;
            pl.addSong(id, name, m, s);
        } else if (choice == 2) { int id; cout << "ID to delete: "; cin >> id; pl.deleteSong(id); }
        else if (choice == 3) pl.displayForward();
        else if (choice == 4) pl.displayBackward();
        else if (choice == 5) { int id; cout << "ID to search: "; cin >> id; pl.search(id); }
        else if (choice == 6) pl.playNext();
        else if (choice == 7) pl.playPrev();
        else if (choice == 8) pl.playCurrent();
        else if (choice == 9) pl.reverse();
    } while (choice != 0 && cin);
    cout << "Goodbye!\n";
    return 0;
}
