#include <iostream>
#include "DB.h"

int main() {
	setlocale(LC_ALL, "Russian");
	DatabaseClients client;
	client.CreateDB();
	client.AddClient("John", "Smith", "smith@gmail.com");
	client.AddClient("Sam", "Right", "smith@gmail.com");
	client.AddClient("Ben", "Jones", "smith@gmail.com");

	client.AddPhone(1, "+79500000000");
	client.AddPhone(2, "+79100000000");
	client.AddPhone(3, "+79203000000");

	client.AddPhone(client.GetClientID("John", "Smith"), "+79110000000");
	std::cout << client.GetClientID("John", "Smith") << std::endl;
	std::cout << "Все записи таблицы: \n";
	client.PrintAll();

	client.ChangeClient(1, "Itan", "Hope", "");
	client.DeletePhone(3);
	client.DeleteClient(1);
	std::cout << "Поиск клиента: \n";
	client.FindClient("Sam");
	return 0;


} 
