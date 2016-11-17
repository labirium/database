/// @file 
/// @brief Файл содержит реализацию классов для формирования запроса.

#include <database/include/precompiled.h>

namespace sqlite
{
//=====================================================================================================================
StmtPtr Query::operator()( const Transaction& transaktion ) const
{
	//Формируем запрос для таблицы
	std::wostringstream stream;
	stream << L"SELECT " << StrToStringList( fieldDeclarationTable_->GetFieldNameList() ) << " FROM " << tableName_;

	
	//Задаем праметры для WHERE
	tools::FirstString firstString( L", ");
	stream << ( where_.size() ? L" WHERE " : std::wstring() );

	std::for_each
	( 
		std::begin (where_), 
		std::end( where_ ),  
		[ &stream, &firstString ]( const std::wstring& data )
		{
			stream << data << firstString();
		}
	);

	stream << orderBy_ << limit_;

	return std::make_shared<Stmt>( transaktion, fieldDeclarationTable_, stream.str() );
}
//=====================================================================================================================
Query& Query::OrderBy( const std::wstring& name, enums::OrderByType type )
{
	orderBy_ = L" ORDER BY \"" + name + ( type == enums::ASC ? L"\" ASC" : L"\" DESC" );
	return *this;
}
//=====================================================================================================================
Query& Query::Limit( const unsigned int limit )
{
	limit_ = L" LIMIT " + std::to_wstring( limit );
	return *this;
}
//=====================================================================================================================
void Query::Where( const std::wstring& whereTable )
{
	if( 0 == whereTable.size() )
	{
		assert( !"Invalid input data" );
		throw Exception( "Invalid input data" );
	}

	where_.push_back( whereTable );
}
//=====================================================================================================================
Query::Query( const TablePtr& table ) 
	: fieldDeclarationTable_( table->GetFieldDeclarationTablePtr() ), tableName_( table->GetName() )
{
	assert( table && "Invalid input data." );
}
//=====================================================================================================================
Query::Query( const Table& table ) 
	: fieldDeclarationTable_( table.GetFieldDeclarationTablePtr() ), tableName_( table.GetName() )
{
}
//=====================================================================================================================
Query::~Query() throw() 
{	
}
//=====================================================================================================================
}