#include "Tag.h"

Tag::Tag( std::string const& tagname )
	: m_tagname( tagname )
{
	
}

std::string Tag::generate_html( unsigned level ) const
{
	std::string tabs;
	
	for (int i=0; i < level; i++)
		tabs += '\t'; 
	
	std::string str;

	// start tag
	str += tabs +"<" + m_tagname + ">\n";

	// nested tags
	for ( auto const& tag: m_nested )
		str += tag.generate_html( level+1  );
	
	str+= tabs + "</" + m_tagname + ">\n";
	
	return str;
}

void Tag::push( Tag nested )
{
	m_nested.push_back( nested );
}

void Tag::push_level( Tag tag, unsigned level )
{
	if ( m_nested.size() == 0 )
		throw std::runtime_error("Can't push to non-existing level " + std::to_string(level));
	else if ( level == 0 )
		m_nested.push_back( tag ); // push to this level
	else
		m_nested.back().push_level( tag, level-1 ); // push further down
}

Tag & Tag::top()
{
	if ( m_nested.size() > 0 )
		return m_nested.back().top();
	else
		return *this;
}
