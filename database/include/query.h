/// @file 
/// @brief Файл содержит объявление классов для формирования запроса.

#pragma once

namespace sqlite
{
namespace enums
{
/// Тип сортировки
typedef enum tagOrderByType
{
	/// ASC
	ASC,
	/// DESC
	DESC
}OrderByType;
}

/// @brief Класс осуществляет формирование запроса
///
class Query
{
	friend Table;
protected:
    /// @brief Конструктор
	///
	/// @param[in] table Указатель на описание таблицы
	explicit Query( const TablePtr& table );
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit Query( const Table& table );
public:
    /// @brief Деструктор
	///
    ~Query() throw();
public:
	/// @brief Формирование запроса к БД
	///
	/// @param[in] transaktion Транзакция в рамках которой идет обращение к БД
	StmtPtr operator()( const Transaction& transaktion ) const;
public:
	/// @brief Задает тип сортировки
	///
	/// @param[in] name имя параметра
	/// @param[in] type тип сортировки
	Query& OrderBy( const std::wstring& name, enums::OrderByType type = enums::ASC );
	/// @brief Ограничевает запрос количеством элементов ( LIMIT = N )
	///
	/// @param[in] limit Лимит в выборке
	Query& Limit( const unsigned int limit );
	/// @brief Позволяет задать произвольные условия
	///
	/// @param[in] whereTable запрос
	void Where( const std::wstring& whereTable );
private:
	///< Список условий
	std::vector<std::wstring> where_;
	///< сортировка
	std::wstring orderBy_;
	///< ограничение выборки
	std::wstring limit_;
private:
	///< Описание Таблицы
    const FieldDeclarationTablePtr fieldDeclarationTable_;
	///< Описание Таблицы
    const std::wstring tableName_;
};
}
