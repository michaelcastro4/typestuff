// Programming Assignment #1

//Suggested Library List from discussion slides (Week 4)

#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <bitset>
#include <string>
using namespace std;


string crc_function(string data_crc){

string space = "0000000000000000";
string code = data_crc + space;
string crc_16 = "10000010000010001";

    for (int i = 0; i < data_crc.length(); i ++){
        
        if((code[i] == '1')){
            code[i] = '0';
            for(int j = 1; j < crc_16.length(); j++){
                
                if(code[i+j] != crc_16[j]){
                    code[i+j] = '1';
                }
                else{
                    code[i+j] = '0';
                }
                
            }
        }
        
    }
        
    string crc_result = code.substr(data_crc.length(), space.length());
    
	
	return crc_result;
    
    
}

string crc_function_w_error(string normal_data, string updated_data){


string space = "0000000000000000";
string code = updated_data;
string crc_16 = "10000010000010001";

    for (int i = 0; i < normal_data.length(); i ++){
        
        if((code[i] == '1')){
            code[i] = '0';
            for(int j = 1; j < crc_16.length(); j++){
                
                if(code[i+j] != crc_16[j]){
                    code[i+j] = '1';
                }
                else{
                    code[i+j] = '0';
                }
                
            }
        }
        
    }
        
    string crc_error_result = code.substr(normal_data.length(), space.length());
	
	return crc_error_result;
    
    
}




uint64_t checksum_function(string checksumbitstring){


uint64_t Checksum_Total = 0;

uint64_t Checksum1 = 0;
uint64_t Checksum2 = 0;
uint64_t Checksum = 0;


for(int i = 0; i < checksumbitstring.length(); i = i + 16){

	for(int j = 0; j < 16; j++ ){

	if (checksumbitstring[i+j] == '1'){
	Checksum_Total = Checksum_Total + pow(2,(15-j));
	}
	

	
	}
	

}

    uint64_t checksum_total = (Checksum_Total & 0xFFFF) + (Checksum_Total >> 16);
    uint64_t checksum = 65535 - (checksum_total & 0xFFFF);


return checksum;

}

string data_w_error(string data, string errorbitstring){

string space = "0000000000000000";
string code = data + space;

string data_changed = code;

for(int i = 0; i < errorbitstring.length(); i ++){

	if (((code[i] == '1') && (errorbitstring[i] == '0')) || ((code[i] == '0') && (errorbitstring[i] == '1'))){
	
		code[i] = '1';
		}
		else{
		code[i] = '0';
		}
	
	
	}

return code;
}

int main() {
    ifstream myfile("data.txt");
    if (!myfile.is_open()) {
        cout << "The file can't be opened" << endl;
        return 1;
    } else {
        string input;
        while (getline(myfile, input)) {
            size_t space_index = input.find(' ');
            if (space_index != string::npos) {
                string data = input.substr(0, space_index);
                string error = input.substr(space_index + 1);

                cout << "====================================================" << endl;
                cout << "Data: " << data << endl;
                cout << "Error: " << error << endl;
                
                

                cout << "CRC-16" << endl;
                
                string crc_results = crc_function(data);
                
                string updated_data = data_w_error(data, error);
                
                string crc_updated_results = crc_function_w_error(data, updated_data);
                cout << "CRC: " << crc_results << ";";
                
	
                if (crc_results == crc_updated_results){
                cout << "		Result: " << "Pass" << endl;
                }
                else{
		cout << "		Result: " << "Not Pass" << endl;
		}
		
		
                cout << "Checksum" << endl;
                uint64_t num1 = checksum_function(data);
                uint64_t num2 = checksum_function(updated_data);

                bitset<16> binary1(num1);
                bitset<16> binary2(num2);
                
                

                cout << "Checksum: " << binary1 << ";";
          
                if (binary1 == binary2){
                cout << "	Result: " << "Pass" << endl;
		}
		else{
		cout << "	Result: " << "Not Pass" << endl;
		}
		
            } else {
                cout << "Invalid input format" << endl;
            }
        }
    }
    myfile.close();
    return 0;
}

		

