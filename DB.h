#pragma once
#include <pqxx/pqxx>
#include <iostream>

class DatabaseClients
{
public:
	DatabaseClients();
	void CreateDB();
	void AddClient(std::string name, std::string surname, std::string email);
	int GetClientID(std::string name, std::string surname);
	void AddPhone(int client_id, std::string phone);
	void ChangeClient(int id, std::string name, std::string surname, std::string email);
	void DeletePhone(int client_id);
	void DeleteClient(int client_id);
	void FindClient(std::string search);
	void PrintAll();
private:
	std::unique_ptr<pqxx::connection> con;
};
