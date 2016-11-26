/// @file 
/// @brief Файл содержит реализацию классов для осуществления получения данных из выборки.

#include <database/include/precompiled.h>

namespace sqlite
{

//=====================================================================================================================
sqlite3_stmt* Stmt::Get( void ) const throw()
{
	assert( stmt_ && "Invalid create query base." );
	return stmt_;
}
//=====================================================================================================================
sqlite3* Stmt::GetSqlite( void ) const
{
	assert( dataBase_ && "Invalid connect data base." );
	return dataBase_->GetSqlite();
}
//=====================================================================================================================
sqlite::DatabasePtr Stmt::GetDataBase( void ) const
{
	return dataBase_;
}
//=====================================================================================================================
sqlite::ValueTablePtr Stmt::Step( void )
{
	//Возвращаем результат смещение по выборке
	const auto returnStep = sqlite3_step( stmt_ );
	switch( returnStep )
	{
	case SQLITE_ROW:
		break;
	case SQLITE_DONE:
		return sqlite::ValueTablePtr();
	default:
		throw sqlite::Exception( dataBase_->GetErrMessage() );
	}

	//Формируем переменную
	auto valueTable = std::make_shared<sqlite::ValueTable>( fieldDeclarationTable_ );
	assert( valueTable && "Invalid create object.");

	//Получаем количество столбцов и перебираем их
	const auto  count = sqlite3_column_count(stmt_);
	for( int index = 0; index < count; ++index )
	{
		//Получаем имя столбца для заданного номера
		const auto& nameColumn = culture::utf2w( sqlite3_column_name( stmt_, index ) );
		const auto typeColumn = sqlite3_column_type(stmt_, index);
		if (SQLITE_NULL == typeColumn){
			//Получаем переменную
			auto value = valueTable->GetBlobValue(nameColumn);
			if (!value){
				throw sqlite::Exception("Invalid get column name.");
			}

			value->SetNull();
			continue;
		}

		//получаем тип столбца БД
		const auto field = fieldDeclarationTable_->operator()(nameColumn);
		if (!field){
			throw sqlite::Exception("Invalid column name.");
		}

		switch (field->GetFieldType())
		{
		case sqlite::enums::FieldType::Integer:
			{
				//Получаем переменную
				auto value = valueTable->GetIntegerValue( nameColumn );
				if( !value ){
					throw sqlite::Exception("Invalid get column name.");
				}
				//Задаем значение
				value->Set( sqlite3_column_int64( stmt_, index) );
				break;
			}
		case sqlite::enums::FieldType::Float:
			{
				//Получаем переменную
				auto value = valueTable->GetFloatValue( nameColumn );
				if( !value ){
					throw sqlite::Exception("Invalid get column name.");
				}
				//Задаем значение
				value->Set( sqlite3_column_double( stmt_, index) );
				break;
			}
		case sqlite::enums::FieldType::Text:
			{
				//Получаем переменную
				auto value = valueTable->GetStringValue( nameColumn );
				if( !value ){
					throw sqlite::Exception("Invalid get column name.");
				}
				//Задаем значение
				value->Set( culture::utf2w( reinterpret_cast<const char*>( sqlite3_column_text( stmt_, index) ) ) );
				break;
			}
		case sqlite::enums::FieldType::BLob:
			{
				//Получаем переменную
				auto value = valueTable->GetBlobValue( nameColumn );
				if( !value ){
					throw sqlite::Exception("Invalid get column name.");
				}
				
				const auto size = sqlite3_column_bytes(stmt_, index);
				const auto buffer = sqlite3_column_blob(stmt_, index);
				if( size > 0 && nullptr != buffer )
				{
					types::SQLITE_TYPE_BLOB blob( size, 0 );
					memcpy( &blob[0], buffer, size );

					//Задаем значение
					value->Set( blob );
				}
				break;
			}
		default:
			assert( !"Invalid input type data." );
			throw sqlite::Exception("Invalid input type data.");
		}
	}
		
	return valueTable; 
}
//=====================================================================================================================
Stmt::Stmt( const Transaction& transaktion, const FieldDeclarationTablePtr& fieldDeclarationTable, const std::wstring& query ) 
	: dataBase_( transaktion.GetDataBase() ), fieldDeclarationTable_(fieldDeclarationTable), stmt_( nullptr )
{
	assert( fieldDeclarationTable && "Invalid input data" );
	assert( transaktion.GetDataBase() && "Invalid input data" );

	//Формируем запрос
	const auto string = culture::w2utf8(query);
	const auto ret = sqlite3_prepare_v2(transaktion.GetDataBase()->GetSqlite(), string.c_str(), static_cast<int>(string.length()), &stmt_, nullptr);
    if( SQLITE_OK != ret ){
        throw sqlite::Exception( transaktion.GetDataBase()->GetErrMessage() );
    }
}
//=====================================================================================================================
Stmt::~Stmt() throw()
{
	if( stmt_ != nullptr )
	{
		//Удаляем запрос
		const auto ret = sqlite3_finalize( stmt_ );
    	assert( SQLITE_OK == ret && sqlite3_errmsg(dataBase_->GetSqlite() ));
	}
}
//=====================================================================================================================
} 
