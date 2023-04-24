#include <iostream>
#include <string>
#include <fstream>
//#include <windows.h>
//#include <time.h>
//#include <algorithm>
//#include <array>

// Service functions prototypes ------------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		
int Get_Int_PG();				// peek&get вариант проверки ввода INTEGER	
double Get_Dbl_SA();		// String-analysis вариант фильтра DOUBLE.
double Get_Dbl_Positive();	// String-analysis вариант фильтра DOUBLE_POSITIVE
double Get_Dbl_PG();		// peek&get вариант проверки ввода DOUBLE	
int Get_Random(int Range_min, int Range_max);
double Get_Random(double Range_min, double Range_max);
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max);
template <typename ANY> void Array_Console_Out(ANY arr[], int Size);

// Classwork 24.04.2023 ----------------------------------------------------	

// fstream

//Task 1. Reading and overwriting
void Task_1(std::string File_Path, std::fstream& file_object)
{
	std::cout << "\n" << "Task_1";

	if (file_object.is_open())
	{
		std::string temp_str = "text information here";

		std::cout << "\n" << "File is open";
		//std::cout << "\n" << "Enter a string: " << temp_str;
		file_object << temp_str << "\n";
		std::cout << "\n" << "Data added: " << temp_str;

	}
	else std::cout << "Error file openning";
}

//Task 2
void Task_2(std::string File_Path, std::fstream& file_object)
{
	std::cout << "\n\n" << "Task_2";
	if (file_object.is_open())
	{
		std::string temp_str = "text information here";

		std::cout << "\n" << "File is open";
		std::cout << "\n" << "File " << File_Path <<" :\n";
		
		char sym;
		while (file_object.get(sym))
			std::cout << sym;
	}
	else std::cout << "Error file openning"; if (file_object.is_open());			
}

//Task_3 combine reading/overwriting
void Task_3(std::string File_Path, std::fstream& file_object)
{
	std::cout << "\n\n" << "Task_3";

	// .seekg() - seek get pointer 
	// .seekp() - seek put pointer
	// parameters: (offset, [position] = ios::cur)

	// [position]:
	//ios::beg - begin of file label
	//ios::end - end of file label
	//ios::cur - текущая позиция указателя

	if (file_object.is_open())
	{
		std::string temp_str = "text information here";

		file_object << temp_str << "\n";
		std::cout << "\n" << "Data added: " << temp_str;

		file_object.seekg(0, std::ios::beg);
		//std::cout << "\n" << "File is open";

		std::cout << "\n\n" << "File " << File_Path << ":\n";

		char sym;
		while (file_object.get(sym))
			std::cout << sym;

	}
	else std::cout << "Error file openning"; if (file_object.is_open());
}

//Task_4
void Task_4(std::string File_Path, std::fstream& file_object)
{
	std::cout << "\n\n" << "Task_4";

	// открытие в режимах in (чтение), app (добавка)

	file_object.close();
	file_object.open(File_Path, std::ios::in | std::ios::app);

	// std::ios::app  - режим добавки в файл (всегда добавляет в конец)


	if (file_object.is_open())
	{
		std::string temp_str = "text information here";

		file_object << temp_str << "\n";
		std::cout << "\n" << "Data added: " << temp_str;

		file_object.seekg(0, std::ios::beg);
		//std::cout << "\n" << "File is open";

		std::cout << "\n\n" << "File " << File_Path << ":\n";

		char sym;
		while (file_object.get(sym))
			std::cout << sym;

	}
	else std::cout << "Error file openning"; if (file_object.is_open());
}

//Task_5
bool file_cout(std::string File_Path)
{
	static std::ifstream in;
	in.open(File_Path);
	if (in.is_open())
	{
		char sym;
		while (in.get(sym))
			std::cout << sym;
		std::cout << "\n";
		in.close();
		return true;
	}
	in.close();
	return false;
}
bool in_file_insertion(std::string File_Path, int N_position, std::string STRING_INSERTION)
{
	std::fstream filestream_for_insertion;
	std::string file_data;


	filestream_for_insertion.open(File_Path, std::ios::in);
	
	if (filestream_for_insertion.is_open())
	{
		char sym;
		while (filestream_for_insertion.get(sym))
			file_data += sym;

	}
	else
	{
		filestream_for_insertion.close();
		return false;
	}

	filestream_for_insertion.close();

//////
	file_data.insert(N_position, STRING_INSERTION);
//////

	//std::ofstream filestream_for_insertion;
	
	filestream_for_insertion.open(File_Path, std::ios::out);

	if (filestream_for_insertion.is_open())
	{
		filestream_for_insertion << file_data;
		filestream_for_insertion.close();
		return true;
	}
	else
	{
		filestream_for_insertion.close();
		return false;
	}

}
void Task_5(std::string File_Path, std::fstream& file_object)
{
	std::cout << "\n\n" << "Task_5";
	std::cout << "\nFile read:\n";
	file_cout(File_Path);
	std::string STRING_INSERTION = "<<<STRING_INSERTION>>>";
	std::cout << "\n\n" << "Enter position to insert ";
	int N_position = Get_Int_Positive();
	in_file_insertion(File_Path, N_position, STRING_INSERTION);

	std::cout << "\nFile read:\n";
	file_cout(File_Path);
}

