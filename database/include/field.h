/// @file 
/// @brief Файл содержит объявление классов для формирования описания полей таблицы.

#pragma once

namespace sqlite
{
/// Перечисления используемые модулем database
namespace enums
{
/// @brief Типы полей sqlite
///
enum class FieldType : int
{
	/// SQLITE_INTEGER
	Integer = 1,
	/// SQLITE_FLOAT
	Float = 2,
	/// SQLITE_TEXT
	Text = 3,
	/// SQLITE_BLOB
	BLob = 4,
};
}
/// @brief Осуществляет конвертирование типа в строку
///
class FieldType
{
public:
	/// @brief Конструктор
	///
	/// @param[in] type тип поля sqlite
	FieldType( const enums::FieldType type );
	/// @brief Деструктор
	///
	~FieldType();
public:
	/// @brief Возвращает строку типа поля
	///
	const wchar_t* const ToString( void ) const;
	/// @brief Возвращает строку типа поля
	///
	operator const wchar_t* () const;
private:
	///< Хранит тип поля
	const enums::FieldType type_;
};

/// @brief Хранит описание поля в таблице
///
class Field
{
public:
	/// @brief Конструктор
	///
	/// @param[in] name имя поля
	/// @param[in] type тип поля
	/// @param[in] primaryKey является поле ключом
	Field( const std::wstring& name, const enums::FieldType type, const bool primaryKey = false );
	/// @brief Деструктор
	///
	~Field();
public:
	/// @brief Возвращает строку для добавления поля в таблицу
	///
	std::wstring operator ()() const;
	/// @brief Возврщает тип поля
	///
	enums::FieldType GetFieldType( void ) const;
	/// @brief Возвращает имя поля
	///
	std::wstring GetName(void ) const;
	/// @brief Возвращает признак поля
	///
	bool GetPrimaryKey(void) const;
private:
	///< Имя поля
	const std::wstring name_;
	///< Тип поля
	const enums::FieldType type_;
	///< признак поля является основным ключем
	const bool primaryKey_;
};

/// @brief Хранит описание полей зарегестрированные в таблице
///
class FieldDeclarationTable
{
public:
	/// @brief Конструктор
	///
	FieldDeclarationTable( void );
	/// @brief Деструктор
	///
	~FieldDeclarationTable();
public:
	/// @brief Добавляет запись в таблицу
	///
	/// @param[in] field запись в таблице
	/// @return Возвращает ссылку на себя
	FieldDeclarationTable& AddField( const sqlite::FieldPtr& field );
	/// @brief Добавляет запись в таблицу
	///
	/// @param[in] name имя поля
	/// @param[in] type тип поля
	/// @param[in] primaryKey является поле ключом
	/// @return Возвращает ссылку на себя
	FieldDeclarationTable& AddField( const std::wstring& name, const sqlite::enums::FieldType type, const bool primaryKey = false );
public:
	/// @brief Возвращает описание поля по его имени
	///
	/// @param[in] name имя поля
	const sqlite::FieldPtr operator()( const std::wstring& name ) const;
	/// @brief Возвращает список зарегестрированных полей
	///
	const sqlite::FieldList& operator()( void ) const;
	/// @brief Возвращает список имен зарегестрированных в таблице
	///
	StringList GetFieldNameList( void ) const;
private:
	///< Список полей
	sqlite::FieldList fieldList_;
};

/// @brief Потоковая запись строки
///
/// @param[in] stream поток
/// @param[in] fieldType объект на запись
std::wostream& operator<<( std::wostream& stream, const FieldType& fieldType );
/// @brief Потоковая запись строки
///
/// @param[in] stream поток
/// @param[in] field объект на запись
std::wostream& operator<<( std::wostream& stream, const Field& field );
/// @brief Потоковая запись строки
///
/// @param[in] stream поток
/// @param[in] fieldList объект на запись
std::wostream& operator<<( std::wostream& stream, const sqlite::FieldList& fieldList );

/// @brief Формирование строки из списка строк
///
/// @param[in] stringList список строк
std::wstring StrToStringList( const sqlite::StringList& stringList );
}
