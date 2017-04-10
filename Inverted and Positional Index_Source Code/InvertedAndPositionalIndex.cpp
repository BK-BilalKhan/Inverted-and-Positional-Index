/* ***************************************************************** */

/**
*  Inverted And PositionalIndex
*  main.cpp
*
*  Created by Bilal on October 28, 2016.
*
*
*	Inverted Index Steps
*	Step 1: Create Inverted Index (i.e.: term, totalDocCount : <Doc4, Doc9, ...>)
*	Step 1.1: Take Hadeeth Dataset
*	...
*
*/

/* ***************************************************************** */

#include "include\HashTable.h"

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
#include <chrono>
#include <fstream>
#include <sstream>
#include <process.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

extern unsigned int toalHadeethDatast = 15;
// Inverted Index (HashMap)
map <string, list<string>> index;
// Positional Index (HashMap)
map <string, map <string, list<int>>> pIndex;

void invertedIndex();
void positionalIndex();
int makeHadeethDataSet(string, map <string, list<string>>&, HashTable&);
int makePositionalHadeethDataSet(string, map <string, map <string, list<int>>>&, HashTable&);
void makeQuranDataSet(string, map <string, list<string>>&, HashTable&, unsigned int&);
void makePositionalQuranDataSet(string, map <string, map <string, list<int>>>&, HashTable&, unsigned int&);
bool loadInvertedIndex(string);
bool loadPositionalIndex(string);
void searchInvertedIndex(string);
void searchPositionalIndex(string);
bool stopWords(string, HashTable&);
void Tokenize(const string&, vector<string>&, const string&);
void removeCharsFromString(string&, char*);
char options();
void setConsoleSize(int, int);
void gotoXY(int, int);
void clrscr();

template<class It> It unique2(It const begin, It const end)
{
	It i = begin;
	if (i != end)
	{
		It j = i;
		for (++j; j != end; ++j)
		{
			if (*i != *j)
			{
				using std::swap; swap(*++i, *j);
			}
		}
		++i;
	}
	return i;
}

