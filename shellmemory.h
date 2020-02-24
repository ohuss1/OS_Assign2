/*
 * shellmemory.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Omar Yunus
 */

#ifndef SHELLMEMORY_H_
#define SHELLMEMORY_H_
int shell_memory_set(const char *key, const char *value);
const char *shell_memory_get(const char *key);

void shell_memory_initialize();
void shell_memory_destory();
#endif /* SHELLMEMORY_H_ */
