#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"

#define MAXLINE 256

using namespace std;
using namespace mongo;
using namespace bson;

void dealSet(string cmd, DBClientConnection& conn);
void dealCheck(string cmd, DBClientConnection& conn);

int main(void)
{
	cout << "Welcome." << endl;
	string cmd;
	char buffer[MAXLINE];
	DBClientConnection conn;

	conn.connect("localhost");

	while(1){
		cout << "> ";
		cin.getline(buffer,MAXLINE);
		buffer[MAXLINE] = '\0';
		cmd = buffer;

		if(cmd.substr(0,4) == "quit"){
			return 0;
		}else if(cmd.substr(0,5) == "check"){
			//todo	
			dealCheck(cmd, conn);	
		}else if(cmd.substr(0,3) == "set"){
			//todo
			dealSet(cmd, conn);
		}else{
			cout << "synax error!" << endl;
		}
	}	

	return 0;
}


void dealSet(string cmd, DBClientConnection& conn)
{
	int index = 4;
	BSONObj p;
	if(cmd[index] == ' ')
			index ++;
	
	string code = cmd.substr(index, 9);
	cout << code << endl;
	index += 10;
	if(cmd[index] == ' ')
		index ++;
	
	string option = cmd.substr(index,2);
	cout << option << endl;

	Query query = QUERY("code" << code);

	if(option == "-n" || option == "-N")
		conn.update(	"HXTBBH.coupon", 
						query,
					   	BSON("$set" << BSON("status" << "unused")),false,true);
	else if(option == "-y" || option == "-Y")
		conn.update(	"HXTBBH.coupon", 
						query, 
						BSON("$set" << BSON("status" << "used")),false,true);
}
void dealCheck(string cmd, DBClientConnection& conn)
{
	int index = 6;
	BSONObj p;

	if(cmd[index] == ' ')
		index ++;
	
	//cout << cmd << endl;	
	string code = cmd.substr(index, 9);
	cout << code << endl;

	auto_ptr<DBClientCursor> cursor = conn.query("HXTBBH.coupon",BSON("code" << code));
	
	if(cursor->more())
		p = cursor->next();
	cout << p.getStringField("status") << endl;
}