int main()
{
	/* Inverted Index */
	char choice;
	char choice3;
	char choice4;
	do {
		int q = 0;
		switch (choice = options())
		{
		case '1':
			clrscr();
			// Call Inverted Index to Create
			invertedIndex();
			system("pause");
			break;
		case '2':
			clrscr();
			// Call Positional Index to Create
			positionalIndex();
			system("pause");
			break;
		case '3':
			clrscr();
			do {
				gotoXY(10, 4);
				cout << "----------------------------------------------------";
				gotoXY(20, 5);
				cout << "Load Inverted and Positional Index";
				gotoXY(10, 6);
				cout << "----------------------------------------------------";
				gotoXY(12, 8);
				cout << "1) Press \'1\' to Load Inverted Index";
				gotoXY(12, 9);
				cout << "2) Press \'2\' to Load Positional Index";
				gotoXY(12, 10);
				cout << "3) Press \'3\' or Any Key to Exit";
				gotoXY(12, 13);
				cout << "Please Select: ";
				gotoXY(10, 15);
				cout << "----------------------------------------------------";
				gotoXY(27, 13);
				choice3 = _getch();
			} while (choice3 != '1'&& choice3 != '2' && choice3 != '3');

			if (choice3 == '1') {
				clrscr();

				// Start Time
				chrono::steady_clock::time_point begin = chrono::steady_clock::now();

				// Print
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "-- Load Inverted Index (Using HashMap)			       [Please Wait]" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "Inverted Index (/Inverted-Index.txt)";
				bool isWork = loadInvertedIndex("Inverted-Index.txt");
				if (isWork) {
					cout << "					[OK]" << endl;
				}
				else {
					cout << "				    [Error]" << endl;
					cout << "Warning: Sorry, Unable to open file." << endl;
				}

				// End Time
				chrono::steady_clock::time_point end = chrono::steady_clock::now();

				cout << endl << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "-- Statistics" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "Total Time							[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000 << " Seconds]" << endl;
				cout << endl << endl << "-- ";
				system("pause");
			}
			else if (choice3 == '2') {
				clrscr();

				// Start Time
				chrono::steady_clock::time_point begin = chrono::steady_clock::now();

				// Print
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "-- Load Positional Index (Using HashMap)		       [Please Wait]" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "Positional Index (/Positional-Index.txt)";
				bool isWork = loadPositionalIndex("Positional-Index.txt");
				if (isWork) {
					cout << "				[OK]" << endl;
				}
				else {
					cout << "				    [Error]" << endl;
					cout << "Warning: Sorry, Unable to open file." << endl;
				}

				// End Time
				chrono::steady_clock::time_point end = chrono::steady_clock::now();

				cout << endl << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "-- Statistics" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "Total Time							[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000 << " Seconds]" << endl;
				cout << endl << endl << "-- ";
				system("pause");
			}

			break;
		case '4':
			clrscr();
			do {
				gotoXY(10, 4);
				cout << "----------------------------------------------------";
				gotoXY(20, 5);
				cout << "Search Inverted and Positional Index";
				gotoXY(10, 6);
				cout << "----------------------------------------------------";
				gotoXY(12, 8);
				cout << "1) Press \'1\' to Search Inverted Index";
				gotoXY(12, 9);
				cout << "2) Press \'2\' to Search Positional Index";
				gotoXY(12, 10);
				cout << "3) Press \'3\' to Search Both Index (Auto.)";
				gotoXY(12, 11);
				cout << "4) Press \'4\' or Any Key to Exit";
				gotoXY(12, 13);
				cout << "Please Select: ";
				gotoXY(10, 15);
				cout << "----------------------------------------------------";
				gotoXY(27, 13);
				choice3 = _getch();
			} while (choice3 != '1'&& choice3 != '2' && choice3 != '3' && choice3 != '4');

			if (choice3 == '1') {
				clrscr();
				if (index.empty()) {
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "-- Sorry, Inverted Index has not been loaded." << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << endl << endl << "-- ";
					system("pause");
				}
				else {
					do {
						cout << "----------------------------------------------------------------------------" << endl;
						cout << "-- Search Inverted Index" << endl;
						cout << "----------------------------------------------------------------------------" << endl;
						string query;
						do {
							query = "";
							cout << endl << "-- Enter Search Query: ";
							getline(cin, query);
						} while (query.empty());
						cout << "-- Query is being processed..." << endl << endl;
						searchInvertedIndex(query);
						cout << endl << endl << "-- Do you want to search again? (Any Key / n): ";
						choice4 = _getch();
						clrscr();
					} while (choice4 != 'n');
				}
			}
			else if (choice3 == '2') {
				clrscr();
				if (pIndex.empty()) {
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "-- Sorry, Positional Index has not been loaded." << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << endl << endl << "-- ";
					system("pause");
				}
				else {
					do {
						cout << "----------------------------------------------------------------------------" << endl;
						cout << "-- Search Positional Index" << endl;
						cout << "----------------------------------------------------------------------------" << endl;
						string query;
						do {
							query = "";
							cout << endl << "-- Enter Search Query: ";
							getline(cin, query);
						} while (query.empty());
						cout << "-- Query is being processed..." << endl << endl;
						searchPositionalIndex(query);
						cout << endl << endl << "-- Do you want to search again? (Any Key / n): ";
						choice4 = _getch();
						clrscr();
					} while (choice4 != 'n');
				}
			}
			else if (choice3 == '3') {
				clrscr();
				if (index.empty() && pIndex.empty()) {
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "-- Sorry, Inverted And Positional Index has not been loaded." << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << endl << endl << "-- ";
					system("pause");
				}
				else {
					if (index.empty()) {
						cout << "----------------------------------------------------------------------------" << endl;
						cout << "-- Sorry, Inverted Index has not been loaded." << endl;
						cout << "----------------------------------------------------------------------------" << endl;
						cout << endl << endl << "-- ";
						system("pause");
					}
					else if (pIndex.empty()) {
						cout << "----------------------------------------------------------------------------" << endl;
						cout << "-- Sorry, Positional Index has not been loaded." << endl;
						cout << "----------------------------------------------------------------------------" << endl;
						cout << endl << endl << "-- ";
						system("pause");
					}
					else {
						do {
							cout << "----------------------------------------------------------------------------" << endl;
							cout << "-- Search Inverted Index" << endl;
							cout << "----------------------------------------------------------------------------" << endl;
							string query;
							do {
								query = "";
								cout << endl << "-- Enter Search Query: ";
								getline(cin, query);
							} while (query.empty());
							cout << "-- Query is being processed..." << endl << endl;
							int foundC = query.find("/");
							if (foundC != string::npos) {
								searchPositionalIndex(query);
							}
							else {
								searchInvertedIndex(query);
							}
							cout << endl << endl << "-- Do you want to search again? (Any Key / n): ";
							choice4 = _getch();
							clrscr();
						} while (choice4 != 'n');
					}
				}
			}
			cout << endl << endl << "-- ";
			break;
		case '5':
			clrscr();
			cout << endl << "  " << "Please Wait";
			while (q != 3) {
				cout << ".";
				Sleep(400);
				q++;
			}
			cout << endl << endl << "  ";
			exit(1);
			break;
		default:
			break;
		}
	} while (choice != '5');

	return 0;
}

