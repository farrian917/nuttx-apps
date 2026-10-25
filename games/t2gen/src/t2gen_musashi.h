#pragma once
#include <stddef.h>
#include <stdint.h>
void t2gen_musashi_probe(const uint8_t *rom, size_t len, const char *fbdev);

void t2gen_musashi_set_gameplay(int enabled);
