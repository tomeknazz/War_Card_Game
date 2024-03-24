#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <limits>
using namespace std;

class card {
public:
	enum rank { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };

	enum suit { clubs, diamonds, hearts, spades };

	explicit card(const rank r = ace, const suit s = spades) : rank_(r), suit_(s) {}

	int get_value() const {
		if (rank_ >= two && rank_ <= king)
			return rank_;
		else // A
			return 14;
	}

	void display() const {
		switch (rank_) {
		case ace: cout << 'A'; break;
		case two: cout << '2'; break;
		case three: cout << '3'; break;
		case four: cout << '4'; break;
		case five: cout << '5'; break;
		case six: cout << '6';break;
		case seven: cout << '7'; break;
		case eight: cout << '8'; break;
		case nine: cout << '9'; break;
		case ten: cout << 'T'; break;
		case jack: cout << 'J'; break;
		case queen: cout << 'Q';break;
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

class deck {
public:
	deck() {

		for (int s = card::clubs; s <= card::spades; ++s) {
			for (int r = card::ace; r <= card::king; ++r) {
				cards_.push_back(card(static_cast<card::rank>(r), static_cast<card::suit>(s)));
			}
		}
		shuffle();
	}

	void shuffle() {
		random_shuffle(cards_.begin(), cards_.end());
	}

	card deal_card() {
		const card card = cards_.back();
		cards_.pop_back();
		return card;
	}
private:
	vector<card> cards_;
};

struct table
{
	card card1;
	card card2;
	int player_score;
	int computer_score;
	int player_cards;
	int computer_cards;
	queue<card> player_queue;
	queue<card> computer_queue;

};

bool compare_cards(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score);

void war(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score);

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));

	deck deck;
	int player_score = 0;
	int computer_score = 0;
	int round = 1;
	table table;
	queue<card> war_queue;
	queue<card> player_queue;
	queue<card> computer_queue;

	for (int i = 0; i < 26; i++)
	{
		player_queue.push(deck.deal_card());
		computer_queue.push(deck.deal_card());
	}

	while (player_queue.size() > 0 && computer_queue.size() > 0)
	{
		cout << "komputer ilosc kart - " << computer_queue.size() << endl;
		cout << "Gracz ilosc kart - " << player_queue.size() << endl;
		cout << "Runda " << round << ": Gracz rzuca ";
		player_queue.front().display();
		cout << ". Komputer rzuca ";
		computer_queue.front().display();
		cout << "." << endl;
		if (!compare_cards(player_queue, computer_queue, war_queue, player_score, computer_score))
			break;
		cout << "---------------------------------------" << endl;

		round++;
		cout << "Naci�nij Enter aby kontynuowa�..." << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
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

bool compare_cards(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score)
{
	if (player_queue.empty() || computer_queue.empty()) {
		return false;
	}

	if (player_queue.front().get_value() > computer_queue.front().get_value()) {
		cout << "Gracz wygrywa te runde!" << endl;
		++player_score;
		player_queue.push(computer_queue.front());
		player_queue.push(player_queue.front());
		player_queue.pop();
		computer_queue.pop();

	}
	else if (player_queue.front().get_value() < computer_queue.front().get_value()) {
		cout << "Komputer wygrywa te runde!" << endl;
		++computer_score;
		computer_queue.push(computer_queue.front());
		computer_queue.push(player_queue.front());
		player_queue.pop();
		computer_queue.pop();


	}
	else {
		if (player_queue.front().get_value() == computer_queue.front().get_value()) {
			cout << " REMIS ------- WOJNA!" << endl;
			war_queue.push(player_queue.front());
			war_queue.push(computer_queue.front());
			player_queue.pop();
			computer_queue.pop();
			war(player_queue, computer_queue, war_queue, player_score, computer_score);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

void war(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score)
{
	war_queue.push(player_queue.front());
	war_queue.push(computer_queue.front());
	player_queue.pop();
	computer_queue.pop();
	cout << "gracz wyrzucil - ";
	player_queue.front().display();
	cout << endl;
	cout << "komputer  wyrzucil - ";
	computer_queue.front().display();
	cout << endl;
	if (player_queue.front().get_value() > computer_queue.front().get_value()) {
		cout << "Gracz wygrywa Wojne!" << endl;
		++player_score;
		computer_queue.pop();
		player_queue.pop();
		war_queue.push(player_queue.front());
		war_queue.push(computer_queue.front());
		if (!war_queue.empty())
		{
			while (!war_queue.empty())
			{
				player_queue.push(war_queue.front());
				war_queue.pop();
			}
		}
	}
	else if (player_queue.front().get_value() < computer_queue.front().get_value()) {
		cout << "Komputer wygrywa Wojne!" << endl;
		++computer_score;
		player_queue.pop();
		computer_queue.pop();
		war_queue.push(player_queue.front());
		war_queue.push(computer_queue.front());
		if (!war_queue.empty())
		{
			while (!war_queue.empty())
			{
				computer_queue.push(war_queue.front());
				war_queue.pop();
			}
		}
	}
	else {
		if (player_queue.front().get_value() == computer_queue.front().get_value()) {
			cout << " REMIS wojna trwa dalej!" << endl;
			war_queue.push(player_queue.front());
			war_queue.push(computer_queue.front());
			player_queue.pop();
			computer_queue.pop();
			war(player_queue, computer_queue, war_queue, player_score, computer_score);
		}
	}
}
