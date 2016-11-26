/// @file 
/// @brief Файл содержит описание классов для храенения и предоставления доступа к данных БД

#pragma once

namespace sqlite
{
/// @brief Класс осуществляет представление переменной/значения поля таблицы БД
///
class Value 
{
protected:
	/// @brief Конструктор
	///
	/// @param[in] data значение
	/// @param[in] field описание поля в БД
	Value( const boost::any& data, const sqlite::FieldPtr& field );
public:
	/// @brief Деструктор
	///
	virtual ~Value();
protected:
	/// @brief Возвращает переменную
	///
	const boost::any& Get( void ) const throw();
	/// @brief Задает переменную
	///
	void Set( const boost::any& data ) throw();
public:
	/// @brief Задает nil для поля
	///
	void SetNull( void ) throw();
	/// @brief Проверяет евыствлен ли nil
	///
	bool IsNull( void ) const throw();
public:
	/// @brief Возвращает описание поля 
	///
	const sqlite::FieldPtr& Field( void ) const throw();
private:
	///< переменная
	boost::any data_;
	///< описание поля в БД
	const sqlite::FieldPtr field_;
	///< Выставлен ли nil
	bool isNull_;
};

/// @brief Реализация шаблона для типизации работы с переменной/значения поля таблицы БД
template< typename TypeObject>
class ValueType : public Value
{
public:
	/// @brief Конструктор
	///
	/// @param[in] field описание поля в БД
	explicit ValueType( const sqlite::FieldPtr& field ) : Value( TypeObject(), field )
	{
	}
	/// @brief Конструктор
	///
	/// @param[in] data значение
	/// @param[in] field описание поля в БД
	ValueType( const TypeObject& data, const sqlite::FieldPtr& field )  :  Value( data, field )
	{
	}
	/// @brief Деструктор
	///
	~ValueType()
	{
	}
public:
	/// @brief Возвращает переменную
	///
	TypeObject Get( void ) const
	{
		return boost::any_cast<TypeObject>( Value::Get() );
	}
	/// @brief Возвращает переменную
	///
	TypeObject operator()() const
	{
		return Get( void );
	}
	/// @brief Задает значение в переменную
	void Set( const TypeObject& data )
	{
		Value::Set( data );
	}
};
}
