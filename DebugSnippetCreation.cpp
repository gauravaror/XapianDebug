
#include <xapian/document.h>
#include <xapian/enquire.h>
#include <xapian/termgenerator.h>
#include <xapian/queryparser.h>
#include <xapian/query.h>
#include <xapian/stem.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cmath> 

using namespace std;
int main() {

    string text="MFamily trusts^MWhat is a Family Trust?^MA trust is a legal structure under which a âtrusteeâ holds property for the^Mbenefit of        certain beneficiaries. A Family Trust is usually put in place in^Morder to benefit certain members of a family. It is the responsibility of^Mt       he trustee to administer the trust in accordance with the trust deed.^M^M^M    Our Recommendation^M^M    <<ClientName>>, you have approximatel       y <<$xxxx>> <<already invested^M    within your Family Trust / that you would like to invest in your Family^M    Trust <once it is established       >>>. You have requested our advice in^M    determining an appropriate investment strategy in relation to this^M    amount alone.^M^M    <<stat       e investment recommendations here>>^M^M<<insert other strategy text as appropriate>>^M^M<< use text where Centrelink benefits are relevant>>^M       ^M<<insert other strategy text as appropriate>>^M^M<<Include for all>>^M^MThe recommended structure is expected to assist you in meeting your        stated^Mobjectives of StateGoalsHere.^M^M^MCentrelink treatment of family trusts^M^MWhen you are involved in a private trust, Centrelink will        take income and^Massets of that trust into account when working out your entitlements,^Munless you satisfy two specific tests â the Control te       st, and the Source^Mtest. Only Centrelink can determine whether you satisfy these two tests.^M^M<<insert where Centrelink has already assessed        the clients>>^M^M<<ClientName>>, we understand that Centrelink has already assessed you, and^Mhas found that you <<do/do not>> satisfy <<both        of these tests / either of^Mthese two tests / the control test only/the source test only>>. As a result^Myour Centrelink entitlements <<are l       ikely to / should not>> be affected by^Mthe trust assets and income.^M^M<<insert where Centrelink has not already assessed the clients>>^M^M<<       ClientName>>, you have not yet been assessed by Centrelink. Based on the^Minformation you have provided us with we believe that you <<should /        will^Mnot>> satisfy <<both/either of the two tests/the control test only/the^Msource test only>>. As a result your Centrelink entitlements <<       are likely^Mto / should not >> be affected by the trust assets and income. Please note,^Mthis is intended as a guide only. Centrelink will req       uire documentation^Msuch as the trust deed, minutes, and statutory returns in order to^Mdetermine the affect on your Centrelink entitlements.^";
    // Retrieve actual snippet.
    size_t last_pos = 0;
    string snippet;
    int snippet_begin = 177;
    unsigned int current_size = 0;
    size_t length = 550;
    while (snippet.size() < length) {
	if (last_pos == text.length()) {
	    break;
	}

	size_t new_pos = text.find(". ", last_pos);
	if (new_pos == string::npos) {
	    new_pos = text.length() - 1;
	}

	string sentence(text, last_pos, new_pos - last_pos + 1);
	Document sent_doc;
	term_gen.set_document(sent_doc);
	term_gen.index_text(sentence);

	int sent_size = 0;
	for (TermIterator it = sent_doc.termlist_begin(); it != sent_doc.termlist_end(); ++it) {

	    sent_size += it.positionlist_count();
	}

	current_size += sent_size;
	if (current_size > snippet_begin)
	    snippet += sentence;

	last_pos = new_pos + 1;
    }

    if (snippet.size() >= length) {
	snippet.resize(length - 3);
	snippet += "...";
    }

    cout<<snippet;
}