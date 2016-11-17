/// @file 
/// @brief Файл содержит реализацию классов для работы со значениями полей таблицы БД

#include <database/include/precompiled.h>

namespace
{
/// Размер буфера для формирования строки BLOB
const size_t SIZE_BUFFER = 32;
}

namespace
{
//=====================================================================================================================
sqlite::ValuePtr GetDevaulData( const sqlite::FieldPtr& field )
{
	assert( field && "Invalid input data.");

	switch( field->GetFieldType() )
	{
	case sqlite::enums::FieldType::Integer:
		return std::make_shared<sqlite::ValueType<sqlite::types::SQLITE_TYPE_INTEGER>>( field );
	case sqlite::enums::FieldType::Float:
		return std::make_shared<sqlite::ValueType<sqlite::types::SQLITE_TYPE_FLOAT>>( field );
	case sqlite::enums::FieldType::Text:
		return std::make_shared<sqlite::ValueType<sqlite::types::SQLITE_TYPE_STRING>>( field );
	case sqlite::enums::FieldType::BLob:
		return std::make_shared<sqlite::ValueType<sqlite::types::SQLITE_TYPE_BLOB>>( field );
	}

	throw sqlite::Exception( "Don't declaration default data." );
}
//=====================================================================================================================
sqlite::ValueList GetDefaultValueList( const sqlite::FieldDeclarationTable& fieldDeclarationTable )
{
	auto fields = fieldDeclarationTable();

	sqlite::ValueList values;
	std::for_each
	( 
		std::begin( fields ), 
		std::end( fields ), 
		[&values]( const sqlite::FieldPtr& field )
		{ 
			values.insert( std::make_pair( field->GetName(),  GetDevaulData( field ) ) ).first->second;
		}
	);

	return values;
}
//=====================================================================================================================
}

namespace sqlite
{
//=====================================================================================================================
ValueTable::ValueTable( const TablePtr& table )
	: fieldDeclarationTable_( table->GetFieldDeclarationTablePtr() ), valueList_( GetDefaultValueList( table->GetFieldDeclarationTable() ) )
{
	assert( table && "Invalid input data" );
}

ValueTable::ValueTable( const FieldDeclarationTablePtr& fieldDeclarationTable  ) 
	: fieldDeclarationTable_( fieldDeclarationTable ), valueList_( GetDefaultValueList( *fieldDeclarationTable ) )
{
	assert( fieldDeclarationTable && "Invalid input data" );
}
//=====================================================================================================================
ValueTable::~ValueTable()
{
}
//=====================================================================================================================
const FieldDeclarationTable& ValueTable::GetFieldDeclarationTable( void ) const
{
	return *fieldDeclarationTable_;
}
//=====================================================================================================================
ValuePtr ValueTable::GetAndCheckValue( const std::wstring& name, const sqlite::enums::FieldType type ) const
{
	//Осуществляем поиск записи
	const auto& itr = valueList_.find( name );
	if( itr == valueList_.end() ){
		throw sqlite::Exception( "Don't declaration field." );
	}
	
	if( itr->second->Field()->GetFieldType() != type ){
		throw sqlite::Exception( "Incorrect setting of variable type." );
	}
	
	return itr->second;
}
//=====================================================================================================================
ValuePtr ValueTable::GetValue( const std::wstring& name ) const
{
	//Осуществляем поиск записи
	const auto& itr = valueList_.find( name );
	if( itr == valueList_.end() ){
		throw sqlite::Exception( "Don't declaration field." );
	}

	return itr->second;
}
//=====================================================================================================================
ValuePtr ValueTable::operator[]( const std::wstring& name ) const
{
	return GetValue( name );
}
//=====================================================================================================================
types::ValueStringPtr ValueTable::GetStringValue( const std::wstring& name ) const
{
	return std::static_pointer_cast<ValueType<types::SQLITE_TYPE_STRING>>( GetAndCheckValue( name, sqlite::enums::FieldType::Text ) );
}
//=====================================================================================================================
types::ValueIntegerPtr ValueTable::GetIntegerValue( const std::wstring& name ) const
{
	return std::static_pointer_cast<ValueType<types::SQLITE_TYPE_INTEGER>>( GetAndCheckValue( name, sqlite::enums::FieldType::Integer ) );
}
//=====================================================================================================================
types::ValueFloatPtr ValueTable::GetFloatValue( const std::wstring& name ) const
{
	return std::static_pointer_cast<ValueType<types::SQLITE_TYPE_FLOAT>>( GetAndCheckValue( name, sqlite::enums::FieldType::Float ) );
}
//=====================================================================================================================
types::ValueBlobPtr ValueTable::GetBlobValue( const std::wstring& name ) const
{
	return std::static_pointer_cast<ValueType<types::SQLITE_TYPE_BLOB>>( GetAndCheckValue( name, sqlite::enums::FieldType::BLob ) );
}
//=====================================================================================================================
std::wostream& operator<<( std::wostream& stream, const sqlite::ValuePtr& value )
{
	//Проверяем входные данные
	if(  !value || !value->Field() )
	{
		assert( !"Invalid's paramtr." );
		return stream;
	}

	//Проверяем на NULL
	if( value->IsNull() )
	{
		stream << L"NULL";
		return stream;
	}
	
	//Получаем данные
	switch( value->Field()->GetFieldType() )
	{
	case enums::FieldType::Integer:
		stream << std::static_pointer_cast<ValueType<types::SQLITE_TYPE_INTEGER>>( value )->Get();
		break;
	case enums::FieldType::Float:
		stream << std::static_pointer_cast<ValueType<types::SQLITE_TYPE_FLOAT>>( value )->Get();
		break;
	case enums::FieldType::Text:
		stream << std::static_pointer_cast<ValueType<types::SQLITE_TYPE_STRING>>( value )->Get();
		break;
	case enums::FieldType::BLob:
		{
			stream << "x'";
			//Перебираем BLOB
			const auto& valueType = std::static_pointer_cast<ValueType<types::SQLITE_TYPE_BLOB>>( value )->Get();
			std::for_each
				(
				std::begin( valueType ),
				std::end( valueType ),
				[&stream]( const unsigned char byte )
				{
					//Формируем результат
					std::vector<wchar_t> data( SIZE_BUFFER, 0 );
					swprintf_s( &data[0], data.size(), L"%02X", byte );
					
					//Отправляем в поток
					stream << &data[0];
				}
			);
			stream << "'";
			break;
		}
	default:
		throw sqlite::Exception( "Invalid type paramtr.");
	}

	return stream;
}
//=====================================================================================================================
std::wostream& operator<<( std::wostream& stream, const sqlite::ValueTable& valueTable )
{
	//флаг о первом вхождении
	auto bFirst = true;

	const auto& dfieldList = valueTable.GetFieldDeclarationTable()();
	std::for_each
	( 
		std::begin( dfieldList ), 
		std::end( dfieldList ), 
		[ &stream, &bFirst, valueTable ]( const sqlite::FieldPtr& field )
		{
			assert( field && "Invalid's data.");

			const auto& value = valueTable.GetValue( field->GetName() );
			assert( value && "Invalid input data");

			stream << ( bFirst ? L"" : L", " );

			if( value->IsNull() )
			{
				stream << value;
			}
			else if (enums::FieldType::BLob == field->GetFieldType())
			{
				stream << value;
			}
			else
			{
				stream << L"\"" << value << L"\"";
			}

			bFirst = false;
		} 
	);
	
	return stream;
}
//=====================================================================================================================
}
