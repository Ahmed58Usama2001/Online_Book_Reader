#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<sstream>
#include<ctime>
#include<iomanip>

using namespace std;

string GetCurrentTimeDate() {	
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

void Run();

class Book {
private:
	string title,author_name;
	int ISBN,n_pages;
	

public:
	vector<string>pages;
	void set_ISBN()
	{
		int n;
		cout << "Enter ISBN: ";
		cin >> n;
		ISBN = n;

	}

	void set_title() {
		string s;
		cout << "Enter Title: ";
		cin >> s;
		title = s;
	}

	void set_author()
	{
		string s;
		cout << "Enter Author name: ";
		cin >> s;
		author_name = s;
	}

	void set_npages()
	{
		cout << "Enter How many pages: ";
		int n;
		cin >> n;
		n_pages = n;
	}

	void set_pages()
	{
		string s;
		for (int i = 0; i < n_pages; i++)
		{
			cout << "Enter Page # " << i + 1 << ": ";
			cin >> s;
			pages.push_back(s);
		}
	}

	const string& get_title()const
	{
		return title;
	}

	const int& getn_pages()const
	{
		return n_pages;
	}

	const string& get_author()const
	{
		return author_name;
	}

	const int & get_ISBN()const
	{
		return ISBN;
	}
	

};

vector<Book>books;

struct reading {
	int current{1};
	int n_pages;
	string book_title;
	
	vector<string>read_pages;

	void next_page(int n)
	{
		if (current < n)
			current++;
		else
			cout << "Last page of the book.";
	}

	void prev_page()
	{
		if (current > 1)
			current--;
		else
			cout << "First page of the book.";
	}

	string stop_reading()
	{
		return GetCurrentTimeDate();
	}


};

class user {
private:
	string name, password, email, username;

	vector<reading>reads;
public:

	const string & get_username()const
	{
		return username;
	}

	const string & get_name() const
	{
		return name;
	}

const string & get_password()const
	{
		return password;
	}

const string & get_email()const
	{
		return email;
	}

	void set_username()
	{
		string s;
		cout << "Enter user name (no spaces) :";
		cin >> s;
		username = s;
	}

	void set_password()
	{
		string s;
		cout << "Enter password (no spaces) :";
		cin >> s;
		password = s;
	}

	void set_name()
	{
		string s;
		cout << "Enter name (no spaces) :";
		cin >> s;
		name = s;
	}

	void set_email()
	{
		string s;
		cout << "Enter email (no spaces) :";
		cin >> s;
		email = s;
	}

	void menu()
	{
		int choice;
		cout << "Hello " << name << " | User veiw\n\n";
		cout << "menu:\n\t1) view profile";
		cout << "\n\t2) List & select from my reading history";
		cout << "\n\t3) List & select from available books";
		cout << "\n\t4) Logout";
		cout << "\nEnter number in range 1 - 4 : ";
		cin >> choice;

		if (choice == 1)
			view_profile();

		else if (choice == 2)
			l_s_from_readings();

		else if (choice == 3)
			l_s_from_books();

		else if (choice == 4)
			logout();

		else
		{
			cout << "Please enter a valid choice";
			menu();
		}
	}

	void view_profile()
	{
		cout << "Name: " << get_name()<<endl;
		cout << "Username: " << get_username() << endl;
		cout << "E - mail: " << get_email() << endl;
		menu();
	}

	void read(Book b)
	{
		reading r;
		r.book_title = b.get_title();
		r.n_pages = b.getn_pages();

		for (int i = 0; i < b.getn_pages(); i++)
		{
			string s;
			s = b.pages[i];
			r.read_pages.push_back(s);
		}
		
		cout << "Current page: "<<r.current<<"/"<<r.n_pages<<endl;
		cout << r.read_pages[r.current - 1] << endl;

			while (true)
			{
				int choice;
				cout << "Menu:\n\t1:Next page";
				cout << "\n\t2:Previous page";
				cout << "\n\t3:stop reading";
				cout << "\nEnter number from range 1 - 3 :";
				cin >> choice;

				if (choice == 1)
				{
					r.next_page(b.getn_pages());
					cout << "Current page: " << r.current << "/" << r.n_pages << endl;
					cout << r.read_pages[r.current-1] << endl;
				}

				else if (choice == 2)
				{
					r.prev_page();
					cout << "Current page: " << r.current << "/" << r.n_pages << endl;
					cout << r.read_pages[r.current-1] << endl;
				}

				else
				{
					r.stop_reading();
					reads.push_back(r);
					break;
				}
		    }
	}

	void continue_reading(reading &r) {
		cout << "Current page: " << r.current << "/" << r.n_pages << endl;
		cout << r.read_pages[r.current-1]<<endl;

		while (true)
		{
			int choice;
			cout << "Menu:\n\t1:Next page";
			cout << "\n\t2:Previous page";
			cout << "\n\t3:stop reading";
			cout << "\nEnter number from range 1 - 3 :";
			cin >> choice;

			if (choice == 1)
			{
				r.next_page(r.n_pages);
				cout << "Current page: " << r.current << "/" << r.n_pages << endl;
				cout << r.read_pages[r.current-1] << endl;
			}

			else if (choice == 2)
			{
				r.prev_page();
				cout << "Current page: " << r.current << "/" << r.n_pages << endl;
				cout << r.read_pages[r.current-1] << endl;
			}

			else
			{
				r.stop_reading();
				break;
			}
		}

	}

	void l_s_from_books()
	{
		int choice;
		

		if (books.size() < 1)
		{
			cout << "There is no books for now.\n";
			menu();
		}
		cout << "Our current book collection:";
		for (int i = 0; i < books.size(); i++)
		{
			cout << "\n\t" << i + 1 << " " << books[i].get_title();
		}

		cout << "\nWhich book to read?:";
		cout << "\nEnter number in range 1 - " << books.size() <<": ";;
		cin >> choice;

		read(books[choice - 1]);
		menu();

	}

	void l_s_from_readings()
	{
		int choice;

		if (reads.size() < 1)
		{
			cout << "There wasn`t any sessions before.\n";
			menu();
		}

		for(int i=0;i<reads.size();i++){
			cout <<endl<< i + 1 << " " << reads[i].book_title << ": " << reads[i].current << "/" << reads[i].n_pages << " - " << reads[i].stop_reading();
		}

		cout << "\nwhich session to open?:";
		cout << "\nEnter number in range 1 - " << reads.size()<<": ";
		cin >> choice;

		continue_reading(reads[choice - 1]);
		menu();
	}

	void logout()
	{
		Run();
	}
};

class Admin {
private:
	string name, username, password;


public:
	void set_username()
	{
		string s;
		cout << "Enter user name (no spaces) :";
		cin >> s;
		username = s;
	}

	void set_password()
	{
		string s;
		cout << "Enter password (no spaces) :";
		cin >> s;
		password = s;
	}

	void set_name()
	{
		string s;
		cout << "Enter name (no spaces) :";
		cin >> s;
		name = s;
	}

const	string & get_name() const {
		return name;
	}

const	string & get_username() const {
		return username;
	}

const	string & get_password()const
	{
		return password;
	}


	void menu()
	{
		int choice;
		cout << "Hello " << name << " | Admin veiw\n\n";
		cout << "menu:\n\t1) view profile";
		cout << "\n\t2) Add book";
		cout << "\n\t3) Logout";
		cout << "\nEnter number in range 1 - 3 : ";
		cin >> choice;

		if (choice == 1)
			view_profile();

		else if (choice == 2)
			add_book();

		else if (choice == 3)
			logout();

		else
		{
			cout << "Please enter a valid choice";
			menu();
		}
	}

	void view_profile()
	{
		cout << "Name: " << get_name() << endl;
		cout << "Username: " << get_username() << endl;
		menu();
	}


	void add_book()
	{
		Book b;
		b.set_ISBN();
		b.set_title();
		b.set_author();
		b.set_npages();
		b.set_pages();

		for (int i = 0; i < books.size(); i++)
		{
			if (books[i].get_ISBN() == b.get_ISBN() && books[i].get_title() == b.get_title())
			{
				cout << "This books already exists.";
				add_book();
			}
		}

		books.push_back(b);
		menu();
	}

	void logout()
	{
		Run();
	}

};

vector<user>users;
vector<Admin>admins;

void signup()
{
	int choice;
	cout << "Enter 1 for admin veiw and 2 for user veiw: ";
	cin >> choice;

	if (choice == 2)
	{
		user u;
		u.set_name();
		u.set_email();
		u.set_password(); 
		u.set_username();
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].get_username() ==u.get_username() && users[i].get_password() == u.get_password())
			{
				cout << "This user already exist\n";
					signup();
			}
		}
		users.push_back(u);
		u.menu();
	}

	else if (choice == 1)
	{
		Admin a;
		a.set_name(); 
		a.set_password();
		a.set_username();
		for (int i = 0; i < admins.size(); i++)
		{
			if (admins[i].get_username() ==a.get_username() && admins[i].get_password() ==a.get_password())
			{
				admins[i].menu();
				break;
			}
		}

		admins.push_back(a);
		a.menu();
	}

	else
	{
		cout << "Invalid choice.";
			signup();
	}
}

void login()
{
	int choice;
	cout << "Enter 1 for Admin veiw\n 2 for User veiw: ";
	cin >> choice;

	string username, password;
	
	cout<< "Enter user name (no spaces): ";
    cin >> username;

    cout << "Enter password (no spaces): ";
    cin >> password;

	if (choice == 2) {
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].get_username() == username && users[i].get_password() == password)
			{
				users[i].menu();
				break;
			}
		}
	}

	else if (choice == 1) {
		for (int i = 0; i < admins.size(); i++)
		{
			if (admins[i].get_username() == username && admins[i].get_password() == password) {
				admins[i].menu();
				break;
			}
		}
	}

	else
	{
		cout << "Invalid choice.";
		login();
	}

	cout << "There is no such data in database\n";
	Run();

}

void Run()
{
	int choice;
	cout << "Menu\n\t1)Log in\n\t2)Sign up";
	cout << "\nEnter number in range 1 - 2 : ";
	cin >> choice;
	
	if (choice == 1)
		login();

	else if (choice == 2)
		signup();

	else
	{
		cout << "Please..Enter a valid choice";
		Run();
	}
}


int main()
{
	Run();


	return 0;
}