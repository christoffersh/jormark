#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Tag.h"

class Tag;


class Tag
{
public:
	Tag( std::string const& tagname );
	std::string generate_html( unsigned curlevel ) const;
	void push( Tag nested );
	Tag & top();
	void push_level( Tag tag, unsigned level );
	
private:
	std::string m_tagname;
	std::vector<Tag> m_nested;
};