void searchInvertedIndex(string query) {
	// Start Time
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	transform(query.begin(), query.end(), query.begin(), (int(*)(int))tolower);
	vector<string> tokens;
	Tokenize(query, tokens, " ");
	string term;
	int i = 0;					// How Many Tokens
	for (auto& element : tokens) {
		term = element;
		if (i++ > 1) {
			exit;
		}
	}
	if (i == 1) {
		// One Token
		//list<string>::iterator it = index[term].begin();
		//if (it != index[term].end())
			//cout << *it;
		bool found = false;
		for (list<string>::iterator it = index[term].begin(); it != index[term].end(); it++) {
			if (it == index[term].begin()) {
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "-- Results for \'" << query << "\'" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
			}
			if (it != index[term].end()) {
				cout << "DOC" << *it << ", ";
				found = true;
			}
			else {
				cout << "Did not match any documents.";
			}
		}
		if (!found)
			cout << "-- Did not match any documents.";
	}
	else {
		// More Than One Token
		bool found = false;
		string curTerm = "";
		string preTerm = "";
		vector<string> AND;
		vector<string> OR;
		vector<string> NOT;
		int i = 0;
		while (!tokens.empty())
		{
			curTerm = tokens.back();
			transform(curTerm.begin(), curTerm.end(), curTerm.begin(), (int(*)(int))tolower);
			if (curTerm == "and") {
				AND.push_back(preTerm);
				//AND.push_back(curTerm);
				tokens.pop_back();
				AND.push_back(tokens.back());
			}
			if (curTerm == "or") {
				OR.push_back(preTerm);
				//OR.push_back(curTerm);
				tokens.pop_back();
				OR.push_back(tokens.back());
			}
			if (curTerm == "not") {
				NOT.push_back(preTerm);
				//NOT.push_back(curTerm);
			}
			if (i++ == 0) {
				int pos = find(tokens.begin(), tokens.end(), "not") - tokens.begin();
				if (pos == 1) {
					//cout << pos;
					OR.push_back(tokens.front());
				}
			}
			preTerm = tokens.back();
			tokens.pop_back();
		}

		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Query Refinement" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		for (auto& element : OR) {
			AND.erase(remove(AND.begin(), AND.end(), element), AND.end());
		}
		//unique(AND.begin(), AND.end());
		//unique(OR.begin(), OR.end());
		//unique(NOT.begin(), NOT.end());

		sort(AND.begin(), AND.end());
		AND.erase(unique(AND.begin(), AND.end()), AND.end());

		sort(OR.begin(), OR.end());
		OR.erase(unique(OR.begin(), OR.end()), OR.end());

		sort(NOT.begin(), NOT.end());
		NOT.erase(unique(NOT.begin(), NOT.end()), NOT.end());

		vector<string> result;

		cout << "--[OR_]-- ";
		while (!OR.empty()) {
			cout << OR.back() << "  ";
			for (list<string>::iterator it = index[OR.back()].begin(); it != index[OR.back()].end(); it++) {
				if (it != index[OR.back()].end()) {
					//cout << "DOC" << *it << ",\t";
					result.push_back(*it);
					found = true;
				}
			}
			OR.pop_back();
		}
		cout << endl << "--[AND]-- ";
		bool emptyAND = false;
		if (result.empty())
			emptyAND = true;
		vector<string> tmp;
		while (!AND.empty()) {
			cout << AND.back() << "  ";
			for (list<string>::iterator it = index[AND.back()].begin(); it != index[AND.back()].end(); it++) {
				if (emptyAND) {
					result.push_back(*it);
					found = true;
				}
				else {
					if (find(result.begin(), result.end(), *it) != result.end()) {
						//cout << *it << "   ||   ";
						tmp.push_back(*it);
					}
				}
			}
			AND.pop_back();
			emptyAND = false;
			if (AND.empty()) {
				result.clear();
				result = tmp;
			}
		}
		cout << endl << "--[NOT]-- ";
		while (!NOT.empty()) {
			cout << NOT.back() << "  ";
			for (list<string>::iterator it = index[NOT.back()].begin(); it != index[NOT.back()].end(); it++) {
				result.erase(remove(result.begin(), result.end(), *it), result.end());
			}
			NOT.pop_back();
		}

		// End Time
		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		cout << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Query Results" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		found = false;
		sort(result.begin(), result.end());
		for (vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
			cout << "DOC" << *it << ", ";
			found = true;
		}
		cout << "\b\b  ";

		if (!found)
			cout << "-- Did not match any documents.";

		// Statistics
		cout << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Statistics" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Total Time						[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000 << " Milliseconds]" << endl;

	}
}

