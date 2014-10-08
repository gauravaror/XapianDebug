
/*#include <xapian/document.h>
#include <xapian/enquire.h>
#include <xapian/termgenerator.h>
#include <xapian/queryparser.h>
#include <xapian/query.h>
#include <xapian/stem.h>*/
#include <xapian.h>
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cmath> 
#include <fstream>

using namespace std;
int main() {

    string text="";
    string line;
    		ifstream myfile ("/home/gaurav/Frisk/TestData/Test data - saved/Golf test 01.txt");
		if (myfile.is_open())
		{
		  while ( getline (myfile,line) )
		  {
		    text += line;
		  }
		  myfile.close();
		}

    // Retrieve actual snippet.
    cout<<"TEXT"<<endl;
    cout<<text<<endl;
    size_t last_pos = 0;
    string snippet;
    int snippet_begin = 62412;
    unsigned int current_size = 0;
    size_t length = 550;
    while (snippet.size() < length) {
	if (last_pos == text.length()) {
	    break;
	}

	size_t new_pos = text.find(". ", last_pos);
	cout<<"new_pos"<<new_pos<<endl;
	if (new_pos == string::npos) {
	    new_pos = text.length() - 1;
		if(new_pos-last_pos < length) {
	    	last_pos = text.length()-length+1;
	}    
	}
	
	string sentence(text, last_pos, new_pos - last_pos + 1);
	cout<<"sentence size "<<sentence.size()<<"  "<<length<<endl;

	if (sentence.size() > length) {
		cout<<sentence.size()<<"  "<<length<<"  "<<text.find(" ", new_pos-50)<<"  "<<new_pos<<" ddd "<<last_pos<<endl;
		int newlength = text.find(" ",last_pos+length-50);
		if(newlength == -1) {
			newlength = last_pos+length-10;
			cout<<"new lenght"<<endl;
		}
		int origlen = newlength - last_pos ;
		cout<<"newlength : "<<newlength<<"origlen  "<<origlen<<" sentence1 "<<endl;
		new_pos = last_pos+origlen;
		string sentence1(text, last_pos, origlen);
		sentence = sentence1;
		cout<<"sentence1 : " <<" sentence1 "<<sentence<<endl;
	}

	Xapian::Document sent_doc;
	Xapian::TermGenerator term_gen;

	term_gen.set_document(sent_doc);
	term_gen.index_text(sentence);

	int sent_size = 0;

	for (Xapian::TermIterator it = sent_doc.termlist_begin(); it != sent_doc.termlist_end(); ++it) {
	    sent_size += it.positionlist_count();
	}

	current_size += sent_size;
	cout<<"current_size"<<current_size<<" snippet_size"<<snippet.size()<<endl;
		if (current_size > snippet_begin) {
	    	snippet += sentence;
		}
	    last_pos = new_pos + 1;
    }

    cout<<"OLD Snippet"<<endl;;
    //cout<<snippet<<endl;
    if (snippet.size() >= length) {
	snippet.resize(length - 3);
	snippet += "...";
    }
	cout<<"New Snippet"<<endl;
    cout<<snippet<<endl;


}