//Task_6
void Task_6()
{
	std::string	File_Path = "date.txt";
	std::string	File_Data;

	std::fstream file_stream;

	file_stream.open(File_Path);
		if (file_stream.is_open())
		{
			char symb;
			while (file_stream.get(symb))
			{
				File_Data += symb;
			}
		}

		



		unsigned int day, month, year;

		day = stoi(File_Data.substr(0, File_Data.find(".")));

		int month_offset = File_Data.find(".", File_Data.find("."));


		month = stoi(File_Data.substr(File_Data.find(".")+1, month_offset));
		
		//int year_offset = File_Data.find(".", month_offset, File_Data.find(".", month_offset+1));
		int year_offset = File_Data.find(".", month_offset+1);

		year = stoi(File_Data.substr(year_offset +1));

		std::cout << "Day " << day << "\nMonth " << month << "\nYear " << year;

}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	std::string File_Path =  "file.txt" ;	
	std::fstream file_object;
	
	file_object.open(File_Path);
	/*
	Task_1(File_Path, file_object);
	Task_2(File_Path, file_object);
	Task_3(File_Path, file_object); //	combine reading/overwriting
	Task_4(File_Path, file_object);
	
	File_Path = "file_2.txt";
	Task_5(File_Path, file_object);
	//file_cout(File_Path);
	*/
	Task_6();



	





	file_object.close();
	
	std::cout << "\n\n";
	system("pause");
	return 0;
}

// Service functions -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); 
	std::cin.clear(); 
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding. [INTEGER] expected.\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. [INTEGER] expected.\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol. [INTEGER] expected.\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. [INTEGER] expected.\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "") 
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Input Error: overflow. Positive [INTEGER] expected.\n";
			}
		}
		else
		{
			std::cout << "Input Error: Positive [INTEGER] expected.\n";
			return Get_Int_Positive();
		}		
	}
	else
		std::cout << "Input Error: NULL input. Positive [INTEGER] expected.\n";
	return Get_Int_Positive();
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [INTEGER] expected. Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA(){
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding. [DOUBLE] expected.\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig. [DOUBLE] expected.\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}		 	
				try{
					return stod(a);
				}
				catch (std::out_of_range) {
					std::cout << "Input Error: overflow. [DOUBLE] expected.\n";
					return Get_Dbl_SA();					
				}						
	}
	else {		
		std::cout << "Incorrect symbols: [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}
double Get_Dbl_Positive(){
	std::string a, dot = ".";
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{
		if ((a.find_first_not_of(".0123456789") == -1))
		{
			bool One_Dot_already = false;
			for (int i = 0; i < a.size(); i++)
			{				
				if (a[i] == dot[0] && One_Dot_already == true) //проверяем количество разделителей
				{
					std::cout << "Input Error: Dot misstandig. Positive [DOUBLE] expected.\n";
					return Get_Dbl_Positive();
				}
				if (a[i] == dot[0])	One_Dot_already = true;
			}
			try
			{				
				return stod(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. Positive [DOUBLE] expected.\n";
				return Get_Dbl_Positive();
			}
		}
		else
		{
			//std::cout << "Incorrect symbols: positive REAL expected.\nUse coma instead of dot. Example 50,64\n"; // да точно говорю вот даже сообщение такое было, а теперь наоборот wtf*2?!
			std::cout << "Incorrect symbols: Positive [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
			return Get_Dbl_Positive();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. Positive [DOUBLE] expected.\n";
		return Get_Dbl_Positive();
	}
	return Get_Dbl_Positive();
}
double Get_Dbl_PG()
{
	double a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [DOUBLE] expected. Repeat please...\n";
	}
	return a;
}
int Get_Random(int Range_min=-999, int Range_max=999)
{
	if (Range_min > Range_max) 
	{ 
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	//return (Range_min + rand() % (Range_max - Range_min + 1));
	double K_random = double((rand() % RAND_MAX)) / RAND_MAX;
	int random = Range_min + ((Range_max - Range_min) * K_random);
	//return Range_min + (Range_max - Range_min) * (rand() % RAND_MAX) / RAND_MAX;
	return random;
}
double Get_Random(double Range_min=-9999.0, double Range_max=9999.0)
{
	if (Range_min > Range_max)
	{
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	return 	Range_min + (Range_max - Range_min) * double(rand() % RAND_MAX) / RAND_MAX;	
}
template <typename ANY> void Array_Console_Out(ANY arr[], int Size)
{
	std::cout << "\n[";
	for (int i = 0; i < Size; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b]\n";
}
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max)
{
	for (int i = 0; i < Size; i++)
	{
		arr[i] = Get_Random(Range_min, Range_max);		
	}
}