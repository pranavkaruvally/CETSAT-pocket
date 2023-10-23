#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct deque {
  bool *queue;
  int16_t size;
  int16_t front;
  int16_t rear;

  void (*insert_front)(struct deque*, int);
  void (*insert_rear)(struct deque*, int);
  void (*delete_front)(struct deque*);
  void (*delete_rear)(struct deque*);
  bool (*is_full)(struct deque*);
  bool (*is_empty)(struct deque*);
  bool (*get_front)(struct deque*);
  bool (*get_rear)(struct deque*);
};

void insert_front(struct deque*, int);
void insert_rear(struct deque*, int);
void delete_front(struct deque*);
void delete_rear(struct deque*);
bool is_full(struct deque*);
bool is_empty(struct deque*);
bool get_front(struct deque*);
bool get_rear(struct deque*);

struct deque* initialize_deque(int n) {
  struct deque *dq = malloc(sizeof(struct deque));
  dq->queue = malloc(n*sizeof(bool));
  dq->size = n;
  dq->front = dq->rear = -1;
  dq->insert_front = insert_front;
  dq->insert_rear = insert_rear;
  dq->delete_front = delete_front;
  dq->delete_rear = delete_rear;
  dq->is_full = is_full;
  dq->is_empty = is_empty;
  dq->get_front = get_front;
  dq->get_rear = get_rear;

  return dq;
}

void free_deque(struct deque* dq) {
  free(dq->queue);
  dq->queue = NULL;
  free(dq);
}

bool is_full(struct deque* dq) {
  return ((dq->front == 0 && dq->rear == dq->size - 1)
              || dq->front == dq->rear + 1);
}

bool is_empty(struct deque* dq) { return dq->front == -1; }

void insert_front(struct deque* dq, int key) {
  if (dq->is_full(dq)) {
    return;
  }

  if (dq->front == -1) {
    dq->front = 0;
    dq->rear = 0;
  } else if (dq->front == 0) {
    dq->front = dq->size - 1;
  } else {
    dq->front--;
  }
  dq->queue[dq->front] = key;
}

void insert_rear(struct deque* dq, int key) {
  if (dq->is_full(dq)) {
    return;
  }
  if (dq->front == -1) {
    dq->front = 0;
    dq->rear = 0;
  } else if (dq->rear == dq->size - 1) {
    dq->rear = 0;
  } else {
    dq->rear++;
  }

  dq->queue[dq->rear] = key;
}

void delete_front(struct deque* dq) {
  if (dq->is_empty(dq)) {
    return;
  }

  if (dq->front == dq->rear) {
    dq->front = -1;
    dq->rear = -1;
  }
  else
      if (dq->front == dq->size - 1)
      dq->front = 0;
 
  else 
      dq->front++;
}

void delete_rear(struct deque* dq) {
  if (dq->is_empty(dq)) {
      return;
  }
  
  if (dq->front == dq->rear) {
      dq->front = -1;
      dq->rear = -1;
  }
  else if (dq->rear == 0)
      dq->rear = dq->size - 1;
  else
      dq->rear = dq->rear - 1;
}

bool get_front(struct deque* dq) {
  return dq->queue[dq->front];
}

bool get_rear(struct deque* dq) {
  return dq->queue[dq->rear];
}
