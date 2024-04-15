#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

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
	card player_card;
	card computer_card;
	size_t player_cards;
	size_t computer_cards;
	int round{};
	queue<card> player_queue;
	queue<card> computer_queue;
};

void start_screen();

bool compare_cards(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score);

void war(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score);

void get_table_state(table& table, const queue<card>& player_queue, const queue<card>& computer_queue, int round);

void display_table(const table& table);

int main() {
	start_screen();
	char choice;
	cin.get(choice);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (choice != '1')
	{
		return 0;
	}
	system("cls");


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

	while (!player_queue.empty() && !computer_queue.empty())
	{
		get_table_state(table, player_queue, computer_queue, round);
		display_table(table);
		if (!compare_cards(player_queue, computer_queue, war_queue, player_score, computer_score))
			break;
		cout << "---------------------------------------" << '\n';
		round++;
		cout << "Nacisnij Enter aby kontynuowac..." << '\n';
		cout << '\n';
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << '\n' << '\n';
	if (player_score > computer_score) {
		cout << "Gracz wygrywa gre!" << '\n';
	}
	else if (player_score < computer_score) {
		cout << "Komputer wygrywa gre!" << '\n';
	}
	cout << "Karty gracza: " << player_queue.size() << '\n';
	cout << "Karty komputera: " << computer_queue.size() << '\n';

	return 0;
}

void start_screen()
{
	cout << "_    _            _____               _ _____" << '\n';
	cout << "| |  | |          /  __ \\             | |  __ \\" << '\n';
	cout << "| |  | | __ _ _ __| /  \\ / __ _ _ __ __| | |  \\ / __ _ _ __ ___   ___" << '\n';
	cout << "| |/\\| |/ _` | '__| |    / _` | '__/ _` | | __ / _` | '_ ` _ \\ / _ \\" << '\n';
	cout << "\\ / \\ / (_| | |  | \\__ / \\ (_| | | | (_| | |\\ \\ (_| | | | | | |  __/" << '\n';
	cout << " \\_/\\_/\\__,_|_|  |_|\\____/\\__,_|_|  \\__,_|_| \\_\\__,_|_| |_| |_|\\___|" << '\n';
	cout << "Tomasz Nazar 197613           Lukasz Orluk 197641" << '\n';
	cout << "Wybierz jedna z opcji: " << '\n';
	cout << "1. Zacznij gre" << '\n';
	cout << "2. Wyjdz z gry" << '\n';
}

void display_table(const table& table)
{
	cout << "Gracz ilosc kart - " << table.player_cards << '\n';
	cout << "Komputer ilosc kart - " << table.computer_cards << '\n';
	cout << "Runda: " << table.round << '\n';
	cout << "Gracz rzuca ";
	table.player_card.display();
	cout << ". Komputer rzuca ";
	table.computer_card.display();
	cout << "." << '\n';
	cout << "---------------------------------------" << '\n';
}

void get_table_state(table& table, const queue<card>& player_queue, const queue<card>& computer_queue, const int round)
{
	table.player_card = player_queue.front();
	table.computer_card = computer_queue.front();
	table.player_cards = player_queue.size();
	table.computer_cards = computer_queue.size();
	table.player_queue = player_queue;
	table.computer_queue = computer_queue;
	table.round = round;
}

bool compare_cards(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score)
{
	if (player_queue.empty() || computer_queue.empty()) {
		return false;
	}
	if (player_queue.front().get_value() > computer_queue.front().get_value()) {
		cout << "Gracz wygrywa te runde!" << '\n';
		++player_score;
		player_queue.push(computer_queue.front());
		player_queue.push(player_queue.front());
		player_queue.pop();
		computer_queue.pop();
	}
	else if (player_queue.front().get_value() < computer_queue.front().get_value()) {
		cout << "Komputer wygrywa te runde!" << '\n';
		++computer_score;
		computer_queue.push(computer_queue.front());
		computer_queue.push(player_queue.front());
		player_queue.pop();
		computer_queue.pop();
	}
	else {
		if (player_queue.front().get_value() == computer_queue.front().get_value()) {
			cout << "REMIS ------- WOJNA!" << '\n' << '\n';
			war_queue.push(player_queue.front());
			war_queue.push(computer_queue.front());
			player_queue.pop();
			computer_queue.pop();
			war(player_queue, computer_queue, war_queue, player_score, computer_score);
		}
	}
	if (player_score > computer_score)
	{
		while (!war_queue.empty())
		{
			player_queue.push(war_queue.front());
			war_queue.pop();
		}
	}
	else
	{
		while (!war_queue.empty())
		{
			computer_queue.push(war_queue.front());
			war_queue.pop();
		}
	}
	return true;
}

void war(queue<card>& player_queue, queue<card>& computer_queue, queue<card>& war_queue, int& player_score, int& computer_score)
{
	if (player_queue.empty() || computer_queue.empty()) return;
	
	war_queue.push(player_queue.front());
	war_queue.push(computer_queue.front());
	player_queue.pop();
	computer_queue.pop();
	if (player_queue.empty())
	{
		cout << "Gracz nie ma wiecej kart!" << '\n';
		return;
	}
	if (computer_queue.empty())
	{
		cout << "Komputer nie ma wiecej kart!" << '\n';
		return;
	}
	cout << "Gracz wyrzucil - ";
	player_queue.front().display();
	cout << '\n';
	cout << "Komputer  wyrzucil - ";
	computer_queue.front().display();
	cout << '\n';
	if (player_queue.front().get_value() > computer_queue.front().get_value()) {
		cout << '\n' << "Gracz wygrywa Wojne!" << '\n';
		++player_score;
		war_queue.push(player_queue.front());
		war_queue.push(computer_queue.front());
		computer_queue.pop();
		player_queue.pop();
		while (!war_queue.empty())
		{
			player_queue.push(war_queue.front());
			war_queue.pop();
		}
	}
	else if (player_queue.front().get_value() < computer_queue.front().get_value()) {
		cout << '\n' << "Komputer wygrywa Wojne!" << '\n';
		++computer_score;
		war_queue.push(player_queue.front());
		war_queue.push(computer_queue.front());
		player_queue.pop();
		computer_queue.pop();
		while (!war_queue.empty())
		{
			computer_queue.push(war_queue.front());
			war_queue.pop();
		}
	}
	else {
		if (player_queue.front().get_value() == computer_queue.front().get_value()) {
			cout << " REMIS wojna trwa dalej!" << '\n' << '\n';
			war_queue.push(player_queue.front());
			war_queue.push(computer_queue.front());
			player_queue.pop();
			computer_queue.pop();
			war(player_queue, computer_queue, war_queue, player_score, computer_score);
		}
	}
}
