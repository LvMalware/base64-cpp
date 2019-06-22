/*
 base64.cpp -- Functions to encode/decode a string from/to base64

 Copyright 2019 Lucas V. Araujo.

 	This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
	 
 	This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 GNU General Public License for more details.

 	You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
	 */
#include <iostream>

#include "base64.h"

/*	Base64 default charset	*/
static const char*
base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890+/";

/*	Base64 decoding table	*/
static const char decode64[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

string
base64Encode(const string &str)
{
	/*
	 * Encodes the input string (str) to base64
	 */

	/*	This string variable will (temporaly) store the encoded string	*/
	string encoded;

	/*	With a loop, it converts 3 chars at time
	 (3 chars in normal base become 4 in base64)	*/
	for (u64 i = 0; i<str.size(); i+=3)
	{
		/*	Store the 3 octets in a int variable (32 bits), left shifting
			each char in a factor of 16, 8, 0	*/
		unsigned int octets_3 = (unsigned int) (str[i] << 16)
			+ (unsigned int) (str[i+1] << 8) + (unsigned int) str[i+2];
		/*	The first char will be that int right shifted 18 times.
		 	The & operation forces it to have only 6 significant bits	*/
		encoded += base64[ (octets_3 >> 18) & 63 ];
		/*	The second char will be the int right shifted 12 times	*/
		encoded += base64[ (octets_3 >> 12) & 63 ];
		/*	The third char will be the int right shifted 6 times	*/
		encoded += base64[ (octets_3 >>  6) & 63 ];
		/*	The last char will be the last 6 bits of the int	*/
		encoded += base64[ (octets_3      ) & 63 ];
	}
	/*	Gets the rest of the division of STR length by 3	*/
	int fill = str.size() % 3;
	/*	Based on FILL, it fills the string with "=" to match the
	 apropriate base64 length that should be of 4*size/3	*/
	if (fill == 2)
		encoded += "=";
	else if (fill == 1)
		encoded += "==";
	return encoded;
}

string
base64Decode(const string &str)
{
	/*	Decodes the base64 input string (str)	*/

	/*	String variable to temporaly store the decoded data	*/
	string decoded;

	/*	This loop will decode 4 characteres at time
	 (which will become 3 when decoded)	*/
	for (u64 i = 0; i < str.size(); i+=4)
	{
		/*	Gets the four octets correspondences on the decod table as unsigned
		 ints (32 bits)	taking care to get only the valid chars */
		unsigned int octet_0 = (str[i+0] != '=') ? decode64[str[i+0]] : 0;
		unsigned int octet_1 = (str[i+1] != '=') ? decode64[str[i+1]] : 0;
		unsigned int octet_2 = (str[i+2] != '=') ? decode64[str[i+2]] : 0;
		unsigned int octet_3 = (str[i+3] != '=') ? decode64[str[i+3]] : 0;

		/*	Join all the four octets in one variable of 32 bits,
		 	left shifting each one in factors of 18, 12, 6, 0 */
		unsigned int octets4 = (octet_0 << 18) + (octet_1 << 12)
			+ (octet_2 << 6) + (octet_3 << 00);
		
		/*	The first character (if exists) will be that int right shifted
			16 times. The if statement verify if its a valid char (not 0)
			The & operation forces the char to have only 8 significant bits */
		if ((char) (octets4 >>16))
			decoded += (octets4 >> 16) & 255;
		/*	The second char (if exists) will be that int right shifted 8 times.
			The if statement verify if it is a valid char (different of 0) */
		if ((char) (octets4 >> 8 ))
			decoded += (octets4 >> 8) & 255;
		/*	The last char (if exists) will be the left 8 bits of the int.
			The if statement verify if it is a valid char (different of 0) */
		if ((char) (octets4))
			decoded += (octets4) & 255;
	}
	return decoded;
}