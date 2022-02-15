/**
 * Copyright 2022 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   main.cpp
 * @author Scott Brauer
 * @date   01-28-2022
 */

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
using namespace std;

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
	int af[2];
    pipe(af);

	pid_t pid1;
    pid1 = fork();

    int nbytes, wbytes;
    char inside[20];

    if(pid1 == -1)
    {
        cout << "No child process formed: " << getpid() <<endl;
        exit(1);
    }
    else if(pid1 == 0)
    {
    	// Child
    	cout << pid1 << ": inchild" << endl;
    	dup2(af[1],1);
        close(af[0]);
        //wbytes = write(af[1], "Hello World", 12);
        cout << "\t" << pid1 << ": Hello World" << endl;
        cout << "\t" << pid1 << ": wrote bytes: " << wbytes<<endl;
        cout << "\t" << pid1 << ": Child(write) inside string: " << af[1] << endl;
        close(af[1]);
        cout << "\t" << pid1 << ": in child's end" << endl;
        exit(0);
    }
    else
    {
    	// Parent
    	cout << pid1 << ": inparent" <<endl;
        close(af[1]);

        boost::iostreams::file_descriptor_source src{af[0], boost::iostreams::close_handle};
        boost::iostreams::stream<boost::iostreams::file_descriptor_source> is{src};

        std::string s;
        std::getline(is, s);
        std::cout << pid1 << ": " << s << endl;
        std::getline(is, s);
        std::cout << pid1 << ": " << s << endl;
        std::getline(is, s);
        std::cout << pid1 << ": " << s << endl;
        std::getline(is, s);
        std::cout << pid1 << ": " << s << endl;
        std::getline(is, s);
        std::cout << pid1 << ": " << s << endl;

 //       nbytes = read(af[0], inside, 12);
 //       cout << pid1 << ": read bytes: "<< nbytes << endl;
 //       cout << pid1 << ": parent(read) inside descriptor: " << inside << endl;

//        nbytes = read(af[0], inside, 12);
//        cout << pid1 << ": read bytes: "<< nbytes << endl;
//        cout << pid1 << ": parent(read) inside descriptor: " << inside << endl;

//        close(af[0]);
        cout << pid1 << ": in parents's end" << endl;
        exit(0);
    }

    /*
    if(pid1 == -1)
    {
        cout << "No child process formed: " << getpid() <<endl;
        exit(1);
    }
    else if(pid1 == 0)
    {
    	cout << pid1 << ": inchild" <<endl;
        close(af[1]);
        nbytes = read(af[0],inside,strlen(inside));
        cout << pid1 << ": read bytes: "<< nbytes << endl;
        cout << pid1 << ": child(read) inside descriptor: " << inside << endl;
        close(af[0]);
        cout << pid1 << ": in child's end" << endl;
        exit(0);
    }
    else
    {
    	cout << pid1 << ": inparent" << endl;
        close(af[0]);
        wbytes = write(af[1],"Hello World",12);
        cout << pid1 << ": wrote bytes: " << wbytes<<endl;
        cout << pid1 << ": Parent(write) inside string: " << af[1] << endl;
        close(af[1]);
        cout << pid1 << ": in parent's end" << endl;
        exit(0);
    }
    */

    return 0;
}
