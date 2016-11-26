/// @file 
/// @brief Файл содержит описание классов для работы со значениями полей таблицы БД

#pragma once

///Работа с Базаой Данных
namespace sqlite
{
/// @brief Осуществляет работу с полем таблицы базы данных
class ValueTable
{
	friend std::wostream& operator<<( std::wostream& stream, const sqlite::ValueTable& valueTable );
public:
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit ValueTable( const TablePtr& table  ); 
	/// @brief Конструктор
	///
	/// @param[in] fieldDeclarationTable Описание полей таблицы
	explicit ValueTable( const FieldDeclarationTablePtr& fieldDeclarationTable  ); 
	/// @brief Деструктор
	///
	virtual ~ValueTable();
public:
	/// @brief Возвращает описание полей таблицы
	///
	const FieldDeclarationTable& GetFieldDeclarationTable( void ) const;
private:
	/// @brief Возвращает и проверяет переменную из поля по его имени и типу
	///
	/// @param[in] name имя переменной поля
	/// @param[in] type тип поля
	/// @return Возваращает переменную
	ValuePtr GetAndCheckValue( const std::wstring& name, const sqlite::enums::FieldType type ) const;
protected:
	/// @brief Возвращает переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает переменную
	ValuePtr GetValue( const std::wstring& name ) const;
	/// @brief Возвращает переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает переменную
	ValuePtr operator[]( const std::wstring& name ) const;
public:
	/// @brief Возвращает типизированную переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает строковое значение
	types::ValueStringPtr GetStringValue( const std::wstring& name ) const;
	/// @brief Возвращает типизированную переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает целое чило
	types::ValueIntegerPtr GetIntegerValue( const std::wstring& name ) const;
	/// @brief Возвращает типизированную переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает число с плавующей точкой
	types::ValueFloatPtr GetFloatValue( const std::wstring& name ) const;
	/// @brief Возвращает типизированную переменную из поля по его имени
	///
	/// @param[in] name имя переменной поля
	/// @return Возваращает BLOB
	types::ValueBlobPtr GetBlobValue( const std::wstring& name ) const;
private:
	///< Список значений поля таблицы
	ValueList valueList_;
	///< Описание полей таблицы
	const FieldDeclarationTablePtr fieldDeclarationTable_;
};
/// @brief Потоковый вывод для полей таблицы
///
/// @param[in] stream поток
/// @param[in] valueTable занчение полей таблицы
/// @return Возвращает поток
std::wostream& operator<<( std::wostream& stream, const ValueTable& valueTable );
}
