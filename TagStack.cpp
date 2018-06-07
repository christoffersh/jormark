#include <stdexcept>
#include "TagStack.h"

void TagStack::push_nested( Tag tag )
{
	// nest tag in front tag
	if ( m_tags.size() > 0 )
		m_tags.back().top().push(tag);
	else
		m_tags.push_back( tag );
}

void TagStack::push_level( Tag tag, unsigned level )
{
	if ( m_tags.size() == 0 )
		throw std::runtime_error("Can't push to non-existing level " + std::to_string(level));
	else if ( level == 0)
		m_tags.push_back( tag );
	else
		m_tags.back().push_level( tag, level-1 );
}
	
unsigned TagStack::size() const
{
	return m_tags.size();
}

std::string TagStack::generate_html()
{
	std::string str;
	
	for ( auto const& tag: m_tags )
	{
		str += tag.generate_html(0);
	}
	
	return str;
}
	
