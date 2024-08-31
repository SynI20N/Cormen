#ifdef WIN
#ifdef LDS_EXPORTS
#define DSAPI __declspec(dllexport)
#else
#define DSAPI __declspec(dllimport)
#endif
#else
#ifdef LDS_EXPORTS
#define DSAPI
#else
#define DSAPI
#endif
#endif

#ifdef WIN
#define DSCALL __cdecl
#else
#define DSCALL
#endif

//QUEUE
typedef struct
{
  int64_array arr;
  int64_t tail;
  int64_t head;
} int64_queue;

// LINKED LIST
struct list_node;

typedef struct
{
  struct list_node *head;
} int64_linked_list;

struct list_node
{
  struct list_node *next;
  struct list_node *prev;
  int64_t key;
};

typedef struct list_node list_node;

// HASH TABLE

typedef struct
{
  int64_t key;
  char *word;
} int64_keyed_word;

typedef struct
{
  int64_linked_list *table;
  uint64_t size;
} int64_hash_table;

// BST
struct tree_node;

typedef struct
{
  struct tree_node *head;
} int64_binary_tree;

struct tree_node
{
  struct tree_node *p;
  struct tree_node *left;
  struct tree_node *right;
  int64_t key;
};

typedef struct tree_node tree_node;

// QUEUE
DSAPI int64_queue *create_queue(uint64_t count);
DSAPI int16_t enqueue(int64_queue *Q, int64_t x);
DSAPI int64_t dequeue(int64_queue *Q);
// LINKED LIST
DSAPI int64_linked_list *create_linked_list();
DSAPI list_node *list_search(int64_linked_list *L, int64_t k);
DSAPI void list_insert(int64_linked_list *L, int64_t k);
DSAPI void list_delete(int64_linked_list *L, list_node *x);
DSAPI void list_delete_key(int64_linked_list *L, int64_t k);
DSAPI void list_print(int64_linked_list *L);
DSAPI void reverse_list(int64_linked_list *L);
// HASH TABLE
DSAPI int64_hash_table *create_hash_table(uint64_t size);
// DSAPI void hash_insert(int64_hash_table* T, )
// BINARY SEARCH TREE