// Розробити клас Reservoir.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class Reservoir
{
protected:
	double width;
	double length;
	double depth;
	long double volume;
	long double S;
	int ID;
	string name;
   	static int count;
	string tmp;
public:

	Reservoir()  {
		width = length = depth = ID = volume = S = 0;
		name = "Nod_name";
		 }

	Reservoir(double width, double length, double depth, string name) :  width { width }, length{ length }, depth{ depth }, name{ name }
	{	
		this->S = width * length;
		this->volume = width * length * depth;
		this->ID = count;
		count++;
	}
	
	Reservoir& operator=(const Reservoir&);
	double& GetWidth() { return width; }
	double& GetLenght() { return length; }
	double& GetDepth() { return depth; }
	long double& GetVolume () { return volume; };
	long double& GetS() { return S; }
	int& GetID() { return ID; }
	void Show();
     bool operator==(const Reservoir&);
	 bool operator>(const Reservoir&);
	 bool operator<(const Reservoir& res);
	 Reservoir& createObj();
	 
	 
};
void Reservoir:: Show() {

	cout<<"ID = "<<ID << "  Name of the body of water - " << name << "\t width = " << width << " length = " << length << " depth = " << depth << endl;
	cout << "Square = " << S << "\tVolume = " << volume << endl;
	cout << "________________________________________________________________________________________________________" << endl;
}

 
bool Reservoir::operator==(const Reservoir& res) {
	return this->name == res.name;
}
bool Reservoir:: operator< (const Reservoir& res) {
	return this->S <  res.S;
}
bool Reservoir:: operator>(const Reservoir& res) {
	return this->S > res.S;
}
Reservoir& Reservoir:: operator=(const Reservoir& res) {
	this->name = res.name; this->depth = res.depth; this->length = res.length; this->width = res.width; this->S = res.S; this->volume = res.volume; this->ID = res.ID;
	return *this;
}
Reservoir& Reservoir::createObj()
{
	int width1, length1, depth1;string name1;
	cout << "Enter name reservoir" << endl; cin >> name1; this->name = name1;
	cout << "Enter width" << endl; cin >> width1; this->width = width1;
	cout << "Enter length" << endl;	cin >> length1; this->length = length1;

	cout << "Enter depth" << endl;	cin >> depth1; this->depth = depth1;
	this->S = width * length;
	this->volume = width * length * depth; 
	this->ID = count;
	count++;
	return *this;


}


int Reservoir::count{1};

class Reservoir_mas:public Reservoir {
	Reservoir* res;
	int size;
public:
	Reservoir*& GetRes() { return *&res; }

	void Createmas(int size) {
		this->size = size;
		res = new Reservoir[size];
		for (size_t i = 0; i < size; i++)
		{
			res[i].createObj();
		}

	}
	~Reservoir_mas() {
		delete[]res;
		cout << "Destructor Reservoir_mas" << endl;
	}
	void ShowMas() {
          for (size_t i = 0; i < size; i++)
		{
			  res[i].Show();

		}
	}
		
	void Add_reservoir( Reservoir*& arr);
	void Del_reservoir(Reservoir*& arr);
	void Save_resMass(Reservoir*& arr);
	void Read_resMass(Reservoir*& arr);
};
void Reservoir_mas::Add_reservoir( Reservoir*& arr)
{
	Reservoir* temp = new Reservoir[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		temp[i]= arr[i];
		
	}
	temp[size]= createObj();
	size++;

	delete[]arr;
	arr = temp;

}
void Reservoir_mas::Del_reservoir(Reservoir*& arr) {
	int id_del;
	cout << "Enter ID for removing : " << endl;
	cin >> id_del;
	
	Reservoir* temp = new Reservoir[size-1];
	int new_size = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i].GetID() != id_del) {

			temp[new_size] = arr[i];
			new_size++;

		}
	}
	size--;
	
	delete[]arr;
	arr = temp;
}
void Reservoir_mas::Save_resMass(Reservoir*& arr) {
	ofstream fout;
	fout.open("list.txt", ios::binary);
	if (fout.is_open()) {
		if (size == 0) return;
		fout.write((char*)&size, sizeof(size));
		for (size_t i = 0; i < size; i++)
		{
         fout.write((char*)&arr[i], sizeof(Reservoir));
		}
		
	}
	fout.close();
}
void Reservoir_mas::Read_resMass(Reservoir*& arr) {
	ifstream fin;
	fin.open("list.txt", ios::binary);
	if (fin.is_open()) {
		fin.read((char*)&size, sizeof(size));
		Reservoir* temp = new Reservoir[size];
		for (size_t i = 0; i < size; i++)
		{
			fin.read((char*)&temp[i], sizeof(Reservoir));
		}
		arr = temp;
		

	}

}
int main()
{
	setlocale(LC_ALL, "Rus");
	Reservoir_mas reservoires;
	bool noexit = true;

	do
	{
		cout << "Выберите вариант " << endl;
		cout << "1- Создать массив водоёмов " << endl;
		cout << "2- Вывод списка водоёмов" << endl;
		cout << "3- Добавить водоём в массив" << endl;
		cout << "4- Удалить водоём измассива" << endl;
		cout << "5- Считать список из файла" << endl;
		cout << "6- Сохранить список в файл" << endl;
		cout << "0- Выйти из меню" << endl;
		cout << "Выберите вариант от 0  до 6 :" << endl;

		bool set = true;
		int option = 0;
		do
		{
			cin >> option;
			if (option >= 0 && option <= 6) {
				set = false;
			}

		} while (set);

		switch (option)
		{
		case 1:
			int _size;
			cout << "Введите размер массива:" << endl;
			cin >> _size;
			reservoires.Createmas(_size);
			break;
		case 2:
			reservoires.ShowMas();

			break;
		case 3:
			reservoires.Add_reservoir(reservoires.GetRes());
			break;
		case 4:
			reservoires.Del_reservoir(reservoires.GetRes());
			break;
		case 5:
			reservoires.Read_resMass(reservoires.GetRes());
			break;
		case 6:
			reservoires.Save_resMass(reservoires.GetRes());
			break;
		case 0:
			noexit = false;
			break;
		default:
			break;
		}

	} while (noexit);
	
	
	//Reservoir a{100,50,3.5,"ozero" };//для проверок отдельных фукций (не испульзуются в работе осного меню)
	//a.Show();
	//Reservoir b{};
	//b.Show();
	//b = a;//копирование объекта
	//b.Show();
	//Reservoir d{ 150,70,6,"ozero" };
	//d.Show();
	//Reservoir c{};
	///*c.createObj();*///для заполнения пользователем с клавиатуры данных водоёма
	//c.Show();
	//if (a > d) {
	//	cout << "Square a > d " << endl << endl;
	//} else if(a < d) {
	//	cout << "Square a < d " << endl << endl;
	//}
	//else {
	//	cout << "Square a == d " << endl<<endl;
	//}
	/*Reservoir_mas A;*/
	/*A.Createmas(2);
	A.ShowMas();*/
	/*A.Save_resMass(A.GetRes());*/
	/*A.Read_resMass(A.GetRes());
	A.ShowMas();
	A.Add_reservoir(A.GetRes());
	A.ShowMas();*/
	/*A.Del_reservoir(A.GetRes());
	A.ShowMas();*/
	return 0;
}  


