#include <stack>
#include <string>
#pragma once

#include <string>
#include <vector>
#include "Tag.h"

class TagStack
{
public:
	void push_nested( Tag t );
	unsigned size() const;
	std::string generate_html();
	void push_level( Tag tag, unsigned level );
private:
	std::vector<Tag> m_tags;
};
