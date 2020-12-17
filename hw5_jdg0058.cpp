//Jacob Galanopoulos
//JDG0058
//hw5_jdg0058.cpp
//The program handles the trivia game through linked nodes.
//I worked with Karl Sprayberry on the design of the node list. I also used stackoverflow for the class design.
//FYI the unit testing variable is commmented out to default to the normal mode not the testing.

#include <iostream>
#include <string>
using namespace std;

//#define UNIT_TESTING
void runKeyBoardTest();
void runUnitTesting();

class LinkedList {
	struct Node {
		string question;
		string answer;
		int points;
		Node* next;
	};
public: 
	LinkedList() {
		head = NULL;
		tail = NULL;
	}

	void addNode(string question, string answer, int points) {
		Node *n = new Node();
		n->question = question;
		n->answer = answer;
		n->points = points;
		n->next = NULL;
		if (head == NULL) {
			head = n;
			tail = n;
		} 
		else {
			tail->next = n;
			tail = tail->next;
		}
	}

	void runQuiz(bool countPoints = true) {
		Node *n;
		int totalPoints = 0;
		n = head;
		if (n == NULL) {
			cout << "Warning - The number of trivia to be asked must be equal to or larger than 1." << endl;
		}
		else {
			while (n != NULL) {
				totalPoints += askQuestion(n, countPoints);
				if (countPoints) { //Only reason countPoints exists is because the unit testing doesn't include a points count.
					cout << "Your total points: " << totalPoints << "\n" << endl;
				}
				n = n->next;
			}
		}
	}

	int askQuestion(Node *n, bool countPoints = true) {
		int points = 0;
		string answer;

		cout << "Question: " << n->question << endl;
		cout << "Answer: ";
		getline(cin, answer);

		if (countPoints) {
			if (answer.compare(n->answer) == 0) {
				if (countPoints) { //Only reason countPoints exists is because the unit testing doesn't include a points count.
					cout << "Your answer is correct. You receive " << n->points << " points." << endl;
				}
				points += n->points;
			}
			else {
				cout << "Your answer is wrong. The correct answer is: " << n->answer << endl;
			}
		}
		return points;
	}
	//This function exists just because you want the last question for the Unit Testing.
	void askLastQuestion() {
		Node *n;
		n = tail;
		askQuestion(n, false);
	}
private:
	Node *head,*tail;
};

int main() {
	#ifdef UNIT_TESTING
	runUnitTesting();
	#else
	runKeyBoardTest();
	#endif
}

void runKeyBoardTest() {
	LinkedList list;

	string question;
	string answer;
	string cont;
	string dummy; //This is a dummy string that I use for clearing the cin stream
	bool contin = true;
	int points = 0;

	cout << "*** Welcome to Jake's trivia quiz game" << endl;
	while (contin) {
		cout << "Enter a question: ";
		getline(cin, question);
		cout << "Enter an answer: ";
		getline(cin, answer);
		cout << "Enter award points: ";
		cin >> points;
		getline(cin, dummy); //This clears out the remaining \n from the cin stream
		
		bool c = true;
		while (c) {
			cout << "Continue? (Yes/No): ";
			cin >> cont;
			getline(cin, dummy); //This clears out the remaining \n from the cin stream
			if (cont.compare("No") == 0 || cont.compare("no") == 0) {
				contin = false;
				c = false;
			}
			else if (cont.compare("Yes") == 0 || cont.compare("yes") == 0) {
				c = false;
			}
			else {
				cout << "Improper input, must be Yes or No. Please try again." << endl;
			}
		}
		list.addNode(question, answer, points);
	}
	cout << endl;
	list.runQuiz();
	cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
}

void runUnitTesting() {
	LinkedList list;
	string question1 = "Question: How long was the shortest war on record? (Hint: how many minutes)";
	string question2 = "Question: What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
	string question3 = "Question: What is the best-selling video game of all time? (Hint: Minecraft or Tetris)";
	string answer1 = "38", answer2 = "Bank of Italy", answer3 = "Tetris";
	int questions = 0; //This variable only exists because you have me checking for something that can't happen with the way I made the test
	int points1 = 100, points2 = 50, points3 = 20;

	cout << "*** This is a debug version ***" << endl;
	cout << "Unit Test Case 1: Ask no questions. The program should give a warning message." << endl;
	list.runQuiz(false);
	cout << endl;
	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	list.addNode(question1, answer1, points1);
	questions++;
	list.runQuiz(false);
	cout << "Case 2.1 passed..." << endl;
	cout << endl;
	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	list.runQuiz(false);
	cout << "Case 2.2 passed..." << endl;
	cout << endl;
	list.addNode(question2, answer2, points2);
	questions++;
	list.addNode(question3, answer3, points3);
	questions++;
	cout << "Unit Test Case 3: Ask the last question in the linked list." << endl;
	list.askLastQuestion();
	cout << endl;
	cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
	if (questions < 5) {
		cout << "Warning - There are only " << questions << " trivia in the list." << endl;
	}
	cout << endl;
	cout << "*** End of Debug Version ***" << endl;
}