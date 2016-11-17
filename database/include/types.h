/// @file 
/// @brief Файл содержит описание типов модуля database

#pragma once

namespace sqlite
{

class Database;
/// Указатель на подключение к БД
typedef std::shared_ptr<Database> DatabasePtr;

class TransactionImp;
/// Указатель на реализацию транзакции
typedef std::shared_ptr<TransactionImp> TransactionImpPtr;

class Field;
/// Указатель на поле
typedef std::shared_ptr<Field> FieldPtr;

class FieldDeclarationTable;
/// Указатель на описание полей таблицы
typedef std::shared_ptr<FieldDeclarationTable> FieldDeclarationTablePtr;

/// Cписок описания поля
typedef std::vector<const FieldPtr> FieldList;
/// Список строк
typedef std::vector<std::wstring> StringList;

class Value;
/// Указатель на переменную
typedef std::shared_ptr<Value> ValuePtr;

class ValueTable;
/// Указатель на переменную таблицы
typedef std::shared_ptr<ValueTable> ValueTablePtr;
/// /// Описание списка переменных
typedef std::vector<ValueTable> ValueTableList;
/// Описание списка переменных соотвествием имени поля
typedef std::map<std::wstring, ValuePtr > ValueList;

class Table;
/// Указатель на таблицу базы данных
typedef std::shared_ptr<Table> TablePtr;

class Stmt;
/// Указатель на перебор данных
typedef std::shared_ptr<Stmt> StmtPtr;

template< typename TypeObject> class ValueType;

///Типы данных базы данных
namespace types
{
///Описание строки БД
typedef std::wstring				SQLITE_TYPE_STRING;
///Описание целового числа БД
typedef sqlite_int64				SQLITE_TYPE_INTEGER;
///Описание числа с плавующей точкой БД
typedef double						SQLITE_TYPE_FLOAT;
///Описание BLOB БД
typedef std::vector<unsigned char>	SQLITE_TYPE_BLOB;

/// Указатель на строку БД
typedef std::shared_ptr<ValueType<SQLITE_TYPE_STRING>> ValueStringPtr;
/// Указатель на целое число БД
typedef std::shared_ptr<ValueType<SQLITE_TYPE_INTEGER>> ValueIntegerPtr;
/// Указатель на число с плавующей точкой БД
typedef std::shared_ptr<ValueType<SQLITE_TYPE_FLOAT>> ValueFloatPtr;
/// Указатель на BLOB БД
typedef std::shared_ptr<ValueType<SQLITE_TYPE_BLOB>> ValueBlobPtr;
}

}
