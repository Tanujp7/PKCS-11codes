#include <iostream>
#include<cryptoki.h>
#include<string.h>

using namespace std;

CK_SLOT_ID slotid=0;
CK_SESSION_HANDLE session=0;
const char *slotpin="12345678";

void checkOperation(CK_RV, const char*);
void connect();
void disconnect();

int main(){
connect();
disconnect();
return 0;
}

void checkOperation(CK_RV rv,const char *message){
if(rv!=CKR_OK){

    cout<<message<<"failed with:"<<rv<<endl;
    exit(1);
}
}

void connect(){
checkOperation(C_Initialize(NULL),"C_Initialize");
checkOperation(C_OpenSession(slotid,CKF_SERIAL_SESSION|CKF_RW_SESSION,NULL,NULL,&session),"C_OpenSession");
checkOperation(C_Login(session,CKU_SO,(CK_CHAR_PTR)slotpin,strlen(slotpin)),"C_Login");
cout<<"Connected to slot via: "<<slotid<<" with the session: "<<session<<endl;
}

void disconnect(){
checkOperation(C_Logout(session),"C_Logout");
checkOperation(C_CloseSession(session),"C_CloseSession");
checkOperation(C_Finalize(NULL),"C_Finalize");
cout<<"Disconnected from all the slots"<<endl;
}

