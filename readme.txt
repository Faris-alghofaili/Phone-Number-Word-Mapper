Phone Number Word Mapper
This C program converts a 7-digit phone number (excluding digits 0 and 1) into all possible alphabetical word combinations using the classic telephone keypad layout. It then checks if any of these combinations (full 7-letter words or 3+4 splits) exist in a dictionary file (dict.txt). Valid words are printed to the console and all combinations are written to output.txt.

🔧 Features
Accepts a 7-digit phone number in the format XXX-XXXX.

Generates all possible alphabetical combinations.

Checks if combinations exist in a dictionary using binary search.

Prints valid word(s) to the console.

Saves all possible combinations to output.txt.

📁 Files
main.c: The main C source code.

dict.txt: A dictionary file containing valid lowercase words (sorted).

output.txt: Output file where all generated combinations are saved.

 Format Requirements
Phone number input format: XXX-XXXX

Valid digits: Only 2–9 (no 0 or 1)

Dictionary (dict.txt) must:

Be sorted in ascending order

Contain one word per line

Use only lowercase letters

Key Functions
writeWordsToFile(): Generates and processes all word combinations.

binarySearchWord(): Checks full 7-letter word in dictionary.

binarySearchSplit1() & binarySearchSplit2(): Checks 3-letter and 4-letter split words in dictionary.
