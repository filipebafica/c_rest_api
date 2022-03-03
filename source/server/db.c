#include "server.h"

static int	call_back(void *list, int argc, char **argv, char **col_name)
{
	t_query	*query;
	t_node	*head;
	t_node	*tail;
	t_node	*new_node;

	query = (t_query *)list;
	head = query->head;
	tail = query->head;
	new_node = malloc(sizeof(t_node));
	new_node->id = ft_strdup(argv[0]);
	new_node->book_title = ft_strdup(argv[1]);
	new_node->author = ft_strdup(argv[2]);
	new_node->next = NULL;
	if (!query->count)
	{
		new_node->previous = NULL;
		head = new_node;
		query->head = head;
		query->count += 1;
		return (0);
	}
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_node;
	new_node->previous = tail;
	query->count += 1;
	return (0);
}

void	query_an_item(t_query *query, char *id)
{
	sqlite3		*db;
	int			con;
	char		*sql;
	char		*errmsg = 0;

	/* Open database */
	con = sqlite3_open("db.db", &db);
	/* Create SQL statement */
	sql = ft_strjoin("SELECT * from BOOKS WHERE ID = ", id);
	/* Execute SQL statement */
	con = sqlite3_exec(db, sql, call_back, (void *)query, &errmsg);
	sqlite3_close(db);
	free(sql);
}

void	query_all(t_query *query)
{
	sqlite3		*db;
	int			con;
	char		*sql;
	char		*errmsg = 0;

	/* Open database */
	con = sqlite3_open("db.db", &db);
	/* Create SQL statement */
	sql = "SELECT * from BOOKS";
	/* Execute SQL statement */
	con = sqlite3_exec(db, sql, call_back, (void *)query, &errmsg);
	sqlite3_close(db);
}

void	create_db(void)
{
	sqlite3	*db;
	int		con;
	char	*sql;
	char	*errmsg = 0;

	/* Open database */
	con = sqlite3_open("db.db", &db);
	/* Create SQL statement */
	sql = "CREATE TABLE BOOKS(" \
		"ID INT PRIMARY	KEY		NOT NULL," \
		"BOOK_TITLE		TEXT	NOT NULL," \
		"AUTHOR			TEXT	NOT NULL);";
	/* Execute SQL statement */
	con = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	/* Create SQL statement */
	sql = "INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (1, 'The Da Vinci Code', 'Dan Brown');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (2, 'Sapiens - A Brief History of Humankind', 'Yuval Noah Harari');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (3, 'Harry Potter and the Philosopher''s Stone', 'J.K. Rowling');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (4, 'Foundation', 'Isaac Asimov');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (5, 'The Lord of the Rings', 'J.R.R. Tolkien');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (6, 'Dark Matter', 'Blake Crouch');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (7, 'What Does This Button Do?', 'Bruce Dickinson');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (8, 'The Code Breaker', 'Walter Isaacson');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (9, 'Contact', 'Carl Sagan');" \
		"INSERT INTO BOOKS (ID, BOOK_TITLE, AUTHOR)" \
		"VALUES (42, 'The Hitchhiker''s Guide to the Galaxy', 'Douglas Adams');";
	/* Execute SQL statement */
	con = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	sqlite3_close(db);
}