void searchPositionalIndex(string query) {
	// Start Time
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	transform(query.begin(), query.end(), query.begin(), (int(*)(int))tolower);
	vector<string> tokens;
	Tokenize(query, tokens, " ");
	string term;
	int i = 0;					// How Many Tokens
	for (auto& element : tokens) {
		term = element;
		if (i++ > 1) {
			exit;
		}
	}
	if (i == 1) {
		// One Token
		//list<string>::iterator it = index[term].begin();
		//if (it != index[term].end())
		//cout << *it;
		bool found = false;
		map <string, list<int>> &tmp = pIndex[term];
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Results for \'" << query << "\'" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		for (auto &i : tmp) {
			cout << "DOC" << i.first << ", ";
			found = true;
		}
		if (!found)
			cout << "-- Did not match any documents.";
	}
	else {
		int j = 0;
		for (auto& element : tokens) {
			j++;
		}

		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Query Refinement" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		if (j == 7) {
			// More Than One Token
			bool found = false;
			string term1 = "";
			string term2 = "";
			string term3 = "";
			string pos1 = "";
			string pos2 = "";
			string op1 = "";
			string op2 = "";
			vector<string> results;
			char nextTerm = '0';
			int k = 0;
			for (auto& element : tokens) {
				if (k == 0)
					term1 = element;
				else if (k == 1)
					op1 = element;
				else if (k == 2)
					term2 = element;
				else if (k == 3)
					pos1 = element;
				else if (k == 4)
					op2 = element;
				else if (k == 5)
					term3 = element;
				else if (k == 6)
					pos2 = element;
				k++;
			}
			cout << "--[Query]-- " << term1 << " " << pos1 << " " << term2 << " " << pos2 << " " << term3 << endl;

			removeCharsFromString(pos1, "/");
			removeCharsFromString(pos2, "/");
			vector <string> matchTerm;

			map <string, list<int>> &tmp = pIndex[term1];
			for (auto &i : tmp) {
				//cout << " DOC" << i.first << ": ";
				matchTerm.push_back(i.first);
			}

			cout << endl;

			map <string, list<int>> &tmp2 = pIndex[term2];
			for (auto &i : tmp2) {
				//cout << " DOC" << i.first << ": ";
				matchTerm.push_back(i.first);
			}

			//cout << endl;

			map <string, list<int>> &tmp3 = pIndex[term3];
			for (auto &i : tmp3) {
				//cout << " DOC" << i.first << ": ";
				matchTerm.push_back(i.first);
			}

			// Total Docs Found
			//cout << "-- Docs Found: ";
			//for (vector<string>::iterator it = matchTerm.begin(); it != matchTerm.end(); ++it)
			//cout << " Doc" << *it << ",";
			//cout << "\b " << endl;

			vector<string> fTerms;
			for (vector<string>::iterator it1 = matchTerm.begin(); it1 != matchTerm.end(); ++it1) {
				int x = 0;
				for (vector<string>::iterator it2 = matchTerm.begin() + 1; it2 != matchTerm.end(); ++it2) {
					if (*it1 == *it2) {
						x++;
					}
				}
				if (x > 2) {
					fTerms.push_back(*it1);
				}
			}

			sort(fTerms.begin(), fTerms.end());
			fTerms.erase(unique(fTerms.begin(), fTerms.end()), fTerms.end());

			//for (vector<string>::iterator it1 = fTerms.begin(); it1 != fTerms.end(); ++it1) {
				//cout << *it1 << "  ";
			//}

			// Dublicate Docs Found
			cout << "-- Match Docs Found: ";
			for (vector<string>::iterator it = fTerms.begin(); it != fTerms.end(); ++it) {
				vector<int> mterm1;
				vector<int> mterm2;
				vector<int> mterm3;

				cout << "DOC" << *it << ":{";
				for (auto &i : tmp) {
					if (i.first == *it) {
						for (list<int>::iterator it = i.second.begin(); it != i.second.end(); it++) {
							cout << *it << ", ";
							mterm1.push_back(*it);
						}
					}
				}
				cout << "} ";
				cout << "{";
				for (auto &i : tmp2) {
					if (i.first == *it) {
						for (list<int>::iterator it = i.second.begin(); it != i.second.end(); it++) {
							cout << *it << ", ";
							mterm2.push_back(*it);
						}
					}
				}
				cout << "} ";
				cout << "{";
				for (auto &i : tmp3) {
					if (i.first == *it) {
						for (list<int>::iterator it = i.second.begin(); it != i.second.end(); it++) {
							cout << *it << ", ";
							mterm3.push_back(*it);
						}
					}
				}
				cout << "}; ";

				//cout << endl << endl << "----";

				for (vector<int>::iterator it1 = mterm1.begin(); it1 != mterm1.end(); ++it1) {
					for (vector<int>::iterator it2 = mterm2.begin(); it2 != mterm2.end(); ++it2) {
						for (vector<int>::iterator it3 = mterm3.begin(); it3 != mterm3.end(); ++it3) {
							int position1 = *it1;
							int position2 = *it2;
							if ((position1 + stoi(pos1) + 0) == *it2 && (position2 + stoi(pos2) + 0) == *it3) {
								//cout << "DOC" << *it << "{" << *it1 << ", " << *it2 << "}, ";
								results.push_back("DOC" + *it + "{" + to_string(*it1) + ", " + to_string(*it2) + ", " + to_string(*it3) + "}");
								found = true;
							}
						}
					}
					//cout << endl;
				}
				//cout << '\n';

				//cout << endl << endl << "----";
			}

			// End Time
			chrono::steady_clock::time_point end = chrono::steady_clock::now();

			cout << "\b\b  " << endl << endl;
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "-- Query Results" << endl;
			cout << "----------------------------------------------------------------------------" << endl;

			for (vector<string>::iterator it1 = results.begin(); it1 != results.end(); ++it1) {
				cout << *it1 << ", ";
			}
			cout << "\b\b  ";

			if (!found)
				cout << "-- Did not match any documents.";

			// Statistics
			cout << endl << endl;
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "-- Statistics" << endl;
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "Total Time						[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000 << " Milliseconds]" << endl;

		}
		else {
			// More Than One Token
			bool found = false;
			string term1 = "";
			string term2 = "";
			string op = "";
			vector<string> results;
			char nextTerm = '0';
			for (auto& element : tokens) {
				int foundC = element.find("/");
				if (element != "and" && element != "or" && element != "not" && nextTerm == '0' && foundC == string::npos) {
					term1 = element;
					nextTerm = '1';
				}
				else
					if (element == "and" || element == "or" || element == "not") {
						op = element;
					}
				if (element != "and" && element != "or" && element != "not" && nextTerm == '1' && foundC == string::npos) {
					term2 = element;
				}
				if (foundC != string::npos) {
					cout << "--[Query]-- " << term1 << " " << element << " " << term2 << endl;

					vector <string> matchTerm;

					map <string, list<int>> &tmp = pIndex[term1];
					for (auto &i : tmp) {
						//cout << " DOC" << i.first << ": ";
						matchTerm.push_back(i.first);
					}

					cout << endl;

					map <string, list<int>> &tmp2 = pIndex[term2];
					for (auto &i : tmp2) {
						//cout << " DOC" << i.first << ": ";
						matchTerm.push_back(i.first);
					}

					// Total Docs Found
					//cout << "-- Docs Found: ";
					//for (vector<string>::iterator it = matchTerm.begin(); it != matchTerm.end(); ++it)
						//cout << " Doc" << *it << ",";
					//cout << "\b " << endl;

					// Unique Find
					sort(matchTerm.begin(), matchTerm.end());
					matchTerm.erase(matchTerm.begin(), unique2(matchTerm.begin(), matchTerm.end()));
					sort(matchTerm.begin(), matchTerm.end());
					matchTerm.erase(unique2(matchTerm.begin(), matchTerm.end()), matchTerm.end());


					removeCharsFromString(element, "/");

					// Dublicate Docs Found
					cout << "-- Match Docs Found: ";
					for (vector<string>::iterator it = matchTerm.begin(); it != matchTerm.end(); ++it) {
						vector<int> mterm1;
						vector<int> mterm2;

						cout << "DOC" << *it << ":{";
						for (auto &i : tmp) {
							if (i.first == *it) {
								for (list<int>::iterator it = i.second.begin(); it != i.second.end(); it++) {
									cout << *it << ", ";
									mterm1.push_back(*it);
								}
							}
						}
						cout << "\b\b} ";
						cout << "{";
						for (auto &i : tmp2) {
							if (i.first == *it) {
								for (list<int>::iterator it = i.second.begin(); it != i.second.end(); it++) {
									cout << *it << ", ";
									mterm2.push_back(*it);
								}
							}
						}
						cout << "\b\b}; ";

						//cout << endl << endl << "----";

						for (vector<int>::iterator it1 = mterm1.begin(); it1 != mterm1.end(); ++it1) {
							for (vector<int>::iterator it2 = mterm2.begin(); it2 != mterm2.end(); ++it2) {
								int position = *it1;
								if ((position + stoi(element) + 0) == *it2) {
									//cout << "DOC" << *it << "{" << *it1 << ", " << *it2 << "}, ";
									results.push_back("DOC" + *it + "{" + to_string(*it1) + ", " + to_string(*it2) + "}");
									found = true;
								}
							}
							//cout << endl;
						}
						//cout << '\n';

						//cout << endl << endl << "----";
					}

					cout << "\b\b  " << endl << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "-- Query Results" << endl;
					cout << "----------------------------------------------------------------------------" << endl;

					for (vector<string>::iterator it1 = results.begin(); it1 != results.end(); ++it1) {
						cout << *it1 << ", ";
					}
					cout << "\b\b  ";

				}
			}

			// End Time
			chrono::steady_clock::time_point end = chrono::steady_clock::now();

			//cout << endl << endl;
			//cout << "----------------------------------------------------------------------------" << endl;
			//cout << "-- Query Results" << endl;
			//cout << "----------------------------------------------------------------------------" << endl;

			//found = false;
			//sort(result.begin(), result.end());
			//for (vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
				//cout << "DOC" << *it << ", ";
				//found = true;
			//}
			//cout << "\b\b  ";

			if (!found)
				cout << "-- Did not match any documents.";

			// Statistics
			cout << endl << endl;
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "-- Statistics" << endl;
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "Total Time						[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000 << " Milliseconds]" << endl;
		}
	}
}

