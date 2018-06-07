#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include "TagStack.h"

unsigned numtabs( std::string const& str )
{
	unsigned count = 0;
	for( auto c: str )
	{
		if ( c != '\t' )
			return count;

		count++;
	}

	return count;
}

int main( int argc, char const* argv[] )
{
	if (argc < 2)
	{
		std::cerr << "Error: No file specified\n";
		std::cerr << "  usage: " << argv[0] << " <filename>\n";
		return 1;
	}
	std::string filename = argv[1];

	std::fstream fs;
	fs.open( filename, std::fstream::in );

	if ( fs.is_open() == false )
	{
		std::cerr << "Could not open file: " << filename << "\n"; 
		return 1;
	}

	TagStack tstack;
	std::string line;
	int lastLvl = -1;

	for ( unsigned count=1; std::getline(fs, line); count++ )
	{
		std::cout << "|" << count << "| " << line << "\n";

		unsigned n_tabs = numtabs(line);
		int tabDiff = n_tabs - lastLvl;

		std::stringstream ss(line);
		std::string tagname;
		ss >> tagname;
		Tag tag{ tagname };
			
		if ( tabDiff > 1 )
			throw std::runtime_error( "Extra indent found at line: " + std::to_string( count ) );
		else if ( tabDiff == 1 )
		{
			std::cout << "pushing nested\n";
			tstack.push_nested( tag );
		}
		else
		{
			std::cout << "pushing level\n";
			tstack.push_level( tag, n_tabs );
		}

		lastLvl = n_tabs;
	}

	std::fstream os;
	os.open("out.html", std::fstream::out );

	if ( os.is_open() == false )
	{
		std::cerr << "Could not open output file\n"; 
		return 1;
	}

	os << tstack.generate_html();

	std::cout << "number of tags: " << tstack.size() << "\n";
}
