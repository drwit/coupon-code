#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"

using namespace std;
using namespace mongo;

void dealSet(string cmd, string& code, string& option);
void dealCheck(string cmd, DBClientConnection& conn);

int main(void)
{
	cout << "Welcome." << endl;

	DBClientConnection conn;
	string option;
	string code;
	string cmd;

	conn.connect("localhost");

	while(1){
		cout << "> ";
		getline(cin, cmd);

		if(cmd.substr(0,4) == "quit"){
				return 0;
        }else if(cmd.substr(0,5) == "check"){

			dealCheck(cmd,conn);
	    }else if(cmd.substr(0,3) == "set"){
	        dealSet(cmd, code, option);
			//cout << code << option;

			if(option == "-n" || option == "-N")
	            conn.update("HXTBBH.coupon", BSON("code" << code), BSON("$set" << BSON("status" << "unused")));
	        else if(option == "-y" || option == "-Y")
	            conn.update("HXTBBH.coupon", BSON("code" << code), BSON("$set" << BSON("status" << "used")));
	    }else{
				cout << "synax error!" << endl;
		}
	}
	    return 0;
}


void dealSet(string cmd, string& code, string& option)
{
    int index = 4;
    if(cmd[index] == ' ')
        index ++;

    code = cmd.substr(index, 9);
					    
    index += 10;

	if(cmd[index] == ' ')
        index ++;
	option = cmd.substr(index,2);

}

void dealCheck(string cmd, DBClientConnection& conn)
{
	int index = 6;
	BSONObj p;

	if(cmd[index] == ' ')
		index ++;
		//cout << cmd << endl;  
	string code = cmd.substr(index, 9);
	//cout << code << endl;
	auto_ptr<DBClientCursor> cursor = conn.query("HXTBBH.coupon",BSON("code" << code));
	
	if(cursor->more())
	p = cursor->next();
	cout << p.getStringField("status") << endl;
}                                                                                  
