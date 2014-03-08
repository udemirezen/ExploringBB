/** Simple On-board LED flashing program - written by Derek Molloy
    simple functional struture for the Exploring BeagleBone book
    changed to be a multi-call binary

    This program uses USR LED 3 and can be executed in three ways:
         onled
         offled
         flashled  (flash at 100ms intervals - on 50ms/off 50ms)
         ledstatus (get the trigger status)
    Using the symbolic links that are created in the build script 
*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define LED0_PATH "/sys/class/leds/beaglebone:green:usr3"

void removeTrigger(){
   // remove the trigger from the LED
   std::fstream fs;
   fs.open( LED0_PATH "/trigger", std::fstream::out);
   fs << "none";
   fs.close();
}

bool endsWith(std::string const &in, std::string const &com){
   return (0 == in.compare(in.length() - com.length(), com.length(), com));
}

int main(int argc, char* argv[]){
   if(argc!=1){
	cout << "Use of makeLEDmulti is by calling one of: " << endl;
        cout << "   flashled, onled, offled, ledstatus commands." << endl;
	cout << " example usage:  sudo ./flashled" << endl;
	return 1;
   }
   std::fstream fs;
   //cout << "Starting the makeLEDmulti program" << endl;
   //cout << "args[0] is: " << argv[0] << endl;
   cout << "The current LED Path is: " << LED0_PATH << endl;

   // select whether command is on, off, flash or status
   if(endsWith(argv[0],"onled")){
	removeTrigger();
        cout << "Turning the LED on" << endl;
	fs.open (LED0_PATH "/brightness", std::fstream::out);
	fs << "1";
	fs.close();
   }
   else if (endsWith(argv[0], "offled")){
	removeTrigger();
        cout << "Turning the LED off" << endl;
	fs.open (LED0_PATH "/brightness", std::fstream::out);
	fs << "0";
	fs.close();
   }
   else if (endsWith(argv[0],"flashled")){
        cout << "Flashing the LED" << endl;
	fs.open (LED0_PATH "/trigger", std::fstream::out);
	fs << "timer";
	fs.close();
	fs.open (LED0_PATH "/delay_on", std::fstream::out);
	fs << "50";
	fs.close();
	fs.open (LED0_PATH "/delay_off", std::fstream::out);
	fs << "50";
	fs.close();
   }
   else if (endsWith(argv[0],"ledstatus")){
	// display the current trigger details
        cout << "Current trigger details:" << endl;
	fs.open( LED0_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line;
	fs.close();
   }
   else{
	cout << "Invalid command!" << endl;
   }
   //cout << "Finished the makeLEDmulti" << endl;
   return 0;
}