// function Inverted Index to Create
void invertedIndex() {
	// Start Time
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	// Inverted Index (HashMap)
	map <string, list<string>> invertedIndex;

	// DocID
	unsigned int docID = 0;

	// Print
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Load Stopwords (Using HashTable)" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// StopWords (HashTable)
	HashTable stopWord(29);
	if (stopWords("Corpus/Stopword-List.txt", stopWord)) {
		cout << "Stopword (/Corpus/Stopword-List.txt)					[OK]" << endl;
	}
	else {
		cout << "Stopword (/Corpus/Stopword-List.txt)				[ERROR]" << endl;
	}

	// Print (Hadeeth Dataset)
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Make Hadeeth Dataset Inverted Indexing (Using HashMap) [DocID 0 to 7189]" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// Read Doc from Files (Hadeeth Dataset [1 to 15])
	for (int i = 1; i <= toalHadeethDatast; i++) {
		cout << "Hadeeth Dataset (/Corpus/Hadeeth Dataset/" << i << ")";
		docID = makeHadeethDataSet(("Corpus/Hadeeth Dataset/" + to_string(i)), invertedIndex, stopWord);
		if (docID > 0) {
			cout << "				[OK]" << endl;
		}
		else {
			cout << "			[ERROR]" << endl;
		}
	}

	// Print (Quran Dataset)
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Make Quran Dataset Inverted Indexing (Using HashMap) [DocID 7190 to ~]" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Hadeeth Dataset (/Corpus/Quran Dataset/Quran Translation.txt)";
	makeQuranDataSet("Corpus/Quran Dataset/Quran Translation.txt", invertedIndex, stopWord, docID);
	if (docID > 0) {
		cout << "		[OK]" << endl;
	}
	else {
		cout << "	[ERROR]" << endl;
	}

	// Print
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Store Inverted Index (Using Filing)" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// End Time
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	// Write invertedIndex into File
	ofstream outFile("Inverted-Index.txt");
	if (outFile.is_open())
	{
		cout << "Filling (Inverted-Index.txt)";
		for (auto const& ent1 : invertedIndex) {
			invertedIndex[ent1.first].unique();		// Remove Duplicates Doc
			outFile << ent1.first << "," << invertedIndex[ent1.first].size() << ":<";		// Count Term (Docs)
			for (list<string>::iterator it = invertedIndex[ent1.first].begin(); it != invertedIndex[ent1.first].end(); it++) {
				if (it != next(invertedIndex[ent1.first].end(), -1))
					outFile << *it << ',';
				else
					outFile << *it;
			}
			outFile << ">" << endl;
		}
		outFile.close();
		cout << "						[OK]" << endl;
	}
	else {
		cout << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Sorry, Unable to open file.							[Error]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}

	// Load (Copy) invertedIndex to index
	index.clear();
	index = invertedIndex;

	cout << endl << endl;
	if (index.empty()) {
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Index has not been loaded.				[ERROR]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}
	else {
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Index has been loaded.						[OK]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}

	// Statistics
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Statistics" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Average Time (Each Index)					[" << (chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000) / (toalHadeethDatast + 1) << " Seconds]" << endl;
	cout << "Total Time							[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000 << " Seconds]" << endl;
	cout << endl << endl << "-- ";

	// Search Query
	//list<string>::iterator it = invertedIndex["sonhood"].begin();
	//	if (*it != NULL)
	//	cout << *it;

	/* Print invertedIndex
	for (auto const& ent1 : invertedIndex) {
		invertedIndex[ent1.first].unique();		// Remove Duplicates Doc
		cout << ent1.first << "," << invertedIndex[ent1.first].size() << ":<";		// Count Term (Docs)
		for (list<string>::iterator it = invertedIndex[ent1.first].begin(); it != invertedIndex[ent1.first].end(); it++) {
			if (it != next(invertedIndex[ent1.first].end(), -1))
				cout << *it << ',';
			else
				cout << *it;
		}
		cout << ">" << endl;
	}*/

}

