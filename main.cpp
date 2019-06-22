/*	main.cpp -- main file just to test the functions	*/
#include <iostream>
#include "base64.h"

using namespace std;

int
main()
{
	/*	A fragment of "To See a World..." of William Blake	*/
	string text = "\
	To see a World in a Grain of Sand\n\
	And a Heaven in a Wild Flower,\n\
	Hold Infinity in the palm of your hand\n\
	And Eternity in an hour.";
	/*	Encode the text	*/
	string code = base64Encode(text);
	/*	Decode the text	*/
	string orig = base64Decode(code);
	
	cout << code << endl << endl;
	
	cout << orig << endl << endl;
	return 0;
}
