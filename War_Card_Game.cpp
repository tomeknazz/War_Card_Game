#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Klasa reprezentujaca karte
class card {
public:
	enum rank { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };

	enum suit { clubs, diamonds, hearts, spades };

	explicit card(const rank r = ace, const suit s = spades) : rank_(r), suit_(s) {}

    int get_value() const {
        // Wartosci kart
        if (rank_ >= two && rank_ <= ten)
            return rank_;
        else if (rank_ >= jack && rank_ <= king)
            return 10;
        else // ACE
            return 11;
    }

    void display() const {
        // Wyswietlanie karty
        switch (rank_) {
        case ace: cout << 'A'; break;
        case two: cout << '2'; break;
        case three: cout << '3'; break;
        case four: cout << '4'; break;
        case five: cout << '5'; break;
        case six: cout << '6'; break;
        case seven: cout << '7'; break;
        case eight: cout << '8'; break;
        case nine: cout << '9'; break;
        case ten: cout << 'T'; break;
        case jack: cout << 'J'; break;
        case queen: cout << 'Q'; break;
        case king: cout << 'K'; break;
        }
        switch (suit_) {
        case clubs: cout << 'C'; break;
        case diamonds: cout << 'D'; break;
        case hearts: cout << 'H'; break;
        case spades: cout << 'S'; break;
        }
    }

private:
    rank rank_;
    suit suit_;
};

// Klasa reprezentujaca talie kart
class deck {
public:
    deck() {
        // Tworzenie tali kart
        for (int s = card::clubs; s <= card::spades; ++s) {
            for (int r = card::ace; r <= card::king; ++r) {
                cards.push_back(card(static_cast<card::rank>(r), static_cast<card::suit>(s)));
            }
        }
        shuffle(); // Tasowanie talii
    }

    void shuffle() {
        random_shuffle(cards.begin(), cards.end());
    }

    card dealCard() {
        // Rozdanie karty
        const card card = cards.back();
        cards.pop_back();
        return card;
    }

private:
    vector<card> cards;
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora liczb losowych

    deck deck; // Stworzenie talii kart
    int player_score = 0;
    int computer_score = 0;

    for (int round = 1; round <= 26; ++round) { // 26 rund, bo 52 karty / 2 graczy
        card player_card = deck.dealCard();
        card computer_card = deck.dealCard();

        cout << "Runda " << round << ": Gracz rzuca ";
        player_card.display();
        cout << ". Komputer rzuca ";
        computer_card.display();
        cout << "." << endl;

        if (player_card.get_value() > computer_card.get_value()) {
            cout << "Gracz wygrywa te runde!" << endl;
            ++player_score;
        }
        else if (player_card.get_value() < computer_card.get_value()) {
            cout << "Komputer wygrywa te runde!" << endl;
            ++computer_score;
        }
        else {
            cout << "Remis w tej rundzie." << endl;
        }

        cout << "Aktualny wynik - Gracz: " << player_score << ", Komputer: " << computer_score << endl;
        cout << "---------------------------------------" << endl;
    }

    if (player_score > computer_score) {
        cout << "Gracz wygrywa gre!";
    }
    else if (player_score < computer_score) {
        cout << "Komputer wygrywa gre!";
    }
    else {
        cout << "Remis!";
    }

    return 0;
}