// function Positional Index to Create
void positionalIndex() {
	// Start Time
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	// Positional Index (HashMap)
	map <string, map <string, list<int>>> positionalIndex;

	// DocID
	unsigned int docID = 0;

	// Print
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Load Stopwords (Using HashTable)" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// StopWords (HashTable)
	HashTable stopWord(29);
	if (stopWords("Corpus/Stopword-List.txt", stopWord)) {
		cout << "Stopword (/Corpus/Stopword-List.txt)					[OK]" << endl;
	}
	else {
		cout << "Stopword (/Corpus/Stopword-List.txt)				[ERROR]" << endl;
	}

	// Print (Hadeeth Dataset)
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Make Hadeeth Dataset Positional Indexing (Using HashMap) [DocID 0 to 7189]" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// Read Doc from Files (Hadeeth Dataset [1 to 15])
	for (int i = 1; i <= toalHadeethDatast; i++) {
		cout << "Hadeeth Dataset (/Corpus/Hadeeth Dataset/" << i << ")";
		docID = makePositionalHadeethDataSet(("Corpus/Hadeeth Dataset/" + to_string(i)), positionalIndex, stopWord);
		if (docID > 0) {
			cout << "				[OK]" << endl;
		}
		else {
			cout << "			[ERROR]" << endl;
		}
	}

	// Print (Quran Dataset)
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Make Quran Dataset Positional Indexing (Using HashMap) [DocID 7190 to ~]" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Hadeeth Dataset (/Corpus/Quran Dataset/Quran Translation.txt)";
	makePositionalQuranDataSet("Corpus/Quran Dataset/Quran Translation.txt", positionalIndex, stopWord, docID);
	if (docID > 0) {
		cout << "		[OK]" << endl;
	}
	else {
		cout << "	[ERROR]" << endl;
	}

	// Print
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Store Positional Index (Using Filing)" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	// End Time
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	// Write positionalIndex into File
	ofstream outFile("Positional-Index.txt");
	if (outFile.is_open())
	{
		cout << "Filling (Positional-Index.txt)";
		for (auto &i : positionalIndex) {
			outFile << i.first << "," << positionalIndex[i.first].size() << ":<";
			for (auto &j : i.second) {
				outFile << j.first;			//outFile << j.first << ":";
				outFile << "{";
				for (list<int>::iterator it = j.second.begin(); it != j.second.end(); it++) {
					if (it != next(j.second.end(), -1))
						outFile << *it << ',';
					else
						outFile << *it;
				}
				outFile << "};";
			}
			outFile << ">" << endl;
		}

		outFile.close();
		cout << "						[OK]" << endl;
	}
	else {
		cout << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Sorry, Unable to open file.							[Error]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}


	// Load (Copy) positionalIndex to index
	pIndex.clear();
	pIndex = positionalIndex;

	cout << endl << endl;
	if (pIndex.empty()) {
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Index has not been loaded.				[ERROR]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}
	else {
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "-- Index has been loaded.						[OK]" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}

	// Statistics
	cout << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "-- Statistics" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Average Time (Each Index)					[" << (chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000) / (toalHadeethDatast + 1) << " Seconds]" << endl;
	cout << "Total Time							[" << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000 << " Seconds]" << endl;
	cout << endl << endl << "-- ";

}

