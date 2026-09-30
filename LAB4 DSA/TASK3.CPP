#include <iostream>
#include <string>
using namespace std;
struct Bit {
    int bit;
    Bit *next, *prev;
    Bit(int b) : bit(b), next(nullptr), prev(nullptr) {}
};
class BinaryDLL {
public:
    Bit *head, *tail;
    int size;
    BinaryDLL() : head(nullptr), tail(nullptr), size(0) {}
    BinaryDLL(const BinaryDLL &o) : head(nullptr), tail(nullptr), size(0) {  // deep copy
        for (Bit *p = o.head; p; p = p->next) pushBack(p->bit);
    }
    BinaryDLL& operator=(const BinaryDLL &o) {                              // deep assignment
        if (this != &o) { clear(); for (Bit *p = o.head; p; p = p->next) pushBack(p->bit); }
        return *this;
    }
    ~BinaryDLL() { clear(); }
    void clear() {
        while (head) { Bit *t = head; head = head->next; delete t; }
        tail = nullptr; size = 0;
    }
    void pushBack(int b) {
        Bit *n = new Bit(b);
        if (!tail) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
        size++;
    }
    void pushFront(int b) {
        Bit *n = new Bit(b);
        if (!head) head = tail = n;
        else { n->next = head; head->prev = n; head = n; }
        size++;
    }
    // Pad with leading zeros so size is a multiple of 8
    void pad8() { while (size % 8 != 0 || size == 0) pushFront(0); }

    // Store binary number
    void store(const string &s) {
        clear();
        for (char c : s) pushBack(c - '0');
        pad8();
    }
    void display() const {
        int i = 0;
        for (Bit *p = head; p; p = p->next, i++) {
            cout << p->bit;
            if ((i + 1) % 8 == 0 && p->next) cout << " ";   // space between 8-bit blocks
        }
        cout << "\n";
    }
    // One's complement: flip every bit
    void onesComplement() { for (Bit *p = head; p; p = p->next) p->bit ^= 1; }
};
// Binary addition (traverse from LSB to MSB, carrying)
// fixedWidth = true -> result keeps the same width (overflow carry is dropped)
BinaryDLL add(const BinaryDLL &a, const BinaryDLL &b, bool fixedWidth = false) {
    BinaryDLL r;
    Bit *pa = a.tail, *pb = b.tail;
    int carry = 0;
    while (pa || pb) {
        int s = carry + (pa ? pa->bit : 0) + (pb ? pb->bit : 0);
        r.pushFront(s % 2);
        carry = s / 2;
        if (pa) pa = pa->prev;
        if (pb) pb = pb->prev;}
    if (carry && !fixedWidth) r.pushFront(1);
    r.pad8();
    return r;
}
//Two's complement = one's complement + 1
BinaryDLL twosComplement(const BinaryDLL &a) {
    BinaryDLL c(a);
    c.onesComplement();
    BinaryDLL one;
    for (int i = 0; i < a.size - 1; i++) one.pushBack(0);
    one.pushBack(1);
    return add(c, one, true);
}
// Multiplication = repeated addition + shifting
BinaryDLL multiply(const BinaryDLL &a, const BinaryDLL &b) {
    BinaryDLL result; result.store("0");
    BinaryDLL shifted(a);
    for (Bit *p = b.tail; p; p = p->prev) {       // LSB of b first
        if (p->bit == 1) result = add(result, shifted);  // add shifted multiplicand
        shifted.pushBack(0);                             // shift left by 1
    }
    return result;
}
// Convert to decimal
unsigned long long toDecimal(const BinaryDLL &a) {
    unsigned long long v = 0;
    for (Bit *p = a.head; p; p = p->next) v = v * 2 + p->bit;
    return v;
}

bool valid(const string &s) {
    if (s.empty()) return false;
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}

int main() {
    BinaryDLL A, B;
    string s;
    int choice;
    do {
        cout << "\n===== BINARY DLL MENU =====\n"
             << "1. Store Number A\n2. Store Number B\n3. 1's Complement of A\n"
             << "4. 1's Complement of B\n5. 2's Complement of A\n6. 2's Complement of B\n7. Add A + B\n8. Multiply A x B\n"
             << "9. Convert A to Decimal\n10. Convert B to Decimal \n11. Display A and B\n0. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1 || choice == 2) {
            cout << "Enter binary bits: "; cin >> s;
            if (!valid(s)) { cout << "Invalid! Use only 0 and 1.\n"; continue; }
            (choice == 1 ? A : B).store(s);
            cout << "Stored: "; (choice == 1 ? A : B).display();
        } else if (choice == 3) {
            BinaryDLL t(A); t.onesComplement();
            cout << "A       = "; A.display(); cout << "1's comp= "; t.display();
        } 
        else if (choice == 4) {
            BinaryDLL t(B); t.onesComplement();
            cout << "B       = "; B.display(); cout << "1's comp= "; t.display();
        }
        else if (choice == 5) {
            BinaryDLL t = twosComplement(A);
            cout << "A       = "; A.display(); cout << "2's comp= "; t.display();
        }
        else if (choice == 6) {
            BinaryDLL t = twosComplement(B);
            cout << "B       = "; B.display(); cout << "2's comp= "; t.display();
        } else if (choice == 7) {
            BinaryDLL t = add(A, B);
            cout << "A = "; A.display(); cout << "B = "; B.display();
            cout << "Sum = "; t.display(); cout << "Decimal: " << toDecimal(t) << "\n";
        } else if (choice == 8) {
            BinaryDLL t = multiply(A, B);
            cout << "A = "; A.display(); cout << "B = "; B.display();
            cout << "Product = "; t.display(); cout << "Decimal: " << toDecimal(t) << "\n";
        } else if (choice == 9) {
            cout << "A = "; A.  display(); cout << "Decimal: " << toDecimal(A) << "\n";
        } else if (choice == 11) {
            cout << "A = "; A.display(); cout << "B = "; B.display();
        }
        else if (choice=10){
             cout << "B = "; B.display(); cout << "Decimal: " << toDecimal(B) << "\n";
        }
    } while (choice != 0 && cin);
    return 0;
}