
#include "DB.h"

	DatabaseClients::DatabaseClients() {
		try {
			con = std::make_unique<pqxx::connection>(
				"host=localhost "
				"port=5432 "
				"dbname=clients "
				"user=postgres "
				"password=postgres "
				);

		}
		catch (const std::exception& ex) {
			std::cout << "Error when connecting to database: " << ex.what() << std::endl;
		}
	}
	//������� ��
	void DatabaseClients::CreateDB() {
		std::string create_client = "CREATE TABLE IF NOT EXISTS client ( "
			"id INTEGER PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY, "
			"name VARCHAR(50) NOT null, "
			"surname VARCHAR(50) NOT null, "
			"email varchar(50) "
			");";

		std::string create_phone = "CREATE TABLE IF NOT EXISTS phone ( "
			"id INTEGER PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY, "
			"client_id INTEGER not null references client(id) ON DELETE CASCADE, "
			"phone VARCHAR(20) "
			");";
		pqxx::work txn(*con);
		txn.exec(create_client);
		txn.exec(create_phone);
		txn.commit();
	}
	//�������� �������
	void DatabaseClients::AddClient(std::string name, std::string surname, std::string email) {
		pqxx::work txn(*con);
		std::string client = "INSERT INTO client (name, surname, email) VALUES ('"
			+ txn.esc(name) + "'" + ", '" + txn.esc(surname) + "', '" + txn.esc(email) + "');";
		txn.exec(client);
		txn.commit();
	}
	//�������� ID �� ����� � �������
	int DatabaseClients::GetClientID(std::string name, std::string surname) {
		pqxx::work g(*con);
		std::string get = "SELECT ID FROM CLIENT WHERE NAME = '" + g.esc(name) + "' AND SURNAME = '" + g.esc(surname) + "';";
		pqxx::result result = g.exec(get);
		if (!result.empty()) {
			int clientID = result[0][0].as<int>();
			return clientID;
		}
		else {
			std::cout << "����� �������������� ID";
			return 0;
		}

	}
	//�������� �������
	void DatabaseClients::AddPhone(int client_id, std::string phone) {
		pqxx::work txn(*con);
		std::string query = "INSERT INTO phone (client_id, phone) VALUES (" + txn.esc(std::to_string(client_id)) + ", '" + txn.esc(phone) + "');";
		txn.exec(query);
		txn.commit();
	}
	//�������� ������ � �������
	void DatabaseClients::ChangeClient(int id, std::string name, std::string surname, std::string email) {

		pqxx::work txn(*con);
		if (!(name.empty()) || !(surname.empty()) || !(email.empty())) {
			if (!(name.empty())) {
				std::string change = "update client set name ='" + txn.esc(name) + "' where id =" + std::to_string(id);
				txn.exec(change);

			}
			if (!(surname.empty())) {
				std::string change = "update client set surname ='" + txn.esc(surname) + "' where id =" + std::to_string(id);
				txn.exec(change);
			}
			if (!(email.empty())) {
				std::string change = "update client set email ='" + txn.esc(email) + "' where id =" + std::to_string(id);
				txn.exec(change);
			}
			txn.commit();

		}
		else {
			std::cout << "�������� ������ ��������";
		}

	}
	//������� �������
	void DatabaseClients::DeletePhone(int client_id) {
		pqxx::work txn(*con);
		std::string query = "DELETE FROM phone WHERE CLIENT_ID = " + txn.esc(std::to_string(client_id)) + ";";
		txn.exec(query);
		txn.commit();
	}
	//������� �������
	void DatabaseClients::DeleteClient(int client_id) {
		pqxx::work txn(*con);
		std::string query = "DELETE FROM client WHERE ID = " + txn.esc(std::to_string(client_id)) + ";";
		txn.exec(query);
		txn.commit();
	}
	//����� �������
	void DatabaseClients::FindClient(std::string search) {
		pqxx::work txn(*con);
		std::string query = "SELECT C.NAME, C.SURNAME, C.EMAIL, P.PHONE FROM CLIENT C "
			"LEFT JOIN PHONE P ON P.CLIENT_ID = C.ID "
			"WHERE C.NAME LIKE '" + txn.esc(search) + "' "
			"OR C.SURNAME LIKE '" + txn.esc(search) + "' "
			"OR C.EMAIL LIKE '" + txn.esc(search) + "' "
			"OR P.PHONE LIKE '" + txn.esc(search) + "'; ";
		pqxx::result res = txn.exec(query);
		std::cout << "Name\t" << "Surname\t" << "Email\t\t" << "Phone\t" << std::endl;
		for (int row = 0; row < res.size(); row++) {
			for (int col = 0; col < res.columns(); col++) {
				std::cout << res.at(row).at(col).c_str() << "\t";
			}
			std::cout << std::endl;
		}
	}
	//������� ��� �������
	void DatabaseClients::PrintAll() {
		pqxx::work txn(*con);
		std::string query = "SELECT C.NAME, C.SURNAME, C.EMAIL, P.PHONE FROM CLIENT C "
			"LEFT JOIN PHONE P ON P.CLIENT_ID = C.ID;";
		pqxx::result res = txn.exec(query);
		std::cout << "Name\t" << "Surname\t" << "Email\t\t" << "Phone\t" << std::endl;
		for (int row = 0; row < res.size(); row++) {
			for (int col = 0; col < res.columns(); col++) {
				std::cout << res.at(row).at(col).c_str() << "\t";
			}
			std::cout << std::endl;
		}
	}