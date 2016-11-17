/// @file 
/// @brief Файл используется для осуществления предварительной сборки заголовков

#include <database/include/precompiled.h>

/// @mainpage The module for work with the Database
///
/// Модуль предоставляет С++ интерфейс для работы с объектами Базы Данных( далее БД )
/// Для подключения работы модуля необходимо добавить заголовочный файл: <database/database.h>
///
///
/// @code
///
///	//Пример использования модуля:
///
///	try
///	{
///			// путь к БД
///			const boost::filesystem::path& pathDb = boost::filesystem::temp_directory_path() / L"example.db";
///
///			//Открываем базу данных
///			auto database = std::make_shared<sqlite::Database>( pathDb, false );
///
///			//Описание полей таблицы
///			sqlite::FieldDeclarationTable fieldDeclarationTable;
///			//Добавляем поле id и выставляем как основной ключ таблицы
///			fieldDeclarationTable.AddField( L"id", sqlite::enums::FieldType::Integer, true );
///			//Добавляем строковое поле в таблицу
///			fieldDeclarationTable.AddField( L"value", sqlite::enums::FieldType::Text );
///
///			//Формируем таблицу на основе описания
///			auto table = std::make_shared<sqlite::Table>( L"testTable", fieldDeclarationTable );
///
///			//Открываем транзакцию
///			sqlite::Transaction transaction( database );
///
///			//Удаление таблицы
///			table->Drop( transaction );
///			//Создание таблицы
///			table->Create( transaction );
///
///
///			//Запись данных в таблицу (подготовка данных)
///			sqlite::ValueTable valueTable( table ); 
///			//Выставка значения для поля id
///			valueTable.GetIntegerValue( L"id" )->SetNull();
///			//Выставка значения для поля value
///			valueTable.GetStringValue( L"value" )->Set( L"data" );
///
///			//Запись данных в таблицу  (подготовка данных)
///			sqlite::ValueTable valueTable2( table );
///			//Выставка значения для поля id
///			valueTable2.GetIntegerValue( L"id" )->SetNull();
///			//Выставка значения для поля value
///			valueTable2.GetStringValue( L"value" )->Set( L"data2" );
///
///			//Вставка одной записи в теблицу
///			table->Insert( transaction, valueTable );
///
///			//Вставка группы записей
///			sqlite::InsertValue insertValue( table );
///			insertValue.Add( valueTable );
///			insertValue.Add( valueTable2 );
///			//Заносим группу в таблицу
///			insertValue.Exec( transaction );
///			//Закрываем транзакцию
///			transaction.Commit();
///
///
///						
///			//Получаем запрос для выборки по таблице и задаем параметры для выборки
///			auto query = table->GetQueryWhereRecordSet();	
///			//query.Where( L"id", L"" );
///
///			//Открываем транзакцию
///			sqlite::Transaction transaction2( database );
///			
///			//Выполняем запрос к таблице БД
///			auto stmt = query( transaction2 );
///				
///			//Закрываем транзакцию
///			transaction2.Commit();
///
///			//Обрабатываем данные из выборки
///			while( const auto value = stmt->Step() )
///			{
///				//Получаем данные для поля id
///				auto id = value->GetIntegerValue( L"id" )->Get();
///				//Получаем данные для поля value
///				auto data = value->GetStringValue( L"value" )->Get();
///				//Выводим на экран
///				std::cout << "id: " << id << " value: " << culture::w2utf8( data ) << std::endl;
///			}			
///	}
///	catch (const std::exception& exp )
///	{
///		assert(!"Exception's detect.");
///		std::cout << "exception: " << exp.what() << std::endl;
///	}
/// @endcode
///
/// @see sqlite::Database, sqlite::FieldDeclarationTable, sqlite::Table, sqlite::ValueTable, sqlite::Query, sqlite::Stmt.
