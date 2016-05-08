#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"

using namespace std;
using namespace mongo;

string randomCode(void);


int main(){
	
	DBClientConnection conn;

	try{	
		conn.connect("localhost");
		cout << "connection to 127.0.0.1 succeed." << endl;
	}catch(DBException& e){
		cout << "caught exception:" << e.what() << endl;	
	}
	
	//BSONObj p = BSON("name" << "Charizard" << "type1" << "fire" << "type2" << "flying");
	/*
	 * try{	
		conn.insert("Pokemon.Pokedex",p);
		cout << "one record updated." << endl;
	}catch(DBException& e){
		cout << "caught exception:" << e.what() << endl;
	}
	*/
	
	int cnt;
    cout << "How many sets do you want to generate?：";
	cin >> cnt ;
	system("cls");

	vector<string> code(cnt);
	BSONObj p;

	srand((unsigned)time(0));

	for(int i = 0; i < cnt; i++){
		code[i] = randomCode();
	}

	for(int i = 0; i < cnt; i++){
		cout << code[i] << endl;
		p = BSON("code" << code[i] << "status" << "unused" );
	
		try{
			conn.insert("HXTBBH.coupon",p);
		}catch(DBException& e){
			cout << "caught exception:" << e.what() << endl;
		}
	}
	
	return 0;
}

string randomCode(){
	string str = "0000-0000";
	int x;

	for(int i = 0; i < 4; i++){
		x = rand()%36;
		if(x < 10)
			str[i] += x;
		else
		    str[i] += x+7;
		x = 0;
	}

	for(int i = 5; i < 9; i++){
	    x = rand()%36;
	    if(x < 10)
		    str[i] += x;
        else
		    str[i] += x+7;
		x = 0;
	}
    return str;
}

