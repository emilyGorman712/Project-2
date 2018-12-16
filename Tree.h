// Emily Gorman
// Project 2: Tracking Trees
// 12/15/2018
// Trees.h

#ifndef TREE_H_
#define TREE_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Tree
{
protected:
	class Record
	{
	public:
		Record * left_;
		Record * right_;
		string ID_;
		string ParentID_;
		string RawEvent_;
		string RHASH_;
		string LHASH_;
		vector<string> RHIST_;
		vector<string> LHIST_;

	public:
		Record(string ID,
			string ParentID,
			string RawEvent,
			string RHASH,
			string LHASH,
			vector<string> RHIST,
			vector<string> LHIST,
			Record* left = NULL,
			Record* right = NULL)
			: ID_(ID),
			ParentID_(ParentID),
			RawEvent_(RawEvent),
RHASH_(RHASH),
LHASH_(LHASH),
RHIST_(RHIST),
LHIST_(LHIST),
left_(left),
right_(right)
{ }

~Record()
{
}

	private:
		Record(const Record &);
		const Record & operator =(const Record &);
	};

public:
	Tree();
	~Tree();
	void display(std::ostream& outfile) const;
	void build();
	void insert(Record * & subtree);
	void search(string ID);
	void update(string ID);
private:
	Record * tree_;
	static const char alphanum[];
	static int stringLength;
private:
	Tree& operator=(Tree &);
	Tree(const Tree&);

private:
	Record * search(string ID, Record * & subtree);
	void update(string ID, string RawEvent, string Lhash, string Rhash, Record * subtree);
	static void destroy(Record * & root);
	static void displayLeft(std::ostream & outfile,
		Record * subtree, std::string prefix);
	static void displayRight(std::ostream & outfile,
		Record * subtree, std::string prefix);
};


const char Tree::alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
int Tree::stringLength = sizeof(alphanum) - 1;

Tree::Tree()
	: tree_(NULL)
{
}

Tree:: ~Tree()
{
	destroy(tree_);
}
void
Tree::build()
{
	insert(tree_);
}
void
Tree::update(string ID)
{
	string NewID, NewRE, NewLHASH, NewRHASH;
	cout << "Please enter in new contents for said node: " << endl;
	cout << "New ID: ";
	cin >> NewID;
	cout << "New Raw Event: ";
	cin >> NewRE;
	cout << "New LHASH: ";
	cin >> NewLHASH;
	cout << "New RHASH: ";
	cin >> NewRHASH;
	update(NewID, NewRE, NewLHASH, NewRHASH, search(ID, tree_));
}
void Tree::search(string ID)
{
	cout << "ID: " << search(ID, tree_)->ID_ << " Parent ID: " << search(ID, tree_)->ParentID_ << " Raw Event: " <<
		search(ID, tree_)->RawEvent_ << " LHASH: " << search(ID, tree_)->LHASH_ << " RHASH: " << search(ID, tree_)->RHASH_ << " LHIST: ";
	for (vector<string>::const_iterator i = search(ID, tree_)->LHIST_.begin(); i != search(ID, tree_)->LHIST_.end(); i++)
	{
		cout << *i << " ";
	}
	cout << " RHIST: ";
	for (vector<string>::const_iterator j = search(ID, tree_)->RHIST_.begin(); j != search(ID, tree_)->RHIST_.end(); j++)
	{
		cout << *j << " ";
	}	
	cout << endl;
}
void
Tree::display(std::ostream& outfile) const
{
	string prefix;
	if (tree_ == NULL)
	{
		outfile << "-" << endl;
	}
	else
	{
		displayLeft(outfile, tree_->left_, "    ");
		outfile << "---" << tree_->ID_ << endl;
		displayRight(outfile, tree_->right_, "    ");

	}
}
void
Tree::update(string ID, string RawEvent, string Lhash, string Rhash, Record * subtree)
{
	subtree->ID_ = ID;
	subtree->RawEvent_ = RawEvent;
	subtree->LHASH_ = Lhash;
	subtree->RHASH_ = Rhash;
}
Tree::Record * Tree::search(string ID, Record * & subtree)
{
	Record * found;
	if (!subtree || subtree->ID_ == ID) return subtree;

	found = search(ID, subtree->left_);

	return (found) ? found : search(ID, subtree->right_);
}
void Tree::insert(Record * & subtree)
{
	if (subtree == NULL)
	{
		string null = "";
		string rawe = "FOO";
		vector<string> n(8);
		string PID;
		for (unsigned int i = 0; i < 8; i++)
		{
			PID += (alphanum[rand() % stringLength]);
		}
		size_t h1 = hash<string>() (rawe);
		size_t h2 = hash<string>() (PID);
		size_t h3 = h1 ^ (h2 << 1);
		subtree = new Record(to_string(h3), PID, rawe, null, null, n, n);
	}
	else
	{
		if (subtree->left_ != NULL)
		{
			insert(subtree->left_);
		}else {
			string null = "";
			vector<string> n(8);
			string re;
			for (unsigned int i = 0; i < 3; i++)
			{
				re += (alphanum[rand() % stringLength]);
			}
			size_t h1 = hash<string>() (subtree->ID_);
			size_t h2 = hash<string>() (re);
			size_t h3 = h1 ^ (h2 << 1);
			subtree->left_ = new Record(to_string(h3), subtree->ID_, re, null, null, n, n);
			size_t hash1 = hash<string>() (to_string(h3));
			size_t hash2 = hash<string>() (subtree->ID_);
			size_t hash3 = hash1 ^ (hash2 << 1);
			subtree->LHASH_ = to_string(hash3);
			subtree->LHIST_.push_back(to_string(hash3));
			subtree->left_->left_ = NULL;
			subtree->left_->right_ = NULL;
		}
		if (subtree->right_ != NULL)
		{
			insert(subtree->right_);
		}else {
			string RE;
			string null = "";
			vector<string> n(8);
			for (unsigned int i = 0; i < 3; i++)
			{
				RE += (alphanum[rand() % stringLength]);
			}
			size_t H1 = hash<string>() (RE);
			size_t H2 = hash<string>() (subtree->ID_);
			size_t H3 = H1 ^ (H2 << 1);
			subtree->RHASH_ = to_string(H3);
			subtree->RHIST_.push_back(to_string(H3));
			subtree->right_ = new Record(to_string(H3), subtree->ID_, RE, null, null, n, n);
			subtree->right_->right_ = NULL;
			subtree->right_->left_ = NULL;
		}
		
		
	}
}
void
Tree::displayLeft(std::ostream & outfile,
	Record * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "     ");
		outfile << prefix + "/---" << subtree->ID_ << std::endl;
		displayRight(outfile, subtree->right_, prefix + "|    ");
	}
}
void
Tree::displayRight(std::ostream & outfile,
	Record * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "|    ");
		outfile << prefix + "\\---" << subtree->ID_ << std::endl;
		displayRight(outfile, subtree->right_, prefix + "     ");
	}
}
void
Tree::destroy(Record * & subtree)
{
	if (subtree != NULL)
	{
		destroy(subtree->left_);
		destroy(subtree->right_);
		delete subtree;
		subtree = NULL;
	}
}
#endif