# Decrypter
Substitution cipher decoder

Made using C++. Project for "CS32: Introduction to Computer Science II" (course at UCLA)

Wrote the code in MyHash.h, Decrypter.cpp, Tokenizer.cpp, Translator.cpp, WordList.cpp and myTester.cpp
The rest of the code was provided by the professor.

A report describing the classes implemented is included, and present in the Decrypter folder 

The code has been set up to decrypt an 
already provided ciphertext. Steps to decrypt any other ciphertext are provided below. 

There are four example ciphertexts provided as the variables string1, ... , string4
in myTester.cpp (lines 31-34). The string to be decoded is set on line 127 (decrypter.crack(string1))
in the same .cpp file. It is currently set to string1. To decode other ciphertexts, change the argument 
of decrypter.crack() from string1 to any of the other available strings (string2 for example)
or to any other ciphertext of your choosing (place double-quoted ciphertext within the parentheses of decrypter.crack()). 
Follow the aforementioned steps to get all possible decrypted texts for any ciphertext.

Decrypting a ciphertext may take a few seconds. Some ciphertexts may take long though. 
It may help to run in release mode, which inreases the execution speed. To do this, open the Configuration Manager
from the Build dropdown menu. Change the mode from "Debug" to "Release" under "Active solution configuration". 
Then run using "Start Without Debugging".  


