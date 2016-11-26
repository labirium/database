/// @file 
/// @brief Файл содержит реализацию классов для вставки полей в таблицу

#include <database/include/precompiled.h>

namespace sqlite
{
//=====================================================================================================================
std::wstring InsertValue::operator()( void ) const
{
	const std::wstring& tablename = tableName_;
	std::wstringstream stream;

	std::for_each
	( 
		std::begin( valueTableList_ ), 
		std::end( valueTableList_ ),
		[&stream, tablename ]( const ValueTable& valueTable )
		{
			stream << L"INSERT INTO " << tablename;
			stream << L" ( " <<  sqlite::StrToStringList( valueTable.GetFieldDeclarationTable().GetFieldNameList() );
			stream << L" ) VALUES ( " << valueTable << L"); ";
		}
	);

	return stream.str();
}
//=====================================================================================================================
void InsertValue::Add( const sqlite::ValueTable& data )
{
	valueTableList_.push_back( data );
}
//=====================================================================================================================
void InsertValue::Exec( const sqlite::Transaction& transaction ) const
{
	const auto& data = this->operator()();
	if( !data.length() ){
		throw sqlite::Exception( "Don't set value." );
	}

	//Выполняем
	transaction().Exec( data );
}
//=====================================================================================================================
InsertValue::InsertValue( const sqlite::Table& table ) : tableName_( table.GetName() )
{
}
//=====================================================================================================================
InsertValue::InsertValue( const sqlite::TablePtr& table ) : tableName_( table->GetName() )
{
	assert( table && "Invalid input data" );
}
//=====================================================================================================================
InsertValue::~InsertValue()
{
}
//=====================================================================================================================
}
