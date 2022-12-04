#include <HashTable.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*****************	Структуры	*********************/

typedef struct node
{
	struct node *	next;
	char *			key;
	void *			value;
}
node_t;

/**************	Статичные функции	*****************/

static	char *			Key					();
static	int				HashFunction		(char *, unsigned int);

/**************	Статичные переменные	*****************/

static	unsigned char	Rand8[256];

/**
 * Создать новую таблицу.
 * Вход		:	hash_table_t **		-	указатель на хеш таблицу
 * 				unsigned int		-	размер таблицы (макс. 65535)
 * Выход	:	void				-	отсутствует
*/
void HashTableCreate(hash_table_t ** hash_table_tag, unsigned int size)
{
	if (size > 65536)
	{
		return;
	}

	hash_table_t * 	table	= malloc(sizeof(hash_table_t));

	table->nodes	= calloc(size, sizeof(node_t *));
	table->size		= size;
	table->count	= 0;

	*hash_table_tag	= table;
}

/**
 * Вставить новую запись в хеш таблицу.
 * Вход		:	hash_table_t *		-	хеш таблица
 * 				char *				-	ключ записи
 * 				char *				-	значение записи
 * Выход	:	char *				-	ключ записи
*/
char * HashTableInsert(hash_table_t * hash_table, char * key, void * value)
{
	if (!hash_table)
	{
		return 0;
	}

	if (!key)
	{
		key = Key();
	}

	int			hash		= HashFunction(key, hash_table->size);
	node_t *	new_node	= malloc(sizeof(node_t));

	new_node->next	= hash_table->nodes[hash];
	new_node->key	= key;
	new_node->value	= value;

	hash_table->nodes[hash] = new_node;
	hash_table->count++;

	return key;
}

/**
 * Удалить запись в хеш таблице по ключу.
 * Вход		:	hash_table_t **		-	указатель на хеш таблицу
 * 				char *				-	ключ записи
 * Выход	:	void				-	отсутствует
*/
void HashTableDelete(hash_table_t ** hash_table_tag, char * key)
{
	if (!hash_table_tag || !key)
	{
		return;
	}

	hash_table_t *	table	= *hash_table_tag;
	int				bucket	= HashFunction(key, table->size);
	node_t *		temp	= 0;
	node_t * 		node	= table->nodes[bucket];

	while (node)
	{
		if (!strcmp(node->key, key))
		{
			break;
		}
		temp = node;
		node = node->next;
	}

	if (!node)
	{
		return;
	}

	if (temp)
	{
		temp->next = node->next;
	}
	else
	{
		table->nodes[bucket] = node->next;
	}

	free(node);
}

/**
 * Поиск записи в хеш таблице по ключу.
 * Вход		:	hash_table_t *		-	хеш таблица
 * 				char *				-	ключ записи
 * Выход	:	void *				-	значение записи
*/
void * HashTableFind(hash_table_t * hash_table, char * key)
{
	if (!hash_table || !key)
	{
		return 0;
	}
	
	node_t *	node	= hash_table->nodes[HashFunction(key, hash_table->size)];

	while (node)
	{
		if (!strcmp(node->key, key))
		{
			break;
		}
		node = node->next;
	}

	if (!node)
	{
		return 0;
	}

	return node->value;
}

/**
 * Генерация случайного кода.
 * Вход		:	void				-	отсутсвует
 * Выход	:	char *				-	случайный ключ
*/
static char * Key()
{
	int			size		= 16;
	const char	charset[]	= "abcdefghijklmnopqrstuvwxyz0123456789";
	char *		key			= malloc(size * sizeof(char));
	int			symbol		= 0;

	if (size)
	{
		for (int n = 0; n < size - 2; n++)
		{
			symbol = rand() % (int)(sizeof(charset) - 1);
			key[n] = charset[symbol];
		}
		key[size - 1] = '\0';
	}

	return key;
}

/**
 * Хеш функция.
 * Вход		:	char *				-	ключ
 * 				unsigned int		-	размерность хеш таблицы
 * Выход	:	int					-	идентификатор записи
*/
static int HashFunction(char * key, unsigned int size)
{
	if (!key)
	{
		return 0;
	}

	int				h	= 0;

	while (*key != '\0')
	{
		h += *key;
		key++;
	}

	return h % size;
}