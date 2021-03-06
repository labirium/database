/// @file 
/// @brief Файл содержит реализацию классов для храенения и предоставления доступа к данных БД

#include <database/include/precompiled.h>

namespace sqlite
{

//=====================================================================================================================
void Value::Set( const boost::any& data ) throw()
{
	data_ = data;
	isNull_ = false;
}
//=====================================================================================================================
void Value::SetNull( void ) throw()
{
	data_ = boost::any();
	isNull_ = true;
}
//=====================================================================================================================
bool Value::IsNull( void ) const throw()
{
	return isNull_;
}
//=====================================================================================================================
const boost::any& Value::Get( void ) const throw()
{
	return data_;
}
//=====================================================================================================================
const sqlite::FieldPtr& Value::Field( void ) const throw()
{
	return field_;
}
//=====================================================================================================================
Value::Value( const boost::any& data, const sqlite::FieldPtr& field ) : data_( data ), field_( field ), isNull_( false )
{
	if( !field )
	{
		assert( !"Invalid input data.");
		throw sqlite::Exception( "Invalid input data." );
	}
}
//=====================================================================================================================
Value::~Value()
{
}
//=====================================================================================================================
}
