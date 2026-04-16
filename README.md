🎵 MP3 Tag Reader in C
📌 Overview

This project is a simple MP3 Tag Reader developed in C that extracts metadata from audio files. 
It reads information such as title, artist, album, and other details stored in ID3 tags by processing the binary structure of MP3 files.

🚀 Features
1.Extracts MP3 metadata (ID3 tags)
2.Displays title, artist, album, and more
3.Works with binary file processing
4.Simple and lightweight C implementation

🛠️ Technologies Used
C Programming
File Handling
String Manipulation
Structures and Functions

⚙️ How It Works

The program reads the MP3 file in binary mode and locates the ID3 tag section. It then parses different frames within the tag to extract meaningful metadata like song name, artist, and album, and displays it to the user.

▶️ How to Run
gcc mp3_tag_reader.c -o reader
./reader sample.mp3

📚 Learning Outcomes
Understanding of binary file handling in C
Knowledge of MP3 file structure and ID3 tags
Improved string handling and parsing skills
Hands-on experience with real-world file formats

⚠️ Challenges Faced
Handling binary data accurately
Parsing ID3 tag structure correctly
Managing memory and avoiding data corruption

🔮 Future Improvements
Support for editing MP3 tags
GUI-based interface
Support for more audio formats

👤 Author
Rushikesh
