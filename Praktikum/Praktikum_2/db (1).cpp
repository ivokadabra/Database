#include <iostream>
#include "libpq-fe.h"
#include "db.h"
using namespace std;



PGconn* conn;
PGresult* res;

int db_login(const string& host, const string& port, const string& dbname, const string& user, const string& password) {
	conn = PQconnectdb(("host = " + host + " port = " + port + " dbname=" + dbname + " user=" + user + " password=" + password).c_str());
	if (PQstatus(conn) == CONNECTION_BAD) {
		cout << "failed connection" << endl;
		return -1;
	}
	return 0;

}

void db_logout() {
	PQfinish(conn);

}

int db_begin() {
	res = PQexec(conn, "BEGIN");
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);
		cout << "BEGINN succes" << endl;
		return 0;
	}
	PQclear(res);
	return -1;
}

int db_commit() {
	res = PQexec(conn, "COMMIT");
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "COMMIT succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}
int db_rollback() {
	res = PQexec(conn, "ROLLBACK");
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "ROLLBACK succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}

int db_create_table_hersteller() {
	res = PQexec(conn, "CREATE TABLE hersteller(hnr VARCHAR(4),name VARCHAR(30),stadt VARCHAR(30),PRIMARY KEY(hnr));");
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "create table hersteller succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;

}
int db_create_table_produkt() {
	res = PQexec(conn, "CREATE TABLE produkt(pnr VARCHAR(4),name VARCHAR(30),preis NUMERIC(8,2),hnr VARCHAR(4),PRIMARY KEY(pnr));");
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "create table produkt succes" << endl;
		return 0;
	}
	PQclear(res);
	return -1;


}


int db_drop_table(const string& tablename) {
	res = PQexec(conn,( "DROP TABLE " + tablename + ";").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "drop table" + tablename + "succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}

int db_insert_produkt(const string& pnr, const string& name, const string& preis, const string& hnr) {
	res = PQexec(conn, ("INSERT INTO produkt (pnr,name,preis,hnr) values ('" + pnr + "'" + "," + "'" + name + "'" + "," + "'" + preis + "'" + "," + "'" + hnr + "');").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "insert" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}

int db_insert_hersteller(const string& hnr, const string& name, const string& stadt) {
	res = PQexec(conn, ("INSERT INTO hersteller (hnr, name, stadt) values ('" + hnr + "'" + "," + "'" + name + "'" + "," + "'" + stadt + "'" + ");").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "insert" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;

}

int db_update_produkt(const string& pnr, const string& name, const string& preis, const string& hnr) {
	res = PQexec(conn, ("UPDATE produkt SET hnr='" + hnr + "'" + "," + "name='" + name + "'" + "," + "preis='" + preis + "' WHERE pnr='" + pnr + "'" + ";").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "update" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}

int db_update_hersteller(const string& hnr, const string& name, const string& stadt) {
	res = PQexec(conn, ("UPDATE hersteller SET name='" + name + "'" + "," + "stadt='" + stadt + "'" + "WHERE hnr='" + hnr + "';").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "update" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}



int db_delete_produkt(const string& pnr) {
	res = PQexec(conn, ("DELETE FROM produkt WHERE pnr= '" + pnr + "';").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "delete succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;
}


int db_delete_hersteller(const string& hnr) {
	res = PQexec(conn, ("DELETE FROM hersteller WHERE hnr= '" + hnr + "';").c_str());
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		cout << "delete succes" << endl;
		PQclear(res);
		return 0;
	}
	PQclear(res);
	return -1;

}

int db_delete() {
	int h = db_drop_table("hersteller");
	int p = db_drop_table("produkt");
	if (h == 1 && p == 1) {
		PQclear(res);
		return 1;
	}
	else {
		PQclear(res);
		return 0;
	}
}


int db_check_hnr(const string& hnr) {
	res = PQexec(conn,("SELECT COUNT(*) FROM hersteller WHERE hnr = " + hnr+";").c_str());
	if (PQresultStatus(res) == PGRES_TUPLES_OK) {
		cout << "select form hersteller " + hnr + "succes" << endl;
		int n = PQntuples(res);
		if (n == 1) {
			PQclear(res);
			return 1;

		}
		else if (n == 0) {
			PQclear(res);
			return 0;
		}
	}
	else {
		PQclear(res);
		return -1;
	}




}


int db_check_pnr(const string& pnr) {
	res = PQexec(conn,("SELECT COUNT(*) FROM produkt WHERE pnr = " + pnr+";").c_str());
	if (PQresultStatus(res) == PGRES_TUPLES_OK) {
		cout << "select form produkt " + pnr + "succes" << endl;
		int n = PQntuples(res);
		if (n == 1) {
			PQclear(res);
			return 1;
		}
		else if (n == 0) {
			PQclear(res);
			return 0;
		}
	}
	else {
		PQclear(res);
		return -1;
	}

	PQclear(res);


}


int db_count(const string& tablename) {
	res = PQexec(conn,("SELECT COUNT(*) FROM " + tablename + ";").c_str());
	if (PQresultStatus(res) == PGRES_TUPLES_OK) {
		PQclear(res);
		return PQntuples(res);
	}
	else {
		PQclear(res);
		return -1;
	}


}















