#ifndef HASH_TABLE_H
#define HASH_TABLE_H

	/*****************	Структуры	*********************/

	typedef struct hash_table
	{
		struct node **	nodes;
		unsigned int	size;
		unsigned int	count;
	}
	hash_table_t;

	/*****************	Публичные функции	*************/

	/**
	 * Создать новую таблицу.
	 * Вход		:	hash_table_t **		-	указатель на хеш таблицу
	 * 				unsigned int		-	размер таблицы (макс. 65535)
	 * Выход	:	void				-	отсутствует
	*/
	void		HashTableCreate			(hash_table_t **, unsigned int);
	/**
	 * Вставить новую запись в хеш таблицу.
	 * Вход		:	hash_table_t *		-	хеш таблица
	 * 				char *				-	ключ записи
	 * 				char *				-	значение записи
	 * Выход	:	char *				-	ключ записи
	*/
	char *		HashTableInsert			(hash_table_t *, char *, void *);
	/**
	 * Удалить запись в хеш таблице по ключу.
	 * Вход		:	hash_table_t **		-	указатель на хеш таблицу
	 * 				char *				-	ключ записи
	 * Выход	:	void				-	отсутствует
	*/
	void		HashTableDelete			(hash_table_t **, char *);
	/**
	 * Поиск записи в хеш таблице по ключу.
	 * Вход		:	hash_table_t *		-	хеш таблица
	 * 				char *				-	ключ записи
	 * Выход	:	void *				-	значение записи
	*/
	void *		HashTableFind			(hash_table_t *, char *);

#endif