int makeHadeethDataSet(string location, map <string, list<string>>& invertedIndex, HashTable& stopWord) {
	string doc;
	string preDoc;
	ifstream inFile(location);
	string fDoc = "";
	unsigned int totalDocs = 0;
	while (getline(inFile, doc))
	{
		if (!(doc.find('[') && doc.find(']'))) {
			transform(fDoc.begin(), fDoc.end(), fDoc.begin(), (int(*)(int))tolower);
			removeCharsFromString(doc, "[]");

			//cout << endl << doc << endl;		// Print Doc Lines
			//cout << fDoc;						// Print Full Doc (Individual)

			vector<string> tokens;
			Tokenize(fDoc, tokens, " .,/\\*+:;\"()[]{}<>$%#@!&|?-~");

			for (auto& element : tokens) {
				if (stopWord.getItemByKey(element) == NULL) {			// Remove Stop Words
					invertedIndex[element].push_back(preDoc);
				}
			}

			//system("pause");

			// Remove Data from fDoc
			fDoc = "";
			totalDocs = stoi(doc) - 1;
			preDoc = doc;
		}
		else {
			// Append Doc (Lines)
			fDoc = fDoc + doc;
		}
	}
	inFile.close();
	return totalDocs;
}

int makePositionalHadeethDataSet(string location, map <string, map <string, list<int>>>& positionalIndex, HashTable& stopWord) {
	string doc;
	string preDoc;
	ifstream inFile(location);
	string fDoc = "";
	unsigned int totalDocs = 0;
	while (getline(inFile, doc))
	{
		if (!(doc.find('[') && doc.find(']'))) {
			transform(fDoc.begin(), fDoc.end(), fDoc.begin(), (int(*)(int))tolower);
			removeCharsFromString(doc, "[]");

			//cout << endl << doc << endl;		// Print Doc Lines
			//cout << fDoc;						// Print Full Doc (Individual)

			vector<string> tokens;
			Tokenize(fDoc, tokens, " .,/\\*+:;\"()[]{}<>$%#@!&|?-~");

			int i = 0;
			for (auto& element : tokens) {
				if (stopWord.getItemByKey(element) == NULL) {			// Remove Stop Words
					map <string, list<int>> &tmp = positionalIndex[element];
					tmp[preDoc].push_back(i);
					positionalIndex[element] = tmp;
				}
				i++;
			}

			//system("pause");

			// Remove Data from fDoc
			fDoc = "";
			totalDocs = stoi(doc) - 1;
			preDoc = doc;
		}
		else {
			// Append Doc (Lines)
			fDoc = fDoc + doc;
		}
	}
	/*system("pause");

	cout << endl << endl;

	for (auto &i : positionalIndex) {
		cout << i.first << "," << positionalIndex[i.first].size() << ":<";
		for (auto &j : i.second) {
			cout << j.first << ":";
			cout << "{";
			for (list<int>::iterator it = j.second.begin(); it != j.second.end(); it++) {
				cout << *it << ',';
			}
			cout << "\b},";
		}
		cout << "\b>";

		cout << endl << endl;
		system("pause");

	}*/

	inFile.close();
	return totalDocs;
}

void makeQuranDataSet(string location, map <string, list<string>>& invertedIndex, HashTable& stopWord, unsigned int& docID) {
	string doc;
	string preDoc;
	ifstream inFile(location);
	string fDoc = "";
	while (getline(inFile, doc))
	{
		if (!(doc.find('[') && doc.find(']'))) {
			transform(fDoc.begin(), fDoc.end(), fDoc.begin(), (int(*)(int))tolower);

			//cout << endl << doc << endl;		// Print Doc Lines
			//cout << fDoc << endl;						// Print Full Doc (Individual)
			//cout << docID << endl << endl << endl;

			vector<string> tokens;
			Tokenize(fDoc, tokens, " .,/\\*+:;\"()[]{}<>$%#@!&|?-~");
			docID++;
			for (auto& element : tokens) {
				if (stopWord.getItemByKey(element) == NULL) {			// Remove Stop Words
					invertedIndex[element].push_back(preDoc);	// docID
				}
			}

			// Remove Data from fDoc
			fDoc = "";
			preDoc = doc;
		}
		else {
			// Append Doc (Lines)
			fDoc = fDoc + doc;
		}
	}
	inFile.close();
}

