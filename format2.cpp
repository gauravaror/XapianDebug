#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
  
  		unsigned tables = 0;
		string  in;
		string line,value;
		ifstream myfile ("sampleDocument.txt");
		if (myfile.is_open())
		{
		  while ( getline (myfile,line) )
		  {
		    in += line;
		  }
		  myfile.close();
		}
		unsigned heading = 0;
		string::iterator i;
		for (i = in.begin(); i != in.end(); ++i) {
		    switch (*i) {
			
			case '\f': // PAGE
			    value += "\n<hr>\n";
			    break;
			case '|':
			  if( *(i+1) == '\r') {
			    
			     if ( *(i+2) == '\r' && *(i+3) == '\r') {
			     	i++;
			     }
			      break;
				}
			case '\t':
			    if (tables) {
				value += "<td>";
			    } else {
				value += '\t';
			    }
			    break;
			case '\r': // BREAK or BLOCK
			    value += "\n<p>";
			case '\n':
			     if( *i != '\r')
				value += '\n';
			case '\x0b': {
			    if (++i == in.end()) {
				--i;
				break;
			    }
			    switch (*i) {
				/*case ' ':
				    while (tables) {
					--tables;
					value += "</table>\n";
				    }
				    value += "\n<table border=1><tr><td>";
				    ++tables;
				    break;*/
				 case '|':
                                    if (tables) {
                                        value += "<tr><td>";
                                        break;
                                    } else {
                                        value += "\n<table border=1><tr><td>";
                                            ++tables;
                                            break;
                                    }

                                        break;

				/*case '\t':
				    value += "<tr><td>";
				    break;*/
				case '\r':
					if (tables) {
						--tables;
				        value += "</table>\n";
				    }
				    if( *(i+1) == '\r' && *(i+2) != '\r') {
				    	i++;
				      value += "<hr>";
				      if(heading != 0 ) {
				      	 value += "<h3>";
					      heading++;
				      }
				    } else {
				        if(heading) {
					      value += "</h3>";
					      heading--;
					    } else {
					      value += "<h3>";
					      heading++;
					    }
					}

				 
				    break;
				    // FALL THROUGH
				default:
				    //value += "</p> <p>";
					if(heading) {
						value += "</h3>";
						heading--;
					}
				    value += *i;

			    }

			    break;
			}
			case '<':
			    value += "&lt;";
			    break;
			case '>':
			    value += "&gt;";
			    break;
			case '&':
			    value += "&amp;";
			    break;
			default:
			    value += *i;
		    }

		}
		while (tables) {
		    --tables;
		    value += "</table>\n";
		}
		cout<<value;
	
}