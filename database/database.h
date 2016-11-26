/// @file 
/// @brief Файл содержит список хедаров для публикации модуля database

#pragma once

//SQLITE
#include <sqlite/include/sqlite3.h>
//BOOST
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <boost/any.hpp>
//STL
#include <map>
#include <string>
#include <codecvt>
#include <sstream>
#include <stdexcept>
#include <functional>
//DataBase
#include <database/include/firststring.h>
#include <database/include/types.h>
#include <database/include/culture.h>
#include <database/include/exception.h>
#include <database/include/field.h>
#include <database/include/opendatabase.h>
#include <database/include/transaction.h>
#include <database/include/value.h>
#include <database/include/valuetable.h>
#include <database/include/insertvalue.h>
#include <database/include/deletevalue.h>
#include <database/include/statement.h>
#include <database/include/query.h>
#include <database/include/table.h>

#pragma comment(lib, "sqlite.lib")
#pragma comment(lib, "database.lib")