void makePositionalQuranDataSet(string location, map <string, map <string, list<int>>>& positionalIndex, HashTable& stopWord, unsigned int& docID) {
	string doc;
	string preDoc;
	ifstream inFile(location);
	string fDoc = "";
	while (getline(inFile, doc))
	{
		if (!(doc.find('[') && doc.find(']'))) {
			transform(fDoc.begin(), fDoc.end(), fDoc.begin(), (int(*)(int))tolower);

			//cout << endl << doc << endl;		// Print Doc Lines
			//cout << fDoc << endl;						// Print Full Doc (Individual)
			//cout << docID << endl << endl << endl;

			vector<string> tokens;
			Tokenize(fDoc, tokens, " .,/\\*+:;\"()[]{}<>$%#@!&|?-~");
			docID++;
			int i = 0;
			for (auto& element : tokens) {
				if (stopWord.getItemByKey(element) == NULL) {			// Remove Stop Words
					map <string, list<int>> &tmp = positionalIndex[element];
					tmp[preDoc].push_back(i);
					positionalIndex[element] = tmp;
				}
				i++;
			}

			// Remove Data from fDoc
			fDoc = "";
			preDoc = doc;
		}
		else {
			// Append Doc (Lines)
			fDoc = fDoc + doc;
		}
	}
	inFile.close();
}

bool loadInvertedIndex(string location) {
	index.clear();
	string term;
	ifstream inFile(location);
	unsigned int totalDocs = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, term))
		{
			vector<string> tokens;
			Tokenize(term, tokens, ",<>");
			string aterm = "";
			int i = 0;
			for (auto& element : tokens) {
				if (i == 0) {
					aterm = element;
					i++;
				}
				else if (i == 1) {
					i++;
					continue;
				}
				else {
					index[aterm].push_back(element);		//stoi(element)
				}
			}
		}
	}
	else {
		return false;
	}
	inFile.close();
	return true;
}

bool loadPositionalIndex(string location) {
	pIndex.clear();
	string term;
	ifstream inFile(location);
	unsigned int totalDocs = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, term))
		{
			//cout << endl;
			vector<string> tokens;
			Tokenize(term, tokens, "<>");
			string aterm = "";
			int i = 0;
			for (auto& element : tokens) {
				if (i == 0) {
					vector<string> aterms;
					Tokenize(element, aterms, ",");
					aterm = aterms.front();
					i++;
				}
				else {
					//index[aterm].push_back(element);		//stoi(element)
					//cout << aterm << "    ";								// Term
					map <string, list<int>> &tmp = pIndex[aterm];
					vector<string> terms;
					Tokenize(element, terms, ";");
					for (auto& element : terms) {
						//cout << element << "   ";
						vector<string> innerTerms;
						Tokenize(element, innerTerms, "{},");
						int j = 0;
						string fTerm;
						for (auto& element : innerTerms) {
							if (j == 0) {
								//cout << element << " || ";					// Docs
								fTerm = element;
								j++;
							}
							else {
								//cout << element << "   ";					// Docs Positions
								tmp[fTerm].push_back(stoi(element));
							}
						}
					}
					//cout << endl << endl;
					//system("pause");
				}
			}
		}
	}
	else {
		return false;
	}
	inFile.close();
	return true;
}

bool stopWords(string location, HashTable& stopWord) {
	string word;
	ifstream inFile(location);
	if (inFile.is_open())
	{
		while (getline(inFile, word))
		{
			if (word != "") {
				word.erase(remove_if(word.begin(), word.end(), isspace), word.end());
				transform(word.begin(), word.end(), word.begin(), (int(*)(int))tolower);
				stopWord.insertItem(new Item{ word , NULL });
			}
		}
	}
	else {
		return false;
	}
	return true;
}

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
	tokens.clear();
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void removeCharsFromString(string& str, char* charsToRemove) {
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}
}

// function for interface
char options() {
	clrscr();
	gotoXY(10, 4);
	cout << "----------------------------------------------------";
	gotoXY(20, 5);
	cout << "Inverted and Positional Index";
	gotoXY(10, 6);
	cout << "----------------------------------------------------";
	gotoXY(12, 8);
	cout << "1) Press \'1\' to Create Inverted Index";
	gotoXY(12, 9);
	cout << "2) Press \'2\' to Create Positional Index";
	gotoXY(12, 10);
	cout << "3) Press \'3\' to Load Index";
	gotoXY(12, 11);
	cout << "4) Press \'4\' to Search Query";
	gotoXY(12, 12);
	cout << "5) Press \'5\' to Exit";
	gotoXY(12, 13);
	cout << "Please Select: ";
	gotoXY(10, 15);
	cout << "----------------------------------------------------";
	gotoXY(27, 13);
	char choice = _getch();
	return choice;
}

// function definition -- requires windows.h 
void setConsoleSize(int x, int y) {
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, x, y, TRUE);
}

// function definition -- requires windows.h 
void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h 
void clrscr() {
	for (int i = 0; i < 25; i++)
		cout << endl;
	system("cls");
}
