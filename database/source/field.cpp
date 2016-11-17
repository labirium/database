/// @file 
/// @brief Файл содержит реализацию классов для формирования описания полей таблицы.

#include <database/include/precompiled.h>


#include <boost/any.hpp>
#include <map>
//=====================================================================================================================
namespace
{
/// Строка для SQLITE_INTEGER
const wchar_t* const STR_INTEGER = L"INTEGER";
/// Строка для SQLITE_FLOAT
const wchar_t* const STR_FLOAT = L"FLOAT";
/// Строка для SQLITE_TEXT
const wchar_t* const STR_TEXT = L"TEXT";
/// Строка для SQLITE_BLOB
const wchar_t* const STR_BLOB = L"BLOB";
/// Строка для SQLITE_NULL
const wchar_t* const STR_NULL = L"NULL";
/// Строка "PRIMARY KEY"
const wchar_t* const PRIMARY_KEY = L" NOT NULL PRIMARY KEY AUTOINCREMENT";
}
//=====================================================================================================================
namespace sqlite
{
//=====================================================================================================================
const wchar_t* const FieldType::ToString( void ) const
{
	switch( type_ )
	{
	case enums::FieldType::Integer:
		return STR_INTEGER;
	case enums::FieldType::Float:
		return STR_FLOAT;
	case enums::FieldType::Text:
		return STR_TEXT;
	case enums::FieldType::BLob:
		return STR_BLOB;
	default:
		throw sqlite::Exception( "Type isn't defined." );
	}
}
//=====================================================================================================================
FieldType::operator const wchar_t* () const
{
	return ToString();
}
//=====================================================================================================================
FieldType::FieldType( const enums::FieldType type ) : type_( type )
{
}
//=====================================================================================================================
FieldType::~FieldType()
{
}
//=====================================================================================================================
//Field
//=====================================================================================================================
std::wstring Field::operator()() const
{
	std::wstringstream stream;
	
	stream << name_ << " " << FieldType( type_ );
	stream << ( primaryKey_ ? PRIMARY_KEY : std::wstring() );
		
	return stream.str();
}
//=====================================================================================================================
std::wstring Field::GetName(void ) const
{
	return name_;
}
//=====================================================================================================================
enums::FieldType Field::GetFieldType( void ) const
{
	return type_;
}
//=====================================================================================================================
bool Field::GetPrimaryKey(void) const
{
	return primaryKey_;
}
//=====================================================================================================================
Field::Field( const std::wstring& name, const enums::FieldType type, const bool primaryKey ) 
	: name_( name ), type_( type ), primaryKey_( primaryKey )
{
}
//=====================================================================================================================
Field::~Field()
{
}
//=====================================================================================================================
//FieldDeclarationTable
//=====================================================================================================================
FieldDeclarationTable& FieldDeclarationTable::AddField( const sqlite::FieldPtr& field )
{
	fieldList_.push_back( field );
	return *this;
}
//=====================================================================================================================
FieldDeclarationTable& FieldDeclarationTable::AddField( const std::wstring& name, const sqlite::enums::FieldType type, const bool primaryKey )
{
	fieldList_.push_back( std::make_shared<sqlite::Field>( name, type, primaryKey ) );
	return *this;
}
//=====================================================================================================================
const sqlite::FieldPtr FieldDeclarationTable::operator()( const std::wstring& name ) const
{
	const auto& data = std::find_if
	( 
		std::begin( fieldList_ ), 
		std::end( fieldList_ ), 
		[name]( const sqlite::FieldPtr& field ) -> bool
		{
			return field ? ( field->GetName() == name ) : false;
		} 
	);
	return data != std::end( fieldList_ ) ? *data : sqlite::FieldPtr();
}
//=====================================================================================================================
StringList FieldDeclarationTable::GetFieldNameList( void ) const
{
	StringList stringList;

	std::for_each
	( 
		std::begin( fieldList_ ), 
		std::end( fieldList_ ), 
		[ &stringList ]( const sqlite::FieldPtr& field )
		{
			assert( field && "Invalid's data.");
			stringList.push_back( field->GetName() );
		} 
	);

	return stringList;
}
//=====================================================================================================================
const sqlite::FieldList& FieldDeclarationTable::operator()( void ) const
{
	return fieldList_;
}
//=====================================================================================================================
FieldDeclarationTable::FieldDeclarationTable()
{
}
//=====================================================================================================================
FieldDeclarationTable::~FieldDeclarationTable()
{

}
//=====================================================================================================================
// wostream
//=====================================================================================================================
std::wostream& operator<<( std::wostream& stream, const FieldType& fieldType )
{
	stream << fieldType.ToString();
	return stream;
}
//=====================================================================================================================
std::wostream& operator<<( std::wostream& stream, const Field& field )
{
	stream << field();
	return stream;
}
//=====================================================================================================================
std::wostream& operator<<( std::wostream& stream, const sqlite::FieldList& fieldList )
{
	//флаг о первом вхождении
	auto bFirst = true;

	std::for_each
	( 
		std::begin( fieldList ), 
		std::end( fieldList ), 
		[ &stream, &bFirst ]( const sqlite::FieldPtr& field )
		{
			assert( field && "Invalid's data.");
			stream << ( bFirst ? L"" : L", " );
			stream << *field;
			bFirst = false;
		} 
	);
	
	return stream;
}
//=====================================================================================================================
std::wstring StrToStringList( const sqlite::StringList& stringList )
{
	std::wstringstream stream;

	//флаг о первом вхождении
	auto bFirst = true;

	std::for_each
	( 
		std::begin( stringList ), 
		std::end( stringList ), 
		[ &stream, &bFirst ]( const std::wstring& data )
		{
			stream << ( bFirst ? L"" : L", " );
			stream << L"\"" << data << L"\"";
			bFirst = false;
		} 
	);
	
	return stream.str();
}

//=====================================================================================================================
}