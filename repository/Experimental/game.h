#if !defined(GAME_H_INCLUDED)
#define GAME_H_INCLUDED

/* Relinquish an ID. */
int ids_relinquish_id(struct ids_t* self, struct id_t* id);

/* Acquire an ID. */
int ids_acquire_id(struct id_t** result, struct ids_t* self);

/* Acquire the ID module. Acquire a reference to the ID module. */
int ids_acquire(struct ids_t** result);

/* Acquire a reference to the ID module. */
int ids_ref(struct ids_t* self);

/* Destroy an ID module. */
void ids_relinquish(struct ids_t* self);

#endif // GAME_H_INCLUDED
